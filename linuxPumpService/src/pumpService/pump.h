#ifndef __PUMP_H__
#define __PUMP_H__

#include <stdint.h>
#include <stddef.h>
#include <string>
#include <vector>

class Pump {

  public:

	  typedef std::vector<Pump*> List;
	  typedef std::vector<Pump*>::iterator Iterator;

    enum PumpStates
    {
      OFFLINE,
      IDLE,
      CALLING,
      AUTHORIZED,
      BUSY,
      STOP,
      EOT,
      ERROR,
      CLOSED
    };

    enum
    {
      MAX_GRADES = 6,
      UNSET_GRADE = 0xfd,
      ALL_GRADES = 0xfe,
      UNKNOWN_GRADE = 0xff,

      ALL_PUMPS = 0xfe,
      UNKNOWN_PUMP = 0xff
    };

    struct PumpTotals
    {
      uint64_t volume;
      uint64_t money;
      uint8_t grade;
    };

    struct PumpPrice
    {
      uint32_t level_1;
      uint32_t level_2;
    };

    struct PumpSale
    {
      uint32_t volume;
      uint32_t money;
      uint8_t grade;
      uint32_t ppu;
      uint8_t ppuLevel;
    };

    virtual bool authorize(uint8_t grade) = 0;
    virtual bool preset(uint8_t grade, uint32_t value, uint8_t type, uint8_t level) = 0;
    virtual bool stop() = 0;
    virtual bool resume() = 0;
    virtual bool changePrice(uint8_t grade, uint32_t price, uint8_t level) = 0;

    virtual bool status(Pump::PumpStates *status) = 0;
    virtual bool callingGrade(uint8_t *grade) = 0;
    virtual bool totals(uint8_t grade, PumpTotals *total, PumpPrice *price) = 0;
    virtual bool sale(PumpSale *sale) = 0;
    virtual bool realTimeSale(PumpSale *sale) = 0;
    
    virtual void setup() = 0;
    virtual void poll(void) = 0;

    Pump(uint8_t pid, uint8_t wid) : logicId(pid), physicalId(wid) {}
    Pump() {}
    ~Pump() {}

    uint8_t logicId, physicalId;

  protected:

  private:

};

#endif
