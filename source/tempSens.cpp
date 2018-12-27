#include "tempSens.h"
#include <stdint.h>
#define PIN_DATA 3

tempSens::tempSens(){
    wiringPiSetup();
    setStamp(mstate.stamp);
};

int tempSens::testemp()
{
    return mstate.values[0];
};

void tempSens::setClock(int x)
{
    tempSens::sensClock = x;
};

void tempSens::setStamp(std::chrono::milliseconds& stamp){
    stamp = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());    
}

bool tempSens::transState(cstateconf& cstate)
{
    int tcounter=0;

    switch(mstate.cstate)
    {

        case swake:
            cstate.validSig= false;
            pinMode(PIN_DATA, OUTPUT);
            digitalWrite(PIN_DATA, LOW);
            delay(18);
            mstate.bcounter = 0;
            mstate.test = 0;
            for(int i = 0; i<5; i++){
                mstate.values[i] = 0;
            }
            mstate.cstate =swait;
            return true;
        case swait:
            digitalWrite(PIN_DATA, HIGH);
            delayMicroseconds(40);
            mstate.cstate = sresponse;
        case sresponse:
            pinMode(PIN_DATA, INPUT);
            while(!digitalRead(PIN_DATA))
            {
                tcounter++;
                if (tcounter== 81)
                {
                    cstate.validSig = false;
                    return false;
                }
                delayMicroseconds(1);
            }
            mstate.cstate = sprepare;
            cstate.validSig = true;
            return true;
        case sprepare:
            tcounter=0;
            while(digitalRead(PIN_DATA))
            {
                tcounter++;
                if(tcounter == 81)
                {
                    cstate.validSig = false;
                    return false;
                }
                delayMicroseconds(1);
            }
            if (tcounter > 30){
                mstate.cstate = spre;
                return true;
            }else
            {
                return false;
            }
        case spre:
            tcounter = 0;
            mstate.bcounter++;
            while(!digitalRead(PIN_DATA))
            {
                tcounter++;
                if(tcounter == 51)
                {
                    return false;
                }
                delayMicroseconds(1);
            }
            if(tcounter > 10)
            {
                return true;
            }else
            {
                return false;
            }


        case ssignal:
            tcounter = 0;

            while(digitalRead(PIN_DATA)){
                tcounter++;
                if(tcounter==81){
                    return false;
                }
                delayMicroseconds(1);
            }
            if(tcounter < 9)
            {
                return false;
            }
            if( mstate.bcounter == 40){
                mstate.cstate = stest;
                return true;
            }else
            {
                mstate.cstate = spre;
            }
            mstate.values[mstate.bcounter/8] |=(tcounter>25);
            mstate.values[mstate.bcounter/8] <<= 1;
            
            return true;

        case stest:
            mstate.test = 0;
            for (int i = 0; i<4; i++)
            {
                mstate.test += mstate.values[i];
            }
            mstate.test = mstate.test & 0xff;
            mstate.validSig = mstate.test == mstate.values[4];
            mstate.cstate = sfin;
            return mstate.validSig;
        case sfin:
            return false;
    }
};

int tempSens::getUpdatetime(){
    std::chrono::milliseconds temp;
    setStamp(temp);
    return (temp - mstate.stamp).count();
}
void tempSens::callSens(){
    mstate.cstate=swake;
    while(transState(mstate))
    {
    }
}
