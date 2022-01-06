
#include "optab.h"
#include <string>
//I plan to use constructor to create a hashmap with all the needed data
optab::optab()
{
	this->opcodes = (sicxe_op**) malloc(sizeof(sicxe_op*) * NUM_OPS);

	//59 entries
	this->opcodes[0]	= new sicxe_op(0x18, 3);	// ADD
	this->opcodes[1]	= new sicxe_op(0x58, 3);	// ADDF
	this->opcodes[2]	= new sicxe_op(0x90, 2);	// ADDR
	this->opcodes[3]	= new sicxe_op(0x40, 3);	// AND
	this->opcodes[4]	= new sicxe_op(0xB4, 2);	// CLEAR
	this->opcodes[5]	= new sicxe_op(0x28, 3);	// COMP
	this->opcodes[6]	= new sicxe_op(0x88, 3);	// COMPF
	this->opcodes[7]	= new sicxe_op(0xA0, 2);	// COMPR
	this->opcodes[8]	= new sicxe_op(0x24, 3);	// DIV
	this->opcodes[9]	= new sicxe_op(0x64, 3);	// DIVF
	this->opcodes[10]	= new sicxe_op(0x9C, 2);	// DIVR
	this->opcodes[11]	= new sicxe_op(0xC4, 1);	// FIX
	this->opcodes[12]	= new sicxe_op(0xC0, 1);	// FLOAT
	this->opcodes[13]	= new sicxe_op(0xF4, 1);	// HIO
	this->opcodes[14]	= new sicxe_op(0x3C, 3);	// J
	this->opcodes[15]	= new sicxe_op(0x30, 3);	// JEQ
	this->opcodes[16]	= new sicxe_op(0x34, 3);	// JGT
	this->opcodes[17]	= new sicxe_op(0x38, 3);	// JLT
	this->opcodes[18]	= new sicxe_op(0x48, 3);	// JSUB
	this->opcodes[19]	= new sicxe_op(0x00, 3);	// LDA
	this->opcodes[20]	= new sicxe_op(0x68, 3);	// LDB
	this->opcodes[21]	= new sicxe_op(0x50, 3);	// LDCH
	this->opcodes[22]	= new sicxe_op(0x70, 3);	// LDF
	this->opcodes[23]	= new sicxe_op(0x08, 3);	// LDL
	this->opcodes[24]	= new sicxe_op(0x6C, 3);	// LDS
	this->opcodes[25]	= new sicxe_op(0x74, 3);	// LDT
	this->opcodes[26]	= new sicxe_op(0x04, 3);	// LDX
	this->opcodes[27]	= new sicxe_op(0xD0, 3);	// LPS
	this->opcodes[28]	= new sicxe_op(0x20, 3);	// MUL
	this->opcodes[29]	= new sicxe_op(0x60, 3);	// MULF
	this->opcodes[30]	= new sicxe_op(0x98, 2);	// MULR
	this->opcodes[31]	= new sicxe_op(0xC8, 1);	// NORM
	this->opcodes[32]	= new sicxe_op(0x44, 3);	// OR
	this->opcodes[33]	= new sicxe_op(0xD8, 3);	// RD
	this->opcodes[34]	= new sicxe_op(0xAC, 2);	// RMO
	this->opcodes[35]	= new sicxe_op(0x4C, 3);	// RSUB
	this->opcodes[36]	= new sicxe_op(0xA4, 2);	// SHIFTL
	this->opcodes[37]	= new sicxe_op(0xA8, 2);	// SHIFTR
	this->opcodes[38]	= new sicxe_op(0xF0, 1);	// SIO
	this->opcodes[39]	= new sicxe_op(0xEC, 3);	// SSK
	this->opcodes[40]	= new sicxe_op(0x0C, 3);	// STA
	this->opcodes[41]	= new sicxe_op(0x78, 3);	// STB
	this->opcodes[42]	= new sicxe_op(0x54, 3);	// STCH
	this->opcodes[43]	= new sicxe_op(0x80, 3);	// STF
	this->opcodes[44]	= new sicxe_op(0xD4, 3);	// STI
	this->opcodes[45]	= new sicxe_op(0x14, 3);	// STL
	this->opcodes[46]	= new sicxe_op(0x7C, 3);	// STS
	this->opcodes[47]	= new sicxe_op(0xE8, 3);	// STSW
	this->opcodes[48]	= new sicxe_op(0x84, 3);	// STT
	this->opcodes[49]	= new sicxe_op(0x10, 3);	// STX
	this->opcodes[50]	= new sicxe_op(0x1C, 3);	// SUB
	this->opcodes[51]	= new sicxe_op(0x5C, 3);	// SUBF
	this->opcodes[52]	= new sicxe_op(0x94, 2);	// SUBR
	this->opcodes[53]	= new sicxe_op(0xB0, 2);	// SVC
	this->opcodes[54]	= new sicxe_op(0xE0, 3);	// TD
	this->opcodes[55]	= new sicxe_op(0xF8, 1);	// TIO
	this->opcodes[56]	= new sicxe_op(0x2C, 3);	// TIX
	this->opcodes[57]	= new sicxe_op(0xB8, 2);	// TIXR
	this->opcodes[58]	= new sicxe_op(0xDC, 3);	// WD

	
	std::string mnem[59]={
		"ADD",
		"ADDF",
		"ADDR",
		"AND",
		"CLEAR",
		"COMP",
		"COMPF",
		"COMPR",
		"DIV",
		"DIVF",
		"DIVR",
		"FIX",
		"FLOAT",
		"HIO",
		"J",
		"JEQ",
		"JGT",
		"JLT",
		"JSUB",
		"LDA",
		"LDB",
		"LDCH",
		"LDF",
		"LDL",
		"LDS",
		"LDT",
		"LDX",
		"LPS",
		"MUL",
		"MULF",
		"MULR",
		"NORM",
		"OR",
		"RD",
		"RMO",
		"RSUB",
		"SHIFTL",
		"SHIFTR",
		"SIO",
		"SSK",
		"STA",
		"STB",
		"STCH",
		"STF",
		"STI",
		"STL",
		"STS",
		"STSW",
		"STT",
		"STX",
		"SUB",
		"SUBF",
		"SUBR",
		"SVC",
		"TD",
		"TIO",
		"TIX",
		"TIXR",
		"WD"
	};
	
	for (int x=0;x<59;x++)
	{
		this->insert(mnem[x], opcodes[x]->get_op());
	}
	
	//this->print();
}

optab::~optab()
{
	//
}

int optab::get_format(int op)
{
	int f = 1;

	for (int i = 0; i < NUM_OPS; i++)
	{
		if (opcodes[i]->get_op() == op)
		{
			f = opcodes[i]->get_format();
		}
	}

	return f;
}
