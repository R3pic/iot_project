# Makefile

CC = gcc

SRCS = main.c user_db.c input.c state.c

HEADERS = user_db.h input.h state.h

OBJS = $(SRCS:.c=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lsqlite3 -lwiringPi

%.o: %.c $(HEADERS)
	$(CC) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
