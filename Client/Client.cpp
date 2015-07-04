/////////////////////////////////////////////////////////////////////////////
// Client.cpp - Uses sender and Receiver								  //
// Ver 1.0                                                                //
// Language:       Visual C++ 2013                                        //
// Application:    CSE687 - Project 3 (Message Passing Communivation),    //
//					Spring 2015	   										  //
// Platform:       HP G62, Windows 7 Home Premium, Visual Studio 2013     //
// Author:         Dhivya Narayanan, Master's- Computer Engineering,      //
//				   Syracuse University,                                   //
//                 dnnaraya@syr.edu                                       //
////////////////////////////////////////////////////////////////////////////


#include"Client.h"
#include<iostream>
#include<string>

//----< starts the client by Initializing sender and receiver object for client >------------------------------

void Client::InitializeClient(Message& msg)
{
	std::cout << "------------------- start of client -------------------\n";
	size_t srcport = msg.getsrcPort();
	Sender sr;
	Receiver rc(srcport);

	std::thread sendthread(&Sender::Send,sr,msg);		// Sender Thread for Sender Class- Send method
	std::thread recvthread(&Receiver::Recv,rc);			// Receiver Thread for Receiver class - Recv method
	
	sendthread.join();
	recvthread.join();
	
	std::cout << "---------------- End of client----------------\n";	
}

//----< test stub >--------------------------------------------------


#ifdef TEST_CLIENT

int main()
{
	Client cl;
	std::string cmd = "FILE_UPLOAD";
	std::string srcaddr = "localhost";
	std::string dstaddr = "localhost";
	size_t srcport = 8080;
	size_t dstport = 9080;
	std::string path = "../TextFile.txt";
	Message msg(cmd, srcaddr, srcport, dstaddr, dstport, path);
	cl.InitializeClient(msg);
	return 0;
}
#endif