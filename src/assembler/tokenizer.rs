// tokenizer.rs

use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

pub struct Tokenizer;

impl Tokenizer {
    pub fn read(&self, name: String) {
        let p = Path::new(&name);
        println!("opening {}...", p.display());
        let f = match File::open(&p) {
            Err(why) => panic!("couldnt open {}: {}", p.display(), why),
            Ok(f) => f,
        };

        // from https://doc.rust-lang.org/rust-by-example/std_misc/file/read_lines.html

        let lines = io::BufReader::new(f).lines();
        for line in lines {
            match line {
                Err(why) => panic!("error reading file: {}: {}", p.display(), why),
                Ok(line) => println!("{}", line),
            };
            //println!("{:?}", line);
        }
    }

    pub fn tokenize(&self) {
        unimplemented!()
    }
}

#[test]
fn test_read() {
    let t = Tokenizer {};
    t.read(String::from("test.sic"));
}

// #[cfg(test)]
// mod tests {
//     use super::*;
//
//     #[test]
//     fn it_works() {
//         assert_eq!(1 + 1, 2);
//     }
//
//     #[test]
//     fn test_read() {
//         let t = Tokenizer;
//         t.read("./test.sic");
//     }
// }
