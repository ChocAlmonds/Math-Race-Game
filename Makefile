# Matthew Hembrador G01364958
# CS 262, Lab Section 210
# Project 1

CC = gcc
CFLAGS = -g -Wall -std=c89 -pedantic-errors
TARGET = p1_mhembrad_210

$(TARGET) : $(TARGET).c
	$(CC) $(TARGET).c -o $(TARGET) $(CFLAGS) $(LIBS)

clean: 
	rm $(TARGET)
