#include "../include/version.h"
#include "../include/tty.h"
#include "../include/io.h"
#include "../include/kbd.h"
#include "../include/string.h"
#include "../include/time.h"
#include "../include/math_shell.h"
#include "../include/parsing.h"
#include "../include/bool.h"
#include "../include/sha224.h"
#include "../include/sha256.h"
#include "../include/utils.h"
#include "../include/easter.h"
#include "../include/sleep.h"
#include "../include/thread.h"
#include "../include/memory.h"
#include "../include/shell_history.h"

#define DEBUG false

#define BUFFER_SIZE 1024

uint8_t numlock = true;
uint8_t capslock = false;
uint8_t scrolllock = false;
uint8_t shift = false;
char current_version[7];

int main(void)
{
	char buffer[BUFFER_SIZE];
	char *string;
	char *buff;
	uint8_t byte;
	node_t *head = NULL;

	terminal_initialize(default_font_color, COLOR_BLACK);
	terminal_set_colors(COLOR_LIGHT_GREEN, COLOR_BLACK);
	sprintf(current_version, "%u.%u.%u", V1, V2, V3 + 1);
	print_logo();
	about(current_version);
	printf("\n\tType \"help\" for a list of commands.\n\n");
	// printf("\tCurrent datetime: ");
	// datetime();
	printf("\n\tWelcome!\n\n");

	terminal_set_colors(default_font_color, COLOR_BLACK);

	// initialize heap
	heap_init();

#if DEBUG
	// memory test
	int *a = (int *)kmalloc(sizeof(int));
	void *b = kmalloc(5000);
	void *c = kmalloc(50000);
	*a = 1;
	printf("\na: %d", *a);
	printf("\na: %p", (void *)a);
	printf("\nb: %p", (void *)b);
	printf("\nc: %p", (void *)c);
	// int *b = (int *)kmalloc(0x1000);
	// int *c = (int *)kmalloc(sizeof(int));
	// printf("\nb: %x", b);
	// printf("\nc: %x", c);
	// kfree(b);
	// int *d = (int *)kmalloc(0x1000); // here should be adress of B
	// printf("\nd: %x", d);
	// kfree(d);
	// kfree(c);
	kfree(a);
	kfree(b);
	kfree(c);
#endif

	strcpy(&buffer[strlen(buffer)], "");
	print_prompt();
	while (true)
	{
		while (byte = scan())
		{
			if (byte == ENTER)
			{
				strcpy(buffer, tolower(buffer));
				insert_at_head(&head, create_new_node(buffer));

				if (strlen(buffer) > 0 && strcmp(buffer, "exit") == 0)
				{
					printf("\nGoodbye!");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "hello") == 0)
				{
					printf("\nHi!");
				}
				if (strlen(buffer) > 0 && strcmp(buffer, "why") == 0)
				{
					why();
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "sha256(") != NULL)
				{
					char *parser;
					char string[64];
					parser = strstr(buffer, "sha256(");
					parser += strlen("sha256(");
					parse_string(string, parser, ')');
					sha256(string);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "sha224(") != NULL)
				{
					char *parser;
					char string[64];
					parser = strstr(buffer, "sha224(");
					parser += strlen("sha224(");
					parse_string(string, parser, ')');
					sha224(string);
				}
				else if (math_func(buffer))
				{
					math_shell(buffer);
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "math") == 0)
				{
					printf("\n\n\tMathematical functions:\n");
					printf("\n\t rand()             - \tpseudo random number generator");
					printf("\n\t srand()            - \tpseudo random number generator seed");
					printf("\n\t fact(x)            - \treturns factorial of x");
					printf("\n\t abs(x)             - \treturns absolute value of x");
					printf("\n\t sqrt(x)            - \treturns square root of x");
					printf("\n\t pow(x,y)           - \treturns the y power of x");
					printf("\n\t exp(x)             - \treturns the natural exponential of x");
					printf("\n\t ln(x)              - \treturns the natural logarithm of x");
					printf("\n\t log10(x)           - \treturns the logarithm of x base 10");
					printf("\n\t log(x,y)           - \treturns the logarithm of x base y");
					printf("\n\t sin(x)             - \treturns sine of x");
					printf("\n\t cos(x)             - \treturns cosine of x");
					printf("\n\t tan(x)             - \treturns tangent of x");
					printf("\n\t asin(x)            - \treturns arcsine of x");
					printf("\n\t acos(x)            - \treturns arccosine of x");
					printf("\n\t atan(x)            - \treturns arctangent of x");
					printf("\n\t sinh(x)            - \treturns hyperbolic sine of x");
					printf("\n\t cosh(x)            - \treturns hyperbolic cosine of x");
					printf("\n\t tanh(x)            - \treturns hyperbolic tangent of x");
					printf("\n\t asinh(x)           - \treturns inverse hyperbolic sine of x");
					printf("\n\t acosh(x)           - \treturns inverse hyperbolic cosine of x");
					printf("\n\t atanh(x)           - \treturns inverse hyperbolic tangent of x");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "crypto") == 0)
				{
					printf("\n\nCryptography utilities:\n");
					printf("\n\t sha224(string)     - \tSHA-224 hashing");
					printf("\n\t sha256(string)     - \tSHA-256 hashing");
					printf("\n");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "help") == 0)
				{
					printf("\n\n\tBasic kernel commands:\n");
					printf("\n\t about              - \tabout PrimusOS");
					printf("\n\t math               - \tlists all mathematical functions");
					printf("\n\t crypto             - \tlists all cryptography utilities");
					printf("\n\t clear              - \tclears the screen");
					printf("\n\t fontcolor          - \tchange default font color");
					printf("\n\t datetime           - \tdisplays current date and time");
					printf("\n\t date               - \tdisplays current date");
					printf("\n\t clock              - \tdisplays clock");
					// printf("\n\t history            - \tdisplays commands history");
					printf("\n\t reboot             - \treboots system");
					printf("\n\t shutdown           - \tsends shutdown signal");
					printf("\n");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "about") == 0)
				{
					about(current_version);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "315_print(") != NULL)
				{
					// 315_print(sdkjfhsj)
					// sdkjfhsj
					char *parser;
					char string[64];
					parser = strstr(buffer, "315_print(");
					parser += strlen("315_print(");
					parse_string(string, parser, ')');
					printf("\n%s", string);
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "315") == 0)
				{
					printf("\n\nOur functions 315\n\t- csci315\n\t- 315_print(string)\n\t- 315_history\n\t- 315_colorHelp\n\t- 315_color(color number)\n");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "csci315") == 0)
				{
					printf("\n\n\tGreetings Doctor :)\n");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "315_history") == 0)
				{
					print_history(head);
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "315_colorhelp") == 0)
				{
					printf("\n\nUser 315_color(color number) to change font color\n\n");
					printf("COLOR_BLACK = 0\n");
					printf("COLOR_BLUE = 1\n");
					printf("COLOR_GREEN = 2\n");
					printf("COLOR_CYAN = 3\n");
					printf("COLOR_RED = 4\n");
					printf("COLOR_MAGENTA = 5\n");
					printf("COLOR_BROWN = 6\n");
					printf("COLOR_LIGHT_GREY = 7\n");
					printf("COLOR_DARK_GREY = 8\n");
					printf("COLOR_LIGHT_BLUE = 9\n");
					printf("COLOR_LIGHT_GREEN = 10\n");
					printf("COLOR_LIGHT_CYAN = 11\n");
					printf("COLOR_LIGHT_RED = 12\n");
					printf("COLOR_LIGHT_MAGENTA = 13\n");
					printf("COLOR_LIGHT_BROWN = 14\n");
					printf("COLOR_WHITE = 15\n");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "315_color(") != NULL)
				{

					char *parser;
					uint32_t num;
					parser = strstr(buffer, "315_color(");
					parser += strlen("315_color(");
					// parse_string(string, parser, ')');
					num = parse_int(parser, ')');
					if (num >= 0 && num <= 15)
					{
						terminal_set_colors(num, COLOR_BLACK);
						printf("\nDone :) nice color btw");
					}
					else
					{
						printf("\n Invalid color code use 315_colorhelp to display color codes");
					}
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "fontcolor") == 0)
				{
					default_font_color = change_font_color();
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "clear") == 0)
				{
					terminal_initialize(default_font_color, COLOR_BLACK);
					strcpy(&buffer[strlen(buffer)], "");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "datetime") == 0)
				{
					printf("\nCurrent datetime: ");
					datetime();
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "date") == 0)
				{
					printf("\nCurrent date: ");
					date();
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "clock") == 0)
				{
					printf("\nCurrent clock: ");
					clock();
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "reboot") == 0)
				{
					reboot();
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "shutdown") == 0)
				{
					shutdown();
				}
				else if (strlen(buffer) == 0)
				{
				}
				else
				{
					printf("\n'%s' is not a recognized command. ", buffer);
				}
				print_prompt();
				memset(buffer, 0, BUFFER_SIZE);
				strcpy(&buffer[strlen(buffer)], "");
				break;
			}
			else if ((byte == BACKSPACE) && (strlen(buffer) == 0))
			{
			}
			else if (byte == BACKSPACE)
			{
				char c = normalmap[byte];
				char *s;
				s = ctos(s, c);
				printf("%s", s);
				buffer[strlen(buffer) - 1] = '\0';
			}
			else
			{
				char c1 = togglecode[byte];
				char c2 = shiftcode[byte];
				char c;
				if (c1 == CAPSLOCK)
				{
					if (!capslock)
					{
						capslock = true;
					}
					else
					{
						capslock = false;
					}
				}
				if (capslock)
				{
					c = capslockmap[byte];
				}
				else if (shift)
				{
					c = shiftmap[byte];
					shift = false;
				}
				else
				{
					c = normalmap[byte];
				}
				char *s;
				s = ctos(s, c);
				printf("%s", s);
				strcpy(&buffer[strlen(buffer)], s);
				if (byte == 0x2A || byte == 0x36)
				{
					shift = true;
				}
			}
			move_cursor(get_terminal_row(), get_terminal_col());
		}
	}
	return 0;
}
