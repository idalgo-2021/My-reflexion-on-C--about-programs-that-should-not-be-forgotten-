#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "logger.h"

#define MAX_PATH_LENGTH 1000
#define MAX_INPUT_LENGTH 1000
#define ALPHABET_SIZE 26

int appendToFile(const char *filepath, const char *text);
int readAndPrintFile(const char *filepath);
void menu_show();
void loop();
void caesar_cipher_files(const char *dir_path, int shift);
void clear_header_files(const char *dir_path);

int appendToFile(const char *filepath, const char *text) {
    FILE *file = fopen(filepath, "a");
    if (file == NULL) {
        logcat(ERROR, "Could not open file %s for appending", filepath);
        return 1;
    }

    fprintf(file, "%s", text);
    fclose(file);

    logcat(INFO, "Appended to file: %s", filepath);
    return 0;
}

int readAndPrintFile(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    // fprintf(stderr, "Error: Could not open file %s for reading.\n", filepath);
    if (file == NULL) {
        logcat(ERROR, "Could not open file %s for reading", filepath);
        return 1;
    }

    int symbol;
    int count = 0;

    while ((symbol = getc(file)) != EOF) {
        printf("%c", symbol);
        count++;
    }

    fclose(file);

    if (count > 0) {
        logcat(INFO, "Read from file: %s", filepath);
        return 0;
    } else {
        // printf("File is empty.\n");
        logcat(WARNING, "File %s is empty", filepath);
        return 1;
    }
}

void menu_show() {
    system("clear");
    printf("=== Menu ===\n");
    printf("1. Enter the path to the file and output its contents\n");
    printf("2. Add a line to the end of the file\n");
    printf("3. Caesar cipher all .c files in a directory and clear all .h files\n");
    printf("-1. Exit\n");
}

void caesar_cipher_files(const char *dir_path, int shift) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char filepath[MAX_PATH_LENGTH];
    char temp_filepath[MAX_PATH_LENGTH];
    FILE *file_in, *file_out;
    int c;

    dir = opendir(dir_path);
    if (dir == NULL) {
        logcat(ERROR, "Error opening directory %s", dir_path);
        // fprintf(stderr, "Error opening directory %s\n", dir_path);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;  // skip "." and ".."
        }

        snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, entry->d_name);

        if (stat(filepath, &file_stat) < 0) {
            // fprintf(stderr, "Error stating file %s\n", filepath);
            logcat(ERROR, "Error stating file %s", filepath);
            continue;
        }

        if (S_ISDIR(file_stat.st_mode)) {
            continue;  // skip directories
        }

        if (strstr(entry->d_name, ".c") == NULL) {
            continue;  // skip non-.c files
        }

        // Create a temporary file for writing the encrypted content
        snprintf(temp_filepath, sizeof(temp_filepath), "%s/%s_temp", dir_path, entry->d_name);

        file_in = fopen(filepath, "r");
        if (file_in == NULL) {
            fprintf(stderr, "Error opening file %s\n", filepath);
            continue;
        }

        file_out = fopen(temp_filepath, "w");
        if (file_out == NULL) {
            // fprintf(stderr, "Error creating temp file %s\n", temp_filepath);
            logcat(ERROR, "Error opening file %s", filepath);
            fclose(file_in);
            continue;
        }

        // Perform Caesar cipher encryption
        while ((c = fgetc(file_in)) != EOF) {
            if (c >= 'A' && c <= 'Z') {
                c = 'A' + (c - 'A' + shift) % ALPHABET_SIZE;
            } else if (c >= 'a' && c <= 'z') {
                c = 'a' + (c - 'a' + shift) % ALPHABET_SIZE;
            }
            fputc(c, file_out);
        }

        fclose(file_in);
        fclose(file_out);

        // Rename the temporary file to overwrite the original
        if (rename(temp_filepath, filepath) != 0) {
            // fprintf(stderr, "Error renaming file %s to %s\n", temp_filepath, filepath);
            logcat(ERROR, "Error renaming file %s to %s", temp_filepath, filepath);
        } else {
            logcat(INFO, "Caesar ciphered file: %s", filepath);  // Пример использования INFO уровня
        }
    }

    closedir(dir);
}

void clear_header_files(const char *dir_path) {
    char command[MAX_PATH_LENGTH];
    snprintf(command, sizeof(command), "find %s -type f -name \"*.h\" -exec truncate -s 0 {} +", dir_path);
    system(command);

    logcat(INFO, "Cleared all header files in directory: %s", dir_path);
}

void loop() {
    int choice = 0;
    char filepath[MAX_PATH_LENGTH];
    char input[MAX_INPUT_LENGTH];
    int shift = 0;

    int filepath_entered = 0;

    menu_show();

    while (choice != -1) {
        if (scanf("%d", &choice) == 1) {
            if (choice < -1 || choice > 3 || choice == 0) {
                printf("n/a\n");
                // Очистка буфера ввода
                while (getchar() != '\n')
                    ;
                continue;
            }

            if (choice == 1) {
                char temp[MAX_PATH_LENGTH];
                if (scanf("%999ss", temp) != 1) {
                    printf("n/a\n");
                    // Очистка буфера ввода
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                if (strlen(temp) >= MAX_PATH_LENGTH) {
                    printf("n/a\n");
                    // Очистка буфера ввода
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                strcpy(filepath, temp);
                filepath_entered = 1;
                int result = readAndPrintFile(filepath);
                if (result != 0) {
                    printf("n/a\n");
                } else {
                    printf("\n");
                }
            }

            if (choice == 2) {
                getchar();  // Очистка символа перевода строки
                if (!filepath_entered) {
                    continue;
                }

                if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
                    printf("n/a\n");
                    while (getchar() != '\n')
                        ;  // Очистка буфера ввода
                    continue;
                }
                int len = strlen(input);
                if (input[len - 1] == '\n') {
                    input[len - 1] = '\0';  // Убираем символ новой строки, если он был считан
                }

                int result = appendToFile(filepath, input);
                if (result != 0) {
                    printf("n/a\n");
                } else {
                    int readResult = readAndPrintFile(filepath);
                    if (readResult != 0) {
                        printf("n/a\n");
                    } else {
                        printf("\n");
                    }
                }
            }

            if (choice == 3) {
                getchar();  // Очистка символа перевода строки
                printf("Enter the directory path: ");
                if (scanf("%999s", filepath) != 1) {
                    printf("n/a\n");
                    while (getchar() != '\n')
                        ;
                    continue;
                }

                printf("Enter the shift value for Caesar cipher: ");
                if (scanf("%d", &shift) != 1) {
                    printf("n/a\n");
                    while (getchar() != '\n')
                        ;
                    continue;
                }

                // Выполнение шифрования файлов .c и очистки файлов .h
                caesar_cipher_files(filepath, shift);
                clear_header_files(filepath);
                // printf("Caesar cipher and header file cleanup completed.\n");
                printf("\n");
            }

        } else {
            printf("n/a\n");
            while (getchar() != '\n')
                ;  // Очистка буфера ввода
        }
    }
}

int main() {
    log_init("cipher.log");  // Инициализация лога при запуске программы

    loop();

    log_close();  // Закрытие лога перед завершением программы

    return 0;
}
