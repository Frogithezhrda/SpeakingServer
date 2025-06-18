#pragma
#include <exception>
#include <string>
#include <iostream>

class DataBaseException : public std::exception
{
public:

    DataBaseException(const std::string& message)
    {
        this->_message = "Database Error: " + message + "\n";
    }

    virtual char const* what() const throw()
    {
        return _message.c_str();
    }
private:
    std::string _message;
};
