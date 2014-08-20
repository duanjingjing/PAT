/*************************************************************************
	> File Name: TcpServer.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Thu 14 Aug 2014 08:31:46 AM PDT
 ************************************************************************/

#include "TcpServer.h"
#include "Socket.h"
#include "PollPoller.h"
#include <functional>
#include <signal.h>
using namespace std;

class IgnoreSigpipe{
public:
	IgnoreSigpipe(){
		if(::signal(SIGPIPE,SIG_IGN)==SIG_ERR){
			ERR_EXIT("sgianl");
		}
	}
};

IgnoreSigpipe initObj;

TcpServer::TcpServer(const InetAddress& addr){
}

