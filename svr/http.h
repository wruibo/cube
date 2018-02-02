#pragma once
#include "cube\svr\def.h"
#include "cube\svr\tcp.h"
#include "cube\http\rqstream.h"
#include "cube\http\rpstream.h"
BEGIN_CUBE_SVR_HTTP_NS
//http servlet class
class servlet {
public:
	servlet() {}
	virtual ~servlet() {}

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
class applet {
public:
	applet() {}
	virtual ~applet() {}

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
	void mount(const std::string &method, const std::string &path, servlet *servlet);

private:
	//registered servlets, <method, <path, servlet>>
	std::map<std::string, std::map<std::string, std::shared_ptr<servlet>>> _servlets;
};

//http session class
class session : public net::session {
	//session send & recv buffer size
	static const int BUFSZ = 4096;
public:
	session() : _applet(0) {}
	virtual ~session() {}

	int on_open(void *arg);
	int on_send(int transfered);
	int on_recv(char *data, int transfered);
	void on_close();

private:
	//relate applet
	applet *_applet;

	//session request stream
	cube::http::rqstream _req;
	//session response stream
	cube::http::rpstream _resp;
};

//http server class
class server {
public:
	server() {}
	virtual ~server() {}

	/*
	*	start http server on specified port
	*@param port: in, local http service port
	*@param workers: in, workers for http session
	*@param servlets: in, servlets for processing request
	*@return:
	*	0 for success, otherwise <0
	*/
	int start(ushort port, int workers, applet *applet);

	/*
	*	stop http server
	*@return:
	*	void
	*/
	void stop();

private:
	//http server
	tcp::server<session> _server;
};
END_CUBE_SVR_HTTP_NS
