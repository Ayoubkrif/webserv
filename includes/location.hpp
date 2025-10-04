#pragma once

#include <vector>
#include <string>

class location {
    std::vector<std::string> paths;

    public:

        location();
        ~location();

        operator=(const Location& src);
};
