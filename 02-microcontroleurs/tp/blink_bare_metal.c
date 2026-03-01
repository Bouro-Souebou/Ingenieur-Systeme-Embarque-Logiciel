/**
 * TP 2 - Microcontrôleurs
 * Blink LED en bare-metal (sans HAL)
 *
 * À adapter selon ta carte :
 * - RCC : activer l'horloge du port GPIO (ex. RCC_AHB1ENR pour GPIOA sur STM32F4).
 * - GPIO : base du port, broche (ex. PA5 = bit 5), mode sortie, push-pull.
 *
 * Ce fichier est un TEMPLATE : les adresses et noms de registres
 * doivent correspondre à ton MCU (voir Reference Manual).
 */

#include <stdint.h>

/* Exemple STM32F4 (à adapter) */
#define RCC_BASE        0x40023800u
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_AHB1ENR_GPIOA_EN  (1u << 0)

#define GPIOA_BASE      0x40020000u
#define GPIOA_MODER     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR       (*(volatile uint32_t *)(GPIOA_BASE + 0x14))

#define LED_PIN         5u
#define MODER_OUT       (1u << (LED_PIN * 2))   /* 01 = output */

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
