#ifndef __GILBARCO_PUMP_CONTROLLER_H__
#define __GILBARCO_PUMP_CONTROLLER_H__

#include <stdint.h>
#include <stddef.h>
#include <iostream>

#include "../pumpService/pump.h"
#include "../pumpService/pumpController.h"

using namespace std;

class NullPump : public Pump {

public:

	bool authorize(uint8_t grade) { return false; }
	bool preset(uint8_t grade, uint32_t value, uint8_t type, uint8_t level) { return false; }
	bool stop() { return false; }
	bool resume() { return false; }
	bool changePrice(uint8_t grade, uint32_t price, uint8_t level) { return false; }

	bool status(Pump::PumpStates *status) { return false; }
	bool callingGrade(uint8_t *grade) { return false; }
	bool totals(uint8_t grade, Pump::PumpTotals *total, Pump::PumpPrice *price) { return false; }
	bool sale(Pump::PumpSale *sale) { return false; }
	bool realTimeSale(Pump::PumpSale *sale) { return false; }

	void setup(void) {}
	void poll(void) {}

	NullPump(uint8_t pid, uint8_t wid, uint8_t* config, int config_size) {}
	NullPump() {}

protected:

private:

};

class NullPumpController : public PumpController {

public:

	// controller thread
	void thread_setup(void) {}
	void thread_loop(void) {}

	IConfiguration* getConfiguration() { return &controllerConfig; }

	// pump and controller creation
	Pump* pumpCreate(uint8_t pid, uint8_t wid, uint8_t *config, int config_size) { return new NullPump; }
	bool pumpAdd(Pump* pump) { return true; }

	NullPumpController() { cout << "nullPumpController construct" << endl; }
	~NullPumpController() {}

protected:

private:

	PumpControllerConfiguration controllerConfig;

};

#endif
