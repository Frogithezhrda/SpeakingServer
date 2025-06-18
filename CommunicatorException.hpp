#pragma
#include <exception>
#include <string>
#include <iostream>

class CommunicatorException : public std::exception
{
public:
    CommunicatorException(const std::string& message)
    {
        this->_message = "Comms Error: " + message + "\n";
    }

    virtual char const* what() const throw()
    {
        return _message.c_str();
    }
private:
    std::string _message;
};