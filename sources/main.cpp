#include "webserv.hpp"

int main(int argc, char **argv) {

	if (argc > 2) {
		return errorMessage(USAGE, 1);
	}

	std::string	configFile = argc == 2 ? argv[1] : DEFAULT_CONFIG;

	// 2 - argc -> fallback strategy already set since we're using DEFAULT_CONFIG
	parseConfig(configFilePath, 2 - argc);

	startServer();

	runServer();

	exitServer();

    return 0;
}
