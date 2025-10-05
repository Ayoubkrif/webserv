#include "webserv.hpp"

Location::Location() {
}

Location::Location(
		std::string& path,
		std::vector<std::string> methods) {
	_path = path;
	_methods = methods;
}

Location::~Location() {
}

Location::Location(const Location& src) {
	_path = src._path;
	_methods = src._methods;
}

Location Location::operator=(const Location& src) {
	(void)src;
	return *this;
}
