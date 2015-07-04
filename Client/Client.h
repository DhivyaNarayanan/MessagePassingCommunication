#ifndef CLIENT_H
#define CLIENT_H

/////////////////////////////////////////////////////////////////////////////
// Client.h - Uses sender and Receiver									   //
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
*  This package initiaizes sender and receiver class
* 
*  Required Files:
*  ---------------
*  ClientTest.cpp, Sender.h, Sender.cpp, Receiver.h, Receiver.cpp
*
*  Build Command:
*  --------------
*  devenv TestProject3.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
*  
*  ver 1.0 - 08 April 2015
*  - first release
*/

#include<iostream>
#include<string>
#include"../Message/Message.h"
#include"../ApplicationHelpers/AppHelpers.h"
#include"../Sender/Sender.h"
#include"../Receiver/Receiver.h"


class Client
{
public:
	Client(){}
	void InitializeClient(Message& msg);			//Starts the client
	
};

#endif