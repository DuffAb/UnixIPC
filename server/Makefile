unix_ipc_pipe : IPCServer.o UnixIPCPipe.o
        g++ -o unix_ipc_pipe IPCServer.o UnixIPCPipe.o

IPCServer.o : IPCServer.c
        g++ -c IPCServer.c
UnixIPCPipe.o : UnixIPCPipe.c
        g++ -c UnixIPCPipe.c
clean :
        rm unix_ipc_pipe IPCServer.o UnixIPCPipe.o