// assembler.rs

mod instruction;
mod sicxe_op;
mod tokenizer;

use std::collections::HashMap;

const WORD_SIZE: u8 = 3;

enum Directives {
    START,
    END,
    BYTE,
    WORD,
    RESB,
    RESW,
    BASE,
}

// Registers:
// 10 x 24 bit registers
//
//   MNEMONIC	  Register #	  Comment/note
//   A	             0       	  Accumulator
//   X	             1       	  Index register
//   L	             2       	  Linkage register (JSUB/RSUB)
//   B (SIC/XE)	     3	          Base register
//   S (SIC/XE)      4	          General register
//   T (SIC/XE)	     5	          General register
//   F (SIC/XE)	     6	          Floating Point Accumulator (48 bits)
//
//   PC	             8	          Program Counter (PC)
//   SW	             9	          Status Word (includes Condition Code, CC)

pub struct Assembler {
    reg_a: u32,
    reg_x: u32,
    reg_l: u32,
    reg_b: u32,
    reg_s: u32,
    reg_t: u32,
    reg_f: u32,
    reg_pc: u32,
    reg_sw: u32,
    tokenizer: tokenizer::Tokenizer,
    optab: HashMap<String, u32>,
    symtab: HashMap<String, u32>,
    dtab: HashMap<String, u8>,
}

impl Assembler {
    pub fn new() -> Assembler {
        Assembler {
            reg_a: 0x0,
            reg_x: 0x0,
            reg_l: 0x0,
            reg_b: 0x0,
            reg_s: 0x0,
            reg_t: 0x0,
            reg_f: 0x0,
            reg_pc: 0x0,
            reg_sw: 0x0,
            tokenizer: tokenizer::Tokenizer {},
            optab: HashMap::new(),
            symtab: HashMap::new(),
            dtab: HashMap::new(),
        }
    }

    pub fn assemble(&self, file: String) {
        self.tokenizer.read(file);
    }
}
