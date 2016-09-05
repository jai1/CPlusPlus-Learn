
#include "CEventGenServer.h"
#include "CSocketException.h"
#include <fstream>

CEventGenServer::CEventGenServer(int nPort)
{
    //Create server socket
    if(!create())
    {
        throw CSocketException("Error : Could not create Server socket!!!");
    }

    if(!bind(nPort))
    {
        throw CSocketException("Error : Could not bind to port!!!");
    }

    if(!listen())
    {
        throw CSocketException("Error : Could not listen to socket!!!");
    }
}


CEventGenServer::CEventGenServer()
{

}

CEventGenServer::~CEventGenServer()
{

}

void  CEventGenServer::accept(CEventGenServer &serverSocket)
{
    if(!CSocket::accept(serverSocket))
    {
        throw CSocketException("Error : Sould not accept the Socket!!!");
    }
}

bool CEventGenServer::recieveConfFile(string path, string &filename)
{
    string buffer = "";
    filename = "";
    

    //Get the filename from recieved data
    while(recieve(buffer) > 0)
    {
        int npos = buffer.find(ACK, 0);
        if(npos != string::npos)
        {
            filename = filename + buffer.substr(0, npos);
            buffer.erase(0, npos + ACK.length());    
            break;            
        }
        else
        {
            filename = filename + buffer;
            continue;
        }
    }
    //Send back the acknowledge signal back to client which indicate filename recieved successfully.
    if(!send(ACK))
    {
        throw CSocketException("Error: Failed to send filename recieved ACK!!!");
    }

    //Create ASCII file at given path with filename present in filename variable
    ofstream confFile;

    filename = path + filename;

    confFile.open(filename.c_str());

    if(!confFile.is_open())
        throw CSocketException("Error : Failed to create Configuration File");

    //Recieve the data from socket and write it on file
    
    confFile<<buffer;

    while(recieve(buffer) > 0)
    {
        int npos = buffer.find(ACK, 0);

        if(npos != string::npos)
        {
            confFile<<buffer.substr(0, npos);
            break;
        }
        else
        {
            confFile<<buffer;
            continue;
        }
    }    

    confFile.close();
    
    return true;

}

bool CEventGenServer::recieveBinaryFile(string path, string &filename)
{
    filename = "";

    string buffer = "";

    //Get the binary file from socket
    while(recieve(buffer) > 0)
    {
        int npos = buffer.find(ACK, 0);
        if(npos != string::npos)
        {
            filename = filename + buffer.substr(0, npos);
            buffer.erase(0, npos + ACK.length());

            break;
        }
    }

    //Send back the ACK signal to client
    if(!send(ACK))
        throw CSocketException("Error : Failed to send filename recieved ACK");

    //Recieve the file data from socket and store it in file
    ofstream binFile;

    filename = path + filename;
    binFile.open(filename.c_str(), ios::out | ios::binary);

    binFile.write(buffer.c_str(), buffer.length());

    buffer = "";

    //Recieve data from socket
    while(recieve(buffer) > 0)
    {
        int npos = buffer.find(ACK, 0);
        
        if(npos != string::npos)
        {
            string temp = buffer.substr(0, npos);
            binFile.write(temp.c_str(), temp.length());
            break;            
        }
        else
        {
            binFile.write(buffer.c_str(), buffer.length());
        }
        
        buffer = "";
    }

    binFile.close();
    
    return true;
}
