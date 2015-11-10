# Makefile for Graphics Project
# Created by: Taylor Andrews

EXE=taan7753fp

# Main target
all: $(EXE)

CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
CLEAN=rm -f $(EXE) main *.o *.a

# Dependencies
ex13.o: ex13.c CSCIx229.h
fatal.o: fatal.c CSCIx229.h
loadtexbmp.o: loadtexbmp.c CSCIx229.h
print.o: print.c CSCIx229.h
project.o: project.c CSCIx229.h
errcheck.o: errcheck.c CSCIx229.h
object.o: object.c CSCIx229.h

#  Create archive
CSCIx229.a:fatal.o loadtexbmp.o print.o project.o errcheck.o object.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG) $<

#  Link
taan7753fp:mor.o fin.o scene.o main.o CSCIx229.a
	gcc -O3 -o $@ $^   $(LIBS)

#  Clean
clean:
	$(CLEAN)
