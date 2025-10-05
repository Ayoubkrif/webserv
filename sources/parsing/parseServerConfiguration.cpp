#include "webserv.hpp"

/*
void parseLocation() {

}
*/
/*
Server parseServer(std::string serverConfig) {
    Server server;
    size_t end, start = serverConfig.find(SERVER_KEYWORD);
    try {
        if (start != 0) {
            //Logger::logMsg(ERROR, INVALID_CONFIG_FORMAT);     
            throw CustomException("Invalid config format: expected 'server' at start", PARSING_ERROR);
            }
        start = serverConfig.find_first_of("{", start);
        end = serverConfig.find_first_of("}", start);
        
        std::cout << "Server's config:\n" + serverConfig.substr(start, end) << std::endl;
        
    } catch (const CustomException& e) {
        Logger::logMsg(ERROR, e.what());
    }
	return server;
}
*/
/*
void parseServerConfiguration() {

    std::vector<std::string> serverConfigs;
    std::vector<Server> servers;
    std::string::iterator start;

    while () {
        std::string server;

        serverConfigs.push_back(server);
    }
}
*/
