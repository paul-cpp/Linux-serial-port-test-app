#include <exception>
#include <iostream>
#include <fstream>
#include <string>

#include "client.h"

Client::Client(std::string& portName)
    : port{nullptr},
      fileContent{}
{
    port = std::make_unique<SerialPort> (portName);
}

void Client::run()
{
    int bytesWritten = port.get()->writeData(fileContent);
    if(bytesWritten > 0)
        std::cout << bytesWritten << " bytes written" << std::endl;
}

void Client::readFile(std::string& fileName)
{
    if(fileName.empty())
        throw std::runtime_error("File name cannot be empty");

    //это быстро
    fileContent.clear();
    std::ifstream f(fileName);
    f.seekg(0, std::ios::end);
    size_t size = f.tellg();

    fileContent.resize(size, ' ');
    f.seekg(0);
    f.read(&fileContent[0], size);
}

Client::~Client()
{

}
