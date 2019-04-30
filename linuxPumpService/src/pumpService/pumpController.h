#ifndef __PUMP_CONTROLLER_H__
#define __PUMP_CONTROLLER_H__

#include <stdint.h>
#include <stddef.h>
#include <map>

#include <lib/rapidjson/document.h>

#include "pump.h"

class PumpController {

  public:

    virtual void thread_setup(void) = 0;
    virtual void thread_loop(void) = 0;

	virtual Pump* pumpCreate(uint8_t pid, uint8_t wid, uint8_t *config, int config_size) = 0;
    virtual bool pumpAdd(Pump* pump) = 0;

    PumpController() {}
    // ~PumpController();

    // PumpController() {}

  protected:

  private:

};

#endif
