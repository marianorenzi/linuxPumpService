#ifndef __PUMP_SERVICE_H__
#define __PUMP_SERVICE_H__

#include <cstdint>
#include <string>
#include <vector>

#include "pump.h"
#include "pumpController.h"
#include "pumpServiceConfiguration.h"

class PumpService {

  public:

    enum
    {
      PRESET_VOLUME,
      PRESET_MONEY
    };

    bool pumpAuthorize(uint8_t pid, uint8_t grade);
    bool pumpPreset(uint8_t pid, uint8_t grade, uint32_t value, uint8_t type, uint8_t level);
    bool pumpStop(uint8_t pid);
    bool pumpAllStop(void);
    bool pumpResume(uint8_t pid);
    bool pumpChangePrice(uint8_t pid, uint8_t grade, uint32_t price, uint8_t level);

    bool pumpStatus(uint8_t pid, Pump::PumpStates *status);
    bool pumpCallingGrade(uint8_t pid, uint8_t *grade);
    bool pumpTotals(uint8_t pid, uint8_t grade, Pump::PumpTotals *total, Pump::PumpPrice *price);
    bool pumpSale(uint8_t pid, Pump::PumpSale *sale);
    bool pumpRealTimeSale(uint8_t pid, Pump::PumpSale *sale);

    bool pumpAcknowledgeSale(uint8_t pid);

    bool pumpVolumeDecimals(uint8_t id, uint8_t *volumeDecimals);
    bool pumpMoneyDecimals(uint8_t id, uint8_t *moneyDecimals);
    bool pumpPriceDecimals(uint8_t id, uint8_t *priceDecimals);
    uint8_t pumpVolumeDecimals(uint8_t id);
    uint8_t pumpMoneyDecimals(uint8_t id);
    uint8_t pumpPriceDecimals(uint8_t id);

	PumpService() {}
	PumpService(std::string configFilePath, std::string logFilePath = NULL);
	~PumpService() {}

	void join() { serviceThread.join(); }

  private:

    struct PumpContainer
    {
      Pump* pump;

      // flags
      bool closed;
      bool authorized;
      bool authSent;
      bool stop;
      bool stopSent;

      PumpContainer() {}
      PumpContainer(Pump* pump) : pump(pump) {}
    };

    enum 
    {
      maxPumps = 2,
      maxPumpControllers = 1,
    };

    PumpContainer* retrievePump(uint8_t pid);

    bool attachPumpController(PumpController *pumpController);
    bool attachPump(Pump *pump);

	void setup(std::string configFileName);
	void thread(void);

	PumpServiceConfiguration serviceConfiguration;

	std::vector<PumpContainer*> _pumpList;
	std::vector<PumpController*> _pumpControllerList;

	std::thread serviceThread;

};

#endif
