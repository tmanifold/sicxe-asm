
// instruction.h

#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <string>
#include <sstream>

#include "hashmap.h"

class instruction
{
	private:
		int op;
		int format;
		int mode;
		int address;
		int instr;

		// Valid modes are as follows:
		// n - indirect
		// i - immediate
		// x - indexed
		// b - base relative
		// p - pc relative
		// e - extended format

	public:
		instruction(int, int, int, int);

		int get(); // return instr

		int  opcode();	  // get op
		void opcode(int); // set op
		
		int  addr_mode();	  // get mode
		void addr_mode(int);	  // set mode
		
		int  addr();	  // get address
		void addr(int);// set address

		bool isPCRelative();
		bool isIndexRelative();
		bool isBaseRelative();

		void build(); // build the instruction using bitwise operations
		void print(); 
};

#endif // _INSTRUCTION_H_
