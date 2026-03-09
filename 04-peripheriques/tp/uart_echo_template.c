/**
 * TP UART - Squelette
 * Objectif : configurer USART, envoyer une banniere au demarrage, echo RX -> TX.
 *
 * A FAIRE :
 * - Inclure les en-tetes HAL/Cube (ex. stm32xxx_hal.h)
 * - Declarer handle UART (ex. UART_HandleTypeDef huart1)
 * - uart_init() : activer horloge GPIO et USART, configurer TX/RX, 115200 8N1
 * - uart_send_string(const char *s) : boucle sur les caracteres, HAL_UART_Transmit
 * - main() : HAL_Init, SystemClock_Config, uart_init, envoyer "UART OK\r\n"
 * - Boucle : si donnees recues (HAL_UART_Receive ou IT), renvoyer les memes (echo)
 *
 * Piste : reception en IT + callback HAL_UART_RxCpltCallback qui renvoie le byte
 *        ou met le byte dans une queue FreeRTOS pour une tache qui parse (LED ON/OFF).
 */

#include <stdint.h>

/* A FAIRE : includes HAL et GPIO/USART
#include "stm32f4xx_hal.h"
*/

static void uart_init(void)
{
	/* A FAIRE : RCC GPIO + USART, GPIO AF, NVIC si IT */
	(void)0;
}

static void uart_send_string(const char *s)
{
	/* A FAIRE : HAL_UART_Transmit(..., (uint8_t*)s, len, timeout) */
	(void)s;
}

int main(void)
{
	/* A FAIRE : HAL_Init(); SystemClock_Config(); */
	uart_init();
	uart_send_string("UART OK\r\n");

	for (;;) {
		/* A FAIRE : reception (polling ou IT) puis renvoi echo */
	}
	return 0;
}
