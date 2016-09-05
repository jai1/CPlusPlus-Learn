
#ifndef CSOCKETEXCEPTION_H_
#define CSOCKETEXCEPTION_H_
#include <string>


class CSocketException
{

private:
    std::string m_desc;

public:
    CSocketException(std::string str):m_desc(str) {}

    ~CSocketException(){}
    
    std::string description()
    {   
        return m_desc;
    }
    
};

#endif
