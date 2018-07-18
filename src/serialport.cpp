#include <fcntl.h>
#include <sys/signal.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <exception>

#include "serialport.h"

SerialPort::SerialPort(const std::string& portName)
    : portName{},
      fd{-1}
{
    fd = open(portName.data(), O_RDWR | O_NOCTTY | O_NONBLOCK );
    if (fd < 0)
    {
        throw std::runtime_error("Port open error");
    }

    //Save port settings
    tcgetattr(fd, &oldtio);

    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;
    newtio.c_cc[VTIME]    = 1;
    newtio.c_cc[VMIN]     = 0;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &newtio);
}

void SerialPort::closePort()
{
    if(!isOpen())
        throw std::runtime_error ("Port is not opened!");

    //Restore old setting
    tcsetattr(fd, TCSANOW, &oldtio);
    close(fd);
}

bool SerialPort::isOpen() const
{
    return (fd != -1);
}

int SerialPort::readData(int maxTimeOut, std::string& resultString)
{
    char buf [MAXBUFLEN] = {};

    fds[0].fd = fd;
    fds[0].events = POLLIN;
    int pollrc = poll(fds, 1, maxTimeOut);
    if (pollrc < 0)
    {
        throw std::runtime_error("Polling error");
    }
    else if( pollrc > 0)
    {
        if( fds[0].revents & POLLIN )
        {
            memset(&buf, 0, MAXBUFLEN);
            int rc = read(fd, buf, sizeof(buf) );
            if (rc > 0)
            {
                buf[rc] =  '\0';
                resultString = buf;
                return rc;
            }
        }
    }

    //If nothing has been read
    return -1;
}

int SerialPort::writeData(const std::string& data)
{
    int res =  write(fd, data.data(), data.size());
    return res;
}

SerialPort::~SerialPort()
{
    if(isOpen())
        closePort();
}
