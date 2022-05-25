# EBNF Language Project


This project uses designated EBNF rules to create a mini programming language that can perform arithmetic, math, and bitwise operations on given expressions

**Scan Symbol Productions** <br />
  tokenlist  = (token)* <br />
  - token      = intlit | hexlit | binlit | symbol <br />
  - symbol     = '+' | '-' | '*' | '/' | '>>' | '<<' | '~' | '&' | '|' | '^' <br />
  - intlit     = digit (digit)* <br />
  - hexlit     = '0x' | hexdigit (hexdigit)* <br />
  - binlit     = '0b' ['0', '1'] (['0', '1'])* <br />
  - hexdigit   = 'a' | ... | 'f' | 'A' | ... | 'F' | digit <br />
  - digit      = '0' | ... | '9' <br />
SYMBOLS TO BE IGNORED
  - whitespace = ' ' | '\t' (' ' | '\t')*  <br />

**EBNF Parser Productions** <br />
 - program    = expression EOT <br />
 - expression = operand (operator operand)* <br />
 - operand    = intlit
            | hexlit
            | binlit
            | '-' operand
            | '~' operand
            | '(' expression ')'
            
**TEST OUTPUTS** <br />
  $ ./project04 -e "10 + 1" <br />
  -  11 <br />
  $ ./project04 -e "10 + 1" -b 16 <br />
  -  0x0000000B <br />
  $ ./project04 -e "0x0A" -b 10 <br />
  -  10 <br />
  $ ./project04 -e "0b1010 | 0b0101" -b 16 <br />
  -  0x0000000F <br />
  $ ./project04 -b 10 -e "(2 * (0b1111 & 0b1010))" <br />
  -  20 <br />
  $ ./project04 -b 2 -e "(0xF << 0x4) + 1" <br />
  - 0b00000000000000000000000011110001 <br />
