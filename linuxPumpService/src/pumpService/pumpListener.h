#ifndef __PUMP_LISTENER_H__
#define __PUMP_LISTENER_H__

class PumpListener {

  public:

    void start();
    void loop();

    PumpListener() {}
    ~PumpListener() {}


  protected:

    virtual void _pumpListenerThreadSetup(void) = 0;
    virtual void _pumpListenerThreadLoop(void) = 0;

  private:

};

inline void PumpListener::start()
{
  _pumpListenerThreadSetup();
}

inline void PumpListener::loop()
{
  _pumpListenerThreadLoop();
}

#endif
