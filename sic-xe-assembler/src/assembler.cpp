
// assembler.cpp

#include "assembler.h"

#include <math.h>

Assembler::Assembler()
{

}

/**
 * Assemble the file given by <n>
 */
Assembler::Assembler(char* n)
{
	this->file_name = n;

	this->init();

	this->tokenizer = new Tokenizer();

	this->assemble(1); // pass 1
	this->SYMTAB->print();
	this->assemble(2); // pass 2
}

Assembler::~Assembler()
{
	delete this->tokenizer;
	delete this->SYMTAB;
	delete this->OPTAB;
	delete this->DTAB;
}

/**
 * init() should initializes class members, such as
 * OPTAB, SYMTAB, etc.
 */
void Assembler::init()
{
	this->SYMTAB = new hashMap();
	this->OPTAB = new optab();

	this->DTAB = new hashMap();

	this->DTAB->insert("START", Assembler::directive::START);
	this->DTAB->insert("END",   Assembler::directive::END);
	this->DTAB->insert("BYTE",  Assembler::directive::BYTE);
	this->DTAB->insert("WORD",  Assembler::directive::WORD);
	this->DTAB->insert("RESB",  Assembler::directive::RESB);
	this->DTAB->insert("RESW",  Assembler::directive::RESW);
	this->DTAB->insert("BASE",  Assembler::directive::BASE);
//	this->DTAB->print();
}



/**
 * Assemble the object program by initiating the first and second passes
 */
void Assembler::assemble(int pass = 1)
{	
	bool start = true;
	
	this->in_file = new std::ifstream(this->file_name, std::ios::in);
		
	if (this->in_file->is_open())
	{
		std::string* tokens;

		int LOC = 0; // keep track of the memory location for each instruction
			     // Increment at the end of each line based on required memory
		this->reg.pc(0);

		if (pass ==  2)
			printf("%s\t%9s\t%6s\t%10s\t%s %15s\t%10s\n", "FUNC", "LOC", "LABEL", "OP", "OPERAND", "OBJCODE", "PC");
		
		while (in_file->good())
		{
			
			std::string line;

			std::getline(*(in_file), line);

			tokens = tokenizer->tokenize(line);

			// If tokens[2] is equal to empty string, then there is no label
			// => tokens[0] is MNEM
			// => tokens[1] is OPERAND
			// 
			// If tokens[2] has content, all fields are used
			// => tokens[0] is LABEL
			// => tokens[1] is MNEM
			// => tokens[2] is OPERAND
			
			std::string LABEL	= "";
			std::string MNEM	= "";
			std::string OPERAND	= "";

			if (tokens[2] == "")
			{
				MNEM 	= tokens[0];
				OPERAND = tokens[1];
			}
			else
			{
				LABEL	= tokens[0];
				MNEM	= tokens[1];
				OPERAND = tokens[2];

			}

			int dcode = this->DTAB->search_Ele(MNEM);
		
			//printf("directive: %d\n", directive);

			if (dcode == Assembler::directive::START)
			{
				LOC = atoi(OPERAND.c_str());
				this->reg.pc(LOC);
			}
			else
			{
				start = false;
				this->reg.pc_inc();
			}

			if (MNEM != "")
			{
				switch (pass)
				{
					case 1:
						this->assem_pass1(LOC, LABEL, MNEM, OPERAND);
						break;
					case 2:
						this->assem_pass2(LOC, LABEL, MNEM, OPERAND);
						break;
					default:
						break;
				}
			

				if (!start)
				{
					// calculate the location offset
					switch (dcode)
					{
						case Assembler::directive::RESW:

							LOC += WORD_SIZE * atoi(OPERAND.c_str());
							break;

						case Assembler::directive::RESB:
						
							LOC += atoi(OPERAND.c_str());
							break;

						case Assembler::directive::BASE:

							LOC += 0;
							break;

						case Assembler::directive::BYTE:

							switch(OPERAND[0])
							{
								case 'X':
									LOC += 1;
									break;
								case 'C':
									LOC += (OPERAND.length()) / 2; // subtract 3 for the C'' and divde by two for bytes
									break;
								default:
									break;
							}

							break;

						default:
							LOC += WORD_SIZE;
							break;
					}

					this->reg.pc(LOC);
				}
			}
			// print PC
			//printf("%s: PC: 0x%02X\n", __func__, Assembler::reg.pc());
		}
	}
	this->in_file->close();

	//this->SYMTAB->print();
}


/**
 * A simple helper function to cut down on spaghetti code.
 * Checks if the first character of the given string (a mnemonic opcode)
 * is a plus sign, indicated extended format.
 */
