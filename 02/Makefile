#==============================================================================
#                                   Makefile
#==============================================================================
# make all, clean, tar, run2
#==============================================================================
DIR = $(notdir $(CURDIR))
#--------------------------------------------------------
NAME1 = zad2
NAME2 = zad2_a
#--------------------------------------------------------
EXEC1 = $(NAME1).x
OBJS1 = $(NAME1).o

EXEC2 = $(NAME2).x
OBJS2 = $(NAME2).o
#--------------------------------------------------------
CFLAGS = -Wall -std=c99 -pedantic -O
LFLAGS = -Wall -std=c99 -pedantic -O
CO = gcc
LD = $(CO)
#--------------------------------------------------------
%.o: %.c
	$(CO) $(CFLAGS) -c $<
#--------------------------------------------------------
.PHONY: all
all: $(EXEC1) $(EXEC2)
#--------------------------------------------------------
$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2)
	 $(LD) -o $@ $(LFLAGS) $^
#--------------------------------------------------------
run2: $(EXEC1)
	./$(EXEC1) $(arg)
#--------------------------------------------------------
.PHONY: clean tar
# Sprzatanie
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
