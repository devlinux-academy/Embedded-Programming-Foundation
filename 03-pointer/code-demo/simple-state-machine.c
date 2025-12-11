#include <stdio.h>

typedef void(*StateFunc)();

void stateA();
void stateB();
void stateC();

StateFunc stateTable[3] = {stateA, stateB, stateC};

// Current state variable
int currentState = 0;

void stateA(){
    printf("State A\n");
    // Change to state B
    currentState = 1;
}

void stateB(){
    printf("State B\n");
    // Change to state C
    currentState = 2;
}

void stateC(){
    printf("State C\n");
    // Change to state A
    currentState = 0;
}

int main(){
    for (int i = 0; i < 6; ++i){
        stateTable[currentState]();
    }
    
    return 0;
}