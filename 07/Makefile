#==============================================================================
#                                   Makefile
#==============================================================================
# make all, clean, tar, run7, run7d
#==============================================================================
DIR = $(notdir $(CURDIR))
LIB_DIR = ./lib
#--------------------------------------------------------
NAME1 = zad7
NAME2 = zad7_lib
NAME3 = konsument
NAME4 = producent

LIB_NAME = _zad7
LIB_STAT = lib$(LIB_NAME).a
LIB_SHAR = lib$(LIB_NAME).so

#--------------------------------------------------------
EXEC1 = $(NAME1).x
EXEC1d = $(NAME1).x
OBJS1 = $(NAME1).o


EXEC3 = $(NAME3).x
EXEC3d = $(NAME3).x
OBJS3 = $(NAME3).o

EXEC4 = $(NAME4).x
EXEC4d = $(NAME4).x
OBJS4 = $(NAME4).o

OBJS2 = $(NAME2).o
HEADS1 = $(NAME2).h
LIB_OBJS = $(OBJS2)

#--------------------------------------------------------
CFLAGS = -Wall -std=gnu99 -pedantic -O -fPIC
LFLAGS = -Wall -std=gnu99 -pedantic -O
CO = gcc
LD = $(CO)

AR = ar
ARFLAGS = rsv
#--------------------------------------------------------
%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<
#--------------------------------------------------------
.PHONY: all
all: $(EXEC1) $(EXEC3) $(EXEC4) $(EXEC1d) $(EXEC3d) $(EXEC4d)
#--------------------------------------------------------
# Tworzenie biblioteki statycznej przy pomocy programu archiwizującego AR i wrzucenie jej do ./lib
$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)
	
# Tworzenie biblioteki dzielonej (shared library)
$(LIB_SHAR): $(LIB_OBJS)
	$(LD) -shared -o $@ $(LFLAGS) $(LIB_OBJS)
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)

# Linkowanie z biblioteką statyczna
$(EXEC1): $(OBJS1) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME)
	
$(EXEC3): $(OBJS3) $(LIB_STAT)
	 $(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME)
	 
$(EXEC4): $(OBJS4) $(LIB_STAT)
	 $(LD) -o $@ $(LFLAGS) $(OBJS4) -L$(LIB_DIR) -l$(LIB_NAME)
	 
# Linkowanie z biblioteką dzielona
$(EXEC1d): $(OBJS1) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)
	
$(EXEC3d): $(OBJS3) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)
	
$(EXEC4d): $(OBJS4) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS4) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)
	 
#--------------------------------------------------------
# 1) Uruchomienie z biblioteka statyczna
run7: $(EXEC1) $(EXEC3) $(EXEC4)
	./$(EXEC1)
	diff -s magazyn.txt towar.txt

konsument: $(EXEC3)
	    ./$(EXEC3)

producent: $(EXEC4)
	    ./$(EXEC4)

# 2) Uruchomienie z biblioteka dzielona
run7d: $(EXEC1d) $(EXEC3d) $(EXEC4d)
	./$(EXEC1d)
	diff -s magazyn.txt towar.txt

#--------------------------------------------------------
.PHONY: clean tar
# Sprzatanie
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
