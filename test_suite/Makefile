#OBJS specifies which files to compile as part of the project
#OBJS = source.cpp source2.cpp ...
SRC_CARD = test_card.cpp ../include/card.cpp
SRC_DECK = test_deck.cpp ../include/deck.cpp ../include/stack.cpp ../include/card.cpp
SRC_TABLE = test_table.cpp ../include/table.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall --pedantic

#LINKER_FLAGS specifies the libraries we're linking against
#LINKER_FLAGS = -llibrary -llibrary2 ...

#OBJ_NAME specifies the name of our executable
#OBJ_NAME = roubamonte

#This is the target that compiles our executable
#all : $(OBJS)
#	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

#This is the target that compiles test_card.cpp
card : $(SRC_CARD)
	$(CC) $(COMPILER_FLAGS) $(SRC_CARD)

#This is the target that compiles test_deck.cpp
deck : $(SRC_DECK)
	$(CC) $(COMPILER_FLAGS) $(SRC_DECK)

#This is the target that compiles test_deck.cpp
table : $(SRC_TABLE)
	$(CC) $(COMPILER_FLAGS) $(SRC_TABLE)

