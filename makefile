#Susanna Kim & Fujie Liang, 5/9/17

polyexam2: polyexam2.o poly2.o
	g++ -g polyexam2.o poly2.o -o polyexam2

polytest2: polytest2.o poly2.o
	g++ -g polytest2.o poly2.o -o polytest2

polyexam2.o: polyexam2.cxx
	g++ polyexam2.cxx -c

polytest2.o: polytest2.cxx
	g++ polytest2.cxx -c

poly2.o: poly2.cxx poly2.h
	g++ poly2.cxx -c

clean:
	rm polyexam2 polyexam2.o polytest2.o poly2.o


