CXX=g++
CXXFLAGS= -std=c++20 -Wall -g -MMD
EXEC=sorcery
INCLUDES=-I.

CCFILES=$(wildcard *.cc)
OBJECTS=${CCFILES:.cc=.o}
DEPENDS=${CCFILES:.cc=.d}

SUBDIRS = displays enchantments minions rituals spells triggers 
SUBOBJS = $(addsuffix .o,$(SUBDIRS))

%.o: %.cc 
	${CXX} ${CXXFLAGS} ${INCLUDES} -c $< -o $@

${EXEC}:${OBJECTS} ${SUBOBJS}
	${CXX} ${CXXFLAGS} ${INCLUDES} ${OBJECTS} ${SUBOBJS} -o ${EXEC}

${SUBDIRS}: 
	${MAKE} -C $@

-include ${DEPENDS}

.PHONY: clean ${SUBDIRS}
clean:
	rm -f ${EXEC} ${OBJECTS} ${SUBOBJS} ${DEPENDS}