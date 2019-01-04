DIR_INC = ../include
DIR_SRC = ../src
DIR_OBJ = ../obj
DIR_BIN = ../bin

#SRC = $(wildcard ${DIR_SRC}/*.cpp)
#DIR = $(notdir ${SRC})
#OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC}))
#ALL:
#	@echo $(DIR_INC)
#	@echo $(SRC)
#	@echo $(DIR)
#	@echo $(OBJ)

#TARGET = unix_ipc_pipe

#BIN_TARGET = ${DIR_BIN}/${target}

CC = g++
CFLAGS = -g -Wall

#${BIN_TARGET}:${OBJ}
#	$(CC) $(OBJ)  -o $@

#${DIR_OBJ}/%.o:${DIR_SRC}/%.c
#	$(CC) $(CFLAGS) -c  $< -o $@

#.PHONY:clean
#clean:
#	find ${DIR_OBJ} -name *.o -exec rm -rf {}

objects = IPCServer.o UnixIPCPipe.o
unix_ipc_pipe : $(objects)
	$(CC) -o unix_ipc_pipe $(objects)

IPCServer.o : IPCServer.c
	$(CC) $(CFLAGS) -c IPCServer.c
UnixIPCPipe.o : ../src/UnixIPCPipe.c
	$(CC) $(CFLAGS) -c ../src/UnixIPCPipe.c

.PHONY : clean
clean :
	rm unix_ipc_pipe $(objects)
