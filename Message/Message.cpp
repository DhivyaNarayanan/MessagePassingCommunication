///////////////////////////////////////////////////////////////////////////////////
// Message.cpp -   Implement Construction of message to send					 //
//					and Interpretation of the received message                   //
// Ver 1.0																		 //
// Language:       Visual C++ 2013                                               //
// Application:    CSE687 - Project 3 (Message Passing Communivation),           //
//					Spring 2015	   										         //
// Platform:       HP G62, Windows 7 Home Premium, Visual Studio 2013            //
// Author:         Dhivya Narayanan, Master's- Computer Engineering,             //
//				   Syracuse University,                                          //
//                 dnnaraya@syr.edu                                              //
///////////////////////////////////////////////////////////////////////////////////

#include"Message.h"
#include"../FileSystem/FileSystem.h"
#include<iostream>
#include<fstream>
#include<string>


//----< constructor for the class Message >------------------------------

Message::Message(std::string cmd, std::string srcIPaddr, size_t srcport, std::string dstIPaddr, size_t dstport, std::string fpath) :filepath_(fpath)
{
	numBytes = 512; 
	cmd_ = "COMMAND : ";
	cmd_.append(cmd);
	srcIPaddr_ = "SRC_IPADDRESS : ";
	srcIPaddr_.append(srcIPaddr);
	srcPort_ = srcport;
	dstIPaddr_ = "DST_IPADDRESS : ";
	dstIPaddr_.append(dstIPaddr);
	dstPort_ = dstport;
	contentlength_ = "CONTENTLENGTH : ";

	FileSystem::FileInfo fileinfo(filepath_);
	filesize_ = fileinfo.size();

}

//----< Returns the filesize >------------------------------

size_t Message::getFileSize(std::string filespec)
{
	FileSystem::FileInfo fileinfo(filespec);
	size_t tmp_filesize = fileinfo.size();
	return tmp_filesize;
}

//----< Allows to change the command >------------------------------

void Message::changeCmd(std::string cmd)
{
	cmd_ = "COMMAND : ";
	cmd_.append(cmd);
}

//----< create Header which includes Command, SrcAddress , DstAddress, FilePath, FileSize, ContentLength >------------------------------

std::string Message::makeHeader(size_t blocksize)
{
	numBytes = blocksize;
	contentlength_ = "CONTENTLENGTH : ";
	contentlength_ += std::to_string(numBytes);

	std::string header;
	header = cmd_;
	header += '\n';
	header += srcIPaddr_;
	header += '\n';
	header += "SRC_PORT : ";
	header += std::to_string(srcPort_);
	header += '\n';
	header += dstIPaddr_;
	header += '\n';
	header += "DST_PORT : ";
	header += std::to_string(dstPort_);
	header += '\n';
	header += "PATH : ";
	header += filepath_;
	header += '\n';
	header += "FILESIZE : ";
	header += std::to_string(filesize_);
	header += '\n';
	header += contentlength_;
	header += '\n';
	header += '\n';         //blank line - end of header message

	header_ = header;
	return header_;
}

//----< create message which includes header, buffer(blocks of file) >------------------------------

std::string Message::buildMsg(size_t blocksize, std::string buffer)
{
	std::string msg;
	std::string msg_header = makeHeader(blocksize);
	msg = msg_header;
	std::string tbuf;
	for (int i = 0; i < blocksize; i++)
	{
		tbuf += buffer[i];
	}
	msg += tbuf;
	message_ = msg;
	return message_;

}

//----< Returns the command >------------------------------

std::string Message::getCommand()
{
	std::string cmd = cmd_;
	std::string task;
	int i = 0;
	size_t pos = cmd.find(':');
	pos++;
	while (cmd[pos] == ' ')
		pos++;
	i = pos;
	while (cmd[i] != '\0')
	{
		task += cmd[i];
		i++;
	}
	return task;
}

//----< Returns the source IP address >------------------------------

std::string Message::getsrcIP()
{
	std::string srcIP = srcIPaddr_;
	std::string IPaddr;
	int i = 0;
	size_t pos = srcIP.find(':');
	pos++;
	while (srcIP[pos] == ' ')
		pos++;
	i = pos;
	while (srcIP[i] != '\0')
	{
		IPaddr += srcIP[i];
		i++;
	}
	return IPaddr;
}

//----< Returns the source port  >------------------------------

size_t Message::getsrcPort()
{
	return srcPort_;
}

//----< Returns the destination IP address >------------------------------

