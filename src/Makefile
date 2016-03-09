
IDIR=../include
CC=gcc
CFLAGS=-I$(IDIR) -lm

BDIR=../bin
ODIR=../obj
TDIR=../test

_DEPS=event_list.h queue.h random_generator.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))



#all: event_list.o queue.o seed_table_generator

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/seed_table_generator: $(ODIR)/seed_table_generator.o $(ODIR)/random_generator.o 
	$(CC) -o $@ $(ODIR)/seed_table_generator.o $(ODIR)/random_generator.o $(CFLAGS)

$(TDIR)/testtest: $(ODIR)/random_generator.o $(TDIR)/test.c
	$(CC) -o $@ $^ $(CFLAGS)

$(TDIR)/testtest2: $(ODIR)/random_generator.o $(TDIR)/test2.c
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm $(ODIR)/*.o $(BDIR)/* $(TDIR)/testtest $(TDIR)/testtest2
