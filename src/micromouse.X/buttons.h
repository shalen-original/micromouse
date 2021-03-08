#ifndef BUTTONS_H
#define	BUTTONS_H

#include "boolean.h"

void initButtons();

// To be implemented by users
void onButtonChanged(BOOL isCurrentlyPressed);
void onButtonClicked();

#endif
