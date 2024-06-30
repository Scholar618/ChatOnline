#pragma once
#include "const.h"

class CServer:public std::enable_shared_from_this<CServer>
{
public:
	CServer(boost::asio::io_context& ioc, unsigned short& port);
	void Start(); // 服务器启动
private:
	tcp::acceptor _acceptor; // 接收器接受对端连接
	net::io_context& _ioc;    // 上下文
	tcp::socket _socket;     // 复用socket

};