bool Assembler::isExtended(std::string mnem)
{
	return mnem[0] == '+';
}

/**
 * Decide whether or not to do actual code generation based on the value of MNEM.
 * if MNEM is found in DTAB and equal to START, END, or BASE, return false
 */
bool Assembler::doCodeGeneration(std::string MNEM)
{
	bool do_generation = true;

	int dcode = this->DTAB->search_Ele(MNEM);

	switch (dcode)
	{
		case Assembler::directive::START:
		case Assembler::directive::END:
		case Assembler::directive::BASE:
			do_generation = false;
			break;
		default:
			break;
	}

	return do_generation;
}

/**
 * First pass will insert unknown symbols and their memory locations into the
 * SYMTAB for use in pass 2
 */
void Assembler::assem_pass1(int &LOC, std::string LABEL, std::string MNEM, std::string OPERAND)
{

//	print("%s: 0x%02X\t %s\t%s\t%s\n",__func__,  LOC, LABEL.c_str(), MNEM.c_str(), OPERAND.c_str());

	int format = OPTAB->get_format(OPTAB->search_Ele(MNEM));	

	// insert label into the symbol table
	if (LABEL.length() > 0 && this->SYMTAB->search_Ele(LABEL) == -1 && this->doCodeGeneration(MNEM) == true)
	{
		this->SYMTAB->insert(LABEL, LOC);
	}

	
	if (this->doCodeGeneration(MNEM))
	{
		printf("%s: 0x%02X\t %s\t%s\t%s\n",__func__,  LOC, LABEL.c_str(), MNEM.c_str(), OPERAND.c_str());
	}
	else
	{
		printf("%s: \t %10s\t%s\t%s\n",__func__,  LABEL.c_str(), MNEM.c_str(), OPERAND.c_str());
	}

	if (MNEM[0] == '+')
	{
		// instruction is in extended format, add one to LOC so data alignment is maintained when it is incremented later.
		LOC += 1; 
	}

	if (format == 2)
	{
		LOC -= 1;
	}

}

/**
 * The second pass of the assembler uses the now populated SYMTAB to begin generating object code
 */
void Assembler::assem_pass2(int &LOC, std::string LABEL, std::string MNEM, std::string OPERAND)
{

	int opcode;
	int format;
	int r1;
	int r2;

	// When MNEM has a leading '+', it is in extended format
	// Parse the mnemonic beginning at the next index
	if (isExtended(MNEM))
	{
		opcode = OPTAB->search_Ele( MNEM.substr(1, MNEM.length() - 1));
		format = 4;
		this->reg.pc_inc(1);
	}
	else
	{
		opcode = OPTAB->search_Ele(MNEM);
		format = OPTAB->get_format(opcode);
	}

	if (format == 2)
	{
		this->reg.pc(LOC + 2);
		r1 = 0x0;
		r2 = this->calcInstructionAddress_Format2(OPERAND);
	}
	else if (format > 2) // format is 3 or 4
	{
		r1 = this->getInstructionMode(MNEM, OPERAND);
		r2 = this->calcInstructionAddress_Format3(r1, OPERAND);
	}

	//printf("%s: %s 0x%02X, mode: 0x%02X, addr:0x%03X\n",
	//		__func__, MNEM.c_str(), opcode, mode, addr);

	// if opcode is >= 0, then the opcode was found in the OPTAB
	if (opcode >= 0x0)
	{	

		if (MNEM == "LDB")
		{
			if(OPERAND[0] == '#')
			{	
				this->reg.base(SYMTAB->search_Ele(OPERAND.substr(1, OPERAND.length() - 1)));
			}
			else
			{
				this->reg.base(SYMTAB->search_Ele(OPERAND));
			}
			//printf ("\nBASE: 0x%02X\n", Assembler::reg.base());
		}

		instruction* i = new instruction(opcode, format, r1, r2);

		// Print differently depending on instruction format
		switch (format)
		{
			case 1:
				printf("%s: 0x%02X\t %-10s\t%s\t%-10s\t0x%06X\t0x%02X\n", __func__, LOC, LABEL.c_str(), MNEM.c_str(), OPERAND.c_str(),
						(i->get()) ? i->get() : 0,  this->reg.pc()
				      );
		
				break;
			case 2:
				printf("%s: 0x%02X\t %-10s\t%s\t%-10s\t0x%04X\t%-8s0x%02X\n", __func__, LOC, LABEL.c_str(), MNEM.c_str(), OPERAND.c_str(),
						(i->get()) ? i->get() : 0, " ", this->reg.pc()
				      );
			
				break;
			case 3: // format 3
			case 4: // format 4
			default:
				printf("%s: 0x%02X\t %-10s\t%s\t%-10s\t0x%06X\t0x%02X\n", __func__, LOC, LABEL.c_str(), MNEM.c_str(), OPERAND.c_str(),
						(i->get()) ? i->get() : 0, this->reg.pc()
				      );
				break;
		}
	}
	else if (MNEM == "BYTE")
	{
		instruction* i = new instruction(0x0, 0x0, 0x0, tokenizer->get_byte(OPERAND));
		
		printf("%s: 0x%02X\t %-10s\t%s\t%-10s\t0x%06X%5s\t0x%02X\n", __func__, LOC, LABEL.c_str(), MNEM.c_str(), OPERAND.c_str(),
						 (i->get()) ? i->get() : 0, " ", this->reg.pc()
		);
	}
	else
	{
		if (doCodeGeneration(MNEM))
		{
			printf("%s: 0x%02X\t %-10s\t%s\t%s\n",__func__,  LOC, LABEL.c_str(), MNEM.c_str(), OPERAND.c_str());
		}
		else
		{
			printf("%s:\t\t %-10s\t%s\t%s\n",__func__, LABEL.c_str(), MNEM.c_str(), OPERAND.c_str());
		}
	}
	

	// Modify location by adding or subtracting one byte to preserve data alignment in the case of format 2 or format 4 instructions
	switch(format)
	{
		case 2:
			// if format 2, instruction is 2 bytes
			LOC -= 1;
			break;
		case 4:
			// if format 4, instruction is 4 bytes
			LOC += 1;
			break;
		default:
			break;
	}
}

