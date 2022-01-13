#![allow(dead_code)]

mod assembler;

fn main() {
    println!("SIC/XE Assembler");
    let hex = 0xFF;
    println!("{}", hex);

    let asm = assembler::Assembler::new();
    asm.assemble("./test.sic");
}
