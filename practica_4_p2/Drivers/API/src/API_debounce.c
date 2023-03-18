/*
 * API_debounce.c
 *
 *  Created on: Mar 11, 2023
 *      Author: gonza
 */

#include "API_debounce.h"
#include "API_delay.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */
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
static bool_t buttonPressed;

/*
 * @brief Inicializa la maquina de estados del antirrebote del pulsador
 */
void debounceFSM_init() {
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO); // Inicializo el pulsador
	delayInit(&buttonDelay, BUTTON_DEBOUNCE_TIME); // Inicializo el delay
	buttonDebounce = BUTTON_UP; // La maquina de estados inicializa con el pulsador sin presionar
	buttonPressed = false; // Inicio con el pulsador sin presionar
}

/*
 * @brief Actualiza la maquina de estados del antirrebote del pulsador
 */
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
			// Paso el tiempo de delay
			if(BSP_PB_GetState(BUTTON_USER)) {
				// El pulsador sigue presionado, indico que efectivamente se presionó
				buttonDebounce = BUTTON_DOWN;
				buttonPressed = true;
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
			// Paso el tiempo de delay
			if(!BSP_PB_GetState(BUTTON_USER)) {
				// El pulsador sigue sin ser presionado, indico que efectivamente se soltó
				buttonDebounce = BUTTON_UP;
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
 * @brief Devuelve true si se detecto una pulsacion del pulsador (flanco negativo)
 */
bool_t readKey() {
	bool_t ret;
	ret = buttonPressed; // Me hago una copia booleano que me indica si se detecto al menos un flanco negativo del pulsador (una pulsacion)
	buttonPressed = false; // Reinicializo
	return ret; // Devuelvo si se pulsó al menos una vez el pulsador
}
