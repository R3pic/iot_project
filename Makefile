# Makefile

CC = gcc

CFLAGS = -Wall -std=c99

SRCS = main.c user_db.c input.c state.c

HEADERS = user_db.h input.h state.h

OBJS = $(SRCS:.c=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lsqlite3

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)