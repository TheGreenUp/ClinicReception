#pragma once
#include <exception>

class MyException : public std::exception {
private:
    int dataState;
public:
    MyException(const char* msg, int dataState) : std::exception(msg) {
        this->dataState = dataState;
    }
    int getDataState() { 
        return dataState; 
    }
};

