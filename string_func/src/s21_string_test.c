#include "s21_string.h"

#include <stdio.h>

void s21_strlen_test();
void s21_strcmp_test();
void s21_strcpy_test();
void s21_strcat_test();
void s21_strchr_test();
void s21_strstr_test();

void s21_strlen_test() {
    const char *test_strings[] = {"Hello, World!", "", "123", "@", NULL};
    int expected_lengths[] = {13, 0, 3, 1, 0};

    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        int result_length = s21_strlen(test_strings[i]);
        printf("Input: \"%s\", Expected: %d, Result: %d, Test Result: %s\n", test_strings[i],
               expected_lengths[i], result_length,
               (expected_lengths[i] == result_length) ? "SUCCESS" : "FAIL");
    }
}

void s21_strcmp_test() {
    const char *str1[] = {"hello", "hello", "hello", "", "123", " ", "  ", "'", "Moscow", "LoNdOn", "string"};
    const char *str2[] = {"hello", "world", "hell", "", "123", " ", " ", "", "moscow", "LoNdOn", "stringg"};
    int expected_results[] = {0, -15, 111, 0, 0, 0, 32, 39, -32, 0, -103};

    for (size_t i = 0; i < sizeof(expected_results) / sizeof(expected_results[0]); ++i) {
        int result = s21_strcmp(str1[i], str2[i]);
        printf("Comparing \"%s\" and \"%s\": Result: %d, Test Result: %s\n", str1[i], str2[i], result,
               (expected_results[i] == result) ? "SUCCESS" : "FAIL");
    }
}

void s21_strcpy_test() {
    const char *test_cases[] = {"Hello, World!", "",  "12345",
                                "Testing123",    " ", "long string with more than 20 characters"};

    const char *expected_results[] = {"Hello, World!", "",  "12345",
                                      "Testing123",    " ", "long string with more than 20 characters"};

    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); ++i) {
        const char *src = test_cases[i];
        char dest[50];  // Размер dest должен быть достаточно большим

        s21_strcpy(dest, src);

        printf("Test Case %zu:\n", i + 1);
        printf("  Input: \"%s\"\n", src);
        printf("  Expected Result: \"%s\"\n", expected_results[i]);
        printf("  Result: \"%s\"\n", dest);
        printf("  Test Result: %s\n", (s21_strcmp(dest, expected_results[i]) == 0) ? "SUCCESS" : "FAIL");
    }
}

void s21_strcat_test() {
    const char *test_cases[] = {"Hello, ", "World!", "", "123", "'"};
    const char *appended_strings[] = {"OpenAI", "", "456", "678", "345"};
    const char *expected_results[] = {"Hello, OpenAI", "World!", "456", "123678", "'345"};

    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); ++i) {
        char dest[50];
        s21_strcpy(dest, test_cases[i]);

        printf("Input: \"%s\", Appended: \"%s\", Expected Result: \"%s\", Test Result: \"", test_cases[i],
               appended_strings[i], expected_results[i]);
        s21_strcat(dest, appended_strings[i]);

        if (s21_strcmp(dest, expected_results[i]) == 0) {
            printf("SUCCESS");
        } else {
            printf("FAIL");
        }
        printf("\"\n");
    }
}

void s21_strchr_test() {
    const char *test_strings[] = {"Hello, World!", "",  "123",
                                  "Testing123",    " ", "long string with more than 20 characters"};
    const char search_chars[] = {'H', 'o', '1', 'T', ' ', 'm'};
    const char *expected_results[] = {"Hello, World!", NULL, "123",
                                      "Testing123",    " ",  "more than 20 characters"};

    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        char *result = s21_strchr(test_strings[i], search_chars[i]);
        const char *expected = expected_results[i];
        const char *test_result;

        if (result == NULL) {
            test_result = (expected == NULL) ? "SUCCESS" : "FAIL";
        } else {
            test_result = s21_strcmp(result, expected) == 0 ? "SUCCESS" : "FAIL";
        }

        printf("Searching for '%c' in \"%s\": Expected: \"%s\", Result: \"%s\", Test Result: %s\n",
               search_chars[i], test_strings[i], expected, result, test_result);
    }
}

void s21_strstr_test() {
    const char *haystacks[] = {"Hello, World!", "This is a test string", "", "123", "'"};
    const char *needles[] = {"World", "test", "", "2", "'"};
    const char *expected_results[] = {"World!", "test string", "", "23", "'"};

    for (size_t i = 0; i < sizeof(haystacks) / sizeof(haystacks[0]); ++i) {
        char *result = s21_strstr(haystacks[i], needles[i]);
        const char *expected = expected_results[i];
        const char *test_result;

        if ((result == NULL && expected == NULL) || (result != NULL && s21_strcmp(result, expected) == 0)) {
            test_result = "SUCCESS";
        } else {
            test_result = "FAIL";
        }

        printf("Searching for \"%s\" in \"%s\": Expected: \"%s\", Result: \"%s\", Test Result: %s\n",
               needles[i], haystacks[i], expected, result, test_result);
    }
}

void s21_strtok_test() {
    char str1[] = "Hello, World! This is a test string.";
    const char *delim1 = " ,.!";
    char *token1;
    const char *expected_tokens1[] = {"Hello", "World", "This", "is", "a", "test", "string", NULL};

    printf("Test Case 1:\n");
    printf("Input: \"%s\"\n", str1);
    printf("Expected Tokens: ");
    for (size_t i = 0; expected_tokens1[i] != NULL; ++i) {
        printf("\"%s\" ", expected_tokens1[i]);
    }
    printf("\n");

    token1 = s21_strtok(NULL, delim1);
    printf("Result Tokens: ");
    size_t i = 0;
    while (token1 != NULL) {
        printf("\"%s\" ", token1);
        if (s21_strcmp(token1, expected_tokens1[i]) != 0) {
            printf("\nTest Result: FAIL\n\n");
            return;
        }
        token1 = s21_strtok(NULL, delim1);
        ++i;
    }
    printf("\nTest Result: SUCCESS\n\n");

    char str2[] = "123,456,789";
    const char *delim2 = ",";
    char *token2;
    const char *expected_tokens2[] = {"123", "456", "789", NULL};

    printf("Test Case 2:\n");
    printf("Input: \"%s\"\n", str2);
    printf("Expected Tokens: ");
    for (size_t i = 0; expected_tokens2[i] != NULL; ++i) {
        printf("\"%s\" ", expected_tokens2[i]);
    }
    printf("\n");

    token2 = s21_strtok(str2, delim2);
    printf("Result Tokens: ");
    i = 0;
    while (token2 != NULL) {
        printf("\"%s\" ", token2);
        if (s21_strcmp(token2, expected_tokens2[i]) != 0) {
            printf("\nTest Result: FAIL\n\n");
            return;
        }
        token2 = s21_strtok(NULL, delim2);
        ++i;
    }
    printf("\nTest Result: SUCCESS\n\n");
}

int main() {
#ifdef Quest_1
    s21_strlen_test();
#endif
#ifdef Quest_2
    s21_strcmp_test();
#endif
#ifdef Quest_3
    s21_strcpy_test();
#endif
#ifdef Quest_4
    s21_strcat_test();
#endif
#ifdef Quest_5
    s21_strchr_test();
#endif
#ifdef Quest_6
    s21_strstr_test();
#endif
#ifdef Quest_7
    s21_strtok_test();
#endif

    return 0;
}
