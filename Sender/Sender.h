#ifndef SENDER_H
#define SENDER_H

/////////////////////////////////////////////////////////////////////////////
// Sender.h - Send strings, blocks, and buffers  over socket               //
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
*  This package uses Sockets and send message over the socket
*  - pass string which includes header strings and buffer 
*
*  Required Files:
*  ---------------
*  Sender.h, Sender.cpp, BlockingQueue.h, BlockingQueue.cpp
*  Sockets.h, Sockets.cpp, AppHelpers.h, AppHelpers.cpp
*
*  Build Command:
*  --------------
*  devenv TestProject3.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
*  ver 1.0 - 08 Apr 2015
*  - first release
*/

#include"../Message/Message.h"
#include"../Sockets/Sockets.h"
#include"../ApplicationHelpers/AppHelpers.h"
#include"../BlockingQueue/BlockingQueue.h"
#include"../Display/Display.h"
#include<iostream>
#include<string>


class Sender
{
public:
	Sender(){}									// constructor
	void sendMsg(Socket& si,Message&msg);
	void Send(Message&msg);						// method to send the message
	void sendAck(std::string sourceIp, size_t sourcePort, std::string destIp, size_t destPort);  //method to send acknwledgement
	void SendStop(Socket&si);					//method to send stop message

};
#endif