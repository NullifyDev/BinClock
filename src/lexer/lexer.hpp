#ifndef LEXER_HPP
#define LEXER_HPP

#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>

#include "../utils/output.hpp"

class Token
{
public:
    enum class Kind
    {
        Number, Identifier,
        Slash, Comma, Semicolon, Comment,
        EOL, _EOF, Asterisk,

        Unexpected,
    };

    Token(Kind kind) noexcept : m_kind{kind} {}

    Token(Kind kind, const char *beg, std::size_t len) noexcept
        : m_kind{kind}, m_lexeme(beg, len) {}

    Token(Kind kind, const char *beg, const char *end) noexcept
        : m_kind{kind}, m_lexeme(beg, std::distance(beg, end)) {}

    Kind kind() const noexcept { return m_kind; }

    void kind(Kind kind) noexcept { m_kind = kind; }

    bool is(Kind kind) const noexcept { return m_kind == kind; }

    bool is_not(Kind kind) const noexcept { return m_kind != kind; }

    bool is_one_of(Kind k1, Kind k2) const noexcept { return is(k1) || is(k2); }

    template <typename... Ts>
    bool is_one_of(Kind k1, Kind k2, Ts... ks) const noexcept
    {
        return is(k1) || is_one_of(k2, ks...);
    }

    std::string_view lexeme() const noexcept { return m_lexeme; }

    void lexeme(std::string_view lexeme) noexcept
    {
        m_lexeme = std::move(lexeme);
    }

private:
    Kind m_kind{};
    std::string_view m_lexeme{};
};

class Lexer
{
public:
    Lexer(const char *beg) noexcept : m_beg{beg} {}

    Token next() noexcept;

private:
    Token identifier() noexcept;
    Token number() noexcept;
    Token slash_or_comment() noexcept;
    Token atom(Token::Kind) noexcept;

    char peek() const noexcept { return *m_beg; }
    char get() noexcept { return *m_beg++; }

    const char *m_beg = nullptr;
};

std::string etos(Token::Kind token) {
    switch (token)
    {
        case Token::Kind::Number:
            return "Number";         
        case Token::Kind::Identifier:
            return "Identifier";     
        case Token::Kind::Slash:
            return "Slash";     
        case Token::Kind::Comma:
            return "Comma";     
        case Token::Kind::Semicolon:
            return "Semicolon";     
        case Token::Kind::Comment:
            return "Comment";     
        case Token::Kind::EOL:
            return "EOL";     
        case Token::Kind::_EOF:
            return "_EOF";     
        case Token::Kind::Asterisk:
            return "Asterisk";    
        case Token::Kind::Unexpected:
            return "Unexpected"; 
    }
}

bool is_space(char c) noexcept
{
    switch (c)
    {
    case ' ':
    case '\t':
    case '\r':
    case '\n':
        return true;
    default:
        return false;
    }
}

bool is_digit(char c) noexcept
{
    switch (c)
    {
        case '0' ... '9':
            return true;
        default:
            return false;
    }
}

bool is_identifier_char(char c) noexcept
{
    switch (c)
    {
        case 'x':
        case 'a' ... 'f':
        case '0' ... '9':
            return true;
        default:
            return false;
    }
}

Token Lexer::atom(Token::Kind kind) noexcept { return Token(kind, m_beg++, 1); }

Token Lexer::next() noexcept
{
    while (is_space(peek()))
        get();

    switch (peek())
    {
        case '\0':
            return Token(Token::Kind::_EOF, m_beg, 1);
        default:
            return atom(Token::Kind::Unexpected);
        case 'a' ... 'f':
            return identifier();
        case '0' ... '9':
            return number();
        case '*':
            return atom(Token::Kind::Asterisk);
        case '/':
            return slash_or_comment();
            return atom(Token::Kind::Slash);
        case ',':
            return atom(Token::Kind::Comma);
    }
}

Token Lexer::identifier() noexcept
{
    const char *start = m_beg;
    get();
    while (is_identifier_char(peek()))
        get();
    return Token(Token::Kind::Identifier, start, m_beg);
}

Token Lexer::number() noexcept
{
    const char *start = m_beg;
    get();
    while (is_digit(peek()))
        get();
    return Token(Token::Kind::Number, start, m_beg);
}

Token Lexer::slash_or_comment() noexcept
{
    const char *start = m_beg;
    get();
    if (peek() == '/')
    {
        get();
        start = m_beg;
        while (peek() != '\0')
        {
            if (get() == '\n')
            {
                return Token(Token::Kind::Comment, start,
                             std::distance(start, m_beg) - 1);
            }
        }
        return Token(Token::Kind::Unexpected, m_beg, 1);
    }
    else
    {
        return Token(Token::Kind::Slash, start, 1);
    }
}


int lexer(std::string content)
{
    const char * src = content.c_str();
    Lexer lex(src);
    for (auto token = lex.next(); not token.is_one_of(Token::Kind::_EOF, Token::Kind::Unexpected); token = lex.next()) {
        std::cout << std::setw(12);
        std::cout << etos(token.kind());
        std::cout << " |";
        std::cout << token.lexeme();
        std::cout << "|\n";
        std::cout << std::endl;
    }
}

#endif