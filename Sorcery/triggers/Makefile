CXX=g++ 
CXXFLAGS= -std=c++20 -Wall -g -MMD
INCLUDES= -I../minions -I../rituals -I. -I.. -I../displays

CCFILES=${wildcard *.cc}
OBJFILES=${CCFILES:.cc=.o}
DEPENDS=${CCFILES:.cc=.d}
OUTDIR=../
OBJ= ${OUTDIR}triggers.o 

all: ${OBJ}

${OBJ}: ${OBJFILES}
	${CXX} -r $^ -o $@

%.o: %.cc 
	${CXX} ${CXXFLAGS} ${INCLUDES} -c $< -o $@

-include ${DEPENDS}

.PHONY: all clean 
clean:
	rm ${OBJ} ${OBJFILES} ${DEPENDS}
