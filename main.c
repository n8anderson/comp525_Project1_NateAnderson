#include <stdio.h>
#include <math.h>

#define INTEGER_TYPE 1
#define OPERATOR_TYPE 2
#define FLOAT_TYPE 3
#define DECIMAL_TYPE 4

const char* line = "100.5*2 -200";
int pointer = 0;

typedef  struct{
    int integer;
    char op;
    double flt;
    int type;
} Token;

void advance(){
    pointer++;
}

void gettoken(Token* token){
    if (line[pointer] >= '0' && line[pointer] <= '9'){
        int dec_flag = 0;
        int counter = pointer;
        int digit;
        int number = 0;
        while (line[counter] >= '0' && line[counter] <= '9'){
            digit = line[counter] - '0';
            number = number * 10;
            number = number + digit;
            counter++;
        }
        double decimal = 0.0;
        float dig;
        int num = 1;
        if (line[counter] == '.'){
            printf("Just parsed a .\n");
            dec_flag = 1;
            counter++;
            while (line[counter] >= '0' && line[counter] <= '9') {
                dig = line[counter] - '0';
                decimal = decimal + (dig / (pow(10, num)));
                counter++;
                num++;

            }
            decimal = number + decimal;
            printf("Decimal number: %f\n", decimal);
        }

        pointer = counter-1;
        if (dec_flag == 1){
            token->type = FLOAT_TYPE;
            token->flt = decimal;
        } else {
            token->type = INTEGER_TYPE;
            token->integer = number;
        }
    } else if (line[pointer] == '.') {
        token->type = DECIMAL_TYPE;
        token->op = line[pointer];
    }  else if (line[pointer] == ' ') {
        advance();
        gettoken(token);
    } else {
            token->type = OPERATOR_TYPE;
            token->op = line[pointer];
    }
}

//Comment
double term() {
    Token firsttoken;
    gettoken(&firsttoken); //Integer
    advance();
    if (firsttoken.type == 3){
        printf("Term: Just parsed %f\n", firsttoken.flt);
    } else {
        printf("Term: Just parsed %d\n", firsttoken.integer);
    }
    Token optoken;
    gettoken(&optoken);
    if (optoken.type == OPERATOR_TYPE && optoken.op == '*') {
        advance();
        printf("Term parsed a *\n");
        double secondvalue = term();

        if (firsttoken.type == 3){
            return firsttoken.flt * secondvalue;
        } else {
            return firsttoken.integer * secondvalue;
        }
    } else {
        if (firsttoken.type == 3){
            return firsttoken.flt;
        } else {
            return firsttoken.integer;
        }


    }
}

double expression(){
    double firstvalue = term();

    if (line[pointer] == '+'){
        Token plus;
        gettoken(&plus);
        advance();
        printf("Expression: +\n");

        double secondvalue = expression();
        return firstvalue + secondvalue;
    } else if (line[pointer] == '-'){
        Token minus;
        gettoken(&minus);
        advance();
        printf("Expression: -\n");

        double secondvalue = expression();
        return firstvalue - secondvalue;
    } else {
        printf("Expression: Reached End\n");
        return firstvalue;
    }

}

void parse(){
    double answer = expression();
    printf("The Answer is: %f\n", answer);
}

int main() {
    parse();
    return 0;
}
