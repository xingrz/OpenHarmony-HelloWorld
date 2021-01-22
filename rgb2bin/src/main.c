#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LEN (100 * 1024)

static void
print_help(void)
{
	printf("Usage:\n");
	printf("  rgb2bin [output.bin]\n");
}

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		print_help();
		goto exit;
	}

	size_t read = 0;
	size_t size = 0;
	uint8_t rgb24[MAX_LEN] = {0};
	do
	{
		read = fread(&rgb24 + size, 1, sizeof(rgb24) - size, stdin);
		size += read;
	} while (read > 0);

	usleep(100 * 1000);
	printf("rgb2bin\n==========\n");

	printf("Input: %zu bytes\n", size);
	if (size % 3 != 0)
	{
		printf("Error: Input size should be a multiple of 3.\n");
		return 1;
	}

	uint8_t pt[MAX_LEN] = {0};
	size_t pixels = size / 3;
	for (int i = 0; i < pixels; i += 2)
	{
		uint8_t pl = (rgb24[i * 3 + 2 + 0] >> 4) & 0xF;
		uint8_t pr = (rgb24[i * 3 + 2 + 3] >> 4) & 0xF;
		pt[i / 2] = (pl << 4) | pr;
	}

	FILE *out = fopen(argv[1], "wb+");
	fprintf(out, "#ifndef __BIN_TEXT__\n");
	fprintf(out, "#define __BIN_TEXT__\n");
	fprintf(out, "#include <stdint.h>\n");
	fprintf(out, "const uint8_t text[] = {\n");
	for (int i = 0; i < pixels / 2; i++)
	{
		if (i % 16 == 0)
		{
			fprintf(out, "   ");
		}
		fprintf(out, " 0x%02X,", pt[i]);
		if ((i + 1) % 16 == 0)
		{
			fprintf(out, "\n");
		}
	}
	fprintf(out, "};\n");
	fprintf(out, "#endif\n");
	fclose(out);

	printf("Output: %zu pixels\n", pixels / 2);

exit:
	return 0;
}
