#include "s21_string.h"

#include "stdio.h"

// Вычисляет длину строки str
int s21_strlen(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int len = 0;
    while (str[len] != '\0') {
        len++;
    }

    return len;
}

// Сравнивает строки str1 и str2
int s21_strcmp(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

// Копирует содержимое строки src в dest
char *s21_strcpy(char *dest, const char *src) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }

    char *result = dest;
    while ((*dest++ = *src++) != '\0')
        ;

    return result;
}

// Добавляет содержимое строки src в конец строки dest, а затем возвращает указатель на строку dest
char *s21_strcat(char *dest, const char *src) {
    char *ptr = dest;

    while (*ptr) {
        ptr++;
    }

    while (*src) {
        *ptr = *src;
        ptr++;
        src++;
    }

    *ptr = '\0';

    return dest;
}

// Ищет символ character в строке str
char *s21_strchr(const char *str, int character) {
    while (*str != '\0') {
        if (*str == character) {
            return (char *)str;
        }
        str++;
    }

    return NULL;
}

// Ищет подстроку needle в строке haystack и возвращает указатель на первое вхождение needle в haystack
char *s21_strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return (char *)haystack;
    }

    while (*haystack != '\0') {
        const char *h = haystack;
        const char *n = needle;

        while (*n != '\0' && *h == *n) {
            h++;
            n++;
        }

        if (*n == '\0') {
            return (char *)haystack;
        }

        haystack++;
    }

    return NULL;
}

// Разбивает строку str на токены с использованием указанного разделителя delim
char *s21_strtok(char *str, const char *delim) {
    static char *last_token = NULL;
    if (str != NULL) {
        last_token = str;
    } else if (last_token == NULL) {
        return NULL;
    }

    char *token_start = last_token;
    while (*last_token != '\0') {
        const char *d = delim;
        while (*d != '\0') {
            if (*last_token == *d) {
                *last_token = '\0';
                last_token++;
                if (token_start != last_token) {
                    return token_start;
                } else {
                    token_start++;
                    break;
                }
            }
            d++;
        }
        last_token++;
    }

    last_token = NULL;
    return token_start != last_token ? token_start : NULL;
}