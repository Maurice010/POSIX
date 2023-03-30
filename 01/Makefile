#==============================================================================
#                                   Makefile
#==============================================================================
# make all, clean, tar, run1a, run1b, run1c, run1d, run1e
#==============================================================================
DIR = $(notdir $(CURDIR))
#--------------------------------------------------------
NAME1 = zad1_a
NAME2 = zad1_b
NAME3 = zad1_c
NAME4 = zad1_d
NAME5 = zad1_e
#--------------------------------------------------------
EXEC1 = $(NAME1).x
OBJS1 = $(NAME1).o

EXEC2 = $(NAME2).x
OBJS2 = $(NAME2).o

EXEC3 = $(NAME3).x
OBJS3 = $(NAME3).o

EXEC4 = $(NAME4).x
OBJS4 = $(NAME4).o

EXEC5 = $(NAME5).x
OBJS5 = $(NAME5).o
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
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)
#--------------------------------------------------------
$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2)
	 $(LD) -o $@ $(LFLAGS) $^

$(EXEC3): $(OBJS3)
	 $(LD) -o $@ $(LFLAGS) $^

$(EXEC4): $(OBJS4)
	 $(LD) -o $@ $(LFLAGS) $^

$(EXEC5): $(OBJS5)
	 $(LD) -o $@ $(LFLAGS) $^
#--------------------------------------------------------
run1a: $(EXEC1)
	./$(EXEC1)
run1b: $(EXEC2)
	./$(EXEC2)
run1c: $(EXEC3)
	./$(EXEC3)
run1d: $(EXEC4)
	./$(EXEC4)
run1e: $(EXEC5)
	./$(EXEC5)
#--------------------------------------------------------
.PHONY: clean tar
# Sprzatanie
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )