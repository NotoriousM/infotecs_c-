#ifndef BUFFER_HH
#define BUFFER_HH

#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>

class Buffer {
    std::mutex mutex;
    std::condition_variable check;
    std::queue<std::string> buffer;
public:
    void push(const std::string& data);
    std::string pop();
};

#endif // BUFFER_HPP
