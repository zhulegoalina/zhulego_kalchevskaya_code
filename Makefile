CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lsqlite3
TARGET = autopark
SRCDIR = src
BINDIR = bin

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(SRCDIR)/*.c
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test:
	$(CC) $(CFLAGS) -o tests/runner tests/test_database.c $(SRCDIR)/database.c -lsqlite3
	./tests/runner

clean:
	rm -rf $(BINDIR) tests/runner

.PHONY: all clean test