int Assembler::getInstructionMode(std::string mnem, std::string operand)
{
	// ni xbpe
	// 00 0000

	int mode = 0x0;

	// extended format instruction
	if (mnem[0] == '+')
	{
		mode = mode | 0x01;
		//printf("%s: '+' found in %s. mode: 0x%x\n", __func__, mnem.c_str(), mode);
	}
	std::size_t c = operand.find(',');

	if (c != std::string::npos)
	{
		// length from first index to comma is >1
		// which implies it is not a register
		if (operand.substr(0, c).length() > 1)
		{
			if (operand[c+1] == 'X')
				mode = mode | 0x08;
		}
	}

	switch(operand[0])
	{
		case '#': // immediate addressing
			//printf("%s: immediate addressing\n", __func__);
			mode = mode | 0x10;
			break;

		case '@': // indirect addressing
			mode = mode | 0x20;
			break;	
		default: // assume simple addressing
			mode = mode | 0x30;
			break;
	}
	
	return mode;
}

int Assembler::calcInstructionAddress_Format2(std::string operand)
{
	int r1 = 0x0;
	int r2 = 0x0;

	std::size_t c = operand.find(',');

	if (c != std::string::npos)
	{
		
		char a = operand.substr(0, c).c_str()[0];
		char b = operand.substr(c+1, operand.length() - 1).c_str()[0];
		
		switch (a)
		{
			case 'A':
				r1 = 0;
				break;
			case 'X':
				r1 = 1;
				break;
			case 'L':
				r1 = 2;
				break;
			case 'B':
				r1 = 3;
				break;
			case 'S':
				r1 = 4;
				break;
			case 'T':
				r1 = 5;
				break;
			case 'F':
				r1 = 6;
				break;
			default:
				break;

		}
		
		switch (b)
		{
			case 'A':
				r2 = 0;
				break;
			case 'X':
				r2 = 1;
				break;
			case 'L':
				r2 = 2;
				break;
			case 'B':
				r2 = 3;
				break;
			case 'S':
				r2 = 4;
				break;
			case 'T':
				r2 = 5;
				break;
			case 'F':
				r2 = 6;
				break;
			default:
				break;

		}
	}
	else
	{
		char a = operand.substr(0, c).c_str()[0];
		char b = 0x0;

		switch (a)
		{
			case 'A':
				r1 = 0;
				break;
			case 'X':
				r1 = 1;
				break;
			case 'L':
				r1 = 2;
				break;
			case 'B':
				r1 = 3;
				break;
			case 'S':
				r1 = 4;
				break;
			case 'T':
				r1 = 5;
				break;
			case 'F':
				r1 = 6;
				break;
			default:
				break;

		}
	}

	return (r1 << 4) | r2;
}

