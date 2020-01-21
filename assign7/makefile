#
# The 'run' command will only work if you 
# have the approriate files in the same directory,
# and they have the same names
#


PROGRAMS = assign7

#
# to execute commands, type 'make' beforehand.
# ex: 'make run' will run program also
#

all: $(PROGRAMS)

tidy:
	rm -f ,* .,* *~ core a.out graphics.ps
clean:
	rm -f *.o *.a $(PROGRAMS)
run:
	./assign7
test:
	./assign7 < a7Input.txt > a7Out.txt
out:
	./assign7 > a7Out.txt
# ************************************
# compilations
# ************************************
assign7.o:  assign7.c assign7.h
	gcc -g -c assign7.c -o assign7.o

# ************************************
# generate excutable
# ************************************
assign7: assign7.o 
	gcc -g -o assign7 assign7.o
