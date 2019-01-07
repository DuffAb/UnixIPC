#include <sys/types.h>

#include "UnixIPCType.h"
#include "UnixIPCComm.h"
#include "UnixIPCPipe.h"

IPCPipe::IPCPipe()
{
	int uPipe[2];
	pipe(uPipe); // 返回两个文件描述符，前者打开来读，后者打开来写
	_PipeSrvRead  = uPipe[0];
	_PipeCliWrite = uPipe[1];

	pipe(uPipe);
	_PipeSrvWrite = uPipe[1];
	_PipeCliRead  = uPipe[0];
}

IPCPipe::~IPCPipe()
{

}

int IPCPipe::ODerivePipeSrv()
{
	pid_t SrvPid;
	if ((SrvPid = fork()) == 0)
	{
		close(_PipeCliWrite);
		close(_PipeCliRead);
		OServer(_PipeSrvRead, _PipeSrvWrite);
		exit(0);
	}

	close(_PipeSrvWrite);
	close(_PipeSrvRead);
	OClient(_PipeCliRead, _PipeCliWrite);
	waitpid(SrvPid, NULL, 0);
	exit(0);
}

