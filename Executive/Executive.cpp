////////////////////////////////////////////////////////////////////////////
// Executive.cpp - The first package that gets called.                    //
//                  Oversees the control flow of the entire project       //
//                                                                        //
// ver 1.0                                                                //
// Language:       Visual C++ 2013                                        //
// Application:    CSE687 - Project 3 (Message Passing Communivation),    //
//					Spring 2015	   										  //
// Platform:       HP G62, Windows 7 Home Premium, Visual Studio 2013     //
// Author:         Dhivya Narayanan, Master's- Computer Engineering,      //
//				   Syracuse University,                                   //
//                 dnnaraya@syr.edu                                       //
////////////////////////////////////////////////////////////////////////////
/*
Package Operations:
===================
This package doesn't conatin any class.
This module is intended to oversee the program flow. This is the
entry point to the application. All the calls to the subsequent packages
will be routed from here.

Public Interfaces:
==================
None

Build Process:
==============

Required Files:
---------------
Executive.cpp, Display.cpp, Client.h, Client.cpp, Server.h, Server.cpp

Build Command:
--------------
devenv TestProject3.sln /rebuild debug

/Debug/Executive.exe File1 File2

Command line arguments:
- The file has to be uploaded are accepted from the command line argument

Maintanence History:
====================
ver 1.0 -11 Apr 2015
- first release
*/

#include<iostream>
#include<string>
#include<thread>
#include<mutex>

#include"../Client/Client.h"
#include"../Server/Server.h"
#include"../Message/Message.h"
#include"../Sockets/Sockets.h"
#include"../Sender/Sender.h"
#include"../Receiver/Receiver.h"
#include"../ApplicationHelpers/AppHelpers.h"
#include"../BlockingQueue/BlockingQueue.h"

#ifdef TEST_EXECUTIVE

int main(int argc, char* argv[])
{
	{
		std::string cmd = "FILE_UPLOAD";			//Task to be done (command) - hard coded
		std::string srcaddr = "localhost";          //Source Ip address  - hard coded
		std::string dstaddr = "localhost";			//Destination IP address - hard coded
		size_t srcport = 8080;						//Source port - hard coded
		size_t dstport1 = 9080;						//Destination port - hard coded
		std::string path1 = argv[1];		    //File to be uploaded

		std::cout << "\n----------< Client 1 with Server 1 >------------\n";
		Message MsgObj(cmd, srcaddr, srcport, dstaddr, dstport1, path1);		//Message obj is created 
		Client clientObj;														//Client1 obj
		Server serverObj(dstport1);												//Server1 obj which takes the argument of the port to which assigned

		std::thread serverthread1(&Server::InitializeServer, serverObj);		//thread starts server1
		std::thread clientthread1(&Client::InitializeClient,clientObj,MsgObj);	//thread starts client1
		clientthread1.join();
		serverthread1.join();

		std::cout << "\n*********************************************************\n";

		size_t dstport2 = 9090;						//port no. for second server
		std::string path2 = argv[2];		//another file to be uploaded to server2

		std::cout << "\n----------< Client 2 with Server 2 >------------\n";
		Client clientObj2;														//Client1 obj
		Server serverObj2(dstport2);											//Server1 obj which takes the argument of the port to which assigned
		Message MsgObj2(cmd, srcaddr, srcport, dstaddr, dstport2, path2);
		std::thread serverthread2(&Server::InitializeServer, serverObj2);				//thread starts server2
		std::thread clientthread2(&Client::InitializeClient, clientObj2, MsgObj2);		//thread starts client2
		
		clientthread2.join();
		serverthread2.join();

		return 0;
	}
	
	return 0;
		
}


#endif