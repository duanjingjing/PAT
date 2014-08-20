/*************************************************************************
	> File Name: TcpServer.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Thu 14 Aug 2014 08:27:09 AM PDT
 ************************************************************************/

#ifndef TCP_SERVER_H
#define TCP_SERVER_H


#include "NonCopyable.h"
#include "InetAddress.h"
#include "TcpConnection.h"
#include "Socket.h"
#include "PollPoller.h"
#include <memory>

class TcpServer:private NonCopyable{
public:
	typedef TcpConnection::TcpConnectionCallback TcpCallback;
	explicit TcpServer(const InetAddress &addr);

	void setConnection(const TcpCallback &cb){
		onConnect_=cb;
	}

	void setMessage(const TcpCallback& cb){
		onMessage_=cb;
	}

	void setClose(const TcpCallback& cb){
		onClose_=cb;
	}

	void start();
private:
	std::unique_ptr<Socket> sock_;
	std::unique_ptr<PollPoller> poller_;
};







#endif
