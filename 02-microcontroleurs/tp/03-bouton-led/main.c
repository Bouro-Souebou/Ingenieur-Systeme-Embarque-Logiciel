/**
 * TP 3 - Microcontroleurs (NUCLEO-F446RE)
 * Bouton B1 (PC13) + LED LD2 (PA5) en polling.
 *
 * B1 actif a 0 : appuye = lecture 0 sur PC13.
 */

#include <stdint.h>

#define RCC_BASE            0x40023800u
#define RCC_AHB1ENR         (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_AHB1ENR_GPIOA   (1u << 0)
#define RCC_AHB1ENR_GPIOC   (1u << 2)

#define GPIOA_BASE          0x40020000u
#define GPIOA_MODER         (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR           (*(volatile uint32_t *)(GPIOA_BASE + 0x14))

#define GPIOC_BASE          0x40020800u
#define GPIOC_MODER         (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_IDR           (*(volatile uint32_t *)(GPIOC_BASE + 0x10))
#define GPIOC_PUPDR         (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))

#define LED_PIN     5u
#define BTN_PIN     13u

static void gpio_init(void)
{
	RCC_AHB1ENR |= RCC_AHB1ENR_GPIOA | RCC_AHB1ENR_GPIOC;

	/* PA5 sortie */
	GPIOA_MODER = (GPIOA_MODER & ~(3u << (LED_PIN * 2))) | (1u << (LED_PIN * 2));

	/* PC13 entrée ; optionnel : pull-up (01) pour bouton actif à 0 */
	GPIOC_MODER &= ~(3u << (BTN_PIN * 2));
	GPIOC_PUPDR = (GPIOC_PUPDR & ~(3u << (BTN_PIN * 2))) | (1u << (BTN_PIN * 2));
}

static void led_on(void)  { GPIOA_ODR |= (1u << LED_PIN); }
static void led_off(void) { GPIOA_ODR &= ~(1u << LED_PIN); }

/* B1 appuye = niveau bas => retourne 1 si appuye */
static int button_pressed(void)
{
	return (GPIOC_IDR & (1u << BTN_PIN)) == 0;
}

int main(void)
{
	gpio_init();
	for (;;) {
		if (button_pressed())
			led_on();
		else
			led_off();
	}
}
