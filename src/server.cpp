#include <iostream>
#include <fstream>
#include <cstdio>

#include "server.h"

Server::Server(const std::string& portName)
    : port{nullptr}, fileContent{}
{
    port = std::make_unique<SerialPort> (portName);
}

void Server::run()
{
    fileContent.clear();
    int bytesRead = port.get()->readData(-1, fileContent);
    if(bytesRead > 0)
    {
        saveFile();
    }
}

void Server::saveFile()
{
    if(fileContent.empty())
        throw std::runtime_error("File name cannot be empty");

    char buffer[50] = {};
    time_t t = time(nullptr);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%d-%d-%d %d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1,
            tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    std::string fileName = buffer;
    fileName += ".hex";

    std::ofstream file(fileName);
    if(!file.is_open())
        throw std::runtime_error("Cannot open file for saving");
    file << fileContent;
    file.close();

    std::cout << "file " << fileName << " written" << std::endl;
}

Server::~Server()
{

}
