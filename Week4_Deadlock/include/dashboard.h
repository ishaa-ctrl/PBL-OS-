#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "deadlock.h"

void dashboardShowStatus(SystemState *state);
void dashboardShowSafety(SystemState *state);
void dashboardShowDeadlock(SystemState *state);

#endif
