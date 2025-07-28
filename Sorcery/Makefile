CXX=g++
CXXFLAGS= -std=c++20 -Wall -g -MMD
EXEC=sorcery
INCLUDES=-I. -Itriggers/ -Ienchantments/ -Idisplays/ -Ispells/

CCFILES=$(wildcard *.cc)
OBJECTS=${CCFILES:.cc=.o}
DEPENDS=${CCFILES:.cc=.d}

SUBDIRS = displays enchantments minions rituals spells triggers asciiart
SUBOBJS = displays.o enchantments.o minions.o rituals.o spells.o triggers.o asciiart.o

%.o: %.cc 
	${CXX} ${CXXFLAGS} ${INCLUDES} -c $< -o $@

%.o:
	$(MAKE) -C $(basename $@)

${EXEC}:${OBJECTS} ${SUBOBJS}
	${CXX} ${CXXFLAGS} ${INCLUDES} ${OBJECTS} ${SUBOBJS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean ${SUBDIRS}
clean:
	rm -f ${EXEC} ${OBJECTS} ${SUBOBJS} ${DEPENDS}