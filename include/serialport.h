#ifndef SERIALPORT_H
#define SERIALPORT_H
#include <string>
#include <iostream>

#include <termios.h>
#include <sys/poll.h>

#define BAUDRATE B115200
#define _POSIX_SOURCE 1

static const size_t MAXBUFLEN = 2048;

class SerialPort
{
public:
    explicit SerialPort(const std::string& portName);
    void closePort();
    bool isOpen() const;

    /**
     * @brief readData      - waits and reads data from the serial port
     * @param maxTimeOut    - maximum wait timeout
     * @param [out] resultString  - string with read results
     * @return on success: number of bytes read, on failure: -1
     */
    int readData(int maxTimeOut, std::string& resultString);
    int writeData(const std::string& data);

    ~SerialPort();

private:
    std::string portName;

    // Serial port descriptor
    int fd;
    //Additional structures
    struct termios oldtio, newtio;
    struct pollfd fds[1];
};

#endif // SERIALPORT_H
