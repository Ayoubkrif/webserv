#include "webserv.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <ios>

// Try to open 'path' into 'out'. If the stream throws, translate to CustomException.
// C++98: enable stream exceptions temporarily so open() throws std::ios::failure.
static void tryOpenOrThrow(const std::string& path, std::ifstream& out) { 
    out.exceptions(std::ios::failbit | std::ios::badbit);
    try {
        if (path.substr(path.find_last_of(".") + 1) != CONF_EXTENSION) {
            throw CustomException(INVALID_CONFIG_EXTENSION, INVALID_CONFIG_EXTENSION_CODE);
        }
        out.open(path.c_str());
    } catch (const std::ios::failure& e) {
        out.clear();
        out.exceptions(std::ios::goodbit);
        throw CustomException(std::string(e.what()), OPEN_ERROR_CODE);
    }
    out.exceptions(std::ios::goodbit);
}

// Try opening primary; if it fails and allowFallback is true, try fallback.
// If both fail, throw a CustomException that contains both messages (nested).
static void openWithOptionalFallback(
        const std::string& primary,
        const std::string& fallback,
        std::ifstream& out,
        bool allowFallback) {
    try {
        tryOpenOrThrow(primary, out);
        return;
    } catch (const CustomException& primaryEx) {
        if (!allowFallback) {
            throw;
        }
		Logger::logMsg(WARNING, INVALID_CONFIG_FILE); 
		try {
			Logger::logMsg(INFO, LOADING_DEFAULT);
            tryOpenOrThrow(fallback, out);
            std::ostringstream oss;
            oss << DEFAULT_CONFIG_MESSAGE << fallback;
            Logger::logMsg(INFO, oss.str());
            return;
        } catch (const CustomException& fallbackEx) {
            throw CustomException::make_nested(primaryEx, fallbackEx);
        }
    }
}

static std::string parseStream(std::ifstream& configFile)
{
    Server server;
    std::string serverConfig, line;
    try {
        while (std::getline(configFile, line)) {
            if (*line.begin() == '#')
                continue ;
            serverConfig.append(line);
        }
        std::cout << serverConfig << std::endl;
/*
        server = parseServer(serverConfig);
        if (configFile.bad()) {
            throw CustomException(std::string(IO_CONFIG_ERROR), READ_ERROR_CODE);
        }
*/
    } catch (const std::ios::failure& e) {
        throw CustomException(std::string(e.what()), READ_ERROR_CODE);
    }
    return serverConfig;
}

/*
 * parseConfig :
 * - ouvre le fichier de configuration (essaie le fallback si autorisé),
 * - lance CustomException en cas d'erreur (avec messages imbriqués),
 * - retourne SUCCESS quand tout est OK.
 *
 * Signature: int parseConfig(const std::string& configFilePath, bool allowFallback)
 * Note: erreurs graves sont propagées via exceptions pour être traitées dans main.
 */
int parseConfig(const std::string& configFilePath, bool allowFallback)
{
    std::ifstream configFile;
    // Try to open primary or fallback (may throw CustomException)
	try {	
    	openWithOptionalFallback(configFilePath, DEFAULT_CONFIG, configFile, allowFallback);
        parseStream(configFile);
	} catch (const CustomException& e) {
		//Logger::logMsg("Failed to open config file: %s", CONSOLE_OUTPUT, e.what());
		throw;
	}
    // Parse the open stream (may throw CustomException)
//    parseStream(configFile);
    return SUCCESS;
}

/* INTUITION:

    After checking the config file extension, we try to open the primary config file.
    If it fails and fallback is not allowed, we throw the exception immediately.
    If fallback is allowed, we try to open the fallback config file.

    Then, we start parsing the opened config file line by line. If any I/O error occurs during reading,
    we throw a CustomException with the appropriate message.

    We create a std::string std::queue containing the different server blocks and their directives.
    We start by parsing the main server block, then we parse remaining server blocks one by one.
*/
