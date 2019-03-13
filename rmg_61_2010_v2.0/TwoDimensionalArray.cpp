#include "pch.h"

#include "TwoDimensionalArray.h"

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

TwoDimensionalArray::TwoDimensionalArray(const std::string& fout) {
	readFromFile(fout);
}

TwoDimensionalArray::TwoDimensionalArray(const TwoDimensionalArray& a)
	: vec(a.vec) {}

TwoDimensionalArray::~TwoDimensionalArray() {}

const std::vector<std::vector<std::string>>& TwoDimensionalArray::getVector() const {
	return vec;
}

void TwoDimensionalArray::write(std::ofstream* fout) const {
	std::vector <std::vector<std::string>>::const_iterator row;
	std::vector<std::string>::const_iterator column;
	for (row = vec.begin(); row < vec.end(); row++) {
		for (column = row->begin(); column < row->end(); column++) {
			(*fout) << (*column);
			if (column < ((row->end()) - 1)) {
				(*fout) << ";";
			}
			else {
				(*fout) << "\n";
			}
		}
	}
}

bool TwoDimensionalArray::readFromFile(const std::string& fileName) {
	vec.clear();
	std::ifstream fin;
	fin.open(fileName);
	if (!fin.is_open()) {
		std::cout << std::endl << "File can not be opened!" << std::endl;
		return false;
	}
	std::string line;
	std::string cell;
	std::string::const_iterator iter;
	std::vector<std::string> row;
	while (fin.eof() == 0) {
		line.clear();
		std::getline(fin, line);
		for (iter = line.begin(); iter < line.end(); iter++) {
			if ((*iter) != ';') {
				cell += (*iter);
			}
			else {
				row.push_back(cell);
				cell.clear();
			}
		}
		row.push_back(cell);
		cell.clear();
		vec.push_back(row);
		row.clear();
	}
	fin.close();
	return true;
}