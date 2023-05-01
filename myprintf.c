#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void print_int(int constant)
{
    // Declare variables at the beginning of the function (C90 standard)
    unsigned int num;
    int sign;
    char buffer[20];
    int i = 0;

    // Determine sign and absolute value of constant
    sign = (constant < 0);
    num = (sign ? -constant : constant);

    // Convert integer to string
    do {
        buffer[i++] = num % 10 + '0';
    } while ((num /= 10) > 0);
    if (sign) buffer[i++] = '-';
    while (--i >= 0) {
        putchar(buffer[i]);
    }
}

void print_string(char* constant)
{
    printf("%s", constant);
}

void print_rot13(char* constant)
{
    // Declare variables at the beginning of the function (C90 standard)
    int length;
    char buffer[256];
    char *pstr = buffer;

    // Determine length of constant string
    length = strlen(constant);

    // Apply rot13 cipher to constant string
    for (int i = 0; i < length; i++) {
        if (constant[i] >= 'a' && constant[i] <= 'z') {
            *pstr++ = (constant[i] - 'a' + 13) % 26 + 'a';
        } else if (constant[i] >= 'A' && constant[i] <= 'Z') {
            *pstr++ = (constant[i] - 'A' + 13) % 26 + 'A';
        } else {
            *pstr++ = constant[i];
        }
    }

    // Terminate buffer string
    *pstr = '\0';

    // Print buffer string
    printf("%s", buffer);
}

void myprintf(char* format, ...)
{
    va_list args;
    va_start(args, format);

    // Declare variables at the beginning of the function (C90 standard)
    int count = 0;
    int constant;
    char* str;

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'd': {
                    // Read integer argument and print as decimal
                    constant = va_arg(args, int);
                    print_int(constant);
                    break;
                }
                case 's': {
                    // Read string argument and print
                    str = va_arg(args, char*);
                    print_string(str);
                    break;
                }
                case 'R': {
                    // Read string argument and print rot13 cipher
                    str = va_arg(args, char*);
                    print_rot13(str);
                    break;
                }
            }
        } else {
            // Print non-format characters
            putchar(*format);
        }
        format++;
    }

    va_end(args);
}

int main()
{
    // Test myprintf function with different format specifiers
    int num1 = 123;
    float num2 = 3.14;
    char num3 = '!';
    char str[] = "Welcome to our team's printf project";
    char rot13_str[] = "Excellent project\n";

    myprintf("%d\n", num1);
    myprintf("%f\n", num2);
    myprintf("%c\n", num3);
    myprintf("%s\n", str);
    myprintf("%R\n", rot13_str);

    return 0;
}

