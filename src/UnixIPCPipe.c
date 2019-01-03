#include "UnixIPCType.h"
#include "UnixIPCPipe.h"

IPCPipe::IPCPipe(int ipc): _ipc(ipc)
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

int IPCPipe::OCreatePipeSrv()
{
	pid_t SrvPid;
	if ((SrvPid = fork()) == 0)
	{
		close(_PipeCliWrite);
		close(_PipeCliRead);
		OPipeSrv();
		exit(0);
	}

	close(_PipeSrvWrite);
	close(_PipeSrvRead);
	OPipeCli();
	waitpid(SrvPid, NULL, 0);
	exit(0);
}

int IPCPipe::OPipeSrv()
{
	int		fd;
	ssize_t	n;
	char	buff[MAXLINE + 1];

	/* read pathname from IPC channel */
	if ((n = read(_PipeSrvRead, buff, MAXLINE)) == 0)
	{
		printf("end-of-file while reading pathname");
	}
	buff[n] = '\0';		/* null terminate pathname */

	if ((fd = open(buff, O_RDONLY)) < 0) 
	{
		/* error: must tell client */
		snprintf(buff + n, sizeof(buff) - n, ": can't open, %s\n", strerror(errno));
		n = strlen(buff);
		Write(_PipeSrvWrite, buff, n);

	} 
	else 
	{
		/* open succeeded: copy file to IPC channel */
		while ( (n = read(fd, buff, MAXLINE)) > 0)
		{
			write(_PipeSrvWrite, buff, n);
		}
		close(fd);
	}
}

int IPCPipe::OPipeCli()
{
	size_t	len;
	ssize_t	n;
	char	buff[MAXLINE];

	/* read pathname */
	fgets(buff, MAXLINE, stdin);
	len = strlen(buff);		/* fgets() guarantees null byte at end */
	if (buff[len-1] == '\n')
		len--;				/* delete newline from fgets() */

		/* 4write pathname to IPC channel */
	write(writefd, buff, len);

	/* read from IPC, write to standard output */
	while ( (n = read(readfd, buff, MAXLINE)) > 0)
		write(STDOUT_FILENO, buff, n);
}