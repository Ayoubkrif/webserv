/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuistobal <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:43:59 by cuistobal         #+#    #+#             */
/*   Updated: 2025/10/05 10:11:00 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int main(int argc, char **argv) {

	Logger	logger;

	if (argc > 2) {
		logger.logMsg(ERROR, USAGE);
		return USAGE_CODE;
	}
	// If no parameter was passed, we apply the default config && disable the fallback strategy
	std::string configFile = argc == 2 ? argv[1] : DEFAULT_CONFIG;	
	bool allowFallback = (argc == 2);
	std::vector<std::string> configFileContent;
    std::vector<Server> servers;
	try {
		configFileContent = parseConfig(configFile, allowFallback);

/*
		std::vector<std::string>::iterator it = configFileContent.begin();
	
		for (; it < configFileContent.end(); it++) {
			std::cout << *it << std::endl; 
		}
*/
        ConfigParser configParser(configFileContent);
        servers = configParser.parse();
        
		startServer();
/*
		runServer();
	
		exitServer();
*/

	} catch (const CustomException& e) {
		// Build a single-line message using e.what() and nested message if any
		std::string msg = std::string(e.what());
		if (!e.get_nested_message().empty()) {
			msg += " ";
			msg += e.get_nested_message();
		}
		return errorMessage(msg.c_str(), e.get_code());
	} catch (const std::exception& e) {
		// Temp catch
		return errorMessage(e.what(), OPEN_ERROR_CODE);
	}
	
	return SUCCESS;
}
