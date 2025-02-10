#ifndef CLIENT_HH
#define CLIENT_HH

#include <iostream>
#include <string>
#include <thread>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <chrono>

class Client {
    int sock;
    std::string address;
    int port;
    void reconnect(); // Вспомогательная функция переподключения
public:
    Client(const std::string& addr, int p);
    void send_data(const std::string& data);
};

#endif // CLIENT_HPP
