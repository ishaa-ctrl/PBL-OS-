#ifndef MATRIX_VIEW_H
#define MATRIX_VIEW_H

#include "deadlock.h"

void displayAllocationMatrix(SystemState *state);
void displayMaximumMatrix(SystemState *state);
void displayNeedMatrix(SystemState *state);
void displayAvailableVector(SystemState *state);

#endif
