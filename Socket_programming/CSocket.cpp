#include <CSocket.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <iostream>

using namespace std;

#ifndef MSG_NOSIGNAL
# define MSG_NOSIGNAL 0
#endif

CSocket::CSocket():m_sockfd(-1)
{
    memset(&m_addr, 0, sizeof(m_addr));
}

CSocket::~CSocket()
{
    if(isValid())
    {
        close(m_sockfd);
    }
}

bool CSocket::create()
{
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(!isValid())
        return false;

    int on = 1;
    if(setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *) &on, sizeof(on)) == -1)
        return false;

    return true;
}

bool CSocket::bind(const int port )
{
    //check for valid socket
    if(!isValid())
        return false;

    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons(port);

    int bind_return = ::bind(m_sockfd, (struct sockaddr *) &m_addr, sizeof(m_addr));

    if(bind_return == -1)
        return false;

    return true;


}

bool CSocket::listen() const
{
    if(!isValid())
        return false;

    int listen_return = ::listen(m_sockfd, MAXCONNECTIONS);

    if(listen_return == -1)
        return false;

    return true; 

}

bool CSocket::accept(CSocket& new_socket ) const
{
    if(!isValid())
        return false;

    //Call accept call to accept the connection from client
    int addr_lenght = sizeof(m_addr);
    new_socket.m_sockfd = ::accept(m_sockfd, (sockaddr *)&m_addr, &addr_lenght);

    if(new_socket.m_sockfd <= 0)
        return false;

    return true;

    
}

bool CSocket::connect(const std::string host, const int port)
{
    if( !isValid())
        return false;

    //send a connect request to server
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);

    int status = inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);

    if(errno == EAFNOSUPPORT)
        return false;

    status = ::connect(m_sockfd, (sockaddr *)&m_addr, sizeof(m_addr));

    if(status == 0)
        return true;
    else
        return false;
}

bool CSocket::send(const std::string str) const
{
    int status = ::send(m_sockfd, str.c_str(), str.size(), MSG_NOSIGNAL);
    
    if(status == -1)
        return false;
    else
        return true;
}

int CSocket::recieve(std::string &str) const
{
    //declare charecter buffer to hold recieved data
    char buff[MAXRECIEVE + 1] = {0};

    str = "";
    memset(buff, 0, (MAXRECIEVE + 1));

    int status = ::recv(m_sockfd, buff, MAXRECIEVE, 0);

    if(status == -1)
    {
        std::cout<<"status = -1 errono = "<<errno<<" In CSocket::recieve \n";
        return 0;
    }
    else 
    {
        if(status != 0)//if number of bytes read != 0
            str = buff;
    }

    return status;

}

void  CSocket::setNonBlocking(const bool b)
{
    int opts;

    opts = fcntl(m_sockfd, F_GETFL);
    
    if(opts < 0)
        return;

    if(b)
        opts = opts | O_NONBLOCK;
    else
        opts = opts & ~O_NONBLOCK;

    fcntl(m_sockfd, F_SETFL, opts);

}
