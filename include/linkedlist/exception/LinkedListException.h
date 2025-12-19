#pragma once
#include <stdexcept>
#include <string>

class LinkedListException : public std::exception {
    private:
        std::string message;
    public:
        explicit LinkedListException(const std::string &message) : message(message) {}
        const char* what() const noexcept override {
            return message.c_str();
        }
};

class EmptyListException : public LinkedListException {
    public:
        explicit EmptyListException (const std::string &message) : LinkedListException(message){}
};

class IndexOutOfRangeException : public LinkedListException {
    public:
        explicit IndexOutOfRangeException (const std::string &message) : LinkedListException(message) {}
};