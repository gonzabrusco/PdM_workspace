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
 * @brief Indica si se soltó el pulsador al menos una vez desde la última lectura de esta funcion
 * @return Devuelve true si se soltó el pulsador al menos una vez desde la última lectura de esta funcion, false en caso contrario.
 */
bool_t buttonReleased();

/*
 * @brief Indica si se presionó el pulsador al menos una vez desde la última lectura de esta funcion
 * @return Devuelve true si se presionó el pulsador al menos una vez desde la última lectura de esta funcion, false en caso contrario.
 */
bool_t buttonPressed();

/*
 * @brief Indica si el pulsador esta actualmente presionado
 * @return Devuelve true si el pulsador esta actualmente presionado, false en caso contrario.
 */
bool_t buttonDown();

#endif /* API_INC_API_DEBOUNCE_H_ */
