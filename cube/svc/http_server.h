#pragma once
#include "cube\type.h"
#include "cube\http\stream.h"
#include "cube\svc\tcp_server.h"
BEGIN_CUBE_SVC_NS
//http servlet class
class http_servlet {
public:
	http_servlet() {}
	virtual ~http_servlet() {}

	/*
	*	handle http request
	*@param req: in, client request
	*@param resp: in/out, service response
	*@return:
	*	void
	*/
	virtual void handle(const cube::http::request &req, cube::http::response &resp) = 0;
};

//http applet class
class http_applet {
public:
	http_applet() {}
	virtual ~http_applet() {}

	/*
	*	handle request, set response with process result
	*@param req: in, request object
	*@param resp: in/out, response object
	*@return:
	*	void
	*/
	void handle(const cube::http::request &req, cube::http::response &resp);

	/*
	*	mount path with relate servlet
	*@param path: in, servlet relate path
	*@param servlet: in, servlet for path
	*@return:
	*	void
	*/
	void mount(const std::string &method, const std::string &path, http_servlet *servlet);

private:
	//registered servlets, <method, <path, servlet>>
	std::map<std::string, std::map<std::string, std::shared_ptr<http_servlet>>> _servlets;
};

//http session class
class http_session : public net::session {
	//session send & recv buffer size
	static const int BUFSZ = 4096;
public:
	http_session() : _applet(0) {}
	virtual ~http_session() {}

	int on_open(void *arg);
	int on_send(int transfered);
	int on_recv(char *data, int transfered);
	void on_close();

private:
	//relate applet
	http_applet *_applet;

	//session request stream
	cube::http::rqstream _req;
	//session response stream
	cube::http::rpstream _resp;
};

//http server class
class http_server {
public:
	http_server() {}
	virtual ~http_server() {}

	/*
	*	start http server on specified port
	*@param port: in, local http service port
	*@param workers: in, workers for http session
	*@param servlets: in, servlets for processing request
	*@return:
	*	0 for success, otherwise <0
	*/
	int start(ushort port, int workers, http_applet *applet);

	/*
	*	stop http server
	*@return:
	*	void
	*/
	void stop();

private:
	//http server
	tcp_server<http_session> _server;
};
END_CUBE_SVC_NS
