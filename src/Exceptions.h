#pragma once
#include <exception>

class FatalException : public std::exception
{
public:
    int code;
    FatalException(int c)
    {
        code = c;
    }
};

class NonFatalException : public std::exception
{
public:
    int code;
    NonFatalException(int c)
    {
        code = c;
    }
    
};
