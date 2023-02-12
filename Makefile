CFLAGS = -Wall -Wextra -Werror
CPdPFLAGS = -MMD
PREF_SRC = ./src/
PREF_OBJ = ./obj/
PREF_BIN = ./bin/
PREF_TEST = ./test/
PREF_LIB = ./src/lib/

CC = gcc
TARGET = lab1

SRC = $(wildcard $(PREF_SRC)*/*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
POST_OBJ = $(patsubst ./%.c, $(PREF_OBJ)%.o, $(SRC))
STATIC = ./obj/src/lib/static.a

LIB = $(wildcard $(PREF_LIB)*.c)
LIB_OBJ = $(patsubst %.c, %.o, $(LIB))
POST_LIB = $(patsubst ./%.c, $(PREF_OBJ)%.o, $(LIB))

.PHONY: all
all : $(PREF_BIN)$(TARGET)

$(PREF_BIN)$(TARGET) : ./src/main/main.o $(STATIC)
	$(CC) $(CFLAGS) ./obj/src/main/main.o $(STATIC) -o $(PREF_BIN)$(TARGET)

%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -I $(PREF_SRC) -c $< -o $(PREF_OBJ)$@

-include %.d

$(STATIC) : $(LIB_OBJ)
	ar rcs $@ $(POST_LIB)

.PHONY: run
run :	
	$(PREF_BIN)$(TARGET) 2 -a -d

.PHONY: clean
clean :
	rm $(POST_OBJ) $(PREF_BIN)$(TARGET) $(PREF_OBJ)*/*/*.d $(PREF_OBJ)*/*.d $(PREF_OBJ)*/*/*.a $(PREF_BIN)$(TARGET)