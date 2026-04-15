CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lsqlite3
TARGET = autopark
SRCDIR = src
BINDIR = bin
TESTDIR = tests

SOURCES = $(wildcard $(SRCDIR)/*.c)

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(SOURCES) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BINDIR):
	mkdir -p $@

test:
	$(CC) $(CFLAGS) -o $(TESTDIR)/runner_db $(TESTDIR)/test_database_cunit.c $(SRCDIR)/database.c -lsqlite3 -lcunit
	$(CC) $(CFLAGS) -o $(TESTDIR)/runner_auth $(TESTDIR)/test_auth_cunit.c $(SRCDIR)/auth.c $(SRCDIR)/database.c -lsqlite3 -lcunit
	$(CC) $(CFLAGS) -o $(TESTDIR)/runner_cars $(TESTDIR)/test_cars_cunit.c $(SRCDIR)/cars.c $(SRCDIR)/database.c -lsqlite3 -lcunit
	$(CC) $(CFLAGS) -o $(TESTDIR)/runner_drivers $(TESTDIR)/test_drivers_cunit.c $(SRCDIR)/drivers.c $(SRCDIR)/database.c -lsqlite3 -lcunit
	$(CC) $(CFLAGS) -o $(TESTDIR)/runner_orders $(TESTDIR)/test_orders_cunit.c $(SRCDIR)/orders.c $(SRCDIR)/database.c -lsqlite3 -lcunit
	$(CC) $(CFLAGS) -o $(TESTDIR)/runner_reports $(TESTDIR)/test_reports_cunit.c $(SRCDIR)/reports.c $(SRCDIR)/database.c -lsqlite3 -lcunit
	./$(TESTDIR)/runner_db
	./$(TESTDIR)/runner_auth
	./$(TESTDIR)/runner_cars
	./$(TESTDIR)/runner_drivers
	./$(TESTDIR)/runner_orders
	./$(TESTDIR)/runner_reports

clean:
	rm -rf $(BINDIR) $(TESTDIR)/runner_* *.gcno *.gcda *.gcov

.PHONY: all clean test

coverage: CFLAGS += -fprofile-arcs -ftest-coverage
coverage: LDFLAGS += -lgcov
coverage: clean test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report
