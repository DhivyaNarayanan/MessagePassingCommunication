/////////////////////////////////////////////////////////////////////////////
// Display.cpp - Supports console display part of Project					   //
// Ver 1.0                                                                //
// Language:       Visual C++ 2013                                        //
// Application:    CSE687 - Project 3 (Message Passing Communivation),    //
//					Spring 2015	   										  //
// Platform:       HP G62, Windows 7 Home Premium, Visual Studio 2013     //
// Author:         Dhivya Narayanan, Master's- Computer Engineering,      //
//				   Syracuse University,                                   //
//                 dnnaraya@syr.edu                                       //
////////////////////////////////////////////////////////////////////////////

#include"Display.h"
#include<iostream>
#include<string>


//----< display for client side ( sender - File upload) >------------------------------

void Display::display_sendfile(std::string path)
{
	FileSystem::Path pt;
	FileSystem::FileInfo fi(path);
	std::cout << "\n==================================================================\n\n";
	std::cout << "\nFile is Uploading from the client side.......";
	std::cout << "\nPath :  " << pt.getFullFileSpec(path);
	std::cout << "\nName of the file  :   " << pt.getName(path);
	std::cout << "\nSize of the file  :   " << fi.size();
	std::cout << "\n\n---------------------------------------------------------------\n";
}

//----< display for server side (Receiver) >------------------------------

void Display::display_recvfile(std::string path)
{
	FileSystem::Path pt;
	
	std::string fpath = pt.getFullFileSpec(path);
	FileSystem::FileInfo fi(fpath);
	std::cout << "\n----------------------------------------------------------------\n";
	std::cout << "\nFile is Uploaded and stored in the server side ........";
	std::cout << "\nPath :  " << pt.getFullFileSpec(path);
	std::cout << "\nName of the file  :   " << pt.getName(fpath);
	std::cout << "\n\n====================================================================\n";
}

//-----------------------------< test stub >--------------------------------------------------

#ifdef TEST_DISPLAY

int main()
{
	Display dp;
	std::string path = "../TextFile.txt";
	dp.display_sendfile(path);
	dp.display_recvfile(path);
	return 0;
}
#endif