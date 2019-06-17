#ifndef __PUMP_CONTROLLER_H__
#define __PUMP_CONTROLLER_H__

#include <stdint.h>
#include <stddef.h>
#include <vector>

#include "pump.h"
#include "pumpControllerConfiguration.h"

class PumpController {

public:

	virtual IConfiguration* getConfiguration() = 0;

	virtual Pump* pumpCreate(uint8_t pid, uint8_t wid, uint8_t *config, int config_size) = 0;
	virtual bool pumpAdd(Pump* pump) = 0;

	PumpController();
	// ~PumpController();

protected:

	Pump::List pumpList;

private:

	virtual void thread(void) = 0;

	void threadCreate();

	std::thread controllerThread;

};

#endif
