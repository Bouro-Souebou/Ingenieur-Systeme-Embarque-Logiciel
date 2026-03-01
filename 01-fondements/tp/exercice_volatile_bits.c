/**
 * TP 1.1 - C pour l'embarqué
 * Exercice : volatile et accès aux bits
 *
 * À faire :
 * 1. Compiler et exécuter sur PC (gcc -o exo exo.c && ./exo) pour vérifier la logique.
 * 2. Adapter les adresses pour ta cible (ex. STM32) et tester sur carte.
 */

#include <stdint.h>
#include <stdio.h>

/* Simulation d'un registre GPIO (pour test sur PC) */
#if defined(__linux__) || defined(__APPLE__)
static uint32_t sim_reg = 0;
#define REG_GPIO_ODR  (&sim_reg)
#else
/* Sur cible : adresse réelle, ex. GPIOA->ODR */
#define REG_GPIO_ODR  ((volatile uint32_t *)0x4001080C)
#endif

/* Mettre le bit 'n' du registre à 1 */
void set_bit(volatile uint32_t *reg, unsigned int n)
{
	*reg |= (1u << n);
}

/* Mettre le bit 'n' du registre à 0 */
void clear_bit(volatile uint32_t *reg, unsigned int n)
{
	*reg &= ~(1u << n);
}

/* Lire le bit 'n' */
uint32_t read_bit(volatile uint32_t *reg, unsigned int n)
{
	return (*reg >> n) & 1u;
}

/* Écrire un champ de 4 bits à la position 'pos' (bits pos..pos+3) */
void write_field_4(volatile uint32_t *reg, unsigned int pos, uint32_t value)
{
	uint32_t mask = 0xFu << pos;
	*reg = (*reg & ~mask) | ((value & 0xFu) << pos);
}

int main(void)
{
	volatile uint32_t *odr = (volatile uint32_t *)REG_GPIO_ODR;

	set_bit(odr, 5);   /* allumer "LED" sur bit 5 */
	printf("Après set_bit(5): 0x%08X\n", (unsigned)*odr);

	clear_bit(odr, 5);
	printf("Après clear_bit(5): 0x%08X\n", (unsigned)*odr);

	write_field_4(odr, 8, 0x3);  /* exemple : mode 3 sur bits 8..11 */
	printf("Après write_field_4(8, 3): 0x%08X\n", (unsigned)*odr);

	return 0;
}
