#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>

typedef enum { ERROR, WARNING, INFO } LogLevel;

#ifdef WITHOUT_LOGGER

// Заглушки для функций логгирования
#define log_init(logfile) ((void)0)
#define logcat(level, format, ...) ((void)0)
#define log_close() ((void)0)

#else

// Реальные функции логгирования
void log_init(const char *logfile);
void logcat(LogLevel level, const char *format, ...);
void log_close();

#endif /* WITHOUT_LOGGER */

#endif /* LOGGER_H */
