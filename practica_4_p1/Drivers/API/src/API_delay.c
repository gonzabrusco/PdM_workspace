/*
 * API_delay.c
 *
 *  Created on: Mar 9, 2023
 *      Author: gonza
 */

#include "API_delay.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */

/*
 * @brief Inicializa un delay
 * @param [in] delay: puntero a la variable que almacena el delay
 * @param [in] duration: la duracion del delay
 */
void delayInit( delay_t * delay, tick_t duration ) {
	if(delay == NULL) return; // Chequeo de parametros
	delay->duration = duration; // Guardo duracion
	delay->running = false; // Inicializa frenado
}

/*
 * @brief Lee un delay
 * @param [in] delay: puntero a la variable que almacena el delay
 * @param [in] duration: la duracion del delay
 * @return true si se cumplio el delay, false en caso contrario
 */
bool_t delayRead( delay_t * delay ) {
	if(delay == NULL) return false; // Chequeo de parametros
	if(!delay->running) {
		// No esta ejecutandose, tomo marca de tiempo y lo marco como corriendo
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}
	else if(HAL_GetTick() - delay->startTime >= delay->duration) {
		// Se cumplio el tiempo, marco el delay como frenado y retorno avisando que termino el tiempo.
		delay->running = false;
		return true;
	}
	return false;
}

/*
 * @brief Modifica la duracion de un delay
 * @param [in] delay: puntero a la variable que almacena el delay
 * @param [in] duration: la duracion del delay
 */
void delayWrite( delay_t * delay, tick_t duration ) {
	if(delay == NULL) return; // Chequeo de parametros
	delay->duration = duration; // Actualizo la duracion
}
