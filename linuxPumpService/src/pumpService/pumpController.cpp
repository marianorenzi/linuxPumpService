#include <thread>
#include "pumpController.h"

///////////////////////////////////////////////////
/////////// PUMP CONTROLLER CONSTRUCTOR ///////////
///////////////////////////////////////////////////
PumpController::PumpController()
{
	std::thread(PumpController::threadCreate, this);
}

///////////////////////////////////////////////////
///////// PUMP CONTROLLER THREAD CREATION /////////
///////////////////////////////////////////////////
void PumpController::threadCreate()
{
	// wait for configuration
	while (!this->getConfiguration->isSet());

	controllerThread = std::thread(PumpController::thread, this);
}