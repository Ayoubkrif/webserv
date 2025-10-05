#include "webserv.hpp"

ConfigParser::ConfigParser(std::vector<std::string>& configTokens) {
    _state = OUTSIDE;
    _content = configTokens;
}

ConfigParser::~ConfigParser() {
}
/*
static inline bool checkPath(std::string path) {
	try {
		
	} catch {

		return false;
	}
	return true;
}
*/

// Extrait un bloc "server" du vecteur de tokens
std::vector<std::vector<std::string> > splitServerBlocks(const std::vector<std::string>& tokens) {
    std::vector<std::vector<std::string> > blocks;
    std::vector<std::string>::const_iterator it = tokens.begin();

    while (it != tokens.end()) {
        if (*it == "server") {
            std::vector<std::string> block;
            block.push_back(*it);
            ++it;
            if (it == tokens.end() || *it != "{") {
                throw CustomException("Expected '{' after 'server'", 1);
            }
            block.push_back(*it);
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

Location parseLocation(const std::vector<std::string>& locationBlock) {
	std::string path, root;
	std::vector<std::string> methods;
    std::vector<std::string>::const_iterator it = locationBlock.begin();

    if (it == locationBlock.end()) {
        throw CustomException("Empty location block", 1);
    }
    path = *it;
    ++it;
    if (it == locationBlock.end() || *it != "{") {
        throw CustomException("Expected '{' after location path", 1);
    }
    ++it;
    while (it != locationBlock.end() && *it != "}") {
        std::string directive = *it;
        ++it;
        if (directive == "root") {
            if (it == locationBlock.end()) {
                throw CustomException("Missing path after 'root' in location", 1);
            }
            root = *it;
            ++it;
        } else if (directive == "allow_methods") {
            while (it != locationBlock.end() && *it != ";" && *it != "}") {
                methods.push_back(*it);
                ++it;
            }
            if (it != locationBlock.end() && *it == ";") {
                ++it;
            }
        }
		// Additional missing directives here -> autoindex, index
    }
	Location location(path, methods);
//	location.print();
    return location;
}

std::vector<std::string> extractLocationBlock(
    std::vector<std::string>::const_iterator& it,
    const std::vector<std::string>::const_iterator& end) {
    std::vector<std::string> locationBlock;
    if (it == end) {
        throw CustomException("Expected 'location' keyword", 1);
    }
    if (it == end || it->empty() || (*it)[0] != '/') {
        throw CustomException("Expected path (starting with '/') after 'location'", 1);
    }
    locationBlock.push_back(*it);
    ++it;
    if (it == end || *it != "{") {
        throw CustomException("Expected '{' after location path", 1);
    }
    locationBlock.push_back(*it);
    ++it;
    int braceLevel = 1;
    while (it != end && braceLevel > 0) {
        const std::string& token = *it;
        if (token == "{") {
            braceLevel++;
        } else if (token == "}") {
            braceLevel--;
        }
        locationBlock.push_back(token);
        ++it;
    }
    if (braceLevel != 0) {
        throw CustomException("Unclosed location block", 1);
    }
    return locationBlock;
}


// Parse un bloc "server" (vecteur de tokens) et retourne un objet Server
Server ConfigParser::parseServer(const std::vector<std::string>& block) {
	unsigned short port;
	std::string root, name;
	std::vector<Location> locations;
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
        } else if (directive == "location") {
			std::vector<std::string> locationBlock = extractLocationBlock(it, block.end());
			Location location = parseLocation(locationBlock);
			locations.push_back(location);
		}
        // Ajouter d'autres directives ici
    }
	Server server(port, name, root, locations);
    return server;
}

// Parse tous les blocs "server" et retourne un vecteur de serveurs
std::vector<Server> ConfigParser::parse() {
    std::vector<Server> servers;
    std::vector<std::vector<std::string> > serverBlocks = splitServerBlocks(_content);
	std::vector<std::vector<std::string> >::const_iterator it = serverBlocks.begin();

    for ( ;it != serverBlocks.end(); ++it) {
		Server tmp = parseServer(*it);
        //servers.push_back(parseServer(*it));
        servers.push_back(tmp);

	//	std::cout << "[DEBUG] Server has " << tmp._locations.size() << " locations" << std::endl;
    }
    return servers;
}
