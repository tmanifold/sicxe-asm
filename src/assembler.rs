// assembler.rs

mod instruction;

use std::collections::HashMap;

const WORD_SIZE: usize = 3;

enum Directives {
    START,
    END,
    BYTE,
    WORD,
    RESB,
    RESW,
    BASE,
}

struct Register {

}

struct Assembler {
    directive: Directives,
    A: Register,
    X: Register,
    L: Register,
    B: Register,
    S: Register,
    T: Register,
    F: Register,
    PC: Register,
    SW: Register,
    tokenizer: Tokenizer,
    OPTAB: Optab,
    SYMTAB: HashMap,
    DTAB: HashMap,
    file_path: std::path::Path,
    file: std::fs::File,
}
