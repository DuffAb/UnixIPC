#ifndef _UNIX_IPC_PIPE_H_
#define _UNIX_IPC_PIPE_H_

enum ipc_type
{
	ipc_pipe,
};

class IPCPipe
{
public:
	IPCPipe();
	~IPCPipe();

public:
	int ODerivePipeSrv();
	
private:
	int _PipeSrvRead;
	int _PipeSrvWrite;

	int _PipeCliRead;
	int _PipeCliWrite;



		
};
#endif  /* _UNIX_IPC_H_ */