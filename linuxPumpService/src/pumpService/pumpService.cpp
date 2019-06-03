#include "pumpService.h"

// system

// lib
#include "../lib/objectFactrory.h"

// controllers
#include "../pumpControllers/emulatorPumpController.h"
#include "../pumpControllers/nullPumpController.h"

///////////////////////////////////////////////////
/////////////// PUMP SERVICE THREAD ///////////////
///////////////////////////////////////////////////
void PumpService::setup(std::string configFileName)
{
	PumpController* pumpController;

	int i = 0;
	while ((pumpController = serviceConfiguration.getController(i++)))
	{
		this->attachPumpController(pumpController);
	}
}

void PumpService::thread(void)
{
	// load config
	this->setup("");

	// proces pump status and flags
	for (;;)
	{
		// TODO
	}
}

///////////////////////////////////////////////////
/////////////// OPERATIONS ON PUMPS ///////////////
///////////////////////////////////////////////////
bool PumpService::pumpAuthorize(uint8_t pid, uint8_t grade)
{
  PumpContainer* pumpContainer = retrievePump(pid);
  if (pumpContainer == NULL)
  {
    return false;
  }

  //TODO: store auth
  return pumpContainer->pump->authorize(grade);
}

bool PumpService::pumpPreset(uint8_t pid, uint8_t grade, uint32_t value, uint8_t type, uint8_t level)
{
  PumpContainer* pumpContainer = retrievePump(pid);
  if (pumpContainer == NULL)
  {
    return false;
  }

  //TODO: store preset
  return pumpContainer->pump->preset(grade, value, type, level);
}

bool PumpService::pumpStop(uint8_t pid)
{
  PumpContainer* pumpContainer = retrievePump(pid);
  if (pumpContainer == NULL)
  {
    return false;
  }

  //TODO: check status and store action
  return pumpContainer->pump->stop();
}

bool PumpService::pumpAllStop(void)
{
  for (auto i = _pumpList.begin(); i != _pumpList.end(); i++)
  {
    this->pumpStop((*i)->pump->logicId);
  }
  
  return true;
}

bool PumpService::pumpResume(uint8_t pid)
{
  PumpContainer* pumpContainer = retrievePump(pid);
  if (pumpContainer == NULL)
  {
    return false;
  }

  //TODO: check status and store action
  return pumpContainer->pump->resume();
}

bool PumpService::pumpChangePrice(uint8_t pid, uint8_t grade, uint32_t price, uint8_t level)
{
  PumpContainer* pumpContainer = retrievePump(pid);
  if (pumpContainer == NULL)
  {
    return false;
  }

  //TODO: check status and store action
  return pumpContainer->pump->changePrice(grade, price, level);
}

bool PumpService::pumpAcknowledgeSale(uint8_t pid)
{
  PumpContainer* pumpContainer = retrievePump(pid);
  if (pumpContainer == NULL)
  {
    return false;
  }

  //TODO
  return false;
}

///////////////////////////////////////////////////
///////////// DATA REQUESTS TO PUMPS //////////////
///////////////////////////////////////////////////
bool PumpService::pumpStatus(uint8_t pid, Pump::PumpStates *status)
{
  PumpContainer* pumpContainer = retrievePump(pid);
  if (pumpContainer == NULL)
  {
    if (status) *status = Pump::PumpStates::CLOSED;
    return false;
  }

  Pump::PumpStates pump_status;
  if (pumpContainer->pump->status(&pump_status) != true)
  {
    if (status) *status = Pump::PumpStates::OFFLINE;
    return false;
  }

  if (status)
  {
    *status = pump_status;
  }

  // TODO: check pump flags

  return true;
}

bool PumpService::pumpCallingGrade(uint8_t pid, uint8_t* grade)
{
  PumpContainer* pumpContainer = retrievePump(pid);
  if (pumpContainer == NULL)
  {
    return false;
  }
  
  Pump::PumpStates pumpStatus;
  if (!this->pumpStatus(pid, &pumpStatus))
  {
    return false;
  }

  if (pumpStatus != Pump::PumpStates::CALLING)
  {
    return false;
  }

  return pumpContainer->pump->callingGrade(grade);
}

bool PumpService::pumpTotals(uint8_t pid, uint8_t grade, Pump::PumpTotals* total, Pump::PumpPrice* price)
{
  PumpContainer* pumpContainer = retrievePump(pid);
  if (pumpContainer == NULL)
  {
    return false;
  }

  return pumpContainer->pump->totals(grade, total, price);
}

bool PumpService::pumpSale(uint8_t pid, Pump::PumpSale* sale)
{
  PumpContainer* pumpContainer = retrievePump(pid);
  if (pumpContainer == NULL)
  {
    return false;
  }

  return pumpContainer->pump->sale(sale);
}

bool PumpService::pumpRealTimeSale(uint8_t pid, Pump::PumpSale* sale)
{
  PumpContainer* pumpContainer = retrievePump(pid);
  if (pumpContainer == NULL)
  {
    return false;
  }
  
  Pump::PumpStates pumpStatus;
  if (!this->pumpStatus(pid, &pumpStatus))
  {
    return false;
  }

  if (pumpStatus != Pump::PumpStates::BUSY)
  {
    return false;
  }

  return pumpContainer->pump->realTimeSale(sale);
}

///////////////////////////////////////////////////
//////////////// PUMP INFORMATION /////////////////
///////////////////////////////////////////////////
bool PumpService::pumpVolumeDecimals(uint8_t id, uint8_t *volumeDecimals)
{
  //TODO
  return false;
}

bool PumpService::pumpMoneyDecimals(uint8_t id, uint8_t *moneyDecimals)
{
  //TODO
  return false;
}

bool PumpService::pumpPriceDecimals(uint8_t id, uint8_t *priceDecimals)
{
  //TODO
  return false;
}

uint8_t PumpService::pumpVolumeDecimals(uint8_t id)
{
  //TODO
  return 0;
}

uint8_t PumpService::pumpMoneyDecimals(uint8_t id)
{
  //TODO
  return 0;
}

uint8_t PumpService::pumpPriceDecimals(uint8_t id)
{
  //TODO
  return 0;
}

///////////////////////////////////////////////////
//////////////// PUMP LALA /////////////////
///////////////////////////////////////////////////
PumpService::PumpContainer* PumpService::retrievePump(uint8_t pid)
{
  for (auto it = _pumpList.begin(); it != _pumpList.end(); it++)
  {
    if ((*it)->pump->logicId == pid) return (*it);
  }

  return NULL;
}

bool PumpService::attachPumpController(PumpController *pumpController)
{
  //Log.info("Attaching Controller %p", pumpController);

  if (pumpController == NULL) 
  {
    return false;
  }

  if (_pumpControllerList.size() >= maxPumpControllers)
  {
    return false;
  }

  _pumpControllerList.push_back(pumpController);

  return true;
}

bool PumpService::attachPump(Pump *pump)
{
  //Log.info("Attaching Pump %p", pump);

  if (pump == NULL) 
  {
    return false;
  }

  if (_pumpList.size() >= maxPumps)
  {
    return false;
  }

  _pumpList.push_back(new PumpContainer(pump));

  return true;
}