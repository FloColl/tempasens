#ifndef tempSens_H
#define tempSens_H
#include <wiringPi.h>
#include <chrono>

class tempSens{
public:
    tempSens();
    void setClock(int mili);
    int testemp();
    void  callSens();

private:
    enum state{swake, swait, sresponse, sprepare, spre, ssignal, stest, sfin};
    struct cstateconf {
        state cstate;
        uint8_t values[5];
        uint8_t bcounter;
        int test;
        bool validSig;
        std::chrono::milliseconds stamp;
    };
    
    int getUpdatetime();
    void setStamp(std::chrono::milliseconds& ms);
    bool  transState(cstateconf& state);

    cstateconf mstate;
    static int sensClock;
};
#endif
