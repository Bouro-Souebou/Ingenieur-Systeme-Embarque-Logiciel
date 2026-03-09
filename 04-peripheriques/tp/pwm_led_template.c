/**
 * TP PWM - Squelette
 * Generer un PWM sur un timer (LED ou moteur), varier le rapport cyclique.
 *
 * A FAIRE :
 * - Timer (ex. TIM2 CH1), broche GPIO AF
 * - Periode ex. 1 kHz : ARR = 8400 pour 84 MHz / 10
 * - HAL_TIM_PWM_Start ; __HAL_TIM_SET_COMPARE pour le duty
 * - Entree : ADC potentiometre ou UART (ex. "PWM 500")
 */

#include <stdint.h>

#define PWM_ARR  8400u

static void pwm_init(void)
{
	/* A FAIRE : RCC timer + GPIO, TIM + canal PWM */
	(void)0;
}

static void pwm_set_duty(uint32_t value)
{
	/* A FAIRE : __HAL_TIM_SET_COMPARE(..., value) */
	(void)value;
}

int main(void)
{
	pwm_init();
	pwm_set_duty(PWM_ARR / 2);
	for (;;) { }
	return 0;
}
