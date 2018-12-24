#ifndef tempSens_H
#define tempSens_H
#include <wiringPi.h>
#include <chrono>

class tempSens{
public:
    tempSens();
    float getTemp();
    float getHum();
    void setClock(int mili);
    int getUpdatetime();

private:
    void initSens();
    void readSens();
    void  callSens();
    void setStamp(std::chrono::milliseconds& ms);

    int digits[5];
    static int sensClock;
    std::chrono::milliseconds stamp;
};
#endif
