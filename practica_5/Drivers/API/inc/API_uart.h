/*
 * API_uart.h
 *
 *  Created on: Mar 12, 2023
 *      Author: gonza
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"

typedef bool bool_t;

/*
 * @brief Inicializa la UART
 * @return true si la UART se inicializo correctamente, false en caso contrario
 */
bool_t uartInit();
/*
 * @brief Imprime un string por UART
 * @param [in] pstring: puntero al string a imprimir (debe terminar en '\0´)
 */
void uartSendString(uint8_t * pstring);
/*
 * @brief Imprime un array por UART
 * @param [in] pstring: puntero al array a imprimir
 * @param [in] size: tamaño del array a imprimir
 */
void uartSendStringSize(uint8_t * pstring, uint16_t size);
/*
 * @brief Rercibe un array por UART
 * @param [in] pstring: puntero al array donde se almacenara lo recibido
 * @param [in] size: tamaño del array de recepcion
 */
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);


#endif /* API_INC_API_UART_H_ */
