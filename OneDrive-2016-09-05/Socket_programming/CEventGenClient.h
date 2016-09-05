#ifndef EVENTGEN_CLIENT_H
#define EVENTGEN_CLIENT_H

#include "CSocketException.h"
#include "CSocket.h"
#include <string>

class CEventGenClient : public CSocket
{
private:
    
public:
    CEventGenClient(std::string host, int nPort);

    virtual ~CEventGenClient(){}

    bool sendConfFile(std::string filePath);

    
};

#endif
