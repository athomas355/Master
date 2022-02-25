CC = gcc
CFLAGS = -Wall -g
LFLAGS = -lrt
TARGET = master slave
OBJS = config.o master.o slave.o 

all: $(TARGET) 

# $(TARGET): $(OBJS)
# 	$(CC) -o $(TARGET) $(OBJS) $(LFLAGS) 

master: master.o 
	$(CC) master.o config.o -o master $(LFLAGS)

slave: slave.o 
	$(CC) slave.o config.o -o slave $(LFLAGS)

master.o: master.c
	$(CC) $(CFLAGS) -c master.c 

slave.o: slave.c 
	$(CC) $(CFLAGS) -c slave.c

config.o: config.c 
	$(CC) $(CFLAGS) -c config.c

clean:
	/bin/rm -f *.o $(TARGET)