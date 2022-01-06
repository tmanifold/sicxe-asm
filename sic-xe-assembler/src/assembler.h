
/**
 * assembler.h
 *
 * The assembler object will 'own' all of the necessary components and modules
 * required for assembling an SIC/XE object program. For example, assembler
 * will control the various tables (OPTAB, SYMTAB, etc), tokenizer, macro processor,
 * and so on.
 */

#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

#include <fstream>

#include "instruction.h"
#include "tokenizer.h"
#include "optab.h"

#define WORD_SIZE 3

class Assembler
{

	private:
		typedef enum directives
		{
			START,
			END,	
			BYTE,	
			WORD,	
			RESB,
			RESW,
			BASE

		} directive;


		struct registers
		{
			int B  = 0x0;
			int PC = 0x0;

			int base()
			{
				return B;
			}

			void base(int b)
			{
				B = b;
			}

			int pc()
			{
				return PC;
			}

			void pc(int p)
			{
				PC = p;
			}

			void pc_inc()
			{
				PC += WORD_SIZE;
			}

			void pc_inc(int p)
			{
				PC += p;
			}

		} reg;

		Tokenizer *tokenizer;
	
		optab* OPTAB;		// opcodes
		hashMap* SYMTAB;	// symbols
		hashMap* DTAB; 		// assembler directives

		char* file_name;
		std::ifstream* in_file;

		void init();
		void assem_pass1(int&, std::string, std::string, std::string);
		void assem_pass2(int&, std::string, std::string, std::string);

		int getInstructionMode(std::string, std::string);
		int calcInstructionAddress_Format2(std::string);
		int calcInstructionAddress_Format3(int &, std::string);
		int calcRelativeAddress(int&, int);

		// Helper functions
		int getAddressFromString(std::string);

		bool doCodeGeneration(std::string);
		bool isExtended(std::string);

	public:
		Assembler();
		Assembler(char*);
		~Assembler();

		void assemble(int);
};

#endif // _ASSEMBLER_H_
