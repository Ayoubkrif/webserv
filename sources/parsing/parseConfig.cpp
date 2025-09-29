#include "webserv.hpp"

// We start by opening the configuration file, or a default one if the specified one cannot be opened
std::ifstream openConfigFile(const std::string& configFilePath, bool fallback) {

    std::ifstream configFile;

    try {

        configFile.open(configFilePath);

        if (!configFile.is_open()) {
            throw std::runtime_error(OPEN_ERROR + configFilePath);
        }
        
		return configFile;	


    } catch (const std::exception& e) {

        std::cerr << e.what() << std::endl;

        if (fallback) {
            errorMessage(OPEN_ERROR, OPEN_ERROR_CODE);
			return std::ifstream();
        }

        // Essaye le fichier par défaut
        return openConfigFile(DEFAULT_CONFIG, true);
    }
    return SUCCESS;
}



int	parseConfig(std::string configFilePath) {

	std::ifstream configFile = openConfigFile(configFilePath, 2 - argc);
	
	if (!configFile) {
		return ERROR;
	}

	

	return SUCCESS;
}
