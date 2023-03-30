#==============================================================================
#                                   Makefile
#==============================================================================
# make all, clean, tar, run5_a, run5_b
#==============================================================================
DIR = $(notdir $(CURDIR))
#--------------------------------------------------------
NAME1 = zad5_a
NAME2 = zad5_bw
NAME3 = zad5_br

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
run5_a: $(EXEC1)
	./$(EXEC1)
	diff -s magazyn.txt towar.txt
	
run5_b: $(EXEC2) $(EXEC3)
	mkfifo -m 644 towarfifo
	xterm -hold -title writer -e ./$(EXEC2) &
	xterm -hold -title reader -e ./$(EXEC3) &

#--------------------------------------------------------
.PHONY: clean tar
# Sprzatanie
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out towarfifo; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
