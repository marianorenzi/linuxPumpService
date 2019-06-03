#include "IConfiguration.h"

bool IConfiguration::setJsonConfigFilePath(std::string filePath)
{
	//TODO
	return false;
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