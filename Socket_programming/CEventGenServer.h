#ifndef EVENTGENSERVER_H_
#define EVENTGENSERVER_H_

#include <string>
#include "CSocket.h"

using namespace std;

class CEventGenServer:public CSocket
{
private:

public:
    CEventGenServer(int port);
    CEventGenServer();

    ~CEventGenServer();

    void accept(CEventGenServer &serverSocket);

    bool recieveConfFile(string path, string &filename);

    bool recieveBinaryFile(string path, string &filename);

};

#endif
