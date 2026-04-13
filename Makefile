CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lsqlite3
TARGET = autopark
SRCDIR = src
OBJDIR = obj
BINDIR = bin
TESTDIR = tests

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR) $(OBJDIR):
	mkdir -p $@

test: $(BINDIR)/$(TARGET)
	$(CC) $(CFLAGS) -o $(TESTDIR)/runner $(TESTDIR)/test_*.c $(SRCDIR)/database.c -lsqlite3
	./$(TESTDIR)/runner

clean:
	rm -rf $(OBJDIR) $(BINDIR) $(TESTDIR)/runner

.PHONY: clean test
