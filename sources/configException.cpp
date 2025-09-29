#include "customException.hpp"
#include <exception>
#include <string>

// Constructeur de base
ConfigException::ConfigException(const std::string& msg, int c, const std::string& cause_msg)
    : code(c), message(msg), cause(cause_msg) {}

// Constructeur avec message imbriqué
ConfigException::ConfigException(const std::string& msg, int c, const std::string& cause_msg, const std::string& nested_msg)
    : code(c), message(msg), cause(cause_msg), nested_message(nested_msg) {}

// Destructeur
ConfigException::~ConfigException() throw() {}

// what() compatible C++98
const char* ConfigException::what() const throw() {
    static std::string full_msg;
    full_msg = message;
    if (!cause.empty()) {
        full_msg += " (cause: " + cause + ")";
    }
    if (!nested_message.empty() && nested_message != "std::exception") {
        full_msg += " [nested: " + nested_message + "]";
    }
    return full_msg.c_str();
}

// Getters
int ConfigException::get_code() const {
    return code;
}

const std::string& ConfigException::get_cause() const {
    return cause;
}

const std::string& ConfigException::get_nested_message() const {
    return nested_message;
}
