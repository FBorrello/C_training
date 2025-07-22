CC = gcc
CFLAGS = -Iinclude -IUnity/src
SRC = src/dynamic_array.c Unity/src/unity.c
TEST_SRC = test/test_dynamic_array.c
TARGET = test_runner

all: $(TARGET)
$(TARGET): $(SRC) $(TEST_SRC)
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f $(TARGET)