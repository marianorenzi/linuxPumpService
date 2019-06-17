#ifndef _ICONFIGURATION_H_
#define _ICONFIGURATION_H_

#include <stdio.h>
#include <string>

#include "lib/rapidjson/document.h"

class IConfiguration
{
public:

	bool setJsonConfigFilePath(std::string filePath);
	bool setJsonConfigString(std::string jsonString);
	bool setJsonConfigDocument(rapidjson::Document &document);

	bool isSet() { return configIsSet; }

	IConfiguration();

protected:

	// json document
	rapidjson::Document jsonDocumentConfig;

private:

	std::string fileName;

	bool configIsSet;
};

#endif