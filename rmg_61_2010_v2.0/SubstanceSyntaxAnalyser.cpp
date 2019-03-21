#include "pch.h"
#include "SubstanceSyntaxAnalyser.h"

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

SubstanceSyntaxAnalyser::SubstanceSyntaxAnalyser() {}


SubstanceSyntaxAnalyser::~SubstanceSyntaxAnalyser() {}

bool SubstanceSyntaxAnalyser::isValidString(const std::string& str) {
	return str.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789()[]*") == std::string::npos;
//std::isalnum get the Runtime Library Error with cyrilic	
}

const MixtureOfComponents SubstanceSyntaxAnalyser::analyseMixtureOfComponents(const std::string &str, const ElementDataBase &dB) {
	if (!isValidString(str)) {
		throw ParserException(" includes not valid characters!\nOnly ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789()[]* could be in analyzed string\n", str);
	}
	if (!isAllBracketsClosed(str)) {
		throw ParserException(" has wrong brackets!\n ", str);
	}
	std::vector<std::string> individualSubstancesVec;
	individualSubstancesVec = starAndBracketsAnalyser(str);
	std::map<std::string, int> individualSubstancesMap;
	for (std::vector<std::string>::const_iterator i = individualSubstancesVec.begin(); i < individualSubstancesVec.end(); i++) {
		indexMapInsert<std::string>(&individualSubstancesMap, *i);
	}
	IndividualSubstanceComponent indComp;
	MixtureOfComponents resultMixture;
	for (std::map<std::string, int>::const_iterator i = individualSubstancesMap.begin(); i != individualSubstancesMap.end(); i++) {
		indComp = analyseIndividualSubstanceComponent(i->first, dB);
		for (int a = 0; a < (i->second); a++) {
			resultMixture.getVector().push_back(indComp);
		}
	}
	return resultMixture;
}

bool SubstanceSyntaxAnalyser::isAllBracketsClosed(const std::string &str) {
	int amountOfRoundBrackets = 0;
	int amountOfSquareBrackets = 0;
	for (std::string::const_iterator i = str.begin(); i < str.end(); i++) {
		if (*i == '(') {
			amountOfRoundBrackets++;
			continue;
		}
		if (*i == ')') {
			amountOfRoundBrackets--;
			continue;
		}
		if (*i == '[') {
			amountOfSquareBrackets++;
			continue;
		}
		if (*i == ']') {
			amountOfSquareBrackets--;
			continue;
		}
	}
	return (amountOfRoundBrackets == 0) && (amountOfSquareBrackets == 0);
}

std::vector<std::string> SubstanceSyntaxAnalyser::starAndBracketsAnalyser(const std::string &str) { //vector should be changed to map
	std::vector<std::string> vec;
	if (std::count(str.begin(), str.end(), '*') == 0) {
		vec.push_back(str);
		return vec;
	}
	else {
		std::string subString1;
		std::string subString2;

		std::string::const_iterator i = std::find(str.begin(), str.end(), '*');
		std::copy(str.cbegin(), i, std::back_inserter(subString1));
		std::copy((i + 1), str.cend(), std::back_inserter(subString2));
		if (subString1.empty() || subString2.empty()) {
			throw ParserException(" has wrong stars '*' !\n ", str);
		}
		if (isAllBracketsClosed(subString1) && isAllBracketsClosed(subString2) && (std::find(subString2.begin(), subString2.end(), '*') == subString2.end())) {
			vec.push_back(subString1);
			vec.push_back(subString2);
			return vec;
		}
		if (isAllBracketsClosed(subString1) && isAllBracketsClosed(subString2) && (std::find(subString2.begin(), subString2.end(), '*') != subString2.end())) {
			vec.push_back(subString1);
			std::vector<std::string> tmpVector;
			tmpVector = starAndBracketsAnalyser(subString2);
			std::copy(tmpVector.begin(), tmpVector.end(), std::back_inserter(vec));
			return vec;
		}
		
		std::string coefficient;
		std::string index;
		int coef = 1;
		int ind = 1;
		for (std::string::const_iterator i = str.begin(); i < str.end(); i++) {
			if (!std::isdigit(*i)) {
				if (*i == '(') {
					for (std::string::const_iterator y = (str.end() - 1); y > (str.begin() - 1); y--) {
						if (!std::isdigit(*y)) {
							if (*y == ')') {
								subString1.clear();
								std::copy((i + 1), y, std::back_inserter(subString1));
								if (subString1.empty()) {
									throw ParserException(" has empty brackets!\n ", str);
								}
								if (coefficient.empty()) {
									coef = 1;
								}
								else {
									if (Service::isIntegerFromString(coefficient)) {
										coef = std::stoi(coefficient);
									}
									else {
										throw ParserException(" can't be interpreted as coefficient!\n ", coefficient);
									}
								}
								std::reverse(index.begin(), index.end());
								if (index.empty()) {
									ind = 1;
								}
								else {
									if (Service::isIntegerFromString(index)) {
										ind = std::stoi(index);
									}
									else {
										throw ParserException(" can't be interpreted as index!\n ", index);
									}
								}
								subString2.clear();
								subString2 = subString1;
								for (int h = 1; h < (ind*coef); h++) {
									subString2 += "*";
									subString2 += subString1;
								}
								return starAndBracketsAnalyser(subString2);
							}
						}
						index += *y;
					}
				}
				if (*i == '[') {
					for (std::string::const_iterator y = (str.end() - 1); y > (str.begin() - 1); y--) {
						if (!std::isdigit(*y)) {
							if (*y == ']') {
								subString1.clear();
								std::copy((i + 1), y, std::back_inserter(subString1));
								if (subString1.empty()) {
									throw ParserException(" has empty brackets!\n ", str);
								}
								if (coefficient.empty()) {
									coef = 1;
								}
								else {
									if (Service::isIntegerFromString(coefficient)) {
										coef = std::stoi(coefficient);
									}
									else {
										throw ParserException(" can't be interpreted as coefficient!\n ", coefficient);
									}
								}
								std::reverse(index.begin(), index.end());
								if (index.empty()) {
									ind = 1;
								}
								else {
									if (Service::isIntegerFromString(index)) {
										ind = std::stoi(index);
									}
									else {
										throw ParserException(" can't be interpreted as index!\n ", index);
									}
								}
								subString2.clear();
								subString2 = subString1;
								for (int h = 1; h < (ind*coef); h++) {
									subString2 += "*";
									subString2 += subString1;
								}
								return starAndBracketsAnalyser(subString2);
							}
						}
						index += *y;
					}
				}
				else {
					throw ParserException(" has wrong brackets!\n ", str);
				}
			}
			coefficient += *i;
		}
	}	
}

