#ifndef _UNIX_IPC_COMM_H_
#define _UNIX_IPC_COMM_H_

static int OServer(int r, int w)
{
	int		fd;
	ssize_t	n;
	char	buff[MAXLINE + 1];

	printf("OServer read 0\n");
	/* read pathname from IPC channel */
	if ((n = read(r, buff, MAXLINE)) == 0)
	{
		printf("end-of-file while reading pathname");
	}
	buff[n] = '\0';		/* null terminate pathname */
	printf("OServer read 1\n");
	if ((fd = open(buff, O_RDONLY)) < 0) 
	{
		/* error: must tell client */
		snprintf(buff + n, sizeof(buff) - n, ": can't open, %s\n", strerror(errno));
		n = strlen(buff);
		write(w, buff, n);

	} 
	else 
	{
		/* open succeeded: copy file to IPC channel */
		while ( (n = read(fd, buff, MAXLINE)) > 0)
		{
			write(w, buff, n);
		}
		close(fd);
	}
}

static int OClient(int r, int w)
{
	size_t	len;
	ssize_t	n;
	char	buff[MAXLINE];

	/* read pathname */
	fgets(buff, MAXLINE, stdin);
	len = strlen(buff);		/* fgets() guarantees null byte at end */
	if (buff[len-1] == '\n')
		len--;				/* delete newline from fgets() */

	/* write pathname to IPC channel */
	printf("OClient write buff(%s)\n", buff);
	write(w, buff, len);
	printf("OClient write 1\n");
	/* read from IPC, write to standard output */
	while ( (n = read(r, buff, MAXLINE)) > 0)
		write(STDOUT_FILENO, buff, n);
}

#endif  /* _UNIX_IPC_COMM_H_ */