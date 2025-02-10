#include "Server.hh"

int main() {
    Server server(8080);
    server.start();
    return 0;
}