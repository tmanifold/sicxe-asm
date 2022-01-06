
// instruction.cpp

#include "instruction.h"

#include <math.h>
#include <stdio.h>
       

/**
 * The following parameters are as follows for the various instruction formats:
 * Format 1:
 *   op: the given opcode
 *   format: unused
 *   r1: unused
 *   r2: unused
 * 
 * Format 2:
 *   op: the given opcode
 *   format: 2
 *   r1: the first operand
 *   r2: the second operand
 *
 * Format 3/4:
 *   op: the given opcode:
 *   format: 3 or 4
 *   r1: addressing mode (nixbpe)
 *   r2: target address
 */
instruction::instruction(int op = 0x0, int format = 0x0, int r1 = 0x0, int r2 = 0x0)
{
	this->op = op;

	if (r1 & 0x1 == 0x1)
		this->format = 4;
	else
		this->format = format;
	
	switch (format)
	{
		case 1:
			printf("FORMAT 1\n");
			this->instr = this->op;
			break;
		case 2:
			//   opcode | r1 | r2
			// 0000 0000 0000 0000
	
			this->mode = 0x0;
			this->address = (r1 << 4) | r2;

			this->instr = (this->op << 8) | this->address;

			break;
		case 3:
			// OPCODE  ni xbpe       TA
			// 0000 00|11 0000|0000 0000 0000

			// in format 3, r1 is mode, r3 is target address

			this->mode = r1;
			this->address = r2;

			this->instr = (this->op << 16) | (this->mode << 12) | this->address;
			
			break;
		
		case 4:
			// OPCODE  ni xbpe         TA
			// 0000 00|11 0001|0000 0000 0000 0000 0000
			
			this->mode = r1;
			this->address = r2;

			//printf("%s: op: 0x%02X | mode: 0x%02X | TA: 0x%05X\n", __func__, (this->op << 24), (this->mode << 20), this->address);
			
			this->instr = (this->op << 24) | (this->mode << 20) | this->address;
			//printf("%s: instr: 0x%06X\n", __func__, this->instr);

			break;	
		default:
			this->address = r2;
			this->instr = this->address;
			break;
	}

	//this->build();
}

/**
 * For now, build() only constructs format 3 instructions.
 * This will need to be modified to build different types of instructions
 * based on the bit values of mode
 */
void instruction::build()
{
	/*
	int n = mode & 0x20;
	int i = mode & 0x10;
	int x = mode & 0x08;
	int b = mode & 0x04;
	int p = mode & 0x02;
	int e = mode & 0x01;
	*/
	
	this->instr = (this->op << 16) | (this->mode << 12) | this->address;
}

int instruction::get()
{
	return this->instr;
}

/**
 * Return true if instruction is PC relative
 */
bool instruction::isPCRelative()
{
	return (this->mode & 0x02 == 0x02);
}

/**
 * Return true if instruction is index relative
 */
bool instruction::isIndexRelative()
{
	return (this->mode & 0x08 == 0x08);
}

/**
 * Return true if instruction is base relative
 */
bool instruction::isBaseRelative()
{
	return (this->mode & 0x04 == 0x04);
}

int instruction::opcode()
{
	return this->op;
}

void instruction::opcode(int op)
{
	this->op = op;
}

int instruction::addr_mode()
{
	return this->mode;
}

void instruction::addr_mode(int mode)
{
	this->mode = mode;
}

int instruction::addr()
{
	return this->address;
}

void instruction::addr(int addr)
{
	this->address = addr;
}

void instruction::print()
{
	printf("instruction: 0x%06X\n", this->instr);
}
