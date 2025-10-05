#pragma once

#include <vector>
#include <string>

class Location {
	std::string _path;
    std::vector<std::string> _methods;
    //std::vector<std::string> _fileTypes;

	Location();

    public:

        Location(
				std::string& path, 
				std::vector<std::string> methods);
		Location(const Location& src);
        ~Location();

    Location operator=(const Location& src);
};
