#pragma once

#include <stdio.h>
#include <string>

class IConfiguration
{
public:
	IConfiguration();
	virtual ~IConfiguration();
private:
	std::string fileName;
};



IConfiguration::IConfiguration()
{
}


IConfiguration::~IConfiguration()
{
}
