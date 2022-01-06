# sicxe

**TL;DR**
Phoneticizing things is difficult. I'm arbitrarily deciding that SIC/XE will be pronounce as "SICKSEE."
Or something close enough. We can abbreviate SIC/XE as 6e. <-- that will probably be important in later things. But right now I don't care, and neither should you.
It's 6e. Not quite like DnD, but *maybe*. 6e is intented to be a Rust implementation of an assembler (and maybe (probably) eventually interperter/(compiler? targeting [wasm](https://webassembly.org/)? that would be dope)) for [SIC/XE Assembly language.](https://en.wikipedia.org/wiki/Simplified_Instructional_Computer#Emulating_the_SIC_System)

## Intro
Once upon a time in university, I was tasked with implementing an assembler for [SIC/XE](https://en.wikipedia.org/wiki/Simplified_Instructional_Computer).
Now I'm bored and I actually wanted to finish this project. After some research, Rust seemed like the obvious choice for no reason other than I arbitrarily decided it
seemed close enough to C for me to be comfortable, yet new enough to offer modern and unparalleled safety features while also forgoing some stupid garbage collector. (*I hate trying to work around the GC*).
