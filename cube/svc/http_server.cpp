#include "cube\log\log.h"
#include "cube\svc\http_server.h"

BEGIN_CUBE_SVC_NS
//////////////////////////////////////http session class///////////////////////////////////////
int http_session::on_open(void *arg) {
	cube::log::info("[http][%s] open session", name().c_str());
	//save servlets
	_applet = (http::applet*)arg;

	//receive data from client
	std::string errmsg("");
	int err = recv(BUFSZ, &errmsg);
	if (err != 0) {
		cube::log::error("[http][%s]%s", name().c_str(), errmsg.c_str());
		return -1;
	}

	return 0;
}

int http_session::on_send(int transfered) {
	cube::log::info("[http][%s] send data: %d bytes", name().c_str(), transfered);
	//send response content
	char buf[BUFSZ] = { 0 };
	int sz = _resp.take(buf, BUFSZ);
	if (sz > 0) {
		//send left response data
		return send(buf, sz);
	}

	//all response data has sent, close session
	return -1;
}

int http_session::on_recv(char *data, int transfered) {
	cube::log::info("[http][%s] recv data: %d bytes", name().c_str(), transfered);
	try {
		//feed data to request
		_req.feed(data, transfered);

		//request data has completed
		if (_req.done()) {
			//process request
			_applet->handle(_req.request(), _resp.response());

			//send response content
			char buf[BUFSZ] = { 0 };
			int sz = _resp.take(buf, BUFSZ);
			if (sz > 0) {
				//send response data
				return send(buf, sz);
			}

			//no data
			return -1;
		}

		//wait for more data
		return 0;
	} catch (std::exception &e) {
		cube::log::error("[http][%s] recv data: %s", name().c_str(), e.what());
		return -1;
	}
}

void http_session::on_close() {
	cube::log::info("[http][%s] close session", name().c_str());
}

//////////////////////////////////////http server class///////////////////////////////////////
int http_server::start(ushort port, int workers, http::applet *applet) {
	return _server.start(port, workers, applet);
}

void http_server::stop() {
	_server.stop();
}
END_CUBE_SVC_NS
