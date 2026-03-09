/**
 * TP SPI - Squelette
 * Objectif : lire/ecrire un peripherique SPI (capteur, flash, ecran).
 *
 * A FAIRE :
 * - Configurer SPI (MODE 0 ou 3, MSB first), GPIO MOSI/MISO/SCK/NSS
 * - Chip select : GPIO output ou NSS logiciel (pull high, drive low avant transfert)
 * - HAL_SPI_Transmit / HAL_SPI_Receive / HAL_SPI_TransmitReceive
 * - Pour un capteur : envoyer commande/registre, recevoir donnees
 *
 * Exemple : lire ID d'une flash (0x9F), recevoir 3 octets.
 */

#include <stdint.h>

static void spi_init(void)
{
	/* A FAIRE : RCC SPI + GPIO, NSS/CS en sortie */
	(void)0;
}

static void cs_low(void)  { /* A FAIRE : GPIO CS = 0 */ }
static void cs_high(void) { /* A FAIRE : GPIO CS = 1 */ }

static void spi_xfer(const uint8_t *tx, uint8_t *rx, int len)
{
	/* A FAIRE : cs_low(); HAL_SPI_TransmitReceive(...); cs_high(); */
	(void)tx;
	(void)rx;
	(void)len;
}

int main(void)
{
	/* A FAIRE : HAL_Init, clock, spi_init */
	spi_init();

	uint8_t cmd = 0x9F;
	uint8_t id[3];
	cs_low();
	/* A FAIRE : envoyer cmd, recevoir 3 octets dans id */
	cs_high();

	/* A FAIRE : afficher id[] sur UART ou LED */
	(void)id;
	for (;;) { }
	return 0;
}
