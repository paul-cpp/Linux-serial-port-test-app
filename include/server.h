#ifndef SERVER_H
#define SERVER_H

#include <memory>

#include "serialport.h"

class Server
{
public:
    explicit Server(const std::string& portName);
    void run();

    ~Server();
private:
    void saveFile();

    std::unique_ptr<SerialPort> port;
    std::string fileContent;
};

#endif // SERVER_H
