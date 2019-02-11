#ifndef tempSens_H
#define tempSens_H
#include <wiringPi.h>
#include <chrono>

class tempSens{
    using clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<clock>;
    using mics = std::chrono::microseconds;

public:
    tempSens();
    void setClock(int mili);
    int testemp();
    void  callSens();

private:
    enum state{swake, sprepare, spre, stest, sfin};
    struct cstateconf {
        state cstate;
        uint8_t values[5];
        uint8_t bcounter;
        int test;
        bool validSig;
        TimePoint start, end;
        clock myclock; 
        long sigcounter;
    };

    
    
    int getUpdatetime();
    bool  transState(cstateconf& state);

    cstateconf mstate;
    static int sensClock;
};
#endif
