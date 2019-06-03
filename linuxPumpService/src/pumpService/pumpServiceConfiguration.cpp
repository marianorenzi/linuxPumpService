#include "pumpServiceConfiguration.h"

// controllers
#include "../pumpControllers/emulatorPumpController.h"
#include "../pumpControllers/nullPumpController.h"

// libs
#include <lib/rapidjson/document.h>

PumpServiceConfiguration::PumpServiceConfiguration()
{
	// mock-up config
	std::string documentString = "{\"controllers\":[{\"type\":\"emulator\"},{\"type\":\"null\"},{\"type\":\"null\"}]}";
	this->setJsonConfigString(documentString);

	// create controller factory
	controllerFactory.Register("emulator", new DerivedCreator<EmulatorPumpController, PumpController>);
	controllerFactory.Register("null", new DerivedCreator<NullPumpController, PumpController>);
}

PumpServiceConfiguration::~PumpServiceConfiguration()
{
	// TODO: free JSON Document
}

PumpController* PumpServiceConfiguration::getController(int index)
{
	// get controllers config
	const rapidjson::Value& controllersConfig = jsonDocumentConfig["controllers"];

	// check array size
	assert(controllersConfig.IsArray());
	if (index >= controllersConfig.Size())
	{
		return NULL;
	}

	rapidjson::Document controllerDocument;
	controllerDocument.CopyFrom(controllersConfig[index], controllerDocument.GetAllocator());
	PumpController* newPumpController = controllerFactory.Create(std::string(controllerDocument["type"].GetString()));;

	if (newPumpController == NULL) {
		return NULL;
	}

	// set controller configuration
	newPumpController->getConfiguration()->setJsonConfigDocument(controllerDocument);

	return newPumpController;
}