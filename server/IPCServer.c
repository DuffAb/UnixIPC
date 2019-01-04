#include "../src/UnixIPCPipe.h"


int main(int argc, char const *argv[])
{
	IPCPipe pp;
	pp.OCreatePipeSrv();
	return 0;
}