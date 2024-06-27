all: cipher logging_cipher

cipher: cipher.c cipher.o
	gcc -c -Wall -Wextra -Werror cipher.c -o ../build/cipher.o -DWITHOUT_LOGGER
	gcc -Wall -Wextra -Werror ../build/cipher.o -o ../build/cipher

logging_cipher: cipher.c logger.o
	gcc -c -Wall -Wextra -Werror logger.c -o ../build/logger.o
	gcc -c -Wall -Wextra -Werror cipher.c -o ../build/cipher.o
	gcc -Wall -Wextra -Werror ../build/cipher.o ../build/logger.o -o ../build/logging_cipher

clean:
	rm -f *.o
	rm -f ../build/*

rebuild:
	clean all