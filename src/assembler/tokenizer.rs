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
                Ok(line) => self.tokenize(&line),
            };
            //println!("{:?}", line);
        }
    }

    pub fn tokenize(&self, line: &str) {
        // strip comments
        let ln = self.strip_comments(line);
        // split into tokens
        for token in ln.split_whitespace() {
            println!("tokens= {}", token);
        }
    }

    // looks for a dot character and deletes everything following on the line.
    pub fn strip_comments<'a>(&self, line: &'a str) -> &'a str {
        match line.find('.') {
            None => line,
            Some(start) => match line.get(0..start) {
                Some(v) => v,
                None => panic!("Error getting substr from {}", line),
            },
        }
    }
}

#[test]
fn test_read() {
    let t = Tokenizer {};
    t.read(String::from("test.sic"));
}

#[test]
fn test_strip_comments() {
    let s = "NOOP .COMMENT";
    let t = Tokenizer {};
    assert_eq!(t.strip_comments(&s), "NOOP ");
}

#[test]
fn test_tokenize() {
    let t = Tokenizer {};
    let line = "TEST	START	1000";
    let tokens = t.tokenize(&line);
    assert_eq!(tokens, ["TEST", "START", "1000"]);
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
