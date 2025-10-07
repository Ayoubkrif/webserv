#pragma once

#include <string>
#include <vector>
#include <map>
#include "server.hpp"
#include "location.hpp"
#include "errors.hpp"

class ConfigParser {

	std::vector<std::string> _content;
    void tokenize(const std::string &content);

    ConfigParser();
    ConfigParser operator=(const ConfigParser& src);

    public:

        ConfigParser(std::vector<std::string>& configFileContent);
        ~ConfigParser();

        std::vector<Server> parse();

		Server parseServer(const std::vector<std::string>& block);
};
