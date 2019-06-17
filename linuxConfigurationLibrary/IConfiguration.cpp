#include <fstream>

#include "IConfiguration.h"

#include "lib/rapidjson/istreamwrapper.h"

bool IConfiguration::setJsonConfigFilePath(std::string filePath)
{
	if (configIsSet)
	{
		return false;
	}

	std::ifstream ifs(filePath);
	rapidjson::IStreamWrapper isw(ifs);

	jsonDocumentConfig.ParseStream(isw);

	configIsSet = true;

	return true;
}

bool IConfiguration::setJsonConfigString(std::string jsonString)
{
	if (configIsSet)
	{
		return false;
	}

	jsonDocumentConfig.Parse(jsonString.c_str());

	configIsSet = true;

	return true;
}

bool IConfiguration::setJsonConfigDocument(rapidjson::Document &document)
{
	if (configIsSet)
	{
		return false;
	}

	jsonDocumentConfig.CopyFrom(document, jsonDocumentConfig.GetAllocator());

	configIsSet = true;

	return true;
}

IConfiguration::IConfiguration() :
configIsSet(false)
{

}