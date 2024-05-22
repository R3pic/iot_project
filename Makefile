CC = gcc
CFLAGS = -g

SRCS = main.c user_db.c input.c state.c fnd.c hc-sr.c pir.c
HEADERS = user_db.h input.h state.h fnd.h hc-sr.h pir.h
OBJS = $(SRCS:.c=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lsqlite3 -lwiringPi

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
