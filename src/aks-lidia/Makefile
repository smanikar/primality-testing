#CFLAGS="-O2 -Wall -march=pentium4 -g -pg -fprofile-arcs -DSKIPGCD"
CFLAGS="-O2 -Wall -g -pg -fprofile-arcs -DSKIPGCD"
#CFLAGS="-O5 -Wall -march=pentium4 -DSKIPGCD -fomit-frame-pointer -ffast-math -mpreferred-stack-boundary=2 -funroll-all-loops"
#CFLAGS="-O2 -Wall -march=pentium4 -pg -DDEBUG -DDEBUG2 -DSKIPGCD"
CHOST=i686-pc-linux-gnu
CXXFLAGS="${CFLAGS}"
LFLAGS=-lgmp -lLiDIA

all:	test testlist testrange

test:	aks.o main.o
	g++ ${CXXFLAGS} -o test aks.o main.o ${LFLAGS}

testlist:	testlist.o aks.o
	g++ ${CXXFLAGS} -o testlist testlist.o aks.o ${LFLAGS}

testrange:	testrange.o aks.o
	g++ ${CXXFLAGS} -o testrange testrange.o aks.o ${LFLAGS}

aks.o:	aks.cpp aks.h
	g++ ${CXXFLAGS} -c -o aks.o aks.cpp

main.o:	main.cpp aks.h
	g++ ${CXXFLAGS} -c -o main.o main.cpp

testlist.o: testlist.cpp aks.h
	g++ ${CXXFLAGS} -c -o testlist.o testlist.cpp

testrange.o: testrange.cpp aks.h
	g++ ${CXXFLAGS} -c -o testrange.o testrange.cpp

clean:	
	rm -f *.o test testlist testrange core

fullclean:	clean
	rm -f output.log a.out *.dot *.pre *.da gmon.out
