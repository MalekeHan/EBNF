# EBNF Language Project


This project uses designated EBNF rules to create a mini programming language that can perform arithmetic, math, and bitwise operations on given expressions

Scan Symbol Productions
  tokenlist  = (token)*
  token      = intlit | hexlit | binlit | symbol
  symbol     = '+' | '-' | '*' | '/' | '>>' | '<<' | '~' | '&' | '|' | '^'
  intlit     = digit (digit)*
  hexlit     = '0x' | hexdigit (hexdigit)*
  binlit     = '0b' ['0', '1'] (['0', '1'])*
  hexdigit   = 'a' | ... | 'f' | 'A' | ... | 'F' | digit
  digit      = '0' | ... | '9'
 --SYMBOLS TO BE IGNORED--
  whitespace = ' ' | '\t' (' ' | '\t')*

EBNF Parser Productions
  program    = expression EOT
  expression = operand (operator operand)*
  operand    = intlit
            | hexlit
            | binlit
            | '-' operand
            | '~' operand
            | '(' expression ')'
            
TEST OUTPUTS
  $ ./project04 -e "10 + 1"
    11
  $ ./project04 -e "10 + 1" -b 16
    0x0000000B
  $ ./project04 -e "0x0A" -b 10
    10
  $ ./project04 -e "0b1010 | 0b0101" -b 16
    0x0000000F
  $ ./project04 -b 10 -e "(2 * (0b1111 & 0b1010))"
    20
  $ ./project04 -b 2 -e "(0xF << 0x4) + 1"
    0b00000000000000000000000011110001
