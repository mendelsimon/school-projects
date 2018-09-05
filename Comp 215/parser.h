typedef enum {
    PLUS,
    MINUS,
    DIVIDE,
    MULT,
    REMAINDER,
    POWER,
    LPAREN,
    RPAREN,
    NUMBER,
    EOL
} TokenType;

char *TokenTypeStrings[] = {
    "PLUS",
    "MINUS",
    "DIVIDE",
    "MULT",
    "REMAINDER",
    "POWER",
    "LPAREN",
    "RPAREN",
    "NUMBER",
    "EOL"
};

struct Token {
    TokenType type;
    int value;
};

int expr();
int term();
int power();
int factor();
int factor1();
void error(char[]);
void parse();
struct Token getToken();
void ungetToken(struct Token);
struct Token makeToken(TokenType, int);