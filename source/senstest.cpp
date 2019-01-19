#include "tempSens.h"
#include <stdio.h>
#include <iostream>

int main()
{
    std::string muh;
    tempSens test;
    for(int i = 0; i<100; i++){
    
        test.callSens();
        printf("%d\n", test.testemp());
    }

    std::cin >> muh;
    return 0;
}

