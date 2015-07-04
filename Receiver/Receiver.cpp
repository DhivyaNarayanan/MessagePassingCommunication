/////////////////////////////////////////////////////////////////////////////
// Receiver.cpp - Receive strings, blocks, and buffers  over socket       //
// Ver 1.0                                                                //
// Language:       Visual C++ 2013                                        //
// Application:    CSE687 - Project 3 (Message Passing Communivation),    //
//					Spring 2015	   										  //
// Platform:       HP G62, Windows 7 Home Premium, Visual Studio 2013     //
// Author:         Dhivya Narayanan, Master's- Computer Engineering,      //
//				   Syracuse University,                                   //
//                 dnnaraya@syr.edu                                       //
////////////////////////////////////////////////////////////////////////////

#include"Receiver.h"
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

//----< create socket listener and starts the clientHandler which receive strings >------------------------------

void Receiver::Recv()
{
	try
	{	
		SocketSystem ss;
		SocketListener sl(sourcePort, Socket::IP6);
		
		BlockingQueue<std::string> bq;
		ClientHandler cp(bq);
		sl.start(cp);
		destIP=cp.getdestIp();
		destport = cp.getdestPort();
		sourceIP = "localhost";
		
	}
	catch (std::exception& ex)
	{
		std::cout << "  Exception caught:" << ex.what() << "\n\n";
	}
}

//----< return source IP address - this IP >------------------------------

std::string Receiver::getsrcIP()
{
	return sourceIP;
}

//----<return source Port address - this port >------------------------------

size_t Receiver::getsrcPort()
{
	return sourcePort;
}

//----< returns Dest IP -- srcaddress in the message >------------------------------

std::string Receiver::getdestIp()
{
	return destIP;
}

//----< returns dest port - srcport in the message >------------------------------

size_t Receiver::getdestPort()
{
	return destport;
}

//----< Client Handler - functor >------------------------------

void ClientHandler::operator()(Socket& socket_)
{
	while (true)
	{
		// interpret test command

		std::string msg = socket_.recvString();
		if (msg.size() == 0)
			break;
		
		bq.enQ(msg);
		
		if (msg == "START OF FILE_UPLOAD")
		{
			if (RecvStringHandling(socket_))
				std::cout << "------ Message Received successfully ----\n\n";
			else
				std::cout << "----Message  not Received successfully----\n";
			continue; // go back and get another command
		}
		if (msg == "ACKNOWLEDGE")
		{
			if (RecvAcknowledge(socket_))
				std::cout << "\n----------- Acknowledge received ---------\n";
			else
				std::cout << "-----------Waiting for Acknowledgement ---------\n";
			continue;
		}
		
	}

	// we get here if command isn't requesting a test, e.g., "TEST_STOP"

	std::cout << "ClientHandler socket connection closing\n";
	socket_.shutDown();
	socket_.close();
	std::cout << "ClientHandler thread terminating\n";

}
//----< run when receives stop command >------------------------------

void ClientHandler::recvStop(Socket&socket_)
{
	std::cout << "\n\nClientHandler socket connection closing\n";
	socket_.shutDown();
	socket_.close();
	std::cout << "ClientHandler thread terminating\n";
}

//----< Receive messages and write the block into the file >------------------------------

bool ClientHandler::RecvStringHandling(Socket& socket_)
{
	std::cout << "\nReceiving messages on server.......\n";
	std::cout << "-------------------------------------\n";
	std::ofstream myfile;
	std::string filename;
	FileSystem::Path fpath;
	FileSystem::Directory dir;
	if (!dir.exists("NewFolder"))
		dir.create("NewFolder");
	std::string newfile;
			
	
    while (true)
	{
		std::string str = socket_.recvString();			//receives the string message
		
		if (socket_ == INVALID_SOCKET)
			return false;
		if (str.size() > 0)
		{
			if (str == "TEST_STOP")
				recvStop(socket_);
			else
			{
				InterpretMsg IMsg(str);
				std::string cmd = IMsg.getCommand();
				std::string filepath = IMsg.getFilePath();
				 destport = IMsg.getsrcPort();    //source port in the message 
				 destIP = IMsg.getsrcIP();
				 sourceIP = IMsg.getdstIP();
				 sourcePort = IMsg.getdstPort();	//this port -; dest port in the message
 				filename = fpath.getName(filepath);
				 newfile = fpath.fileSpec("NewFolder", filename);
				
				if (cmd == "FILE_UPLOAD")
				{
					myfile.open(newfile, std::ofstream::out | std::ofstream::app);	//create and open new fie in current directory with the same filename as received
					std::string block = IMsg.getBlock();
					myfile << block;										//writes the block into the file
					std::string headermsg = IMsg.getHeader();
					bq.enQ(headermsg);
					myfile.close();
				}
				std::cout << "\nserver received the message ..... ";
			}
			
		}
		else
		{
			break;
		}
		if (socket_.bytesWaiting() == 0)
			break;
	}
	Display dp;				
	dp.display_recvfile(newfile);		//calls display 
	return true;
}

//----< runs when receive acknowledgement >------------------------------

bool ClientHandler::RecvAcknowledge(Socket& socket_)
{
	while (true)
	{
		if (socket_.bytesWaiting() == 0)
			break;
		std::string str = socket_.recvString();
		if (socket_ == INVALID_SOCKET)
			return false;
		if (str.size() > 0)
		{
			std::cout << "\nClient recvd....:   ";
			std::cout << str << "\n";
			bq.enQ(str);
		}
		else
			break;
	}
	return true;

}

//----< returns DestIP - same as sourceIP in the message >------------------------------

std::string ClientHandler::getdestIp()		//gets the sourceIp in the message
{
	return destIP;
}

//----< returns Destport - same as sourcePort in the message >------------------------------

size_t ClientHandler::getdestPort()
{
	return destport;
}

//----< test stub >------------------------------

#ifdef TEST_RECEIVER

int main()
{
	Receiver rc(9080);
	rc.Recv();
	return 0;
}
#endif