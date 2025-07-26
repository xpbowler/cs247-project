CXX=g++ 
CXXFLAGS= -std=c++20 -Wall -g -MMD
OBJ= spells.o 
CCFILES=${wildcard *.cc}
OBJFILES=${CCFILES:.cc=.o}
DEPENDS=${CCFILES:.cc=.d}
OUTDIR=../

all: ${OBJ}

${OBJ}: ${OBJFILES}
	${CXX} -r $^ -o $@

%.o: %.cc 
	${CXX} ${CXXFLAGS} -c $< -o $@

install:
	mv ${OBJ} ${OUTDIR}

-include ${DEPENDS}

.PHONY: all clean 
clean:
	rm ${OBJ} ${OBJFILES} ${DEPENDS}
