#ifndef _OPTAB_H_
#define _OPTAB_H_
#include "hashmap.h"

#define NUM_OPS 59

class sicxe_op
{
	private:
		int opcode;
		int format; // 1, 2, or 3. Format 3 instructions are assumed to be able to be extended to format 4.
	public:
		sicxe_op(int op = 0, int fmt = 1)
		{
			opcode = op;
			format = fmt;
		}

		int get_op()
		{
			return opcode;
		}

		int get_format()
		{
			return format;
		}
};

class optab : public hashMap
{
	private:
		sicxe_op** opcodes;
	public:
		optab();
		~optab();

		int get_format(int);
};
#endif //_OPTAB_H_
