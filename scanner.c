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

static bool match_char(char expected)
{
    if (isAtEnd())
        return false;
    if (scanner.current[0] != expected)
        return false;

    scanner.current++;
    return true;
}

static Token new_token(TokenType type)
{
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

static Token error_token(const char *msg)
{
    Token token;
    token.type = TOKEN_ERROR;
    token.line = scanner.line;
    token.start = msg;
    token.length = strlen(msg);
    return token;
}

static char peek()
{
    return *scanner.current;
}
static char peek_next()
{
    if (isAtEnd())
        return '\0';
    return scanner.current[1];
}
static void skip_whitespace()
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
            if (peek_next() == '/')
            {
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

static Token string()
{
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
            scanner.line++;
        advance();
    }
    if (isAtEnd())
        return error_token("Unterminated string.");

    advance();
    return new_token(TOKEN_STRING);
}

static bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static Token number()
{
    while (is_digit(peek))
        advance();
    if (peek() == '.' && is_digit(peek_next()))
    {
        advance();
    }
    while (is_digit(peek))
        advance();
    return new_token(TOKEN_NUMBER);
}

Token scan_token()
{
    skip_whitespace();
    scanner.start = scanner.current;
    if (is_at_end())
    {
        return new_token(TOKEN_EOF);
    }
    char c = advance();
    if (is_digit(c))
        return number();
    switch (c)
    {
    case '(':
        return new_token(TOKEN_LEFT_PAREN);
    case ')':
        return new_token(TOKEN_RIGHT_PAREN);
    case '{':
        return new_token(TOKEN_LEFT_BRACE);
    case '}':
        return new_token(TOKEN_RIGHT_BRACE);
    case ';':
        return new_token(TOKEN_SEMICOLON);
    case ',':
        return new_token(TOKEN_COMMA);
    case '.':
        return new_token(TOKEN_DOT);
    case '-':
        return new_token(TOKEN_MINUS);
    case '+':
        return new_token(TOKEN_PLUS);
    case '/':
        return new_token(TOKEN_SLASH);
    case '*':
        return new_token(TOKEN_STAR);
    case '!':
        return new_token(match_char('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
    case '=':
        return new_token(
            match_char('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
    case '<':
        return new_token(
            match_char('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
    case '>':
        return new_token(
            match_char('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
    case '"':
        return string();
    }

    return error_token("Unexpected character.");
}
