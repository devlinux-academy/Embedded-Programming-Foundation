#include <stdio.h>

typedef void (*CallbackFunc)(int);

void registerCallback(CallbackFunc cb, int eventData) {
    cb(eventData);
}

void eventHandler(int data) {
    printf("Event handled with data: %d\n", data);
}

int main() {
    registerCallback(eventHandler, 42);
    return 0;
}