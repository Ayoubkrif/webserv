#include "webserv.hpp"
/*


ConfigParser::ConfigParser(std::vector<std::string>& configFileContent) {
    _state = OUTSIDE;
    _content = configFileContent;
}

ConfigParser::~ConfigParser() {

}

static inline void extractToken(std::stringstream& ss, std::string& token) {
	ss >> token;
}

// LOCATION -> path -> GRAMMAR_OPEN -> METHODS -> * -> GRAMMAR_CLOSE
void parseLocation() {

}


void parseDirectives() {

}

bool isGrammar(std::string token) {
	char c = *token.begin();
	return (c == GRAMMAR_OPEN || c == GRAMMAR_CLOSE || c == GRAMMAR_STOP);
}
*/

/*
// SERVER -> GRAMMAR_OPEN -> * {DIRECTIVE | LOCATION} -> GRAMMAR_CLOSE
void parseServer(std::stringstream& ss) {
	(void)ss;
	std::string token;
	extractToken(ss, token);
	if (!isGrammar(token)) {
		throw CustomException("Invalid token: expected { after server", 1);
		std::cout << "ERROR" << std::endl;
	}
	extractToken(ss, token);
	while (!isGrammar(token)) {
		std::cout << token << std::endl;
		extractToken(ss, token);
	}
}
*/
/*
// SERVER -> GRAMMAR_OPEN -> * {DIRECTIVE | LOCATION} -> GRAMMAR_CLOSE
Server parseServer(std::string config) {
	Server	parsed;
	while (config) {

	}
	return parsed;
}
*/
/*
std::vector<std::string> splitServerBlocks(const std::vector<std::string>& content) {
    int brace_level = 0;
    std::vector<std::string> blocks;
    size_t start = 0, open_brace = 0, close_brace = 0;

    while (start < content.size()) {
        start = content.find("server", start);
        if (start == std::string::npos)
			break;
        open_brace = content.find('{', start);
        if (open_brace == std::string::npos)
			break;
        brace_level = 1;
        close_brace = open_brace + 1;
        while (close_brace < content.size() && brace_level > 0) {
            if (content[close_brace] == '{')
				brace_level++;
            else if (content[close_brace] == '}')
				brace_level--;
            close_brace++;
        }
        if (brace_level != 0)
			break;
        std::string block = content.substr(start, close_brace - start);
        blocks.push_back(block);
        start = close_brace;
    }
    return blocks;
}

std::vector<Server> ConfigParser::parse() {
    std::vector<Server> servers;
//	std::stringstream ss(_content);
	std::vector<std::string> serverBlocks;

	serverBlocks = splitServerBlocks(_content);
	std::vector<std::string>::iterator it = serverBlocks.begin();
	for ( ; it != serverBlocks.end(); it++) {
		servers.push_back(parseServer(*it));
	} 

	std::cout << "Parsed " << serverBlocks.size() << " servers" << std::endl;

    return servers;
}
*/
/*	INTUITION
 *
 *	Using an FSM with 4 differente states:
 *
 *		->	OUTSIDE			-	Next token must be a server token 
 *		->	IN_SERVER		-	We're parsing a server, can trasition to state IN_LOCATION
 *		->	IN_LOCATION		-	Must start with a LOCATION token
 *		->	IN_DIRECTIVE	-	.
 *
 *	We must make sure brackets are opened && closed
 *	Certain informations have to be present to get a valid server config (ip, port, adress)
 *	Some tokens need to fit boundaries (port >= 0 && <= 6535)
 *	*/
