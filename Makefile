# --- macros
CC=cc
CFLAGS=  -O3 -Wall -Werror -I.
OBJECTS= mini-printf.o cmblog.o cmblog_example.o
LIBS = -lm


# --- targets
all:    cmblog
cmblog:   $(OBJECTS) 
	$(CC)  -o example  $(OBJECTS) $(LIBS)

cmblog.o: mini-printf.o 
	$(CC) $(CFLAGS) -c cmblog.c cmblog_example.c

mini-printf.o:
	$(CC) $(CFLAGS) -c mini-printf.c 


# --- remove binary and executable files
clean:
	rm -f example $(OBJECTS)
