
// Tokenizer.cpp

#include "tokenizer.h"

Tokenizer::Tokenizer()
{
	
}

Tokenizer::~Tokenizer()
{
	delete in_file;
}

/**
 * Open the specified <file> for reading, then tokenize line by line
 * until EOF
 */
void Tokenizer::read(char* file)
{

	in_file = new std::ifstream(file);

	if (in_file->is_open())
	{
		while(in_file->good())
		{
			std::string line;

			std::getline(*(in_file), line);
			
			this->tokenize(line);
		}

		in_file->close();
	}
	else
	{
		fprintf(stderr, "STDERR: Could not open file \'%s\'\n", file);
	}
}

/**
 * Split the string specified by <line> into tokens and insert
 * them into the tokens[] array, which is then returned.
 */
std::string* Tokenizer::tokenize(std::string line)
{
	this->strip_comments(line);

	std::stringstream ss;
	
	static std::string tokens[3]; 
	int column = 0;

	ss << line;

	for (int i = 0; i < 3; i++)
	{
		tokens[i] = "";
	}


	while (ss.good() && column < 3)
	{	
		ss >> tokens[column++];
	}

	return tokens;
}

/**
 * Find and remove comments from the specified line.
 * Also removes newline (\n) and carriage-return (\r) characters
 */
void Tokenizer::strip_comments(std::string &line)
{
	std::size_t c = line.find('.');

	if (c != std::string::npos)
	{
		// a comment is found, erase from the period to the end of the line
		line.erase(c, line.length());
	}

	c = line.find('\n');
	
	if (c != std::string::npos)
	{
		line.erase(c);
	}

	c = line.find('\r');
	
	if (c != std::string::npos)
	{
		line.erase(c);
	}
}

unsigned int Tokenizer::get_byte(std::string BYTE)
{	
	// 012345
	// C'EOF' => 454F46
	
	unsigned int byte_val = 0x0;

	if (BYTE.length() - 1 > 0)
	{
		std::string byte_string = BYTE.substr(2, BYTE.length() - 1);
		//printf("byte_string.length(): %d\n", byte_string.length() - 1);


		for (int i = 0; i < byte_string.length() - 1; i++)
		{
			switch (BYTE[0])
			{
				case 'X':
					if (byte_string[i] >= 0x41 && byte_string[i] <= 0x46)
					{
						// the char is A-F

						switch(byte_string[i])
						{
							case 'A':
								byte_val |= 0xA;
								break;
							case 'B':
								byte_val |= 0xB;
								break;
							case 'C':
								byte_val |= 0xC;
								break;
							case 'D':
								byte_val |= 0xD;
								break;
							case 'E':
								byte_val |= 0xE;
								break;
							case 'F':
								byte_val |= 0xF;
								break;
							default:
								break;
								
						}
					}
					else if (byte_string[i] >= 0x30 && byte_string[i] <= 0x39)
					{
						// the char is 0-9

						byte_val |= byte_string[i] - 0x30;
					}

					if (i < byte_string.length() - 2)
						byte_val = byte_val << 4;
					
					break;

				case 'C':
					byte_val |= byte_string[i];

					if (i < byte_string.length() - 2)
						byte_val = byte_val << 8;

					break;
				default:
					break;
			}
		}

		//printf("tokenizer.%s: 0x%X\n", __func__, byte_val);
	}
	return byte_val;
}

/*
int Tokenizer::get_mode(std::string opcode, std::string operand)
{
	int mode = 0x0;

	if (isExtended(opcode))
	{
		mode = mode | 0x1;
	}

	mode = mode | proc_operand(operand);

	return mode;
}


/**
 * Return true if op is extended format
 * /
bool Tokenizer::isExtended(std::string op)
{
	return (op[0] == '+');
}

/**
 * Process the operand for its indicated addressing mode
 * i.e., immediate, index relative, etc
 * /
int Tokenizer::proc_operand(std::string operand)
{

	int mode = 0x0;

	std::size_t c = operand.find(',');

	if (c != std::string::npos)
	{
		// ni xbpe
		// 00 0000
		if (operand[c+1] == 'X')
			mode = mode | 0x08;
	}
	else
	{
		switch (operand[0])
		{
			case '#': // immediate addressing
				mode = mode | 0x10;
				break;

			case '@': // indirect addressing
				mode = mode | 0x20;
				break;

			case '=': // operand is a literal
				break;
			default:
				// operand has no special addressing mode
				// assume simple addressing
				
				mode = mode | 0x30;

				break;
		}
	}

	return mode;
}
*/
