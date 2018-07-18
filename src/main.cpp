#include <iostream>
#include <chrono>
#include <thread>

#include "server.h"
#include "client.h"

using namespace std;

void startServer( std::string& port)
{
    //server
    cout << "server started" << endl;
    Server server(port);
    while(1)
    {
        server.run();
    }
    cout << "server finished" << endl; //хотя сюда и не дойдет =)
}

void startClient(std::string& port, std::string& fileName)
{
    //client
    cout << "client started" << endl;
    Client client(port);
    client.readFile(fileName);
    client.run();
    cout << "client finished" << endl;
}

int main(int argc, char** argv) try
{
    if(argc < 3)
    {
        cout
                << "usage:  COM_CS <-s | -c>"
                << endl
                << "SERVER:\t" << "-s <portName>"
                << endl
                << "CLIENT:\t" << "-c <fileName> <portName>" << endl;
        return EXIT_FAILURE;
    }

    if( std::string(argv[1]) == "-s")
    {
        std::string srvPortName = argv[2];
        thread serverThread(startServer, std::ref(srvPortName));
        serverThread.join();
    }
    else if(std::string(argv[1]) == "-c")
    {
        std::string fileName = argv[2];

        std::string clPortName = argv[3];
        thread clientThread(startClient, std::ref(clPortName), std::ref(fileName));
        clientThread.join();
    }
    else
    {
        throw std::invalid_argument("Invalid arguments");
    }

    return EXIT_SUCCESS;
}
catch (std::exception& ex)
{
    cout << "Exception!:\t" << ex.what() << endl;
}
