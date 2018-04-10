// 755 - octal permission number to string expression converter
// 
// Copyright (c) 2016 Takel Hinomoto
// This file is provided under the MIT license.
// 
// To compile: $ cc nanagogo.c -o ~/bin/nngg (If you haven't ~/bin You can make it $ mkdir ~/bin; echo -e '\nexport PATH="$PATH:$HOME/bin"\n' >> ~/.profile)
// To execute: $ nngg 755

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static const char* stringExpressionTable[] =
{
	"---",
	"--x",
	"-w-",
	"-wx",
	"r--",
	"r-x",
	"rw-",
	"rwx",
};

int main(int argc, const char** argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "missing argument.\n");
		return -1;
	}
	
	const char* permissionNumber = argv[1];
	errno = 0;
	char* pEndCh = NULL;
	
	unsigned long value = strtoul(permissionNumber, &pEndCh, 8);
	if ((errno != 0) || (*pEndCh != '\0'))
	{
		fprintf(stderr, "permission value must be an octal number.\n");
		return -1;
	}
	
	if (value > 0777)
	{
		fprintf(stderr, "specified octal permission value too big.\n");
		return -1;
	}
	
	int others = (int)(value & 7);
	int group = (int)((value >> 3) & 7);
	int owner = (int)((value >> 6) & 7);
	
	fprintf(stdout, "%s%s%s\n", stringExpressionTable[owner], stringExpressionTable[group], stringExpressionTable[others]);
	
	return 0;
}
