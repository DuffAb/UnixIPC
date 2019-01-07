#include "../src/UnixIPCType.h"
// #include "../src/UnixIPCPipe.h"
#include "../src/UnixIPCFifo.h"


int main(int argc, char const *argv[])
{
	int ipc = 0;
	printf("Select IPC: \n"
		"\t0: PIPE\n"
		"\t1: FIFO\n"
		"\t2: 原始数据\n"
		"\t3: 固件更新\n"
		"\t4: 数据设置\n");

	if (scanf("%d", &ipc))
	{
		switch(ipc)
		{
		// case 0:{
		// 	IPCPipe pp;
		// 	pp.ODerivePipeSrv();
		// 	break;
		// }

		case 1:{
			IPCFifo fifo("/tmp/srv_r_cli_w.fifo", "/tmp/srv_w_cli_r.fifo");
			fifo.OCreateFifoSrv();
			break;
		}
		
			
		}
	}
	
	return 0;
}