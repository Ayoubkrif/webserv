#include "webserv.hpp"

int main(int argc, char **argv) {

	if (argc > 2) {
		return errorMessage(USAGE, 1);
	}

	std::string	configFile = argc == 2 ? argv[1] : DEFAULT_CONFIG;

	parseConfig();

	startServer();

	runServer();

	exitServer();

    return 0;
}
