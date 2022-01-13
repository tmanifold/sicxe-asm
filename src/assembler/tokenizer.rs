// tokenizer.rs

pub struct Tokenizer;

impl Tokenizer {
    // split the given line into an array of tokens
    pub fn tokenize<'a>(&self, line: &'a str) -> Vec<&'a str> {
        // strip comments
        let ln = self.strip_comments(line);

        // split into tokens and return
        ln.split_whitespace().collect()
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
