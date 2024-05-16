# Makefile

# 컴파일러 설정
CC = gcc

# 컴파일 플래그 설정 (필요시 수정)
CFLAGS = -Wall -std=c99

# 소스 파일
SRCS = main.c user_db.c password.c

# 헤더 파일
HEADERS = user_db.h password.h

# 목적 파일 (오브젝트 파일)
OBJS = $(SRCS:.c=.o)

# 실행 파일
TARGET = main

# 디폴트 빌드
all: $(TARGET)

# 실행 파일 빌드
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lsqlite3

# 각 소스 파일에 대한 목적 파일 생성 규칙
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

# 청소 (오브젝트 파일과 실행 파일 제거)
clean:
	rm -f $(OBJS) $(TARGET)
