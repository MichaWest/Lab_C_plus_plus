#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cctype>

using namespace std;

// =========================
// Интерфейс команды
// =========================

class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

// =========================
// Команда вывода в консоль
// =========================

class PrintCommand : public Command {
private:
    string text;

public:
    explicit PrintCommand(const string& text) : text(text) {}

    void execute() override {
        cout << text << endl;
    }
};

// =========================
// Команда вывода в файл
// =========================

class FileAppendCommand : public Command {
private:
    string filename;
    string text;

public:
    FileAppendCommand(const string& filename, const string& text)
        : filename(filename), text(text) {}

    void execute() override {
        ofstream file(filename, ios::app);

        if (!file.is_open()) {
            throw runtime_error("Ошибка открытия файла: " + filename);
        }

        file << text << endl;
    }
};

// =========================
// Команда арифметической операции
// =========================

class ArithmeticCommand : public Command {
private:
    double left;
    double right;
    char operation;

public:
    ArithmeticCommand(double left, char operation, double right)
        : left(left), right(right), operation(operation) {}

    void execute() override {
        double result = 0;

        switch (operation) {
            case '+':
                result = left + right;
                break;

            case '-':
                result = left - right;
                break;

            case '*':
                result = left * right;
                break;

            case '/':
                if (right == 0) {
                    throw runtime_error("Ошибка: деление на ноль");
                }
                result = left / right;
                break;

            default:
                throw runtime_error("Неизвестная арифметическая операция");
        }

        cout << left << " " << operation << " " << right << " = " << result << endl;
    }
};

// =========================
// Команда счетного цикла
// =========================

class LoopCommand : public Command {
private:
    int count;
    vector<unique_ptr<Command>> commands;

public:
    LoopCommand(int count, vector<unique_ptr<Command>> commands)
        : count(count), commands(move(commands)) {}

    void execute() override {
        for (int i = 0; i < count; ++i) {
            for (auto& command : commands) {
                command->execute();  // вызвать метод execute() у объекта Command
            }
        }
    }
};

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

// =========================
// Парсер
// =========================

class Parser {
private:
    vector<Token> tokens;
    size_t position = 0;

public:
    Parser(vector<Token> tokens) : tokens(move(tokens)) {}

    vector<unique_ptr<Command>> parseProgram() {
        vector<unique_ptr<Command>> commands;

        while (!isEnd()) {
            commands.push_back(parseCommand());
        }

        return commands;
    }

private:
    unique_ptr<Command> parseCommand() {
        string commandName = expectWord();

        if (commandName == "print") {
            return parsePrintCommand();
        }

        if (commandName == "file") {
            return parseFileCommand();
        }

        if (commandName == "calc") {
            return parseArithmeticCommand();
        }

        if (commandName == "repeat") {
            return parseLoopCommand();
        }

        throw runtime_error("Неизвестная команда: " + commandName);
    }

    unique_ptr<Command> parsePrintCommand() {
        string text = expectString();
        expectSymbol(";");

        return make_unique<PrintCommand>(text);
    }

    unique_ptr<Command> parseFileCommand() {
        string filename = expectString();
        string text = expectString();
        expectSymbol(";");

        return make_unique<FileAppendCommand>(filename, text);
    }

    unique_ptr<Command> parseArithmeticCommand() {
        double left = expectNumber();

        string operationToken = expectSymbolAny();
        if (operationToken.size() != 1) {
            throw runtime_error("Ошибка арифметической операции");
        }

        char operation = operationToken[0];

        if (operation != '+' && operation != '-' && operation != '*' && operation != '/') {
            throw runtime_error("Недопустимая арифметическая операция");
        }

        double right = expectNumber();

        expectSymbol(";");

        return make_unique<ArithmeticCommand>(left, operation, right);
    }

    unique_ptr<Command> parseLoopCommand() {
        int count = static_cast<int>(expectNumber());

        if (count < 0) {
            throw runtime_error("Количество повторений цикла не может быть отрицательным");
        }

        expectSymbol("{");

        vector<unique_ptr<Command>> body;

        while (!checkSymbol("}")) {
            if (isEnd()) {
                throw runtime_error("Ошибка: цикл не закрыт символом }");
            }

            body.push_back(parseCommand());
        }

        expectSymbol("}");
        expectSymbol(";");

        return make_unique<LoopCommand>(count, move(body));
    }

    string expectWord() {
        if (tokens[position].type != TokenType::Word) {
            throw runtime_error("Ожидалось имя команды");
        }

        return tokens[position++].value;
    }

    string expectString() {
        if (tokens[position].type != TokenType::String) {
            throw runtime_error("Ожидалась строка в кавычках");
        }

        return tokens[position++].value;
    }

    double expectNumber() {
        if (tokens[position].type != TokenType::Number) {
            throw runtime_error("Ожидалось число");
        }

        return stod(tokens[position++].value);
    }

    void expectSymbol(const string& expected) {
        if (tokens[position].type != TokenType::Symbol ||
            tokens[position].value != expected) {
            throw runtime_error("Ожидался символ: " + expected);
        }

        ++position;
    }

    string expectSymbolAny() {
        if (tokens[position].type != TokenType::Symbol) {
            throw runtime_error("Ожидался символ операции");
        }

        return tokens[position++].value;
    }

    bool checkSymbol(const string& symbol) const {
        return tokens[position].type == TokenType::Symbol &&
               tokens[position].value == symbol;
    }

    bool isEnd() const {
        return tokens[position].type == TokenType::End;
    }
};

// =========================
// Главная программа
// =========================

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Введите команды мини-языка." << endl;
    cout << "Каждая команда должна заканчиваться символом ;" << endl;
    cout << "Для завершения ввода введите: end;" << endl;
    cout << endl;

    string source;
    string line;

    while (true) {
        getline(cin, line);

        if (line == "end;") {
            break;
        }

        source += line + '\n';
    }

    try {
        Lexer lexer(source);
        vector<Token> tokens = lexer.tokenize();

        Parser parser(tokens);
        vector<unique_ptr<Command>> program = parser.parseProgram();

        cout << endl;
        cout << "Выполнение программы:" << endl;
        cout << "---------------------" << endl;

        for (auto& command : program) {
            command->execute();
        }
    }
    catch (const exception& error) {
        cerr << "Ошибка: " << error.what() << endl;
        return 1;
    }

    return 0;
}