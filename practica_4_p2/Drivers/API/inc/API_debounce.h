/*
 * API_debounce.h
 *
 *  Created on: Mar 11, 2023
 *      Author: gonza
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include <stdbool.h>

typedef bool bool_t;

/*
 * @brief Inicializa la maquina de estados del antirrebote del pulsador
 */
void debounceFSM_init();

/*
 * @brief Actualiza la maquina de estados del antirrebote del pulsador
 */
void debounceFSM_update();

/*
 * @brief Devuelve true si se detecto una pulsacion del pulsador (flanco negativo)
 */
bool_t readKey();

#endif /* API_INC_API_DEBOUNCE_H_ */
