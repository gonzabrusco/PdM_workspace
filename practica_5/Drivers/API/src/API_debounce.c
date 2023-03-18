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
static bool_t buttonPushedDown = false;

void debounceFSM_init() {
	/* Initialize BSP PB for BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	delayInit(&buttonDelay, BUTTON_DEBOUNCE_TIME); // Inicializo el delay antirrebote
	buttonDebounce = BUTTON_UP;
	buttonRisingEdge = false;
	buttonFallingEdge = false;
	buttonPushedDown = false;
}

void debounceFSM_update() {
	switch (buttonDebounce) {
	case BUTTON_UP:
		if(BSP_PB_GetState(BUTTON_USER)) {
			// Se detecto que presionaron el pulsador, inicio proceso antirrebote.
			buttonDebounce = BUTTON_FALLING;
		}
		break;
	case BUTTON_FALLING:
		// Espero el tiempo configurado antes de volver a chequear el valor del pulsador
		if(delayRead(&buttonDelay)) {
			// Paso el tiempo de delay antirrebote
			if(BSP_PB_GetState(BUTTON_USER)) {
				// El pulsador sigue presionado, indico que efectivamente se presionó
				buttonDebounce = BUTTON_DOWN;
				buttonFallingEdge = true;
				buttonPushedDown = true;
			}
			else {
				// Paso el tiempo pero no estaba presionado, lo interpreto como un rebote, indico que el pulsador sigue NO presionado.
				buttonDebounce = BUTTON_UP;
			}
		}
		break;
	case BUTTON_DOWN:
		if(!BSP_PB_GetState(BUTTON_USER)) {
			// Se detecto que soltaron el pulsador, inicio proceso antirrebote.
			buttonDebounce = BUTTON_RAISING;
		}
		break;
	case BUTTON_RAISING:
		// Espero el tiempo configurado antes de volver a chequear el valor del pulsador
		if(delayRead(&buttonDelay)) {
			// Paso el tiempo de delay antirrebote
			if(!BSP_PB_GetState(BUTTON_USER)) {
				// El pulsador sigue sin ser presionado, indico que efectivamente se soltó
				buttonDebounce = BUTTON_UP;
				buttonRisingEdge = true;
				buttonPushedDown = false;
			}
			else {
				// Paso el tiempo pero estaba presionado, lo interpreto como un rebote, indico que el pulsador sigue presionado.
				buttonDebounce = BUTTON_DOWN;
			}
		}
		break;
	}
}

/*
 * @brief Indica si se soltó el pulsador al menos una vez desde la última lectura de esta funcion
 * @return Devuelve true si se soltó el pulsador al menos una vez desde la última lectura de esta funcion, false en caso contrario.
 */
bool_t buttonReleased() {
	bool_t ret = buttonRisingEdge;
	buttonRisingEdge = false;
	return ret;
}

/*
 * @brief Indica si se presionó el pulsador al menos una vez desde la última lectura de esta funcion
 * @return Devuelve true si se presionó el pulsador al menos una vez desde la última lectura de esta funcion, false en caso contrario.
 */
bool_t buttonPressed() {
	bool_t ret = buttonFallingEdge;
	buttonFallingEdge = false;
	return ret;
}

/*
 * @brief Indica si el pulsador esta actualmente presionado
 * @return Devuelve true si el pulsador esta actualmente presionado, false en caso contrario.
 */
bool_t buttonDown() {
	return buttonPushedDown;
}

