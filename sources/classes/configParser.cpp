#include "webserv.hpp"

ConfigParser::ConfigParser(std::vector<std::string>& configTokens) {
    _state = OUTSIDE;
    _content = configTokens;
}

ConfigParser::~ConfigParser() {
}

/*
// Vérifie si un token est un symbole de grammaire
static bool isGrammar(const std::string& token) {
    if (token.empty()) return false;
    char c = *token.begin();
    return (c == GRAMMAR_OPEN || c == GRAMMAR_CLOSE || c == GRAMMAR_STOP);
}
*/

// Extrait un bloc "server" du vecteur de tokens
std::vector<std::vector<std::string> > splitServerBlocks(const std::vector<std::string>& tokens) {
    std::vector<std::vector<std::string> > blocks;
    std::vector<std::string>::const_iterator it = tokens.begin();

    while (it != tokens.end()) {
        if (*it == "server") {
            std::vector<std::string> block;
            block.push_back(*it);  // Ajoute "server"
            ++it;
            if (it == tokens.end() || *it != "{") {
                throw CustomException("Expected '{' after 'server'", 1);
            }
            block.push_back(*it);  // Ajoute "{"
            ++it;

            int braceLevel = 1;
            while (it != tokens.end() && braceLevel > 0) {
                if (*it == "{") braceLevel++;
                else if (*it == "}") braceLevel--;
                block.push_back(*it);
                ++it;
            }

            if (braceLevel != 0) {
                throw CustomException("Unclosed server block", 1);
            }

            blocks.push_back(block);
        } else {
            ++it;
        }
    }

    return blocks;
}

// Parse un bloc "server" (vecteur de tokens) et retourne un objet Server
Server ConfigParser::parseServer(const std::vector<std::string>& block) {
	unsigned short port;
	std::string root, name;
    std::vector<std::string>::const_iterator it = block.begin();

    if (it == block.end() || *it != "server" || *(it + 1) != "{") {
        throw CustomException("Invalid server block", 1);
    }
    it += 2;  // Sauter "server" et "{"

    while (it != block.end() && *it != "}") {
        std::string directive = *it;
        ++it;

        if (directive == "listen") {
            if (it == block.end())
				throw CustomException("Missing port after 'listen'", 1);
            port = atoi((*it).c_str());
            ++it;
        } else if (directive == "root") {
            if (it == block.end())
				throw CustomException("Missing path after 'root'", 1);
			root = *it;
            ++it;
        } else if (directive == "server_name") {
            if (it == block.end())
				throw CustomException("Missing name after 'server_name'", 1);
            name = *it;
            ++it;
        }
        // Ajouter d'autres directives ici
    }
	Server server(port, name, root);
    return server;
}

// Parse tous les blocs "server" et retourne un vecteur de serveurs
std::vector<Server> ConfigParser::parse() {
    std::vector<std::vector<std::string> > serverBlocks = splitServerBlocks(_content);
    std::vector<Server> servers;

    for (std::vector<std::vector<std::string> >::const_iterator it = serverBlocks.begin();
         it != serverBlocks.end(); ++it) {
        servers.push_back(parseServer(*it));
    }

    std::cout << "Parsed " << servers.size() << " servers" << std::endl;
    return servers;
}
