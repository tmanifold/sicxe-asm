// instruction.rs

// implements sic-xe instruction

// ref https://rust-lang-nursery.github.io/rust-cookbook/data_structures/bitfield.html

// The following parameters are as follows for the various instruction formats:
// Format 1:
//   op: the given opcode
//   format: unused
//   r1: unused
//   r2: unused
//
// Format 2:
//   op: the given opcode
//   format: 2
//   r1: the first operand
//   r2: the second operand
//
// Format 3/4:
//   op: the given opcode:
//   format: 3 or 4
//   r1: addressing mode (nixbpe)
//   r2: target address

// #[derive(Debug)]
// pub struct Instruction(u32);
//
// impl Instruction {
//     pub fn new() -> Instruction {
//         Instruction(0x0)
//     }
// }
//
// impl PartialEq {
//
// }
//
// #[test]
// fn test_instruction() {
//     assert_eq!(Instruction(0x0), Instruction::new());
// }

trait Instruction {
    fn sicxe(&self) -> Self;
}

impl Instruction for u32 {
    fn sicxe(&self) -> u32 {
        *self
    }
}

#[test]
fn test_instruction() {
    let a = 0xA0.sicxe();
}
