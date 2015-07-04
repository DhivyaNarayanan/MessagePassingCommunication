/////////////////////////////////////////////////////////////////////////////
// Sender.cpp - Send strings, blocks, and buffers  over socket            //
// Ver 1.0                                                                //
// Language:       Visual C++ 2013                                        //
// Application:    CSE687 - Project 3 (Message Passing Communivation),    //
//					Spring 2015	   										  //
// Platform:       HP G62, Windows 7 Home Premium, Visual Studio 2013     //
// Author:         Dhivya Narayanan, Master's- Computer Engineering,      //
//				   Syracuse University,                                   //
//                 dnnaraya@syr.edu                                       //
////////////////////////////////////////////////////////////////////////////


#include"Sender.h"
#include<iostream>
#include<string>
#include<fstream>

using namespace std;


//----< method to build the message and send >------------------------------

void Sender::sendMsg(Socket&si,Message&msg_)
{
	BlockingQueue<std::string> bq;
	std::string cmd = msg_.getCommand();
	std::string filepath = msg_.getFilePath();
	size_t filesize = msg_.getFileSize(filepath);
	const int length = 1024;										// hard-coded maximum block size
	std::string str;
	std::string startmsg = "START OF FILE_UPLOAD";
	bq.enQ(startmsg);
	si.sendString(bq.deQ());
	if (cmd.compare("FILE_UPLOAD") == 0)
	{
		Display dp;
		dp.display_sendfile(filepath);
		std::ifstream infile;
		infile.open(filepath);			//opens the file and read the content
		int i = 0;
		int j = 1;
		int bytesRead, bytesRemaining = filesize;
		while (infile.good())
		{
			if (bytesRemaining < length)
			{
				char * buffer = new char[bytesRemaining];
				for (int i = 0; i < bytesRemaining; i++)
				{
					infile.get(buffer[i]);
				}
				buffer[bytesRemaining] = '\0';
				bytesRead = bytesRemaining;
				std::string HeaderStr = msg_.makeHeader(bytesRead);
				bq.enQ(HeaderStr);
				std::string message_ = msg_.buildMsg(bytesRead, buffer);   // build the message
				bq.deQ();
				si.sendString(message_);									// send the message
				std::cout << "\n client Sending message ........ ";
				
			}
			else
			{
				char buffer_[length];
				infile.read(buffer_, sizeof(buffer_));
				bytesRead = infile.gcount();
				bytesRemaining -= bytesRead;
				std::string HeaderStr = msg_.makeHeader(bytesRead);
				bq.enQ(HeaderStr);
				std::string message_ = msg_.buildMsg(bytesRead, buffer_);
				bq.deQ();
				si.sendString(message_);
				std::cout << " \n client Sending message ......... ";
			}
			j++;
		}
		infile.close();
		std::cout << "\n------------------------------------------\n";
		std::cout << "File uploaded successfully ..\n";
		std::cout << "=================================\n";
		SendStop(si);
	}
	else
		std::cout << "Message not found..\n";
	
}

//----< creates socket and send the message which in turn calls sendMsg function >------------------------------

void Sender::Send(Message&msg_)
{
	SocketSystem ss;
	SocketConnecter si;					//create socketConnector
	 
	std::string cmd = msg_.getCommand();
	std::string sourceIP = msg_.getsrcIP();
	 std::string destIP = msg_.getdstIP();
	size_t sourcePort = msg_.getsrcPort();
	 size_t destPort = msg_.getdstPort();
	std::string filepath = msg_.getFilePath();
	size_t filesize = msg_.getFileSize(filepath);
	std::string addrMsg = sourceIP;
	addrMsg += ':';
	addrMsg += std::to_string(sourcePort);
	addrMsg += '\n';
	addrMsg += destIP;
	addrMsg += ':';
	addrMsg += std::to_string(destPort);
	std::cout << "\ndestIP   :: " << destIP;
	std::cout << "\ndestPort :: " << destPort << "\n";
	
		
	while (!si.connect(destIP, destPort))			//connect to destPort - server
	{
		std::cout << "Client waiting to connect \n";
		::Sleep(100);
	}
	std::cout << "\nClient is connected to the server - Port : " << destPort << "\n";
	if (cmd.compare("FILE_UPLOAD")==0)
		sendMsg(si,msg_);							//build and send message over socket

}

//----< send stop message >------------------------------

void Sender::SendStop(Socket&si)
{
	si.sendString("TEST_STOP");

	std::cout << "\n ----- client calling send shutdown -----\n";
	si.shutDownSend();
}

//----< send acknowledgement >------------------------------

void Sender::sendAck(std::string sourceIp, size_t sourcePort, std::string destIp, size_t destPort)
{
	SocketSystem ss;
	SocketConnecter si;
	
	while (!si.connect(destIp, destPort))
	{
		std::cout << "Client waiting to connect \n";
		::Sleep(100);
	}
	si.sendString("ACKNOWLEDGE");
	std::string ack_str = "Acknowledgement from server..";
	si.sendString(ack_str);
	std::cout << "\n---------------------------------";
	std::cout << "\ndestIP   :: " << destIp;
	std::cout << "\ndestPort :: " << destPort << "\n";
	std::cout << "Sending Acknowledgement.....\n";
	std::cout << "-------------------------------\n";

}

//----< test stub >------------------------------


#ifdef TEST_SENDER

int main()
{
	Sender sr;
	std::string cmd = "FILE_UPLOAD";
	std::string srcaddr = "localhost";
	std::string dstaddr = "localhost";
	size_t srcport = 8080;
	size_t dstport = 9080;
	std::string path = "../TextFile.txt";
	Message msg(cmd, srcaddr, srcport, dstaddr, dstport, path);
	sr.Send(msg);
	return 0;

}
#endif