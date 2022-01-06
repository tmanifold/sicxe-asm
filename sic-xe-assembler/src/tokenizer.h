
/** Tokenizer.h
 *  The Tokenizer class will parse, line by line, a SIC/XE input file.
 *  Each line will be tokenized, with tokens being stored into their appropriate
 *  table, given what column they are in. (e.g. SYMTAB, OPTAB)
 */

#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <cstring>

#include <fstream>
#include <sstream>
#include <iostream>

class Tokenizer {

	private:
		std::ifstream* in_file;

		void strip_comments(std::string&);
	
	public:
		Tokenizer();
		~Tokenizer();

		void read(char*);
		std::string* tokenize(std::string);

		bool isExtended(std::string);

		int proc_operand(std::string);

		int get_mode(std::string, std::string);
		unsigned int get_byte(std::string);
};

#endif // _TOKENIZER_H_
