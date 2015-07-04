#ifndef SERVER_H
#define SERVER_H
/////////////////////////////////////////////////////////////////////////////
// Server.h - Initializes sender and receiver for server                   //
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
*  This package uses Sender and Receiver class and initializes it which is used by server
*
*
*  Required Files:
*  ---------------
*  Server.h, Server.cpp, Sender.h, Sender.cpp, Receiver.h, Receiver.cpp
*  Sockets.h, Sockets.cpp, AppHelpers.h, AppHelpers.cpp
*
*  Build Command:
*  --------------
*  devenv TestProject3.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
*  ver 1.0 - 10 Apr 2015
*  - first release
*/

#include"../ApplicationHelpers/AppHelpers.h"
#include"../Message/Message.h"
#include"../Sender/Sender.h"
#include"../Receiver/Receiver.h"
#include"../Sockets/Sockets.h"
#include<iostream>
#include<string>

class Server
{
public:
	Server(size_t port):port_(port){}
	void InitializeServer();				// Initialize sender and receiver for server
private:
	size_t port_;

};

#endif