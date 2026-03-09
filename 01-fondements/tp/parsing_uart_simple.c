/**
 * TP 1.3 - Fondements
 * Parser une ligne type "CMD arg1 arg2\r\n" et appeler une action selon CMD
 *
 * Sur PC : lire depuis stdin (fgets). Sur cible : remplacer par lecture UART
 * (buffer circulaire rempli par l'ISR RX, ou getchar depuis UART).
 *
 * Compilation : gcc -o parsing parsing_uart_simple.c && ./parsing
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static int str_icmp(const char *a, const char *b)
{
	while (*a && *b && tolower((unsigned char)*a) == tolower((unsigned char)*b)) { a++; b++; }
	return (int)(unsigned char)tolower(*a) - (int)(unsigned char)tolower(*b);
}

#define LINE_MAX  80
#define CMD_MAX   16
#define ARG_MAX   2

static char line_buf[LINE_MAX];
static char cmd[CMD_MAX];
static char *argv[ARG_MAX];
static int argc;

/* Supprimer \r et \n en fin de ligne */
static void trim_crlf(char *s)
{
	size_t n = strlen(s);
	while (n > 0 && (s[n-1] == '\r' || s[n-1] == '\n')) {
		s[--n] = '\0';
	}
}

/* Découper "CMD arg1 arg2" en cmd, argv[0]=arg1, argv[1]=arg2, argc=2 */
static int parse_line(char *line)
{
	argc = 0;
	cmd[0] = '\0';
	argv[0] = argv[1] = NULL;

	char *p = line;
	while (*p == ' ' || *p == '\t') p++;
	if (!*p) return -1;

	char *start = p;
	while (*p && *p != ' ' && *p != '\t') p++;
	size_t cmd_len = (size_t)(p - start);
	if (cmd_len >= CMD_MAX) cmd_len = CMD_MAX - 1;
	memcpy(cmd, start, cmd_len);
	cmd[cmd_len] = '\0';

	while (*p == ' ' || *p == '\t') p++;
	while (*p && argc < ARG_MAX) {
		start = p;
		while (*p && *p != ' ' && *p != '\t') p++;
		argv[argc++] = start;
		if (*p) *p++ = '\0';
		while (*p == ' ' || *p == '\t') p++;
	}
	return 0;
}

/* ---------- Actions selon CMD (à compléter sur cible) ---------- */
static void do_led_on(void)
{
	printf("Action: LED ON\n");
	/* Sur cible : GPIOA->BSRR = (1u << 5); */
}

static void do_led_off(void)
{
	printf("Action: LED OFF\n");
	/* Sur cible : GPIOA->BSRR = (1u << (5+16)); */
}

static void do_set(uint32_t value)
{
	printf("Action: SET %lu\n", (unsigned long)value);
}

static void do_help(void)
{
	printf("Commandes: LED ON, LED OFF, SET <val>, HELP\n");
}

/* Dispatch : appeler la bonne action selon cmd */
static void dispatch(void)
{
	if (str_icmp(cmd, "LED") == 0) {
		if (argc >= 1) {
			if (str_icmp(argv[0], "ON") == 0)  do_led_on();
			else if (str_icmp(argv[0], "OFF") == 0) do_led_off();
			else printf("? LED ON|OFF\n");
		} else printf("? LED ON|OFF\n");
	} else if (str_icmp(cmd, "SET") == 0) {
		if (argc >= 1) {
			uint32_t val = (uint32_t)strtoul(argv[0], NULL, 0);
			do_set(val);
		} else printf("? SET <value>\n");
	} else if (str_icmp(cmd, "HELP") == 0) {
		do_help();
	} else if (cmd[0] != '\0') {
		printf("? Commande inconnue: %s\n", cmd);
	}
}

int main(void)
{
	printf("Parser UART simple. Entrer une ligne (ex: LED ON, SET 42, HELP). Ctrl+D pour quitter.\n\n");

	while (fgets(line_buf, (int)sizeof(line_buf), stdin) != NULL) {
		trim_crlf(line_buf);
		if (parse_line(line_buf) == 0) {
			dispatch();
		}
	}
	return 0;
}
