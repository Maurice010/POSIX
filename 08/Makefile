#==============================================================================
#                                   Makefile
#==============================================================================
# make all, clean, tar, run8
#==============================================================================
DIR = $(notdir $(CURDIR))
LIB_DIR = ./lib
#--------------------------------------------------------
NAME1 = zad8_serwer
NAME2 = zad8_klient
NAME3 = zad8_lib

LIB_NAME = _zad8
LIB_STAT = lib$(LIB_NAME).a

#--------------------------------------------------------
EXEC1 = $(NAME1).x
OBJS1 = $(NAME1).o

EXEC2 = $(NAME2).x
OBJS2 = $(NAME2).o

OBJS3 = $(NAME3).o
HEADS1 = $(NAME3).h
LIB_OBJS = $(OBJS3)

#--------------------------------------------------------
CFLAGS = -Wall -std=c99 -pedantic -O
LFLAGS = -Wall -std=c99 -pedantic -O 
CO = gcc
LD = $(CO)

AR = ar
ARFLAGS = rsv
#--------------------------------------------------------
%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<
#--------------------------------------------------------
.PHONY: all
all: $(EXEC1) $(EXEC2)
#--------------------------------------------------------
$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)

$(EXEC1): $(OBJS1) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME)
	
$(EXEC2): $(OBJS2) $(LIB_STAT)
	 $(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME)
	 
#--------------------------------------------------------
run8: $(EXEC1) $(EXEC2)
	xterm -hold -title serwer -e ./$(EXEC1) &
	xterm -hold -title klient1 -e ./$(EXEC2) &
	xterm -hold -title klient2 -e ./$(EXEC2) &

#--------------------------------------------------------
.PHONY: clean tar
# Sprzatanie
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
