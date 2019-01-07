#ifndef _UNIX_IPC_FIFO_H_
#define _UNIX_IPC_FIFO_H_

class IPCFifo
{
public:
	IPCFifo(const char* SrvReadCliWriteFifo, const char* SrvWriteCliReadFifo);
	~IPCFifo();

public:
	int ODeriveFifoSrv();

	int OCreateFifoSrv();
	int OCreateFifoCli();

private:
	char _SrvReadCliWriteFifo[100];
	char _SrvWriteCliReadFifo[100];

	int _FifoSrvRead;
	int _FifoSrvWrite;

	int _FifoCliRead;
	int _FifoCliWrite;		
};
#endif  /* _UNIX_IPC_FIFO_H_ */