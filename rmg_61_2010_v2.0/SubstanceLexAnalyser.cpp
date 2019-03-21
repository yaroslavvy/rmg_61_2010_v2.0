#include "pch.h"
#include "SubstanceLexAnalyser.h"

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
#include <set>

SubstanceLexAnalyser::SubstanceLexAnalyser() {}


SubstanceLexAnalyser::~SubstanceLexAnalyser() {}

const Element &SubstanceLexAnalyser::analyseElement(const std::string& str, const ElementDataBase& dB) {
	return dB.getElement(str);
}