CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Каталог с исходными файлами
SRC_DIR = .

# Каталог для сохранения объектных и исполняемых файлов
BUILD_DIR = ../build

TARGET1 = $(BUILD_DIR)/Quest_1
TARGET2 = $(BUILD_DIR)/Quest_2
TARGET3 = $(BUILD_DIR)/Quest_3
TARGET4 = $(BUILD_DIR)/Quest_4
TARGET5 = $(BUILD_DIR)/Quest_5
TARGET6 = $(BUILD_DIR)/Quest_6
TARGET7 = $(BUILD_DIR)/Quest_7

# Получение списка исходных файлов с расширением .c в каталоге SRC_DIR
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Преобразование исходных файлов в объектные файлы, сохраняемые в каталоге BUILD_DIR
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Объявление фиктивных (PHONY) целей, чтобы избежать конфликтов с файлами с теми же именами
.PHONY: all clean

all: strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_tests strstr_tests strtok_tests

# Цель strlen_tests зависит от TARGET1 и собирается из s21_string_test.c и s21_string.o
strlen_tests: $(TARGET1)
$(TARGET1): s21_string_test.c $(BUILD_DIR)/s21_string.o
	$(CC) $(CFLAGS) -DQuest_1 $^ -o $@

$(BUILD_DIR)/s21_string_test.o: $(SRC_DIR)/s21_string_test.c
	$(CC) $(CFLAGS) -c -DQuest_1 $< -o $@	

strcmp_tests: $(TARGET2)
$(TARGET2): s21_string_test.c $(BUILD_DIR)/s21_string.o
	$(CC) $(CFLAGS) -DQuest_2 $^ -o $@

$(BUILD_DIR)/s21_string.o: $(SRC_DIR)/s21_string.c
	$(CC) $(CFLAGS) -c -DQuest_2 $< -o $@	

strcpy_tests: $(TARGET3)
$(TARGET3): s21_string_test.c $(BUILD_DIR)/s21_string.o
	$(CC) $(CFLAGS) -DQuest_3 $^ -o $@

$(BUILD_DIR)/s21_string.o: $(SRC_DIR)/s21_string.c
	$(CC) $(CFLAGS) -c -DQuest_3 $< -o $@	

strcat_tests: $(TARGET4)
$(TARGET4): s21_string_test.c $(BUILD_DIR)/s21_string.o
	$(CC) $(CFLAGS) -DQuest_4 $^ -o $@

$(BUILD_DIR)/s21_string.o: $(SRC_DIR)/s21_string.c
	$(CC) $(CFLAGS) -c -DQuest_4 $< -o $@

strchr_tests: $(TARGET5)
$(TARGET5): s21_string_test.c $(BUILD_DIR)/s21_string.o
	$(CC) $(CFLAGS) -DQuest_5 $^ -o $@

$(BUILD_DIR)/s21_string.o: $(SRC_DIR)/s21_string.c
	$(CC) $(CFLAGS) -c -DQuest_5 $< -o $@

strstr_tests: $(TARGET6)
$(TARGET6): s21_string_test.c $(BUILD_DIR)/s21_string.o
	$(CC) $(CFLAGS) -DQuest_6 $^ -o $@

$(BUILD_DIR)/s21_string.o: $(SRC_DIR)/s21_string.c
	$(CC) $(CFLAGS) -c -DQuest_6 $< -o $@

strtok_tests: $(TARGET7)
$(TARGET7): s21_string_test.c $(BUILD_DIR)/s21_string.o
	$(CC) $(CFLAGS) -DQuest_7 $^ -o $@

$(BUILD_DIR)/s21_string.o: $(SRC_DIR)/s21_string.c
	$(CC) $(CFLAGS) -c -DQuest_7 $< -o $@


clean:
	rm -rf $(BUILD_DIR)/*