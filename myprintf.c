#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

void print_int(int constant, int base, int uppercase) {
    char buffer[50];
    char *pstr = &buffer[49];
    *pstr = '\0';
    int sign = (constant < 0);
    if (sign) {
        constant = -constant;
    }
    if (constant == 0) {
        *(--pstr) = '0';
    }
    while (constant != 0) {
        int digit = constant % base;
        *(--pstr) = (digit < 10) ? digit + '0' : (uppercase ? 'A' : 'a') + digit - 10;

        constant /= base;
    }
    if (sign) {
        *(--pstr) = '-';
    }
    printf("%s", pstr);
}

void print_float(double constant, int precision) {
    char format[10];
    snprintf(format, sizeof(format), "%%.%df", precision);
    printf(format, constant);
}

void print_string(char *constant) {
    printf("%s", constant);
}

void print_char(char constant) {
    printf("%c", constant);
}

void print_rot13(char *constant) {
    char buffer[strlen(constant) + 1];
    strcpy(buffer, constant);
    char *pstr = buffer;
    while (*pstr) {
        if (isalpha(*pstr)) {
            if ((*pstr >= 'a' && *pstr <= 'm') || (*pstr >= 'A' && *pstr <= 'M')) {
                *pstr += 13;
            } else {
                *pstr -= 13;
            }
        }
        pstr++;
    }
    printf("%s", buffer);
}

int myprintf(char *format, ...) {
    va_list args;
    va_start(args, format);
    int count = 0;
    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'd':
                case 'i':
                    print_int(va_arg(args, int), 10, 0);
                    break;
                case 'o':
                    print_int(va_arg(args, int), 8, 0);
                    break;
                case 'u':
                    print_int(va_arg(args, int), 10, 0);
                    break;
                case 'x':
                    print_int(va_arg(args, int), 16, 0);
                    break;
                case 'X':
                    print_int(va_arg(args, int), 16, 1);
                    break;
                case 'f':
                    print_float(va_arg(args, double), 6);
                    break;
                case 'c':
                    print_char(va_arg(args, int));
                    break;
                case 's':
                    print_string(va_arg(args, char *));
                    break;
                case 'R':
                    print_rot13(va_arg(args, char *));
                    break;
                default:
                    printf("Unsupported conversion specifier: %%%c\n", *format);
                    break;
            }
            format++;
        } else {
            printf("%c", *format++);
        }
        count++;
    }
    va_end(args);
    return count;
}

int main() {
    int num1 = 42;
    double num2 = 3.14159;
    char num3 = '!';
    char str[] = "Welcome to our team's printf project";
    char rot13_str[] = "Excellent project\n";
    
    myprintf("%d\n", num1);
    myprintf("%f\n", num2); // Add newline character after print of num2
    
    return 0;
}
