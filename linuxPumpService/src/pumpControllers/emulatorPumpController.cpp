#include "emulatorPumpController.h"
#include <iostream>

void EmulatorPumpController::thread_loop(void)
{
    // process tcp remote emulator
    this->processRemoteEmulator();

    for(int i = 0; i < this->emulatorPumpsQty; i++)
    {
        this->_pumpList[i]->poll();
    }
}

void EmulatorPumpController::thread_setup(void)
{
    //this->server.begin();

    for(int i = 0; i < this->emulatorPumpsQty; i++)
    {
        this->_pumpList[i]->setup();
    }
}

void EmulatorPumpController::processRemoteEmulator(void)
{
#if 0
    if (!client.connected())
    {
        client = server.available();
        return;
    }

    while (!client.available()) 
    {
        return;
    }

    switch(client.read())
    {
        // handles for pump 1
        case 'q':
        case 'Q':
        if (this->_pumpList[0]) ((EmulatorPump*)this->_pumpList[0])->toggleHandle(1);
        break;
        
        case 'w':
        case 'W':
        if (this->_pumpList[0]) ((EmulatorPump*)this->_pumpList[0])->toggleHandle(2);
        break;
        
        case 'e':
        case 'E':
        if (this->_pumpList[0]) ((EmulatorPump*)this->_pumpList[0])->toggleHandle(3);
        break;
        
        case 'r':
        case 'R':
        if (this->_pumpList[0]) ((EmulatorPump*)this->_pumpList[0])->toggleHandle(4);
        break;
        
        // handles for pump 2
        case 'a':
        case 'A':
        if (this->_pumpList[1]) ((EmulatorPump*)this->_pumpList[1])->toggleHandle(1);
        break;
        
        case 's':
        case 'S':
        if (this->_pumpList[1]) ((EmulatorPump*)this->_pumpList[1])->toggleHandle(2);
        break;
        
        case 'd':
        case 'D':
        if (this->_pumpList[1]) ((EmulatorPump*)this->_pumpList[1])->toggleHandle(3);
        break;
        
        case 'f':
        case 'F':
        if (this->_pumpList[1]) ((EmulatorPump*)this->_pumpList[1])->toggleHandle(4);
        break;
        
        // nozzle for pump 1
        case 't':
        case 'T':
        if (this->_pumpList[0]) ((EmulatorPump*)this->_pumpList[0])->toggleNozzle();
        break;
        
        // nozzle for pump 2
        case 'g':
        case 'G':
        if (this->_pumpList[1]) ((EmulatorPump*)this->_pumpList[1])->toggleNozzle();
        break;

        //TODO: screens and totals for pumps 1 and 2
    }
#endif
}

Pump* EmulatorPumpController::pumpCreate(uint8_t logicId, uint8_t physicalId, uint8_t* config, int config_size)
{
    Pump* pump = new EmulatorPump(logicId, physicalId, config, config_size);

    //Serial.printlnf("emulatorPumpController::pumpCreate: success, p=%p, pid=%u, wid=%u", pump, pump->pid, pump->wid);
    return pump;
}

bool EmulatorPumpController::pumpAdd(Pump* pump)
{
    if (pump == NULL) 
    {
        //Log.info("emulatorPumpController::pumpAdd: failed, nullptr", pump);
        return false;
    }

    if (this->emulatorPumpsQty >= maxEmulatorPumps)
    {
        //Log.info("emulatorPumpController::pumpAdd: failed, max pumps exceeded");
        return false;
    }

    // add pump to array
    this->_pumpList[this->emulatorPumpsQty++] = pump;

    return true;
}

    EmulatorPumpController::EmulatorPumpController() :
    emulatorPumpsQty(0)
    //server(23)
    {
        /* TODO */ 
		std::cout << "emulatorPumpController construct" << std::endl;
    }

    EmulatorPumpController::~EmulatorPumpController() {}


///////////////////////////////////////////////////
////////////////// EMULATOR PUMP //////////////////
///////////////////////////////////////////////////
void EmulatorPump::poll(void)
{
    switch (this->_status)
    {
        case STATE_INITIALIZING:
            _status = STATE_IDLE;
        break;

        case STATE_IDLE:
        if (this->handleStatus != EMULATOR_HANDLE_OFF) {
            this->_status = STATE_CALLING;
        }
        break;
        
        case STATE_CALLING:
        if (this->handleStatus == EMULATOR_HANDLE_OFF) {
            this->_status = STATE_IDLE;
        }
        break;
        
        case STATE_AUTH:
        if (this->handleStatus != EMULATOR_HANDLE_OFF) {
            //TODO: start busy states
            this->_status = STATE_STARTING_1;
        }
        break;
        
        case STATE_STARTING_1:
        case STATE_STARTING_2:
        case STATE_STARTING_3:
        case STATE_STARTING_4:
        //TODO: timers to change state?
        this->_status++;
        break;
        
        case STATE_BUSY:
        if (this->handleStatus == EMULATOR_HANDLE_OFF) {
            this->_status = IDLE;
        }
        break;
        
        case STATE_STOP:
        break;
    }
}