const IndividualSubstanceComponent SubstanceSyntaxAnalyser::analyseIndividualSubstanceComponent(const std::string &str, const ElementDataBase &dB) {
	if (!isAllBracketsClosed(str)) {
		throw ParserException(" has wrong brackets!\n ", str);
	}
	IndividualSubstanceComponent indComp;
	std::string subStr1;
	std::string subStr2;
	bool statePureElements = true;
	for (std::string::const_iterator i = str.begin(); i < str.end(); i++) {
		if (!std::isalpha(*i)) {
			statePureElements = false;
			break;
		}
	}
	if (statePureElements == true) {
		for (std::string::const_iterator i = str.begin(); i < str.end(); i++) {
			if (std::isupper(*i)) {
				for (std::string::const_iterator a = (i + 1); a < str.end(); a++) {
					if (std::isupper(*a)) {
						subStr1.clear();
						subStr2.clear();
						std::copy(i, a, std::back_inserter(subStr1));
						std::copy(a, str.cend(), std::back_inserter(subStr2));
						indComp.getVector().push_back(SubstanceLexAnalyser::analyseElement(subStr1, dB));
						return (indComp += analyseIndividualSubstanceComponent(subStr2, dB));
					}
				}
				subStr1.clear();
				std::copy(i, str.end(), std::back_inserter(subStr1));
				indComp.getVector().push_back(SubstanceLexAnalyser::analyseElement(subStr1, dB));
				return indComp;
			}
		}
	}
	int coefficient = 1;
	for (std::string::const_iterator i = str.begin(); i < str.end(); i++) {
		if (std::isupper(*i) || (*i == '(') || (*i == '[')) {
			subStr1.clear();
			subStr2.clear();
			std::copy(str.cbegin(), i, std::back_inserter(subStr1));
			std::copy(i, str.cend(), std::back_inserter(subStr2));
			if (subStr1.empty()) {
				break;
			}
			if (!Service::isIntegerFromString(subStr1)) {
				throw ParserException(" can't be interpreted as coefficient!\n ", subStr1);
			}
			coefficient = std::stoi(subStr1);
			break;
		}
	}
	subStr1.clear();
	for (int i = 0; i < coefficient; i++) {
		subStr1 += subStr2;
	}
	bool presenceDigits = false;
	for (std::string::const_iterator p = subStr1.begin(); p < subStr1.end(); p++) {
		if (std::isdigit(*p)) {
			presenceDigits = true;
			break;
		}
	}
	if (!presenceDigits) {
		return (indComp += analyseIndividualSubstanceComponent(subStr1, dB));
	}
	int index = 1;
	std::string tmpLastElement;
	std::string subStr3;
	if ((std::count(subStr1.begin(), subStr1.end(), '(') == 0) && (std::count(subStr1.begin(), subStr1.end(), '[') == 0)) {
		for (std::string::const_iterator i = subStr1.begin(); i < subStr1.end(); i++) {
			if (std::isupper(*i)) {
				tmpLastElement.clear();
				tmpLastElement += (*i);
			}
			if (std::islower(*i)) {
				tmpLastElement += (*i);
			}
			if (std::isdigit(*i)) {
				for (std::string::const_iterator a = i + 1; a < subStr1.end(); a++) {
					if (!std::isdigit(*a)) {
						subStr2.clear();
						std::copy(i, a, std::back_inserter(subStr2));
						if (!Service::isIntegerFromString(subStr2)) {
							throw ParserException(" can't be interpreted as an index!\n ", subStr2);
						}
						index = std::stoi(subStr2);
						if (index < 1) {
							throw ParserException(" index can't be less than 1!\n ", std::to_string(index));
						}
						subStr3.clear();
						std::copy(subStr1.cbegin(), i, std::back_inserter(subStr3));
						std::copy(a, subStr1.cend(), std::back_inserter(subStr3));
						while (index > 1) {
							subStr3 += tmpLastElement;
							index--;
						}
						return (indComp += analyseIndividualSubstanceComponent(subStr3, dB));
					}
				}
				subStr2.clear();
				std::copy(i, subStr1.cend(), std::back_inserter(subStr2));
				if (!Service::isIntegerFromString(subStr2)) {
					throw ParserException(" can't be interpreted as an index!\n ", subStr2);
				}
				index = std::stoi(subStr2);
				if (index < 1) {
					throw ParserException(" index can't be less than 1!\n ", std::to_string(index));
				}
				subStr3.clear();
				std::copy(subStr1.cbegin(), i, std::back_inserter(subStr3));
				while (index > 1) {
					subStr3 += tmpLastElement;
					index--;
				}
				return (indComp += analyseIndividualSubstanceComponent(subStr3, dB));
			}
		}
	}
	bool firstBracket = false;
	index = 1;
	std::string::const_iterator frstBrckt;
	for (std::string::const_iterator j = subStr1.begin(); j < subStr1.end(); j++) {
		if (firstBracket) {
			subStr2.clear();
			subStr3.clear();
			std::copy(subStr1.cbegin(), j, std::back_inserter(subStr2));
			std::copy(j, subStr1.cend(), std::back_inserter(subStr3));
			if (isAllBracketsClosed(subStr2) && isAllBracketsClosed(subStr2)) {
				if (std::isdigit(*j)) {
					if (j == (subStr1.end() - 1)) {
						subStr3.clear();
						std::copy(j, subStr1.cend(), std::back_inserter(subStr3));
						if (!Service::isIntegerFromString(subStr3)) {
							throw ParserException(" can't be interpreted as an index!\n ", subStr3);
						}
						index = std::stoi(subStr3);
						if (index < 1) {
							throw ParserException(" index can't be less than 1!\n ", std::to_string(index));
						}
						subStr3.clear();
						std::copy(subStr1.cbegin(), frstBrckt, std::back_inserter(subStr3));
						subStr2.clear();
						std::copy((frstBrckt + 1), (j - 1), std::back_inserter(subStr2));
						while (index > 0) {
							subStr3 += subStr2;
							index--;
						}
						return (indComp += analyseIndividualSubstanceComponent(subStr3, dB));
					}
					for (std::string::const_iterator a = j + 1; a < subStr1.end(); a++) {
						if (!std::isdigit(*a)) {
							subStr3.clear();
							std::copy(j, a, std::back_inserter(subStr3));
							if (!Service::isIntegerFromString(subStr3)) {
								throw ParserException(" can't be interpreted as an index!\n ", subStr3);
							}
							index = std::stoi(subStr3);
							if (index < 1) {
								throw ParserException(" index can't be less than 1!\n ", std::to_string(index));
							}
							subStr3.clear();
							std::copy(subStr1.cbegin(), frstBrckt, std::back_inserter(subStr3));
							std::copy(a, subStr1.cend(), std::back_inserter(subStr3));
							subStr2.clear();
							std::copy((frstBrckt + 1), (j - 1), std::back_inserter(subStr2));
							while (index > 0) {
								subStr3 += subStr2;
								index--;
							}
							return (indComp += analyseIndividualSubstanceComponent(subStr3, dB));
						}
					}
				}
			}
		}
		if ((*j == '(') || (*j == '[')) {
			if (!firstBracket) {
				frstBrckt = j;
			}
			firstBracket = true;
		}
	}
		throw ParserException(" has wrong brackets!\n ", subStr1);
}