int Assembler::calcInstructionAddress_Format3(int &mode, std::string operand)
{
	// a represents the first byte in mode
	// b represents the second byte
	//
	// for example, given a format 3/4 instruction
	// 0000 aa|aa bbbb|0000 0000 0000
	
	int a = mode & 0x30; 
	//int b = mode & 0xF;

	int x = (mode & 0x08) >> 3;
	int b = (mode & 0x04) >> 2;
	int p = (mode & 0x02) >> 1;
	int e = mode & 0x01;

	int address = 0x0;

	std::string s = "";
	std::string sym = "";
	std::stringstream ss;
	std::size_t c = 0;

	switch (a)
	{
		case 0x10: // immediate addressing
			s = operand.substr(1, operand.length()-1);
			//printf("%s: %s\n", __func__, s.c_str());
			
			address = SYMTAB->search_Ele(s);

			if (address < 0)
			{
				// address is not in symtab, so it must be an integer

				ss << s;
			
				ss >> address;
			}
			else
			{
				address = calcRelativeAddress(mode, address);
			}
			//printf("%s: %d\n", __func__, address);

			ss.clear();

			break;

		case 0x20: // indirect addressing
			s = operand.substr(1, operand.length() - 1);
			
			address = calcRelativeAddress(mode, SYMTAB->search_Ele(s));

		//	if (address == -1)
		//	{
		//		address = 0x0;
		//	}	

			break;
			
		case 0x30: // simple addressing: n = 1, i = 1
			
			if (x == 1)
			{
				// indexed addressing
				c = operand.find(',');
				if (c != std::string::npos)
				{
					sym = operand.substr(0, c);

					//printf("%s:%s 0x%02X\n", __func__, sym.c_str(), SYMTAB->search_Ele(sym));

					address = calcRelativeAddress(mode, SYMTAB->search_Ele(sym));

					mode = mode | 0x30;

					//printf ("%s: addr 0x%02X\n", __func__, address);
				}

			}
			else
			{

				address = calcRelativeAddress(mode, SYMTAB->search_Ele(operand));

				
					
				// determine whether to use PC relative or base relative
				
		//		int disp_base = address - this->reg.base();
		//		int disp_pc   = address - this->reg.pc();

		//		//printf("Address: 0x%06x | PC: 0x%02X | disp_base: 0x%02X | disp_pc: 0x%02X\n", address, Assembler::reg.pc(), disp_base, disp_pc);

		//		if (disp_pc >= -2048 && disp_pc <= 2048)
		//		{
	
		//			// bitwise AND the disp to chop off leading 0xFFFFF000 due to negative result
		//			address = disp_pc & 0xFFF;
		//			//address = disp_pc;
		//			
		//			//printf("addr: 0x%02X\n", address);

		//			//printf("PC_RELA_ADDR: 0x%02X\n", address);

		//			// xbpe
		//			mode = mode | 0x2; 
		//		}
		//		else if (disp_base >= 0 && disp_base <= 4096)
		//		{
		//			address = disp_base;

		//			mode = mode | 0x4;
		//		}		
			}
			
			break;

		default:
			break;
	}

	if (address == -1)
	{
		address = 0x0;
	}

	return address;
}

/**
 * Calculate PC or BASE offset for given address
 */
int Assembler::calcRelativeAddress(int &mode, int address)
{
	// determine whether to use PC relative or base relative
				
	int disp_base = address - this->reg.base();
	int disp_pc   = address - this->reg.pc();

	//printf("Address: 0x%06x | PC: 0x%02X | disp_base: 0x%02X | disp_pc: 0x%02X\n", address, Assembler::reg.pc(), disp_base, disp_pc);

	if (disp_pc >= -2048 && disp_pc <= 2048)
	{

		// bitwise AND the disp to chop off leading 0xFFFFF000 due to negative result
		address = disp_pc & 0xFFF;
		//address = disp_pc;
		
		//printf("addr: 0x%02X\n", address);

		//printf("PC_RELA_ADDR: 0x%02X\n", address);

		// xbpe
		mode = mode | 0x2; 
	}
	else if (disp_base >= 0 && disp_base <= 4096)
	{
		address = disp_base;

		mode = mode | 0x4;
	}

	return address;
}

int Assembler::getAddressFromString(std::string operand)
{
	int addr = 0x0;
	std::string s;

	switch (operand[0])
	{
		case '#':
			s = operand.substr(1, operand.length() - 1);

			addr = this->SYMTAB->search_Ele(s);

			if (addr < 0)
			{
				addr = atoi(operand.c_str());
			}

			break;
		case '@':
			s = operand.substr(1, operand.length() - 1);

			addr = this->SYMTAB->search_Ele(s);

			if (addr < 0)
			{
				addr = atoi(operand.c_str());
			}

			break;
		default:
			addr = atoi(operand.c_str());
			break;
	}

	return addr;
}
