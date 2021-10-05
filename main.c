#include <stdio.h>

#define INTEGER_TYPE 1
#define OPERATOR_TYPE 2
#define FLOAT_TYPE 3
#define DECIMAL_TYPE 4

const char* line = "5*2+6*2*8+9";
int pointer = 0;

typedef  struct{
    int integer;
    char op;
    float flt;
    int type;
} Token;

void gettoken(Token* token){
    if (line[pointer] >= '0' && line[pointer] <= '9'){
        token->type = INTEGER_TYPE;
        token->integer = line[pointer] - '0';
    } else if (line[pointer] == '.') {
        token->type = DECIMAL_TYPE;
        token->op = line[pointer];
    } else {
        token->type = OPERATOR_TYPE;
        token->op = line[pointer];
    }
}

void advance(){
    pointer++;
}

int term(){
    Token firsttoken;
    gettoken(&firsttoken); //Integer
    advance();

    printf("Term: Just parsed %d\n", firsttoken.integer);
    Token optoken;
    gettoken(&optoken);
    if (optoken.type == OPERATOR_TYPE && optoken.op == '*'){
        advance();
        printf("Term parsed a *\n");
        int secondvalue = term();

        return firsttoken.integer * secondvalue;
    } else
        return firsttoken.integer;
}

int expression(){
    int firstvalue = term();

    if (line[pointer] == '\0'){
        printf("Expression: Reached End\n");
        return firstvalue;
    } else {
        Token plus;
        gettoken(&plus);
        advance();
        printf("Expression: +\n");

        int secondvalue = expression();
        return firstvalue + secondvalue;
    }

}

void parse(){
    pointer = 0;
    int answer = expression();
    printf("The Answer is: %d\n", answer);
}

int main() {
    parse();
    return 0;
}
