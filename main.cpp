/*
  Carlos Villagomez & Andrew Zenoni
  CPSC 326 - Organization of Programming Languages
  Assignment 2
  v 1.0.0
  January 29, 2018
  
  Uses MyPL program as input into Lexer and outputs all the Lexemes
*/

#include <iostream>
#include <string>

#include "Token.h"
#include "Lexeme.h"
#include "Lexer.h"

using namespace std;

// I would suggest using this file to test out multiple programs and make sure
// your lexer works the way that it should.

int main(int argc, const char * argv[]) {
    // This is a multiline string.  By saying R"code(, we are saying that
    // the string continues until the characters )code" are encountered.
    // You can put your MyPL code between the starting line and the ending
    // line.
    string code = R"code(
x = readint("Enter an int: ");
y = readint("Enter an int: ");
if x > y then
    println("The first int was bigger than the second!");
elseif y > x then
    println("The second int was bigger than the first!");
else
    println("You entered the same value twice!");
end
    )code";
    
    // Create an istringstream based on the contents of the string "code".
    // We can then use 'ins' just as we would use cin or a file we opened
    // with ifstream.
    istringstream ins(code);
    
    // Try-catch, so that if an error occurs, we are able to output the error
    // message
    try {
        // Pass the istream to the lexer to have it do its thing.
        Lexer lexer(ins);
        while (!lexer.atEOF()) {
            Lexeme current = lexer.next();
            cout << current << endl;
        }
    } catch (MyPLException &e) { // If an error occurs,
        // output the error message
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}
