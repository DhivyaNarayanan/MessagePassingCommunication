#ifndef RECEIVER_H
#define RECEIVER_H

/////////////////////////////////////////////////////////////////////////////
// Receiver.h - Receive strings, blocks, and buffers  over socket          //
// Ver 1.0                                                                //
// Language:       Visual C++ 2013                                        //
// Application:    CSE687 - Project 3 (Message Passing Communivation),    //
//					Spring 2015	   										  //
// Platform:       HP G62, Windows 7 Home Premium, Visual Studio 2013     //
// Author:         Dhivya Narayanan, Master's- Computer Engineering,      //
//				   Syracuse University,                                   //
//                 dnnaraya@syr.edu                                       //
////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package uses Sockets and receive message over the socket
*  - receives string which includes header strings and buffer
*
*  Required Files:
*  ---------------
*  Receiver.h, Receiver.cpp, BlockingQueue.h, BlockingQueue.cpp
*  Sockets.h, Sockets.cpp, AppHelpers.h, AppHelpers.cpp
*
*  Build Command:
*  --------------
*  devenv TestProject3.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
*  ver 1.0  - 08 Apr 2015
*  - first release
*/

#include"../Message/Message.h"
#include"../Sockets/Sockets.h"
#include"../ApplicationHelpers/AppHelpers.h"
#include"../FileSystem/FileSystem.h"
#include"../BlockingQueue/BlockingQueue.h"
#include"../Display/Display.h"
#include<iostream>
#include<string>
#include <thread>
#include <mutex>

class Receiver
{
public:
	Receiver(size_t port) :sourcePort(port){}
	void Recv();
	std::string getsrcIP();
	size_t getsrcPort();
	std::string getdestIp();
	size_t getdestPort();
	
private:
	size_t destport;					
	std::string sourceIP;
	std::string destIP;
	size_t sourcePort;     // port no. of this receiver - equivalent to destPort in the message

};


class ClientHandler
{
public:
	ClientHandler(BlockingQueue<std::string>&q) :bq(q){}
	void operator()(Socket& socket_);
	bool RecvStringHandling(Socket& socket_);
	bool RecvAcknowledge(Socket& socket_);
	void recvStop(Socket&socket_); 
	std::string getdestIp();			//gets the sourceIp in the message
	size_t getdestPort();				//gets the sourceport in the message

private:
	BlockingQueue<std::string>&bq;
	size_t destport;					
	std::string sourceIP;
	std::string destIP;
	size_t sourcePort;   // port no. of this receiver - equivalent to destPort in the message
};

#endif