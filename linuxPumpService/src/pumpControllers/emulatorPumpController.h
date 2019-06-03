#ifndef __EMULATOR_PUMP_CONTROLLER_H__
#define __EMULATOR_PUMP_CONTROLLER_H__

#include <stdint.h>
#include <stddef.h>

#include "../pumpService/pump.h"
#include "../pumpService/pumpController.h"

class EmulatorPumpController : public PumpController {

public:

	// controller thread
	void thread_setup(void);
	void thread_loop(void);
	IConfiguration* getConfiguration();

	// pump and controller creation
	Pump* pumpCreate(uint8_t pid, uint8_t wid, uint8_t *config, int config_size);
	bool pumpAdd(Pump* pump);

	EmulatorPumpController();
	~EmulatorPumpController();

protected:

private:

	enum {
		maxEmulatorPumps = 2,
	};

	void processRemoteEmulator(void);

	PumpControllerConfiguration controllerConfig;

	Pump* _pumpList[maxEmulatorPumps];
	int emulatorPumpsQty;

};

class EmulatorPump : public Pump {

public:

	enum
	{
		EMULATOR_HANDLE_OFF,
		EMULATOR_HANDLE_1,
		EMULATOR_HANDLE_2,
		EMULATOR_HANDLE_3,
		EMULATOR_HANDLE_4,
	};

	bool authorize(uint8_t grade);
	bool preset(uint8_t grade, uint32_t value, uint8_t type, uint8_t level);
	bool stop();
	bool resume();
	bool changePrice(uint8_t grade, uint32_t price, uint8_t level);

	bool status(Pump::PumpStates *status);
	bool callingGrade(uint8_t *grade);
	bool totals(uint8_t grade, Pump::PumpTotals *total, Pump::PumpPrice *price);
	bool sale(Pump::PumpSale *sale);
	bool realTimeSale(Pump::PumpSale *sale);

	void setup(void);
	void poll(void);

	// for controller use    
	void toggleHandle(int handleValue);
	void toggleNozzle();

	EmulatorPump(uint8_t pid, uint8_t wid, uint8_t* config, int config_size);
	EmulatorPump();
	// ~EmulatorPump() {}

protected:

private:

	enum ConfigIndex
	{
		CONFIG_INDEX_HANDLE_PIN,
		CONFIG_INDEX_NOZZLE_PIN,
		CONFIG_INDEX_DECIMALS_AMOUNT,
		CONFIG_INDEX_DECIMALS_QUANTITY,
		CONFIG_INDEX_DECIMALS_PRICE,
	};

	enum
	{
		EMULATOR_MAX_GRADES = 4
	};

	enum EmulatorStates
	{
		STATE_INITIALIZING,
		STATE_IDLE,
		STATE_CALLING,
		STATE_AUTH,
		STATE_STARTING_1,
		STATE_STARTING_2,
		STATE_STARTING_3,
		STATE_STARTING_4,
		STATE_BUSY,
		STATE_STOP,
	};

	bool handlePinEnabled;
	bool nozzlePinEnabled;
	uint8_t handlePin;
	uint8_t nozzlePin;
	uint8_t decimalsAmount;
	uint8_t decimalsQuantity;
	uint8_t decimalsPrice;

	int handleStatus;
	bool nozzleStatus;

	int _status;

	Pump::PumpSale _sale;
	Pump::PumpTotals _totals[EMULATOR_MAX_GRADES];
	Pump::PumpPrice _prices[EMULATOR_MAX_GRADES];
};

#endif