void EmulatorPump::setup(void)
{
    //TODO: load previous pump data such as prices, totals and last sale
}

bool EmulatorPump::authorize(uint8_t grade)
{
    //TODO
    return false;
}

bool EmulatorPump::preset(uint8_t grade, uint32_t value, uint8_t type, uint8_t level)
{
    //TODO
    return false;
}

bool EmulatorPump::stop()
{
    //TODO
    return false;
}

bool EmulatorPump::resume()
{
    //TODO
    return false;
}

bool EmulatorPump::changePrice(uint8_t grade, uint32_t price, uint8_t level)
{
    //TODO
    return false;
}

bool EmulatorPump::status(Pump::PumpStates* status)
{
    Pump::PumpStates pumpStatus;

    switch (this->_status)
    {
        case STATE_INITIALIZING: pumpStatus = PumpStates::OFFLINE; break;
        case STATE_IDLE: pumpStatus = PumpStates::IDLE; break;
        case STATE_CALLING: pumpStatus = PumpStates::CALLING; break;
        case STATE_AUTH: pumpStatus = PumpStates::AUTHORIZED; break;
        case STATE_STARTING_1:
        case STATE_STARTING_2:
        case STATE_STARTING_3:
        case STATE_STARTING_4:
        case STATE_BUSY: pumpStatus = PumpStates::BUSY; break;
        case STATE_STOP: pumpStatus = PumpStates::STOP; break;
    }
    if (status) *status = pumpStatus;

    return true;
}

bool EmulatorPump::callingGrade(uint8_t *grade)
{
    //TODO
    return false;
}

bool EmulatorPump::totals(uint8_t grade, Pump::PumpTotals* total, Pump::PumpPrice* price)
{
    //TODO
    return false;
}

bool EmulatorPump::sale(Pump::PumpSale* sale)
{
    //TODO
    return false;
}

bool EmulatorPump::realTimeSale(PumpSale* sale)
{
        //TODO
    return false;
}

void EmulatorPump::toggleHandle(int handleValue)
{
    if (handleValue > EMULATOR_MAX_GRADES) 
    {
        return;
    }   

    if (this->handleStatus == EMULATOR_HANDLE_OFF)
    {
        this->handleStatus = handleValue;
    }
    else
    {
        this->handleStatus = EMULATOR_HANDLE_OFF;
    }
}

void EmulatorPump::toggleNozzle()
{
    this->nozzleStatus = !this->nozzleStatus;
}

EmulatorPump::EmulatorPump(uint8_t logicId, uint8_t physicalId, uint8_t* config, int config_size) :
handlePinEnabled(false),
nozzlePinEnabled(false),
handleStatus(EMULATOR_HANDLE_OFF),
nozzleStatus(false),
_status(STATE_INITIALIZING)
{
    this->logicId = logicId;
    this->physicalId = physicalId;

    if (config_size >= CONFIG_INDEX_HANDLE_PIN)
    {
        this->handlePin = config[CONFIG_INDEX_HANDLE_PIN];
        this->handlePinEnabled = true;
    }

    if (config_size >= CONFIG_INDEX_NOZZLE_PIN)
    {
        this->nozzlePin = config[CONFIG_INDEX_NOZZLE_PIN];
        this->nozzlePinEnabled = true;
    }

    if (config_size >= CONFIG_INDEX_DECIMALS_AMOUNT)
    {
        this->decimalsAmount = config[CONFIG_INDEX_DECIMALS_AMOUNT];
    }

    if (config_size >= CONFIG_INDEX_DECIMALS_QUANTITY)
    {
        this->decimalsQuantity = config[CONFIG_INDEX_DECIMALS_QUANTITY];
    }

    if (config_size >= CONFIG_INDEX_DECIMALS_PRICE)
    {
        this->decimalsPrice = config[CONFIG_INDEX_DECIMALS_PRICE];
    }
}

EmulatorPump::EmulatorPump() : 
handlePinEnabled(false),
nozzlePinEnabled(false),
handleStatus(EMULATOR_HANDLE_OFF),
nozzleStatus(false),
_status(STATE_INITIALIZING)
{
}
