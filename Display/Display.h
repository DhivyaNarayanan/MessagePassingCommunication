/////////////////////////////////////////////////////////////////////////////
// Display.h - Supports console display part of Project					   //
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
*  This package provides single class Display
*
*  Required Files:
*  ---------------
*  Display.h, Display.cpp, FileSystem.h, FileSystem.cpp
*  Build Command:
*  --------------
*  devenv TestProject3.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
*
*  ver 1.0 - 11 April 2015
*  - first release
*/

#ifndef DISPLAY_H
#define DISPLAY_H
#include"../FileSystem/FileSystem.h"

class Display
{
public:
	void display_sendfile(std::string path);   //display for client side ( sender - File upload)
	void display_recvfile(std::string path);   // display for server side (Receiver)

};
#endif