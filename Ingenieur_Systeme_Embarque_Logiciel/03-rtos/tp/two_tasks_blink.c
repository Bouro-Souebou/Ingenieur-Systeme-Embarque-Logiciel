/**
 * TP 3 - FreeRTOS
 * Deux tâches : une fait clignoter une LED, l'autre simule un travail périodique.
 *
 * Prérequis : projet avec FreeRTOS (CMSIS-RTOS ou FreeRTOS kernel),
 * clock et GPIO déjà initialisés.
 *
 * À intégrer dans ton main() après init hardware et avant vTaskStartScheduler().
 */

#include "FreeRTOS.h"
#include "task.h"

/* Adapter selon ta carte (ou utiliser HAL_GPIO_WritePin) */
extern void led_on(void);
extern void led_off(void);

static void task_led(void *pvParameters)
{
	for (;;) {
		led_on();
		vTaskDelay(pdMS_TO_TICKS(500));
		led_off();
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

static void task_worker(void *pvParameters)
{
	for (;;) {
		/* Simuler un travail (calcul, envoi, etc.) */
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void create_demo_tasks(void)
{
	xTaskCreate(task_led,   "LED",   128, NULL, 1, NULL);
	xTaskCreate(task_worker, "Worker", 128, NULL, 2, NULL);
}

/*
 * Dans main():
 *   create_demo_tasks();
 *   vTaskStartScheduler();
 *   for (;;) ;  // ne doit jamais être atteint
 */
