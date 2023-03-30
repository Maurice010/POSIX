#==============================================================================
#                                   Makefile
#==============================================================================
# make all, clean, tar, run3_a
#==============================================================================
DIR = $(notdir $(CURDIR))
#--------------------------------------------------------
NAME1 = zad3_a
NAME2 = zad3_b
NAME3 = zad3_c
#--------------------------------------------------------
EXEC1 = $(NAME1).x
OBJS1 = $(NAME1).o

EXEC2 = $(NAME2).x
OBJS2 = $(NAME2).o

EXEC3 = $(NAME3).x
OBJS3 = $(NAME3).o
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
all: $(EXEC1) $(EXEC2) $(EXEC3)
#--------------------------------------------------------
$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2)
	 $(LD) -o $@ $(LFLAGS) $^
	 
$(EXEC3): $(OBJS3)
	 $(LD) -o $@ $(LFLAGS) $^
#--------------------------------------------------------
run3_a: $(EXEC1)
	./$(EXEC1) $(arg1) $(arg2)
	
run3_b: $(EXEC2)
	./$(EXEC2) $(arg1) $(arg2)
	
run3_c: $(EXEC3)
	./$(EXEC3) $(arg1) $(arg2)
#--------------------------------------------------------
.PHONY: clean tar
# Sprzatanie
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
