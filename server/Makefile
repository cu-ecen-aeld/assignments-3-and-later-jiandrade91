BUILD_DIR = .
CFLAGS ?= -g -Wall -Werror

CC ?= $(CROSS_COMPILE)gcc $(CFLAGS)

TARGET ?= aesdsocket
LDFLAGS ?= -lpthread -lrt

all: aesdsocket.o $(TARGET)

aesdsocket.o : aesdsocket.c
	@echo "Cross compile is $(CROSS_COMPILE)"...
	$(CC) -c -o aesdsocket.o aesdsocket.c

aesdsocket : aesdsocket.o
	$(CC) aesdsocket.o -o $(TARGET) $(LDFLAGS)
	@echo "------- Successfully built --------"

clean :
	@echo "The main directory is $(BUILD_DIR)"
	rm -rf $(BUILD_DIR)/aesdsocket.o aesdsocket
