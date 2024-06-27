#include "logger.h"

#include <stdarg.h>
#include <time.h>

static FILE *log_file = NULL;

void log_init(const char *logfile) {
    log_file = fopen(logfile, "a");
    if (log_file == NULL) {
        fprintf(stderr, "Error: Could not open log file %s\n", logfile);
        return;
    }

    time_t current_time;
    struct tm *local_time;
    char time_string[100];

    current_time = time(NULL);
    local_time = localtime(&current_time);

    strftime(time_string, sizeof(time_string), "%c", local_time);
    fprintf(log_file, "=== Log Initialized at %s ===\n", time_string);
}

void logcat(LogLevel level, const char *format, ...) {
    if (log_file == NULL) {
        fprintf(stderr, "Error: Log file not initialized\n");
        return;
    }

    va_list args;
    va_start(args, format);

    time_t current_time;
    struct tm *local_time;
    char time_string[100];

    current_time = time(NULL);
    local_time = localtime(&current_time);

    strftime(time_string, sizeof(time_string), "%c", local_time);

    switch (level) {
        case ERROR:
            fprintf(log_file, "[ERROR] ");
            break;
        case WARNING:
            fprintf(log_file, "[WARNING] ");
            break;
        case INFO:
            fprintf(log_file, "[INFO] ");
            break;
        default:
            fprintf(log_file, "[UNKNOWN] ");
            break;
    }

    fprintf(log_file, "[%s] ", time_string);
    vfprintf(log_file, format, args);
    fprintf(log_file, "\n");

    va_end(args);
}

void log_close() {
    if (log_file != NULL) {
        time_t current_time;
        struct tm *local_time;
        char time_string[100];

        current_time = time(NULL);
        local_time = localtime(&current_time);

        strftime(time_string, sizeof(time_string), "%c", local_time);
        fprintf(log_file, "=== Log Closed at %s ===\n", time_string);

        fclose(log_file);
        log_file = NULL;
    }
}
