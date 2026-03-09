/**
 * TP 2 - Microcontroleurs (NUCLEO-F446RE)
 * Blink LED LD2 (PA5) en bare-metal.
 *
 * Registres STM32F446 : RCC AHB1ENR, GPIOA MODER/ODR.
 */

#include <stdint.h>

#define RCC_BASE        0x40023800u
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_AHB1ENR_GPIOA_EN  (1u << 0)

#define GPIOA_BASE      0x40020000u
#define GPIOA_MODER     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR       (*(volatile uint32_t *)(GPIOA_BASE + 0x14))

#define LED_PIN         5u
#define MODER_OUT       (1u << (LED_PIN * 2))

static void gpio_init(void)
{
	RCC_AHB1ENR |= RCC_AHB1ENR_GPIOA_EN;
	GPIOA_MODER = (GPIOA_MODER & ~(3u << (LED_PIN * 2))) | MODER_OUT;
}

static void led_on(void)  { GPIOA_ODR |= (1u << LED_PIN); }
static void led_off(void) { GPIOA_ODR &= ~(1u << LED_PIN); }

static void delay_approx(uint32_t count)
{
	while (count--) { __asm volatile ("nop"); }
}

int main(void)
{
	gpio_init();
	for (;;) {
		led_on();
		delay_approx(500000u);
		led_off();
		delay_approx(500000u);
	}
}
