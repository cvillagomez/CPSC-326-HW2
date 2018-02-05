/*
  Carlos Villagomez & Andrew Zenoni
  CPSC 326 - Organization of Programming Languages
  Assignment 2
  v 1.0.0
  January 29, 2018
  
  This file Lexes through the inputted code, and returns lexemes for the MyPL programming language program
*/

#include <sstream>

#include "Lexer.h"
#include <iostream>
#include <string.h>
using namespace std;

Lexer::Lexer(std::istream &initIn): in(initIn) {
    
    // If we are given an invalid input stream, throw an exception
    if (!in) {
        throw LexerException("Invalid input stream passed to Lexer");
    }
}

Lexeme Lexer::next() {
    eatWhitespace();
    char tmp = peek();
    int startLine = lineNum;
    int startCol = colNum;
    if (tmp == eof()) {
        return Lexeme(Token::EOS, "", lineNum, colNum);
    // following else if checks if string
    } else if ((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z')) {
        string name = "";
      while ((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z')) {
        name += read();
        tmp = peek();
      }
      if (name.compare("readint") == 0) { 
        return Lexeme(Token::READINT, name, startLine, startCol);
      } else if (name.compare("if") == 0) {
        return Lexeme(Token::IF, name, startLine, startCol);
      } else if (name.compare("elseif") == 0) {
        return Lexeme(Token::ELSEIF, name, startLine, startCol);
      } else if (name.compare("else") == 0) {
        return Lexeme(Token::ELSE, name, startLine, startCol);
      } else if (name.compare("and") == 0) {
        return Lexeme(Token::AND, name, startLine, startCol);
      } else if (name.compare("or") == 0) {
        return Lexeme(Token::OR, name, startLine, startCol);
      } else if (name.compare("not") == 0) {
        return Lexeme(Token::NOT, name, startLine, startCol);
      } else if (name.compare("while") == 0) {
        return Lexeme(Token::WHILE, name, startLine, startCol);
      } else if (name.compare("do") == 0) {
        return Lexeme(Token::DO, name, startLine, startCol);
      } else if (name.compare("end") == 0) {
        return Lexeme(Token::END, name, startLine, startCol);
      } else if (name.compare("print") == 0) {
        return Lexeme(Token::PRINT, name, startLine, startCol);
      } else if (name.compare("println") == 0) {
        return Lexeme(Token::PRINTLN, name, startLine, startCol);
      } else if (name.compare("readstr") == 0) {
        return Lexeme(Token::READSTR, name, startLine, startCol);
      } else if (name.compare("then") == 0) {
        return Lexeme(Token::THEN, name, startLine, startCol);
      } else if (name.compare("true") == 0 || name.compare("false") == 0) {
        return Lexeme(Token::BOOL, name, startLine, startCol);
      } else {
        return Lexeme(Token::ID, name, startLine, startCol);
      }
    // checks single characters or operators
    } else if (tmp == '+') {
        return makeSingleCharLexeme(Token::PLUS);
    } else if (tmp == '>') {
        read();
        if (peek() == '=') {
            read();
            return Lexeme(Token::GREATER_THAN_EQUAL, ">=", startLine, startCol);
        } else {
            return Lexeme(Token::GREATER_THAN, ">", startLine, startCol);
        }
    } else if (tmp == '<') {
        read();
        if (peek() == '=') {
            read();
            return Lexeme(Token::LESS_THAN_EQUAL, "<=", startLine, startCol);
        } else {
            return Lexeme(Token::LESS_THAN, "<", startLine, startCol);
        }
    } else if (tmp == '-') {
      //checks for just a minus sign, not neg number
      if(peek() == ' ') {
        return makeSingleCharLexeme(Token::MINUS);
      } else {
        string negNumber = "";
        negNumber += read();
        while (peek() >= '0' && peek() <= '9') {
            negNumber += read();
        }
        return Lexeme(Token::INT, negNumber, startLine, startCol);
      } 
    } else if (tmp == '*') {
      return makeSingleCharLexeme(Token::MULTIPLY);
    } else if (tmp == '/') {
      return makeSingleCharLexeme(Token::DIVIDE);
    } else if (tmp == '%') {
      return makeSingleCharLexeme(Token::MODULUS);
    } else if (tmp == '(') {
      return makeSingleCharLexeme(Token::LPAREN);
    } else if (tmp == ')') {
      return makeSingleCharLexeme(Token::RPAREN);
    } else if (tmp == '[') {
      return makeSingleCharLexeme(Token::LBRACKET);
    } else if (tmp == ']') {
      return makeSingleCharLexeme(Token::RBRACKET);
    } else if (tmp == ',') {
      return makeSingleCharLexeme(Token::COMMA);
    // checks for a string token
    } else if (tmp == '"') {
      read();
      string stringName = "";
      while(peek() != '"') {
        stringName += read();
      }
      read();
      return Lexeme(Token::STRING, stringName, startLine, startCol);
    // checks for ASCII integer values
    } else if (tmp >= '0' && tmp <= '9') {
      string posNumber = "";
      while(peek() >= '0' && peek() <= '9') {
                posNumber += read();    
      }
      return Lexeme(Token::INT, posNumber, startLine, startCol);
    } else if (tmp == '!') {
      read();
      if (peek() == '=') {
        read();
        return Lexeme(Token::NOT_EQUAL, "!=", startLine, startCol);
      } else {
        //just a ! token, not !=
        return Lexeme(Token::NOT, "!", startLine, startCol);
      }
    } else if (tmp == ';') {
      return makeSingleCharLexeme(Token::SEMICOLON);
    } else if (tmp == '=') {
      // compare if assignment operator or == check
      read();
      if (peek() == '=') {
        read();
        return Lexeme(Token::EQUAL, "==", startLine, startCol);
      } else {
        return Lexeme(Token::ASSIGN, "=", startLine, startCol);
      }
    } else {
        // You will not need to change the contents of this "else"
        ostringstream oss;
        oss << "Unexpected symbol: '" << peek() << "'";
        throw LexerException(debugMessage(oss.str()));
    }
    // Yes, you might get a warning about control reaching the end of a
    // non-void function.  Make sure you are returning a Lexeme from each
    // block (the code as distributed has one case with just a TODO).
    //
    // If this is an error in your compiler, you can put in a call to
    // abort() which will stop the program running if control reaches here.
}

bool Lexer::atEOF() {
    // You shouldn't need to modify this function
    return peek() == eof();
}

char Lexer::peek() {
    // You shouldn't need to modify this function
    return in.peek();
}

char Lexer::read() {
    // You shouldn't need to modify this function
    if (in.peek() == '\n') {
        colNum = 1;
        lineNum += 1;
    } else {
        colNum += 1;
    }
    return in.get();
}

void Lexer::eatWhitespace() {
    // Checks what next character is
    char tmp = peek();
    // check for newline, space, tab, or comment
    while (tmp == ' ' || tmp == '\t' || tmp == '\n' || tmp == '#') {
      if (tmp == '#') {
        while(peek() != '\n') {
            read();
        }
      }
      read();
      tmp = peek();
    }
}

char Lexer::eof() {
    // You shouldn't need to modify this function
    return std::istream::traits_type::eof();
}

Lexeme Lexer::makeSingleCharLexeme(Token token) {
    // You shouldn't need to modify this function
    string str(1, read());
    return Lexeme(token, str, lineNum, colNum);
}

std::string Lexer::debugMessage(std::string msg) {
    // You shouldn't need to modify this function
    ostringstream oss;
    oss << msg << " " << lineNum << ":" << colNum;
    return oss.str();
}
