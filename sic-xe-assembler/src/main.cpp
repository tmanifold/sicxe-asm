
// main.cpp
// SIC/XE Assembler

#include "assembler.h"
#include "exit.h"

#include <stdio.h>

int main (int argc, char **argv)
{

	Assembler* a;

	char* fname = argv[1];
	int exit_code = EXIT_CODE_OK;

	// check for correct numer of arguments given by command line

	if (argc != 2)
	{
		fprintf(stderr, "STDERR: Invalid number of arguments\n");
		exit_code = EXIT_CODE_INVALID_ARGS;
	}
	else
	{
		a = new Assembler(fname);
		//a->assemble();
	}


	printf("\nEXIT_CODE: %d\n", exit_code);
	return exit_code;
}