std::string Message::getdstIP()
{
	std::string dstIP = dstIPaddr_;
	std::string IPaddr;
	int i = 0;
	size_t pos = dstIP.find(':');
	pos++;
	while (dstIP[pos] == ' ')
		pos++;
	i = pos;
	while (dstIP[i] != '\0')
	{
		IPaddr += dstIP[i];
		i++;
	}
	return IPaddr;

}

//----< Returns the destination port >------------------------------

size_t Message::getdstPort()
{
	return dstPort_;
}

//----< Returns the file path >------------------------------

std::string Message::getFilePath()
{
	return filepath_;
}

//----< Returns the block size - content length >------------------------------

size_t Message::getBlocksize()
{
	return numBytes;
}

//----< Returns the Header >------------------------------

std::string Message::getHeader()
{
	return header_;
}

//----< Returns the message >------------------------------

std::string Message::getMessage()
{
	return message_;
}


//----< Constructor for the class Interpret message >------------------------------

InterpretMsg::InterpretMsg(std::string &msg) : message_(msg)
{
	std::string tmsg = message_;
	size_t eof_header = tmsg.find("\n\n");
	int i = 0;
	while (i < eof_header)
	{
		header_ += tmsg[i];
		i++;
	}
	header_ += '\n';
	int j = eof_header;
	while (tmsg[j] == '\n')
		j++;
	while (tmsg[j] != '\0')
	{
		block += tmsg[j];
		j++;
	}
}

//----< Returns the Header of the message >------------------------------

std::string InterpretMsg::getHeader()
{
	return header_;
}

//----< Parse the message header and Returns the command >------------------------------

std::string InterpretMsg::getCommand()
{
	std::string cmd_str;
	size_t pos = header_.find('\n');
	int i = 0;
	while (i < pos)
	{
		cmd_str += header_[i];
		i++;
	}
	size_t tpos = cmd_str.find(':');
	tpos++;
	while (cmd_str[tpos] == ' ')
		tpos++;
	int j = tpos;
	while (cmd_str[j] != '\0'&&j != pos)
	{
		cmd_ += cmd_str[j];
		j++;
	}
	return cmd_;
}

//----< Parse the message header and Returns the source IP address >------------------------------

std::string InterpretMsg::getsrcIP()
{
	std::string srcIP_str;
	size_t pos = header_.find("SRC_IPADDRESS : ");
	size_t epos = header_.find('\n', pos);
	size_t tpos = header_.find(':', pos);
	int i = pos;
	while (i < epos)
	{
		srcIP_str += header_[i];
		i++;
	}
	tpos++;
	while (header_[tpos] == ' ')
		tpos++;
	int j = tpos;
	while (j < epos)
	{
		srcIPaddr_ += header_[j];
		j++;
	}
	return srcIPaddr_;
}

//----< Parse the message header and Returns the source port>------------------------------

size_t InterpretMsg::getsrcPort()
{
	std::string srcport_str;
	std::string port;
	size_t pos = header_.find("SRC_PORT : ");
	size_t epos = header_.find('\n', pos);
	size_t tpos = header_.find(':', pos);
	int i = pos;
	while (i < epos)
	{
		srcport_str += header_[i];
		i++;
	}
	tpos++;
	while (header_[tpos] == ' ')
		tpos++;
	int j = tpos;
	while (j < epos)
	{
		port += header_[j];
		j++;
	}
	srcPort_ = std::stoi(port);
	return srcPort_;
}

//----< Parse the message header and Returns the destination IP address>------------------------------

std::string InterpretMsg::getdstIP()
{
	std::string dstIP_str;
	size_t pos = header_.find("DST_IPADDRESS : ");
	size_t epos = header_.find('\n', pos);
	size_t tpos = header_.find(':', pos);
	int i = pos;
	while (i < epos)
	{
		dstIP_str += header_[i];
		i++;
	}
	tpos++;
	while (header_[tpos] == ' ')
		tpos++;
	int j = tpos;
	while (j < epos)
	{
		dstIPaddr_ += header_[j];
		j++;
	}
	return dstIPaddr_;
}

//----< Parse the message header and Returns the destination port >------------------------------

size_t InterpretMsg::getdstPort()
{
	std::string dstport_str;
	std::string port;
	size_t pos = header_.find("DST_PORT : ");
	size_t epos = header_.find('\n', pos);
	size_t tpos = header_.find(':', pos);
	int i = pos;
	while (i < epos)
	{
		dstport_str += header_[i];
		i++;
	}
	tpos++;
	while (header_[tpos] == ' ')
		tpos++;
	int j = tpos;
	while (j < epos)
	{
		port += header_[j];
		j++;
	}
	dstPort_ = std::stoi(port);
	return dstPort_;
}

