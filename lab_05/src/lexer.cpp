#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cctype>

// =========================
// Токенизация
// =========================

enum class TokenType {
    Word,
    String,
    Number,
    Symbol,
    End
};

struct Token {
    TokenType type;
    string value;
};


class Lexer {
private:
    string source;
    size_t position = 0;

public:
    Lexer(const string& source) : source(source) {}

    vector<Token> tokenize() {
        vector<Token> tokens;

        while (position < source.size()) {
            char current = source[position];

            if (isspace(current)) {
                ++position;
                continue;
            }

            if (isalpha(current)) {
                tokens.push_back(readWord());
                continue;
            }

            if (isdigit(current)) {
                tokens.push_back(readNumber());
                continue;
            }

            if (current == '"') {
                tokens.push_back(readString());
                continue;
            }

            if (current == ';' || current == '{' || current == '}' ||
                current == '+' || current == '-' || current == '*' || current == '/') {
                tokens.push_back({TokenType::Symbol, string(1, current)});
                ++position;
                continue;
            }

            throw runtime_error(string("Неизвестный символ: ") + current);
        }

        tokens.push_back({TokenType::End, ""});
        return tokens;
    }

private:
    Token readWord() {
        string result;

        while (position < source.size() &&
               (isalnum(source[position]) || source[position] == '_')) {
            result += source[position];
            ++position;
        }

        return {TokenType::Word, result};
    }

    Token readNumber() {
        string result;

        while (position < source.size() &&
               (isdigit(source[position]) || source[position] == '.')) {
            result += source[position];
            ++position;
        }

        return {TokenType::Number, result};
    }

    Token readString() {
        ++position;
        string result;

        while (position < source.size() && source[position] != '"') {
            result += source[position];
            ++position;
        }

        if (position >= source.size()) {
            throw runtime_error("Ошибка: строка не закрыта кавычкой");
        }

        ++position;

        return {TokenType::String, result};
    }
};
