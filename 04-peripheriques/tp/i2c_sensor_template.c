/**
 * TP I2C - Squelette
 * Lire un capteur I2C (ex. temperature) ou EEPROM, afficher sur UART.
 *
 * A FAIRE :
 * - Configurer I2C (ex. I2C1, 100 kHz), GPIO SDA/SCL en AF open-drain
 * - HAL_I2C_Mem_Read pour capteur avec registre (adresse 7b, reg, 1 ou 2 octets)
 * - Convertir valeur lue en string et envoyer via UART
 *
 * Exemple : adresse 0x48, registre 0x00, lire 2 octets (temperature)
 */

#include <stdint.h>

static void i2c_init(void)
{
	/* A FAIRE : RCC I2C + GPIO, GPIO AF, I2C 100kHz */
	(void)0;
}

static int i2c_read_reg(uint8_t dev_addr, uint8_t reg, uint8_t *buf, int len)
{
	/* A FAIRE : HAL_I2C_Mem_Read */
	(void)dev_addr;
	(void)reg;
	(void)buf;
	(void)len;
	return 0;
}

int main(void)
{
	i2c_init();
	for (;;) {
		uint8_t buf[2];
		/* A FAIRE : i2c_read_reg(0x48, 0x00, buf, 2); convertir, envoyer UART */
		(void)buf;
	}
	return 0;
}
