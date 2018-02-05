/*
  Carlos Villagomez & Andrew Zenoni
  CPSC 326 - Organization of Programming Languages
  Assignment 2
  v 1.0.0
  January 29, 2018
  
  This file defines a Lexeme object
*/

#include "Lexeme.h"

// You shouldn't need to modify this file for HW2

std::ostream& operator<<(std::ostream& out, const Lexeme& lex) {
    out << lex.token << " '" << lex.text << "' " << lex.line << ":" << lex.col;
    return out;
}

std::string toString(const Lexeme &lex) {
    std::ostringstream oss;
    oss << lex;
    return oss.str();
}
