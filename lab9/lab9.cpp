#include <cstdio>

int main(int argc, char *argv[])
{
	long long num;
	int vpn[3];
	int po;

	if (argc != 2)
	{
		printf("Usage ./lab9 <64-bit virtual address>\n");
		return -1;
	}

	sscanf(argv[1], "%lx", &num);

	printf("num = %lx\n", num);

	po = num & 0xfff;
	num >>= 12;
	
	printf("   Level   Index   Byte Offset\n");

	for(int i = 0; i < 3; i++)
	{
		vpn[i] = num & 0x1ff;
		num >>= 9;
	}
	
	for(int i = 2; i >= 0; i--)
	{
		printf("VPN[%d] = %d   (%d)\n", i, vpn[i], (vpn[i] * 8));
	}

	printf("PO     = %x\n", po);

return 0;
}
