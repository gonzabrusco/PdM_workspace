/*
 * API_uart.c
 *
 *  Created on: Mar 12, 2023
 *      Author: gonza
 */

#include <string.h>
#include "API_uart.h"
#include "main.h"

#define INIT_MSG "Uart Inicializada (115200 8N1)\n\r"
#define USART_BAUDRATE 115200

static UART_HandleTypeDef uartHandle;

/*
 * @brief Inicializa la UART
 * @return true si la UART se inicializo correctamente, false en caso contrario
 */
bool_t uartInit() {
	// Inicializo UART
	uartHandle.Instance = USARTx;
	uartHandle.Init.BaudRate = USART_BAUDRATE;
	uartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	uartHandle.Init.StopBits = UART_STOPBITS_1;
	uartHandle.Init.Parity = UART_PARITY_NONE;
	uartHandle.Init.Mode = UART_MODE_TX_RX;
	uartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if(HAL_UART_Init(&uartHandle) != HAL_OK) {
		return false; // Indico que fallo la inicializacion
	}

	// Inicializacion exitosa, imprimo el mensaje y devuelvo true
	uartSendString((uint8_t *)INIT_MSG);
	return true;
}

/*
 * @brief Imprime un string por UART
 * @param [in] pstring: puntero al string a imprimir (debe terminar en '\0´)
 */
void uartSendString(uint8_t *pstring) {
	if(pstring == NULL) return;
	// Calculo de timeout:
	// UART Baudrate = Bits por segundo
	// Entonces 9600 bauds por segundo = 9600 bits por segundo => 1/9600 segundos por bit = 1000/9600 milisegundos por bit.
	// 1 caracter del string = 10 bits en UART (8 bits del char + 1 partity + 1 stop)
	// Entonces el timeout va a ser = (strlen(pstring)+10) * 10 * 1000 <- agregue 10 caracteres extras de seguridad para que el timeout tenga cierto margen.
	uint16_t length = strlen((const char *)pstring); // CAlculo el largo del string a enviar
	HAL_UART_Transmit(&uartHandle, pstring, length, ((length+10)*10000)/uartHandle.Init.BaudRate); // Envio datos
}

/*
 * @brief Imprime un array por UART
 * @param [in] pstring: puntero al array a imprimir
 * @param [in] size: tamaño del array a imprimir
 */
void uartSendStringSize(uint8_t * pstring, uint16_t size) {
	if(pstring == NULL || size == 0) return;
	// Calculo de timeout igual que en uartSendString
	HAL_UART_Transmit(&uartHandle, pstring, size, ((size+10)*10000)/uartHandle.Init.BaudRate); // Envio datos
}

/*
 * @brief Rercibe un array por UART
 * @param [in] pstring: puntero al array donde se almacenara lo recibido
 * @param [in] size: tamaño del array de recepcion
 */
void uartReceiveStringSize(uint8_t * pstring, uint16_t size) {
	if(pstring == NULL || size == 0) return;
	// Calculo de timeout igual que en uartSendString
	HAL_UART_Receive(&uartHandle, pstring, size, ((size+10)*10000)/uartHandle.Init.BaudRate); // Recibo datos
}
