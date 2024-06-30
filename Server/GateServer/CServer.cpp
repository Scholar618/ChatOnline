#include "CServer.h"
#include "HttpConnection.h"
CServer::CServer(boost::asio::io_context& ioc, unsigned short& port) 
	: _ioc(ioc), _acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _socket(ioc)
{
	
}

void CServer::Start() {
	auto self = shared_from_this(); // 智能指针
	_acceptor.async_accept(_socket, [self](beast::error_code ec) { // 接收器 
		try
		{
			// 出错放弃socket连接，继续监听其他连接
			if (ec) {
				self->Start();
				return;
			}
			// 创建新连接，并创建HttpConnection类管理这个连接
			std::make_shared<HttpConnection>(std::move(self->_socket))->Start();
			// HttpConnection(std::move(_socket));

			// 继续监听
			self->Start();
		}
		catch (const std::exception& exp)
		{

		}
		}
	);
}