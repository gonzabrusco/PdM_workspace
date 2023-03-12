/*
 * API_debounce.c
 *
 *  Created on: Mar 11, 2023
 *      Author: gonza
 */

#include "API_debounce.h"
#include "API_delay.h"
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#define BUTTON_DEBOUNCE_TIME	40

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

static debounceState_t buttonDebounce;
static delay_t buttonDelay;
static bool_t buttonRisingEdge = false;
static bool_t buttonFallingEdge = false;
static bool_t buttonDown = false;

void debounceFSM_init() {
	/* Initialize BSP PB for BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	delayInit(&buttonDelay, BUTTON_DEBOUNCE_TIME);
	buttonDebounce = BUTTON_UP;
	buttonRisingEdge = false;
	buttonFallingEdge = false;
	buttonDown = false;
}

void debounceFSM_update() {
	switch (buttonDebounce) {
	case BUTTON_UP:
		if(BSP_PB_GetState(BUTTON_USER)) {
			buttonDebounce = BUTTON_FALLING;
		}
		break;
	case BUTTON_FALLING:
		if(delayRead(&buttonDelay)) {
			if(BSP_PB_GetState(BUTTON_USER)) {
				buttonDebounce = BUTTON_DOWN;
				buttonFallingEdge = true;
				buttonDown = true;
			}
			else {
				buttonDebounce = BUTTON_UP;
			}
		}
		break;
	case BUTTON_DOWN:
		if(!BSP_PB_GetState(BUTTON_USER)) {
			buttonDebounce = BUTTON_RAISING;
		}
		break;
	case BUTTON_RAISING:
		if(delayRead(&buttonDelay)) {
			if(!BSP_PB_GetState(BUTTON_USER)) {
				buttonDebounce = BUTTON_UP;
				buttonRisingEdge = true;
				buttonDown = false;
			}
			else {
				buttonDebounce = BUTTON_DOWN;
			}

		}
		break;
	}
}

bool_t buttonRisingEdgeOccurred() {
	bool_t ret = buttonRisingEdge;
	buttonRisingEdge = false;
	return ret;
}

bool_t buttonFallingEdgeOccurred() {
	bool_t ret = buttonFallingEdge;
	buttonFallingEdge = false;
	return ret;
}

bool_t buttonPressed() {
	return buttonDown;
}

