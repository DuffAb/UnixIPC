#include <sys/types.h>
#include <sys/stat.h>


#include "UnixIPCType.h"
#include "UnixIPCComm.h"
#include "UnixIPCFifo.h"

IPCFifo::IPCFifo(const char* SrvReadCliWriteFifo, const char* SrvWriteCliReadFifo)
{
	int ret = 0;
	snprintf(_SrvReadCliWriteFifo, 100, "%s", SrvReadCliWriteFifo);
	snprintf(_SrvWriteCliReadFifo, 100, "%s", SrvWriteCliReadFifo);

	// 允许用户读、用户写、组成员读和其他用户读
	ret = mkfifo(SrvReadCliWriteFifo, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (ret < 0 && errno != EEXIST)
	{
		printf("can't create %s", SrvReadCliWriteFifo);
	}

	ret = mkfifo(SrvWriteCliReadFifo, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (ret < 0 && errno != EEXIST)
	{
		unlink(SrvReadCliWriteFifo);// 第一个FIFO创建成功，所以需要unlink
		printf("can't create %s", SrvWriteCliReadFifo);
	}
}

IPCFifo::~IPCFifo()
{
	close(_FifoSrvRead);
	close(_FifoSrvWrite);

	close(_FifoCliRead);
	close(_FifoCliWrite);

	unlink(_SrvReadCliWriteFifo);
	unlink(_SrvWriteCliReadFifo);

	exit(0);
}

int IPCFifo::ODeriveFifoSrv()
{
	pid_t SrvPid;
	if ((SrvPid = fork()) == 0)
	{
		_FifoSrvRead  = open(_SrvReadCliWriteFifo, O_RDONLY, 0);
		_FifoSrvWrite = open(_SrvWriteCliReadFifo, O_WRONLY, 0);
		
		OServer(_FifoSrvRead, _FifoSrvWrite);
		exit(0);
	}

	_FifoCliWrite = open(_SrvReadCliWriteFifo, O_WRONLY, 0);
	_FifoCliRead  = open(_SrvWriteCliReadFifo, O_RDONLY, 0);
	
	OClient(_FifoCliRead, _FifoCliWrite);
	waitpid(SrvPid, NULL, 0);	
}

int IPCFifo::OCreateFifoSrv()
{
	_FifoSrvRead  = open(_SrvReadCliWriteFifo, O_RDONLY, 0);
	_FifoSrvWrite = open(_SrvWriteCliReadFifo, O_WRONLY, 0);
		
	OServer(_FifoSrvRead, _FifoSrvWrite);
	exit(0);
}

int IPCFifo::OCreateFifoCli()
{
	_FifoCliWrite = open(_SrvReadCliWriteFifo, O_WRONLY, 0);
	_FifoCliRead  = open(_SrvWriteCliReadFifo, O_RDONLY, 0);
	
	OClient(_FifoCliRead, _FifoCliWrite);
	exit(0);
}