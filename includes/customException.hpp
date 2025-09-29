#pragma once

#include <exception>
#include <string>

class ConfigException : public std::exception {
private:
    int code;
    std::string message;
    std::string cause;
    std::string nested_message;

public:
    // Constructeurs
    ConfigException(const std::string& msg, int c, const std::string& cause_msg = "");
    ConfigException(const std::string& msg, int c, const std::string& cause_msg, const std::string& nested_msg);

    // Destructeur virtuel (format canonique)
    virtual ~ConfigException() throw();

    // Méthodes
    const char* what() const throw();
    int get_code() const;
    const std::string& get_cause() const;
    const std::string& get_nested_message() const;

    // Interdiction de la copie (optionnel, selon tes besoins)
private:
//    ConfigException(const ConfigException&);
    ConfigException& operator=(const ConfigException&);
};
