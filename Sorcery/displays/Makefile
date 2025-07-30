CXX=g++ 
CXXFLAGS= -std=c++20 -Wall -g -MMD
INCLUDES= -I../triggers -I../asciiart -I../minions -I../rituals -I../spells -I../enchantments -I../

CCFILES=cliDisplay.cc
OBJFILES=${CCFILES:.cc=.o}
DEPENDS=${CCFILES:.cc=.d}
OUTDIR=../
OBJ= ${OUTDIR}displays.o

all: ${OBJ}

${OBJ}: ${OBJFILES}
	${CXX} -r $< -o $@

%.o: %.cc 
	${CXX} ${CXXFLAGS} ${INCLUDES} -c $< -o $@

-include ${DEPENDS}

.PHONY: all clean 
clean:
	rm ${OBJ} ${OBJFILES} ${DEPENDS}
