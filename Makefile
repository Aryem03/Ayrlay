CC      = gcc
CFLAGS  = -Wall -Wextra -g -Iheaders
SRCS    = src/main.c src/qcm.c src/enseignant.c src/etudiant.c
TARGET  = qcm

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
