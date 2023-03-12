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

void debounceFSM_init();
void debounceFSM_update();
bool_t buttonRisingEdgeOccurred();
bool_t buttonFallingEdgeOccurred();
bool_t buttonPressed();

#endif /* API_INC_API_DEBOUNCE_H_ */
