_DEPS = vec.h node.h iterator.h queue.h stack.h heap.h cdvec.h dlnode.h
_OBJ = vec.o iterator.o queue.o stack.o cdvec.o
_TOBJ = test.o

LIBARCV = vec.so iterator.so
TESTBIN = ds_test

IDIR = include
CC = gcc
CFLAGS = -I$(IDIR) -Wall -Wextra -g -pthread -fsanitize=address
ODIR = obj
SDIR = src
LDIR = lib
TDIR = test
LIBS = -lm -ldl
XXLIBS = $(LIBS) -lstdc++ -lgtest -lgtest_main -lpthread
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
TOBJ = $(patsubst %,$(ODIR)/%,$(_TOBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(TDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(TESTBIN)

$(LIBARCV): include/vec.h src/vec.c
	 $(CC) $(CFLAGS) -fPIC -shared -o $@ src/vec.c -lc 

$(TESTBIN): $(TOBJ) $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(XXLIBS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	rm -f $(APPBIN) $(TESTBIN)
	rm -f submission.zip
