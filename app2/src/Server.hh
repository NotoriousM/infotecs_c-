#ifndef SERVER_HPP
#define SERVER_HPP

class Server {
    int sockfd;
    int port;

public:
    Server(int p);
    void start();
};

#endif
