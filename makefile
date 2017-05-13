#Susanna Kim 5/9/17
all: polyexam2 polytest2

polyexam2: polyexam2.o poly2.o
	g++ -g -o polyexam2 poly2.o polyexam2.o

polytest2: polytest2.o poly2.o
	g++ -g -o polytest2 poly2.o polytest2.o

polyexam2.o: polyexam2.cxx
	g++ -g polyexam2.cxx -c

polytest2.o: polytest2.cxx
	g++ -g polytest2.cxx -c

poly2.o: poly2.cxx poly2.h
	g++ -g poly2.cxx -c

clean:
	rm -f polyexam2 polytest2 polyexam2.o polytest2.o poly2.o


