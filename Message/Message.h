#ifndef MESSAGE_H
#define MESSAGE_H

///////////////////////////////////////////////////////////////////////////////////
// Message.h - Constructs messages to send and Interpret the received message    //
// Ver 1.0																		 //
// Language:       Visual C++ 2013                                               //
// Application:    CSE687 - Project 3 (Message Passing Communivation),           //
//					Spring 2015	   										         //
// Platform:       HP G62, Windows 7 Home Premium, Visual Studio 2013            //
// Author:         Dhivya Narayanan, Master's- Computer Engineering,             //
//				   Syracuse University,                                          //
//                 dnnaraya@syr.edu                                              //
///////////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package constructs the message header which has to send over socket
*  and provides the class for interpreting the received message
*
*  Required Files:
*  ---------------
*  Message.h, Message.cpp
*
*  Build Command:
*  --------------
*  devenv Project3.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
*  ver 1.0 -06 Apr 2015
*  - first release
*/

#include<string>
#include<iostream>

using namespace std;

//----< class for constructing messages >------------------------------

class Message
{
public:
	Message(){}
	Message(std::string cmd, std::string srcIPaddr, size_t srcPort, std::string dstIPaddr, size_t dstPort, std::string fpath);
	std::string makeHeader(size_t blocksize);						// create header
	std::string buildMsg(size_t blocksize, std::string buffer);		// create message - header + buffer
	size_t getFileSize(std::string filespec);
	std::string getCommand();
	std::string getsrcIP();
	size_t getsrcPort();
	std::string getdstIP();
	size_t getdstPort();
	std::string getFilePath();
	size_t getBlocksize();
	std::string getHeader();
	std::string getMessage();
	void changeCmd(std::string cmd);
private:
	std::string cmd_;
	std::string srcIPaddr_;
	std::string dstIPaddr_;
	size_t srcPort_;
	size_t dstPort_;
	std::string filepath_;
	size_t filesize_;
	size_t numBytes;
	std::string contentlength_;
	char* block_;
	std::string message_;
	std::string header_;
};

//----< class for Interpreting messages >------------------------------


class InterpretMsg
{
public:
	InterpretMsg(std::string &msg);
	std::string getCommand();
	std::string getsrcIP();
	size_t getsrcPort();
	std::string getdstIP();
	size_t getdstPort();
	std::string getFilePath();
	size_t getFileSize();
	size_t getBlocksize();
	std::string getHeader();
	std::string getMessage();
	std::string getBlock();
private:
	std::string message_;
	std::string header_;
	std::string cmd_;
	std::string srcIPaddr_;
	std::string dstIPaddr_;
	size_t srcPort_;
	size_t dstPort_;
	std::string filepath_;
	size_t filesize_;
	size_t numBytes;
	std::string contentlength_;
	std::string block;
};

#endif