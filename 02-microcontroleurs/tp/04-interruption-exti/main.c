/**
 * TP 4 - Microcontroleurs (NUCLEO-F446RE)
 * Bouton B1 (PC13) en interruption EXTI : toggle LED a chaque appui.
 */

#include <stdint.h>

#define RCC_BASE            0x40023800u
#define RCC_AHB1ENR         (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB2ENR         (*(volatile uint32_t *)(RCC_BASE + 0x44))
#define RCC_AHB1ENR_GPIOA   (1u << 0)
#define RCC_AHB1ENR_GPIOC   (1u << 2)
#define RCC_APB2ENR_SYSCFG  (1u << 14)

#define GPIOA_BASE          0x40020000u
#define GPIOA_MODER         (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR           (*(volatile uint32_t *)(GPIOA_BASE + 0x14))

#define GPIOC_BASE          0x40020800u
#define GPIOC_MODER         (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_PUPDR         (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))

#define SYSCFG_BASE         0x40013800u
#define SYSCFG_EXTICR4      (*(volatile uint32_t *)(SYSCFG_BASE + 0x14))

#define EXTI_BASE           0x40013C00u
#define EXTI_IMR            (*(volatile uint32_t *)(EXTI_BASE + 0x00))
#define EXTI_FTSR           (*(volatile uint32_t *)(EXTI_BASE + 0x0C))
#define EXTI_PR             (*(volatile uint32_t *)(EXTI_BASE + 0x14))

#define NVIC_ISER1          (*(volatile uint32_t *)(0xE000E104u))
#define EXTI15_10_IRQn      40
#define NVIC_ISER1_EXTI15_10  (1u << (EXTI15_10_IRQn - 32))

#define LED_PIN     5u
#define BTN_PIN     13u
#define EXTI13_MASK (1u << 13)

static void gpio_init(void)
{
	RCC_AHB1ENR |= RCC_AHB1ENR_GPIOA | RCC_AHB1ENR_GPIOC;
	GPIOA_MODER = (GPIOA_MODER & ~(3u << (LED_PIN * 2))) | (1u << (LED_PIN * 2));
	GPIOC_MODER &= ~(3u << (BTN_PIN * 2));
	GPIOC_PUPDR = (GPIOC_PUPDR & ~(3u << (BTN_PIN * 2))) | (1u << (BTN_PIN * 2));
}

static void exti_nvic_init(void)
{
	RCC_APB2ENR |= RCC_APB2ENR_SYSCFG;
	SYSCFG_EXTICR4 = (SYSCFG_EXTICR4 & ~(0xFu << 4)) | (2u << 4); /* PC13 => 2 */
	EXTI_IMR  |= EXTI13_MASK;
	EXTI_FTSR |= EXTI13_MASK;
	NVIC_ISER1 = NVIC_ISER1_EXTI15_10;
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI_PR & EXTI13_MASK) {
		EXTI_PR = EXTI13_MASK;
		GPIOA_ODR ^= (1u << LED_PIN);
	}
}

int main(void)
{
	gpio_init();
	exti_nvic_init();
	for (;;) {
		__asm volatile ("wfi");
	}
}
