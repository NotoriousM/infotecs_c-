#include "Buffer.hh"

void Buffer::push(const std::string& data) {
    std::lock_guard<std::mutex> lock(mutex);
    buffer.push(data);
    check.notify_one();
}

std::string Buffer::pop() {
    std::unique_lock<std::mutex> lock(mutex);
    check.wait(lock, [this]{ return !buffer.empty(); });
    std::string data = buffer.front();
    buffer.pop();
    return data;
}
