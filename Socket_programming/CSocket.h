#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <string>

using namespace std;

const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECIEVE = 1000;
const string ACK = "END_ACK";

class CSocket
{
      private:
              int m_sockfd;
              sockaddr_in m_addr;
              
      public:

             CSocket();
             virtual ~CSocket();
             //Server initialization methods
             bool create();
             bool bind(const int port );
             bool listen() const;
             bool accept(CSocket &new_socket ) const;

             //client initialization menthod
             bool connect(const std::string host, const int port);
             
             //Data transmission methods
             bool send(const std::string) const;
             int recieve(std::string &) const;
             
             bool isValid() const
             {
                  return (m_sockfd != -1);
             }

             void setNonBlocking(const bool b);
             
};

#endif
