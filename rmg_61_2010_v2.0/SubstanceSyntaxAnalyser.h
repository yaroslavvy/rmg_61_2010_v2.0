#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <map>

#include "ParserException.h"
#include "PrintableObject.h"
#include "TwoDimensionalArray.h"
#include "Element.h"
#include "IndividualSubstanceComponent.h"
#include "MixtureOfComponents.h"
#include "SubstanceLexAnalyser.h"

class SubstanceSyntaxAnalyser
{
public:
	SubstanceSyntaxAnalyser();
	virtual ~SubstanceSyntaxAnalyser();

	static bool isValidString(const std::string&);
	static const MixtureOfComponents analyseMixtureOfComponents(const std::string&, const ElementDataBase &);
	static bool isAllBracketsClosed(const std::string&);
	static std::vector<std::string> starAndBracketsAnalyser(const std::string&);
	static const IndividualSubstanceComponent analyseIndividualSubstanceComponent(const std::string &, const ElementDataBase&);

	template <class T>
	static void indexMapInsert(std::map<T, int> *mp, const T &item) {
		if (mp->find(item) != mp->end()) {
			(mp->find(item)->second)++;
		}
		else {
			mp->insert(std::map<T, int>::value_type(item, 1));
		}
	}
};

