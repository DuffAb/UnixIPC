DIR_INC = ../include
DIR_SRC = ../src
DIR_OBJ = ../obj
DIR_BIN = ../bin

#如果定义了VPATH变量，make就会在当前目录找不到的情况下，到所指定的目录中去找寻文件
VPATH = ../src:../include

#要求make在"../include"目录下搜索所有 .h 结尾的文件
vpath %.h ../include
vpath %.cpp .:../src

SRC = $(wildcard ${DIR_SRC}/*.cpp)
DIR = $(notdir ${SRC})
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC}))

#TARGET = server

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


#声明伪目标 all，这个目标依赖 server ，这样就可以生成多个程序
all:server
.PHONY : all

objects = IPCServer.o UnixIPCPipe.o UnixIPCFifo.o
server : $(objects)
	$(CC) -o server $(objects)

IPCServer.o : IPCServer.cpp
	$(CC) $(CFLAGS) -c IPCServer.cpp
UnixIPCPipe.o : ../src/UnixIPCPipe.cpp
	$(CC) $(CFLAGS) -c ../src/UnixIPCPipe.cpp
UnixIPCFifo.o : ../src/UnixIPCFifo.cpp
	$(CC) $(CFLAGS) -c ../src/UnixIPCFifo.cpp

ALL:
	@echo $(SRC)
	@echo $(DIR)
	@echo $(OBJ)

.PHONY : clean
clean :
	rm server $(objects)
