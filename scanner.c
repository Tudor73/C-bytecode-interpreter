#include <stdio.h>
#include <string.h>
#include "common.h"
#include "scanner.h"

typedef struct Scanner
{
    const char *start;
    const char *current;
    int line;
} Scanner;

Scanner scanner;


void initScanner(const char *source)
{
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}
static bool isAtEnd()
{
    return *scanner.current == '\0';
}


static char advance()
{
    scanner.current++;
    return scanner.current[-1];
}

static Token newToken(TokenType type)
{
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.line = scanner.line;
    token.length = (int)(scanner.current - scanner.start);
    return token;
}

static Token errorToken(const char *message)
{
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner.line;
    return token;
}

static char peek()
{
    return *scanner.current;
}
static char peekNext()
{
    if (isAtEnd())
        return '\0';
    return scanner.current[1];
}

static void skipWhitespace()
{
    for (;;)
    {
        char c = peek();
        switch (c)
        {
        case ' ':
        case '\r':
        case '\t':
            advance();
            break;
        case '\n':
            scanner.line++;
            advance();
            break;
        case '/':
            if (peekNext() == '/')
            {
                // A comment goes until the end of the line.
                while (peek() != '\n' && !isAtEnd())
                    advance();
            }
            else
            {
                return;
            }
            break;
        default:
            return;
        }
    }
}

static bool match(char c)
{
    if (isAtEnd())
        return false;
    if (*scanner.current == c)
        return true;

    scanner.current++;
    return false;
}

static Token string()
{
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
            scanner.line++;
        advance();
    }
    if (isAtEnd())
    {
        return errorToken("Unterminated string");
    }
    advance();
    return newToken(TOKEN_STRING);
}

static bool isDigit(char c) { 
    return c >= '0' && c <= '9';
}

static bool isAlpha(char c) { 
    return (c >= 'a' && c <= 'z') ||
     (c >= 'A' && c <= 'Z') ||
        c == '_';
}

static TokenType identifierType() {
 return TOKEN_IDENTIFIER;
}


   
static Token number()
{ 
    while(isDigit(peek()))
    { 
        advance();
    }
    if (peek() == '.' && isDigit(peekNext())) { 
        advance();
    }
    while(isDigit(peek()))
    { 
        advance();
    }
    return newToken(TOKEN_NUMBER);
}

Token scanToken()
{
    skipWhitespace();
    scanner.start = scanner.current;
    if (isAtEnd())
        return newToken(TOKEN_EOF);

    char c = advance();
    
    if (isDigit(c)) return number(); 

    switch (c)
    {
    case '(':
        return newToken(TOKEN_LEFT_PAREN);
    case ')':
        return newToken(TOKEN_RIGHT_PAREN);
    case '{':
        return newToken(TOKEN_LEFT_BRACE);
    case '}':
        return newToken(TOKEN_RIGHT_BRACE);
    case ';':
        return newToken(TOKEN_SEMICOLON);
    case ',':
        return newToken(TOKEN_COMMA);
    case '.':
        return newToken(TOKEN_DOT);
    case '-':
        return newToken(TOKEN_MINUS);
    case '+':
        return newToken(TOKEN_PLUS);
    case '/':
        return newToken(TOKEN_SLASH);
    case '*':
        return newToken(TOKEN_STAR);
    case '!':
        return newToken(
            match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
    case '=':
        return newToken(
            match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
    case '<':
        return newToken(
            match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
    case '>':
        return newToken(
            match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
    case '"':
        return string();
    }
    return errorToken("Unexpected character");
}
