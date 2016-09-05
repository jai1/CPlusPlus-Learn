
#include <libgen.h>
#include <fstream>
#include "CEventGenClient.h"

CEventGenClient::CEventGenClient(std::string host, int nPort)
{
    //Create socket connection
    if(!create())
        throw CSocketException("Error : Failed to create Socket connection!!!");

    //Connect to Event Generator Server using input host and port
    if(!connect(host, nPort))
    {
        string desc = "Error : Failed to connect to server";
        desc += host;
        desc += "!!!";

        throw CSocketException(desc);
    }
    
}

bool CEventGenClient::sendConfFile(std::string filePath)
{
    string buffer = "";

    //Extract filename from filepath;
    string fileName = basename((char *)filePath.c_str());

    //send filename to Event generator server
    if(!send(fileName))
    {
        string desc = "Error : Failed to send Config Filename data to Event Generator Server!!!";
        throw CSocketException(desc);
    }

    //Send the ACK signal which indicate file name sent successfully
    if(!send(ACK))
        throw CSocketException("Error : Failed to send send ACK signal!!!");

    //Recieve ACK signal from sever which indicate filename recieved successfully.
    while(recieve(buffer) > 0)
    {
        int npos = buffer.find(ACK, 0);

        if(npos != string::npos)
        {
            //ACK recieved successfully from Event generator server
            break;
        }
    }

    
    //Send file information
    ifstream confFile;
    confFile.open(filePath.c_str());

    if(!confFile.is_open())
    {
        string desc = "Error : Unable to open Configuration File ";
        desc += filePath;
        desc += "!!!";

        throw CSocketException(desc);
    }

    string line = "";
    while(confFile.good())
    {
        getline(confFile, line);
        
        if(!confFile.eof())
            line = line + "\n";
        
        if(!send(line))
            throw CSocketException("Error : Failed to send file data to server!!!");

    }
    confFile.close();

    if(!send(ACK))
       throw CSocketException("Error : Failed to send send ACK signal!!!"); 

        
    return true;   
}
