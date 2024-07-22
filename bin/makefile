CC := g++
CFLAGS := -std=c++20 -O

TARGET := threebody
SRC_DIR := ../src
SRC := $(wildcard $(SRC_DIR)/*.cpp)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

DATA_FILE := ../data/results.csv

clean:
	rm -rf $(TARGET) $(DATA_FILE)
