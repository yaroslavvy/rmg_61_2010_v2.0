#include "pch.h"
#include "Service.h"

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

Service::Service() {}

Service::~Service() {}

void Service::writeInFile(const std::string &fileName, const std::vector<PrintableObject*> &vec) {
	std::ofstream fout;
	fout.open(fileName);
	std::for_each(vec.begin(), vec.end(), std::bind2nd(std::mem_fun(&PrintableObject::write), &fout));
	fout.close();
}