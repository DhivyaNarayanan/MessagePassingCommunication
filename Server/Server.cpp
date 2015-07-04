/////////////////////////////////////////////////////////////////////////////
// Server.cpp - Initializes sender and receiver for server                //
// Ver 1.0                                                                //
// Language:       Visual C++ 2013                                        //
// Application:    CSE687 - Project 3 (Message Passing Communivation),    //
//					Spring 2015	   										  //
// Platform:       HP G62, Windows 7 Home Premium, Visual Studio 2013     //
// Author:         Dhivya Narayanan, Master's- Computer Engineering,      //
//				   Syracuse University,                                   //
//                 dnnaraya@syr.edu                                       //
////////////////////////////////////////////////////////////////////////////

#include"Server.h"
#include<iostream>
#include<string>

//----<Initialize sender and receiver for server>------------------------------

void Server::InitializeServer()
{
	std::cout << "------------------ start of Server ---------------------\n";
	Sender sr;
	Receiver rc(port_);
	rc.Recv();
	
	std::string sourceIP = rc.getsrcIP();  //destIp in the message
	size_t sourcePort = rc.getsrcPort();   //destPort in the message - this port
	std::string destIP = rc.getdestIp();	//sourceIp in the message
	size_t destPort = rc.getdestPort();		//sourceport in the message
	
	sr.sendAck(sourceIP,sourcePort,destIP,destPort);		//send acknowledgement
	
	std::cout << "-------------------- End of Server ----------------\n";
	
}

//----< test stub >------------------------------

#ifdef TEST_SERVER

int main()
{
	Server sv(9080);
	sv.InitializeServer();
	return 0;
}
#endif