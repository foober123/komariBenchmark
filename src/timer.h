#ifndef TIMER_H
#define TIMER_H

#include <raylib.h>

// define a timer
typedef struct
{
float Lifetime;
}Timer;

void StartTimer(Timer* timer, float lifetime);
void UpdateTimer(Timer* timer);
bool TimerDone(Timer* timer);

#endif
