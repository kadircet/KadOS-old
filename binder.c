#include <stdio.h>
#include <stdlib.h>

int getSize(FILE *f)
{
	fseek (f, 0, SEEK_END);
	int size = ftell(f);
	rewind (f);
	return size;
}

int main(int argc, char* argv[])
{
	int i;
	FILE *out = fopen(argv[1], "wb");
	for(i=2;i<argc;i++)
	{
		FILE *in = fopen(argv[i], "rb");
		int size = getSize(in);
		unsigned char *buff = (unsigned char*)malloc(sizeof(unsigned char) * size);
		fread(buff, 1, size, in);
		fclose(in);

		fwrite(buff, 1, size, out);
	}
	fclose(out);

	FILE* in = fopen(argv[1], "rb");
	int size = getSize(in);
	unsigned char *buff = (unsigned char*)malloc(sizeof(unsigned char) * size);
	fread(buff, 1, size, in);
	fclose(in);

	out = fopen(argv[1], "wb");
	fwrite(buff, 1, size, out);
	buff = (unsigned char*)calloc(sizeof(unsigned char), (1474560-size));
	fwrite(buff, 1, (1474560-size), out);
	fclose(out);

	return 0;
}
