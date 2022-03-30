
# code details

EXE = ./library
SRC= main.c librarian.c users.c Interface.c book_management.c

# generic build details

CC=      gcc
CFLAGS= -std=c99 -Wall
CLINK= 

# compile to object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

# build executable: type 'make'

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CLINK) -o $(EXE) 

# clean up and remove object code and executable: type 'make clean'

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o:              main.c Interface.h
librarian.o:         librarian.c librarian.h book_management.h Interface.h
users.o:             users.c users.h librarian.h book_management.h Interface.h
Interface.o:         Interface.c Interface.h book_management.h users.h 
book_management.o:   book_management.c book_management.h Interface.h librarian.h