//----< Parse the message header and Returns the filepath >------------------------------

std::string InterpretMsg::getFilePath()
{
	std::string path_str;
	size_t pos = header_.find("PATH : ");
	size_t epos = header_.find('\n', pos);
	size_t tpos = header_.find(':', pos);
	int i = pos;
	while (i < epos)
	{
		path_str += header_[i];
		i++;
	}
	tpos++;
	while (header_[tpos] == ' ')
		tpos++;
	int j = tpos;
	while (j < epos)
	{
		filepath_ += header_[j];
		j++;
	}
	return filepath_;

}

//----< Parse the message header and Returns the total file size >------------------------------

size_t InterpretMsg::getFileSize()
{
	std::string filesize_str;
	std::string fsize;
	size_t pos = header_.find("FILESIZE : ");
	size_t epos = header_.find('\n', pos);
	size_t tpos = header_.find(':', pos);
	int i = pos;
	while (i < epos)
	{
		filesize_str += header_[i];
		i++;
	}
	tpos++;
	while (header_[tpos] == ' ')
		tpos++;
	int j = tpos;
	while (j < epos)
	{
		fsize += header_[j];
		j++;
	}
	filesize_ = std::stoi(fsize);
	return filesize_;
}

//----< Parse the message header and Returns the content length >------------------------------

size_t InterpretMsg::getBlocksize()
{
	std::string length_str;
	std::string bsize;
	size_t pos = header_.find("CONTENTLENGTH : ");
	size_t epos = header_.find('\n', pos);
	size_t tpos = header_.find(':', pos);
	int i = pos;
	while (i < epos)
	{
		length_str += header_[i];
		i++;
	}
	tpos++;
	while (header_[tpos] == ' ')
		tpos++;
	int j = tpos;
	while (j < epos)
	{
		bsize += header_[j];
		j++;
	}
	numBytes = std::stoi(bsize);
	return numBytes;
}
//----< Returns the message >------------------------------

std::string InterpretMsg::getMessage()
{
	return message_;
}

//----<  Returns the block content >------------------------------

std::string InterpretMsg::getBlock()
{
	return block;
}

//----< test stub >------------------------------

#ifdef TEST_MESSAGE

int main()
{
	std::string cmd = "FILE_UPLOAD";
	std::string srcaddr = "localhost";
	std::string dstaddr = "localhost";
	size_t srcport = 8080;
	size_t dstport = 8090;
	std::string path = "TextFile.txt";
	const int length = 300;
	Message msg(cmd, srcaddr, srcport, dstaddr, dstport, path);
	std::string str;
	std::ifstream infile;
	infile.open(path);				//opens the file 
	int i = 0;
	int j = 1;
	int bytesRead, bytesRemaining;

	bytesRemaining = msg.getFileSize(path);
	std::cout << "BytesRemaining :: " << bytesRemaining << "\n";

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
			std::string message_ = msg.buildMsg(bytesRead, buffer);
			std::cout << "Message  " << j << " :: " << message_ << "\n";
			std::cout << "-----------------------------------------------------------\n";
			InterpretMsg Imsg(message_);
			std::cout << " getCommand  :: " << Imsg.getCommand() << "\n";
			std::cout << " getsrcIP()  :: " << Imsg.getsrcIP() << "\n";
			std::cout << " getsrcPort() :: " << Imsg.getsrcPort() << "\n";
			std::cout << " getdstIP() :: " << Imsg.getdstIP() << "\n";
			std::cout << "getdstPort() :: " << Imsg.getdstPort() << "\n";
			std::cout << " getFilePath() :: " << Imsg.getFilePath() << "\n";
			std::cout << " getFileSize() :: " << Imsg.getFileSize() << "\n";
			std::cout << " getBlocksize() :: " << Imsg.getBlocksize() << "\n";
			std::cout << "getHeader() :: " << Imsg.getHeader() << "\n";
			std::cout << "getBlock() :: " << Imsg.getBlock() << "\n";
			std::cout << "===============================================================";

		}
		else
		{
			char buffer_[length];
			infile.read(buffer_, sizeof(buffer_));
			bytesRead = infile.gcount();
			bytesRemaining -= bytesRead;
			std::string message_ = msg.buildMsg(bytesRead, buffer_);
			std::cout << "Message  " << j << " :: " << message_ << "\n";
			std::cout << "-----------------------------------------------------------\n";
		}
		j++;
	}
	infile.close();

	return 0;
}
#endif