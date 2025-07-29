CXX=g++ 
CXXFLAGS= -std=c++20 -Wall -g -MMD

CCFILES=${wildcard *.cc}
OBJFILES=${CCFILES:.cc=.o}
DEPENDS=${CCFILES:.cc=.d}
OUTDIR=../
INCLUDES=-I../triggers -I../rituals -I../ -I../minions
OBJ= ${OUTDIR}spells.o 

all: ${OBJ}

${OBJ}: ${OBJFILES}
	${CXX} -r $^ -o $@

%.o: %.cc 
	${CXX} ${CXXFLAGS} ${INCLUDES} -c $< -o $@

-include ${DEPENDS}

.PHONY: all clean 
clean:
	rm ${OBJ} ${OBJFILES} ${DEPENDS}
