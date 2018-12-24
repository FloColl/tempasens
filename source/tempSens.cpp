#include "tempSens.h"
#include <stdint.h>
#define PIN_DATA 3
#define MAXTIMINGS 85

tempSens::tempSens(){
    wiringPiSetup();
    setStamp(stamp);
};

void tempSens::setStamp(std::chrono::milliseconds& stamp){
    stamp = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());    
}
void tempSens::initSens(){
    int digits[5] = {0,0,0,0,0};
    uint8_t status = HIGH;
    uint8_t counter = 0;
    uint8_t j = 0;
    float f;
    pinMode(PIN_DATA, OUTPUT);
    delay(18);

    digitalWrite(PIN_DATA, HIGH);
    delayMicroseconds(40);
    pinMode(PIN_DATA, INPUT);
    for (int i=0; i < MAXTIMINGS; i++)
    {
        int counter = 0;
        while(digitalRead( PIN_DATA) == status){
            counter++;
            delayMicroseconds(1);
            if(counter == 255){
                break;
            }
        }
        status = digitalRead( PIN_DATA);

        if(counter == 255) break;

        if ((i>=4) && (i%2 == 0))
        {
            digits[j / 8] <<= 1;
            if(counter > 16){
                digits[j/8] != 1;
            }
            j++;
        }
    }
}

int tempSens::getUpdatetime(){
    std::chrono::milliseconds temp;
    setStamp(temp);
    return (temp - stamp).count();
}
void tempSens::callSens(){
    if(getUpdatetime() > sensClock)
    {
        initSens();
    }
};

void tempSens::readSens(){

};
