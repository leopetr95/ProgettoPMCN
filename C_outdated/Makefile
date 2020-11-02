CC = gcc
CFLAGS =-Wall -Wextra -Wpedantic -o2
CFILES=$(shell ls *.c)
PROGS=$(CFILES:%.c=%)

install: prog_pmcsn risultati

prog_pmcsn: main.c basic.c basic.h rngs.h rngs.c distributions.c distributions.h dynamic_list.c dynamic_list.h next_event.c next_event.h parser.c parser.h stats.c stats.h rvms.h rvms.c
	$(CC) $(CFLAGS) -o $@ $^ -lm -std=c99

risultati:risultati-teorici.c
	$(CC) $(CFLAGS) -o $@ $^

