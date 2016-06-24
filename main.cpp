#include <iostream>
#include "ast.h"
#include "st.h"

extern AST::Block* programRoot; //set on Bison file
extern int yyparse();
extern int yydebug;

int main(int argc, char **argv)
{
    //yydebug = 1;              //remove comment to have verbose debug messages
    yyparse();                  //parses whole data
    programRoot->printTree();   //prints the ASTs
    return 0;
}
