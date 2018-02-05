/*
  Carlos Villagomez & Andrew Zenoni
  CPSC 326 - Organization of Programming Languages
  Assignment 2
  v 1.0.0
  January 29, 2018
  
  Defines the implementation of a MyPL token for a Lexeme
*/

#include "Token.h"

// You shouldn't need to modify this file for HW2

/* Provide an output operator allowing Tokens to be outputted to std::cout
 or to any other ostream using << */
std::ostream& operator<<(std::ostream &out, Token token) {
    out << toString(token);
    return out;
}

/* Use the x-macro pattern to create a giant switch statement to return a
 string representations of the passed-in token */
std::string toString(Token token) {
    switch(token) {
#define x(ident) case Token::ident: \
return #ident; \
break;
#include "tokens-inc.h"
#undef x
    }
}
