#include <ctype.h>
#include <stdio.h>
#include "parser.h"

// This is where the input goes
char input[1000];
// This is a pointer to the input
char *exprPtr = input;
// This is a buffer to use if we want to put a token back
struct {
    struct Token token;
    int bufferFull;
} tokenBuffer;
// Keep track of if we encountered an invalid token or grammar
int gotError = 0;

int main(void) {
    printf("Enter the expression > ");
    fgets(input, 1000, stdin); // Put the expression in the input array
    parse();
}

/** Parse the input expression */
void parse() {
    int result = expr();
    if (getToken().type != EOL) {
        error("Expected newline.");
    }
    if (gotError) {
        printf("Result: Error. Invalid expression.\n");
    } else {
        printf("Result: %d\n", result);
    }
}

/** Parse the expr grammar */
int expr() {
    int sum = term();             // Get the first term and put it in the sum.
    struct Token op = getToken(); // Get the operator
    // While the operator is a valid expr operator
    while (op.type == PLUS || op.type == MINUS) {
        printf("%c\t%s\n", op.value, TokenTypeStrings[op.type]);
        int nextTerm = term(); // Get the next term
        // Add or subtract it depending on the operator
        if (op.type == PLUS) {
            sum += nextTerm;
        } else {
            sum -= nextTerm;
        }
        op = getToken(); // Get the next operator.
    }
    // Since the last token we got was not a valid operator, put it back.
    ungetToken(op);
    return sum;
}

/** Parse the term grammar */
int term() {
    int product = power(); // Get the first power and put it in the product.
    struct Token op = getToken(); // Get the operator
    // While the operator is a valid term operator
    while (op.type == MULT || op.type == DIVIDE || op.type == REMAINDER) {
        printf("%c\t%s\n", op.value, TokenTypeStrings[op.type]);
        int nextPower = power(); // Get the next term
        // Multiply, divide, or modulo it depending on the operator
        if (op.type == MULT) {
            product *= nextPower;
        } else if (op.type == DIVIDE) {
            product /= nextPower;
        } else {
            product %= nextPower;
        }
        op = getToken(); // Get the next operator.
    }
    // Since the last token we got was not a valid operator, put it back.
    ungetToken(op);
    return product;
}

/** Parse the power grammar */
int power() {
    int base = factor(); // Get the base of the exponent
    int result = base;
    struct Token op = getToken(); // Get the operator
    // If we have the correct operator, do the exponentiation
    if (op.type == POWER) {
        printf("%c\t%s\n", op.value, TokenTypeStrings[op.type]);
        int exponent = power();
        while (exponent > 1) {
            result *= base;
            exponent--;
        }
    } else { // If the token isn't the POWER operator, put the token back
        ungetToken(op);
    }
    return result;
}

/** Parse the factor grammar */
int factor() {
    struct Token op = getToken();
    // Check if there's a MINUS
    if (op.type == MINUS) {
        printf("%c\t%s\n", op.value, TokenTypeStrings[op.type]);
        return factor1() * -1;
    }
    ungetToken(op); // If it wasn't a minus,
    return factor1();
}

/** Parse the factor1 grammar */
int factor1() {
    int result;
    struct Token token = getToken(); // This may be an LPAREN or a NUMBER
    if (token.type == LPAREN) {
        printf("%c\t%s\n", token.value, TokenTypeStrings[token.type]);
        result = expr();
        struct Token rparen = getToken();
        if (rparen.type == RPAREN) {
            printf("%c\t%s\n", rparen.value, TokenTypeStrings[rparen.type]);
        } else {
            error("Expected RPAREN.");
        }
    } else if (token.type == NUMBER) {
        printf("%d\t%s\n", token.value, TokenTypeStrings[token.type]);
        result = token.value;
    } else {
        error("Expected LPAREN or NUMBER.");
    }
    return result;
}

/**
 * This function gets the next token in the expression.
 * It returns a struct Token with the appropriate type,
 * with the value set to the relevant character. If it's
 * a NUMBER, then the value is the number's value.
 *
 * If there is a token in the buffer, it will return that
 * instead of a new token.
 */
struct Token getToken() {
    // If we have something in the buffer, return that and clear the buffer.
    if (tokenBuffer.bufferFull) {
        tokenBuffer.bufferFull = 0;
        return tokenBuffer.token;
    }

    // Skip the whitespace
    while (*exprPtr == ' ') {
        exprPtr++;
    }

    if (*exprPtr == '(') {
        return makeToken(LPAREN, *exprPtr++);
    } else if (*exprPtr == ')') {
        return makeToken(RPAREN, *exprPtr++);
    } else if (*exprPtr == '+') {
        return makeToken(PLUS, *exprPtr++);
    } else if (*exprPtr == '-') {
        return makeToken(MINUS, *exprPtr++);
    } else if (*exprPtr == '*') {
        return makeToken(MULT, *exprPtr++);
    } else if (*exprPtr == '/') {
        return makeToken(DIVIDE, *exprPtr++);
    } else if (*exprPtr == '%') {
        return makeToken(REMAINDER, *exprPtr++);
    } else if (*exprPtr == '^') {
        return makeToken(POWER, *exprPtr++);
    } else if (*exprPtr == '\n') {
        return makeToken(EOL, *exprPtr++);
    } else if (isdigit(*exprPtr)) {
        int sum = 0;                // Initialize the sum
        while (isdigit(*exprPtr)) { // Shift and add each number
            sum *= 10;
            sum += *exprPtr++ - '0';
        }
        return makeToken(NUMBER, sum);
    } else {
        error("Invalid token.");
        exprPtr++;
    }
}

/** This function acts as an undo for getToken by putting the token into a
 * buffer.
 */
void ungetToken(struct Token token) {
    tokenBuffer.token = token;
    tokenBuffer.bufferFull = 1;
}

/** Prints an error message and sets the gotError flag to 1 */
void error(char message[]) {
    gotError = 1;
    printf("Error: %s\n", message);
}

/** Create a struct Token with the given type and value. */
struct Token makeToken(TokenType tkType, int value) {
    struct Token myToken;
    myToken.type = tkType;
    myToken.value = value;
    return myToken;
}