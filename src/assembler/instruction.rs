// instruction.rs

// implements sic-xe instruction
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

pub struct Instruction {
    pub op: u32,
    pub fmt: u32,
    pub mode: u32,
    pub addr: u32,
    pub instr: u32,
}

impl Instruction {}
