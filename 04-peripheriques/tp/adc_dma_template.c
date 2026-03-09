/**
 * TP ADC + DMA - Squelette
 * Objectif : acquisition continue d'un canal ADC via DMA, moyenne ou envoi UART.
 *
 * A FAIRE :
 * - Configurer ADC (canal, resolution 12b), DMA en mode circulaire
 * - Buffer (ex. uint16_t adc_buf[64]), HAL_ADC_Start_DMA(&hadc, (uint32_t*)adc_buf, 64)
 * - Option 1 : dans une tache ou main loop, calculer moyenne du buffer et envoyer UART
 * - Option 2 : envoyer les echantillons en binaire ou CSV (sprintf) par UART
 *
 * Piste : DMA en double buffer (HT/TC callbacks) pour traiter un bloc pendant que l'autre se remplit.
 */

#include <stdint.h>

#define ADC_BUF_LEN  64

static uint16_t adc_buf[ADC_BUF_LEN];

static void adc_dma_init(void)
{
	/* A FAIRE : RCC ADC + DMA + GPIO (canal analogique), DMA en circulaire */
	(void)adc_buf;
}

static uint32_t adc_average(const uint16_t *buf, int n)
{
	uint32_t sum = 0;
	for (int i = 0; i < n; i++) sum += buf[i];
	return sum / (uint32_t)n;
}

int main(void)
{
	/* A FAIRE : HAL_Init, clock, adc_dma_init */
	adc_dma_init();
	/* A FAIRE : HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_buf, ADC_BUF_LEN) */

	for (;;) {
		/* A FAIRE : attendre demi-buffer (optionnel), puis moyenne = adc_average(adc_buf, ADC_BUF_LEN);
		 *          envoyer par UART (sprintf + uart_send_string) */
		(void)adc_average;
	}
	return 0;
}
