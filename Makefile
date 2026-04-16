CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11
LIBS    = -lm

TARGET  = bigmuscle
SRCS    = main.c funciones.c planes.c sedes.c tiempo.c validadores.c
OBJS    = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
