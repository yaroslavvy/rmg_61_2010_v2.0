#include "pch.h"
#include "ParserException.h"

#include <windows.h>
#include <iostream>
#include <clocale>
#include <cstdlib>
#include <cmath>
#include <stdarg.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <sstream>
#include <cctype>

ParserException::ParserException(const std::string &errDescription, const std::string &wrStr)
	:error(errDescription), wrongString(wrStr) {}

ParserException::ParserException(const ParserException &a)
	:error(a.whatError()), wrongString(a.whatWrongString()) {}

ParserException::~ParserException() {}

const std::string &ParserException::whatError() const {
	return error;
}

const std::string &ParserException::whatWrongString() const {
	return wrongString;
}