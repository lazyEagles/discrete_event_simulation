
IDIR=../include
CC=gcc
CFLAGS=-I$(IDIR) -lm -g

BDIR=../bin
ODIR=../obj
TDIR=../test

_DEPS=event_list.h queue.h random_generator.h customer.h
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

$(TDIR)/testtest3: $(ODIR)/random_generator.o $(TDIR)/test3.c
	$(CC) -o $@ $^ $(CFLAGS)

$(TDIR)/testtest4: $(ODIR)/random_generator.o $(TDIR)/test4.c
	$(CC) -o $@ $^ $(CFLAGS)

$(TDIR)/testtest5: $(ODIR)/random_generator.o $(TDIR)/test5.c
	$(CC) -o $@ $^ $(CFLAGS)

$(TDIR)/testtest6: $(ODIR)/random_generator.o $(TDIR)/test6.c
	$(CC) -o $@ $^ $(CFLAGS)

$(TDIR)/testtest7: $(ODIR)/random_generator.o $(TDIR)/test7.c
	$(CC) -o $@ $^ $(CFLAGS)

$(TDIR)/testtest8: $(ODIR)/random_generator.o $(TDIR)/test8.c
	$(CC) -o $@ $^ $(CFLAGS)

$(TDIR)/testtest9: $(ODIR)/random_generator.o $(TDIR)/test9.c
	$(CC) -o $@ $^ $(CFLAGS)

$(TDIR)/testtest10: $(ODIR)/random_generator.o $(TDIR)/test10.c
	$(CC) -o $@ $^ $(CFLAGS)

$(TDIR)/testtest11: $(ODIR)/random_generator.o $(TDIR)/test11.c
	$(CC) -o $@ $^ $(CFLAGS)

$(TDIR)/testtest12: $(ODIR)/random_generator.o $(TDIR)/test12.c
	$(CC) -o $@ $^ $(CFLAGS)

$(TDIR)/testtest13: $(ODIR)/random_generator.o $(TDIR)/test13.c
	$(CC) -o $@ $^ $(CFLAGS)

$(TDIR)/testtest14: $(ODIR)/random_generator.o $(TDIR)/test14.c
	$(CC) -o $@ $^ $(CFLAGS)

$(TDIR)/testtest15: $(ODIR)/random_generator.o $(TDIR)/test15.c
	$(CC) -o $@ $^ $(CFLAGS)

$(TDIR)/test_mm_one_queue: $(ODIR)/random_generator.o $(ODIR)/customer.o $(ODIR)/queue.o $(ODIR)/event_list.o $(ODIR)/mm_one_queue.o $(TDIR)/test_mm_one_queue.c
	$(CC) -o $@ $^ -lgsl -lgslcblas $(CFLAGS)

$(TDIR)/test_simulation: $(ODIR)/random_generator.o $(ODIR)/customer.o $(ODIR)/queue.o $(ODIR)/event_list.o $(ODIR)/simulation_template.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm $(ODIR)/*.o $(BDIR)/* $(TDIR)/testtest $(TDIR)/testtest2 $(TDIR)/testtest3
