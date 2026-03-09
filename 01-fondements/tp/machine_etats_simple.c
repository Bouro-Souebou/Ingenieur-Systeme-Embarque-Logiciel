/**
 * TP 1.2 - Fondements
 * Machine a etats : bouton + LED avec delai anti-rebond logiciel
 *
 * Sur PC : simule le bouton par une touche (espace). La LED par un message.
 * Sur cible : remplacer button_read() par lecture GPIO et led_set() par ODR.
 *
 * Compilation PC : gcc -o machine_etats machine_etats_simple.c && ./machine_etats
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

static int sim_key = 0;

static bool button_read(void)
{
	if (sim_key != 0) {
		int k = sim_key;
		sim_key = 0;
		return (k == ' ' || k == 'b' || k == 'B');
	}
	return false;
}

static void led_set(bool on)
{
	printf("%s\n", on ? "[LED ON]" : "[LED OFF]");
	(void)on;
}

#define DEBOUNCE_MS    50
#define TICK_MS        10

typedef enum {
	STATE_LED_OFF,
	STATE_LED_ON,
	STATE_DEBOUNCE_OFF,
	STATE_DEBOUNCE_ON
} state_t;

static state_t state = STATE_LED_OFF;
static uint32_t debounce_count = 0;

static void tick(bool button_raw)
{
	switch (state) {
	case STATE_LED_OFF:
		if (button_raw) {
			state = STATE_DEBOUNCE_ON;
			debounce_count = DEBOUNCE_MS / TICK_MS;
		}
		break;
	case STATE_DEBOUNCE_ON:
		if (!button_raw) { state = STATE_LED_OFF; break; }
		debounce_count--;
		if (debounce_count == 0) {
			state = STATE_LED_ON;
			led_set(true);
		}
		break;
	case STATE_LED_ON:
		if (button_raw) {
			state = STATE_DEBOUNCE_OFF;
			debounce_count = DEBOUNCE_MS / TICK_MS;
		}
		break;
	case STATE_DEBOUNCE_OFF:
		if (button_raw) {
			debounce_count--;
			if (debounce_count == 0) {
				state = STATE_LED_OFF;
				led_set(false);
			}
		} else {
			state = STATE_LED_ON;
		}
		break;
	}
}

int main(void)
{
	printf("Machine a etats : bouton + LED (anti-rebond)\n");
	printf("Sur PC : appuyer sur ESPACE pour simuler le bouton. Quitter avec Ctrl+C.\n\n");

	for (;;) {
		if (scanf("%c", (char*)&sim_key) == 1 && sim_key != '\n')
			;
		bool btn = button_read();
		tick(btn);
		for (volatile uint32_t i = 0; i < 50000; i++) { (void)i; }
	}
	return 0;
}
