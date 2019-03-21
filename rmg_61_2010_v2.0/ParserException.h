#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <map>

class ParserException
{
public:
	ParserException(const std::string&, const std::string&);
	ParserException(const ParserException&);
	virtual ~ParserException();

	virtual const std::string &whatError() const;
	virtual const std::string &whatWrongString() const;

private:
	std::string error;
	std::string wrongString;
};

