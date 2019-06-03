#ifndef __PUMP_SERVICE_CONFIGURATION_H__
#define __PUMP_SERVICE_CONFIGURATION_H__

// config base
#include "IConfiguration.h"

// libs
#include <string>
#include "../lib/objectFactrory.h"

#include "pumpController.h"

class PumpServiceConfiguration : public IConfiguration
{
public:

	PumpController* getController(int index);

	PumpServiceConfiguration();
	~PumpServiceConfiguration();

private:


	// pump controller factory
	Factory<PumpController, std::string> controllerFactory;
};

#endif
