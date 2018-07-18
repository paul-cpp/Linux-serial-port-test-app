#ifndef CLIENT_H
#define CLIENT_H

#include <memory>

#include "serialport.h"

class Client
{
public:
    Client(std::string& portName);
    void run();
    void readFile(std::string& fileName);

    ~Client();

private:
    std::unique_ptr<SerialPort> port;

    //It is assumed that the file is small for loading into RAM
    std::string fileContent;

};

#endif // CLIENT_H
