#include "tempSens.h"
#include <stdint.h>
#include <iostream>
#define PIN_DATA 7
int tempSens:: sensClock = 40;

tempSens::tempSens(){
    wiringPiSetup();
};

int tempSens::testemp()
{
    return mstate.values[0];
};

void tempSens::setClock(int x)
{
    tempSens::sensClock = x;
};
/*
void tempSens::setStamp(cstateconf& cstate){
    cstate.stamp = std::chrono::high_resolution_clock::now();    
};
*/
bool tempSens::transState(cstateconf& cstate)
{
    int tcounter=0;
    switch(mstate.cstate)
    {
        case swake:
            cstate.validSig= false;
            mstate.test = 0;
            mstate.bcounter = 0;
            pinMode(PIN_DATA, OUTPUT);
            for(int i = 0; i<5; i++){
                mstate.values[i] = 0;
            }
            digitalWrite(PIN_DATA, LOW);
            delay(18);
            digitalWrite(PIN_DATA, HIGH);
            delayMicroseconds(40);
            pinMode(PIN_DATA, INPUT);
            tcounter = 0;
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
            
            mstate.start = mstate.myclock.now();

            while(digitalRead(PIN_DATA)){
            }
            
            mstate.end = mstate.myclock.now();

            mstate.sigcounter = std::chrono::duration_cast<std::chrono::duration<int>> (mstate.end - mstate.start);

            if( mstate.bcounter == 40){
                mstate.cstate = stest;
                return true;
            }
            tcounter = mstate.sigcounter.count();
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
void tempSens::callSens(){
    mstate.cstate=swake;
    while(transState(mstate))
    {
    }
}
