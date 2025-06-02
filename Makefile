CC = gcc
CFLAGS = -Wall -I./linked_list

SRCS = testapp.c graph.c linked_list/linked_list.c, x.c
OBJS = $(SRCS:.c=.o)
TARGET = testapp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
