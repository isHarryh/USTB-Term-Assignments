/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;

namespace Calculator {
    const long double MAX_NUM = LLONG_MAX;
    const int MAX_DIGITS = (int)floor(log10(MAX_NUM)) - 2;
    const int MAX_PRECISION = numeric_limits<long double>::digits10;

    /**
     * @brief Number status.
     */
    enum NumberStatus {
        ZERO_DIVISION = -2,
        OVERFLOWED = -1,
        NONE = 0,
        OKAY = 1
    };

    /**
     * @brief Wrapped long double number.
     */
    struct Number {
    public:
        NumberStatus status;
        long double value;

        Number(NumberStatus status, long double value) {
            this->status = status;
            this->value = value;
        }

        Number(long double value) {
            this->status = NumberStatus::OKAY;
            this->value = value;
        }

        inline Number add(Number other) {
            if (status != NumberStatus::OKAY || other.status != NumberStatus::OKAY) {
                return Number(NumberStatus::NONE, 0);
            }
            long double a = value;
            long double b = other.value;
            bool of = (a > 0 && b > 0 && a > MAX_NUM - b) ||
                (a < 0 && b < 0 && a < b - MAX_NUM);
            return Number(of ? NumberStatus::OVERFLOWED : NumberStatus::OKAY, a + b);
        }

        inline Number minus(Number other) {
            if (status != NumberStatus::OKAY || other.status != NumberStatus::OKAY) {
                return Number(NumberStatus::NONE, 0);
            }
            long double a = value;
            long double b = other.value;
            bool of = (a > 0 && -b > 0 && a > MAX_NUM - -b) ||
                (a < 0 && -b < 0 && a < MAX_NUM - -b);
            return Number(of ? NumberStatus::OVERFLOWED : NumberStatus::OKAY, a - b);
        }

        inline Number multiply(Number other) {
            if (status != NumberStatus::OKAY || other.status != NumberStatus::OKAY) {
                return Number(NumberStatus::NONE, 0);
            }
            long double a = value;
            long double b = other.value;
            bool of = fabs(b) > fabs(MAX_NUM / a);
            return Number(of ? NumberStatus::OVERFLOWED : NumberStatus::OKAY, a * b);
        }

        inline Number divide(Number other) {
            if (status != NumberStatus::OKAY || other.status != NumberStatus::OKAY) {
                return Number(NumberStatus::NONE, 0);
            }
            long double a = value;
            long double b = other.value;
            if (b == 0) {
                return Number(NumberStatus::ZERO_DIVISION, 0);
            }
            bool of = fabs(b) < fabs(a / MAX_NUM);
            return Number(of ? NumberStatus::OVERFLOWED : NumberStatus::OKAY, a / b);
        }

        inline string toString() {
            if (value == 0) {
                return "0";
            }

            int intDigits = max(0, (int)floor(log10(fabs(value)))) + 1;
            int precision = max(0, MAX_PRECISION - intDigits);
            ostringstream oss;
            oss << fixed << setprecision(precision) << value;

            string formatted = oss.str();
            int dotIdx = formatted.find('.');
            if (dotIdx != std::string::npos) {
                int lastNonZero = formatted.find_last_not_of('0');
                if (lastNonZero == dotIdx) {
                    formatted.erase(dotIdx);
                }
                else {
                    formatted.erase(lastNonZero + 1);
                }
            }
            return formatted;
        }
    };

    /**
     * @brief Char-by-char number parser.
     */
    struct NumberReader {
    private:
        long long value;
        int digitLeft;
        int digitRight;
        bool isStarted;
        bool isEnded;
        bool isNegative;
        bool isDecimal;

    public:
        NumberReader() {
            value = 0;
            digitLeft = 0;
            digitRight = 0;
            isStarted = false;
            isEnded = false;
            isNegative = false;
            isDecimal = false;
        }

        inline bool read(char c) {
            if (c == ' ') {
                flush();
                return true;
            }
            if (!isEnded) {
                if ('0' <= c && c <= '9') {
                    value = value * 10 + (c - '0');
                    digitLeft += !isDecimal;
                    digitRight += isDecimal;
                    isStarted = true;
                    return true;
                }
                if (c == '.' && !isDecimal) {
                    isDecimal = true;
                    isStarted = true;
                    return true;
                }
                if (c == '-' && !isStarted) {
                    isNegative = !isNegative;
                    return true;
                }
            }
            return false;
        }

        inline bool flush() {
            if (isStarted) {
                isEnded = true;
            }
            return isEnded;
        }

        inline bool isFlushed() {
            return isStarted && isEnded;
        }

        inline bool isOverflowed() {
            return digitLeft + digitRight > MAX_DIGITS;
        }

        inline Number get() {
            long double rst = value;
            for (int i = 0; i < digitRight; i++) {
                rst /= 10.0;
            }
            if (isNegative) {
                rst = -rst;
            }
            return Number(isOverflowed() ? NumberStatus::OVERFLOWED : NumberStatus::OKAY, rst);
        }
    };

    /**
     * @brief The type indicator for Expression.
     */
    enum ExpressionType {
        ERR_OVERFLOW = -3,
        ERR_SYNTAX = -2,
        EXIT = -1,
        UNSET = 0,
        OP_ADD = 1,
        OP_MINUS = 2,
        OP_MULTIPLY = 3,
        OP_DIVIDE = 4,
        MEM_ADD = 5,
        MEM_MINUS = 6,
        MEM_CLEAR = 7,
        MEM_RECALL = 8
    };

    /**
     * @brief The expression parser for input streams.
     */
    struct Expression {
    public:
        ExpressionType type;
        NumberReader num1;
        NumberReader num2;

        Expression(istream& is) {
            type = ExpressionType::UNSET;
            num1 = NumberReader();
            num2 = NumberReader();

            char input[1024];
            is.getline(input, 1024);
            int inputLen = strlen(input);

            for (int i = 0; i < inputLen; i++) {
                char c = input[i];
                char nextC = i + 1 < inputLen ? input[i + 1] : '\0';
                if (!num1.read(c) && !(num1.flush() && num2.read(c))) {
                    switch (c) {
                    case '+':
                    case '-':
                    case '*':
                    case '/':
                        if (type || !num1.flush()) {
                            type = ExpressionType::ERR_SYNTAX;
                            return;
                        }
                        switch (c) {
                        case '+':
                            type = ExpressionType::OP_ADD;
                            break;
                        case '-':
                            type = ExpressionType::OP_MINUS;
                            break;
                        case '*':
                            type = ExpressionType::OP_MULTIPLY;
                            break;
                        case '/':
                            type = ExpressionType::OP_DIVIDE;
                            break;
                        }
                        break;
                    case ' ':
                    case '\t':
                        break;
                    case '#':
                        if (type) {
                            type = ExpressionType::ERR_SYNTAX;
                            return;
                        }
                        type = ExpressionType::EXIT;
                        break;
                    case 'M':
                    case 'm':
                        if (type) {
                            type = ExpressionType::ERR_SYNTAX;
                            return;
                        }
                        i++;
                        switch (nextC)
                        {
                        case '+':
                            type = ExpressionType::MEM_ADD;
                            break;
                        case '-':
                            type = ExpressionType::MEM_MINUS;
                            break;
                        case 'C':
                        case 'c':
                            type = ExpressionType::MEM_CLEAR;
                            break;
                        case 'R':
                        case 'r':
                            type = ExpressionType::MEM_RECALL;
                            break;
                        default:
                            type = ExpressionType::ERR_SYNTAX;
                            return;
                        }
                        break;
                    default:
                        type = ExpressionType::ERR_SYNTAX;
                        return;
                    }
                }
            }
            num1.flush();
            num2.flush();
            if (ExpressionType::OP_ADD <= type && type <= ExpressionType::OP_DIVIDE) {
                if (!num1.isFlushed() || !num2.isFlushed()) {
                    type = ExpressionType::ERR_SYNTAX;
                    return;
                }
                if (num1.isOverflowed() || num2.isOverflowed()) {
                    type = ExpressionType::ERR_OVERFLOW;
                    return;
                }
            }
            if (ExpressionType::MEM_ADD <= type && type <= ExpressionType::MEM_RECALL &&
                (num1.isFlushed() || num2.isFlushed())) {
                type = ExpressionType::ERR_SYNTAX;
                return;
            }
            switch (type) {
            case ExpressionType::EXIT:
                if (num1.isFlushed() || num2.isFlushed()) {
                    type = ExpressionType::ERR_SYNTAX;
                }
                break;
            case ExpressionType::UNSET:
                if (num1.isFlushed() && num1.isOverflowed()) {
                    type = ExpressionType::ERR_OVERFLOW;
                }
                break;
            default:
                break;
            }
        }

        inline Number eval() {
            switch (type)
            {
            case ExpressionType::OP_ADD:
            case ExpressionType::UNSET:
                return num1.get().add(num2.get());
            case ExpressionType::OP_MINUS:
                return num1.get().minus(num2.get());
            case ExpressionType::OP_MULTIPLY:
                return num1.get().multiply(num2.get());
            case ExpressionType::OP_DIVIDE:
                return num1.get().divide(num2.get());
                return num1.get();
            default:
                return Number(NumberStatus::NONE, 0);
            }
        }
    };
}

using namespace Calculator;

int main() {
    Number mem = 0;
    Number last = 0;
    while (true) {
        // Get user input
        cout << ">>> ";
        Expression exp = Expression(cin);
#ifdef DEBUG
        cout << "TYPE:  " << exp.type << endl;
        cout << "NUM 1: " << exp.num1.get().value << endl;
        cout << "NUM 2: " << exp.num2.get().value << endl;
#endif

        // Calculate result
        Number rst = Number(NumberStatus::NONE, 0);
        switch (exp.type) {
        case ExpressionType::EXIT:
            return 0;
        case ExpressionType::ERR_OVERFLOW:
            cout << "Error: Numerical overflowed!" << endl;
            break;
        case ExpressionType::ERR_SYNTAX:
            cout << "Error: Invalid expression!" << endl;
            break;
        case ExpressionType::UNSET:
            rst = exp.eval();
            break;
        case ExpressionType::MEM_ADD:
            mem = mem.add(last);
            if (mem.status != NumberStatus::OKAY) {
                cout << "Error: Failed to do memory add!" << endl;
                mem = 0;
            }
            break;
        case ExpressionType::MEM_MINUS:
            mem = mem.minus(last);
            if (mem.status != NumberStatus::OKAY) {
                cout << "Error: Failed to do memory minus!" << endl;
                mem = 0;
            }
            break;
        case ExpressionType::MEM_CLEAR:
            mem = 0;
            break;
        case ExpressionType::MEM_RECALL:
            rst = mem;
            break;
        default:
            rst = exp.eval();
            break;
        }

        // Print result
        switch (rst.status)
        {
        case NumberStatus::ZERO_DIVISION:
            cout << "Error: Cannot divided by zero!" << endl;
            break;
        case NumberStatus::OVERFLOWED:
            cout << "Error: Arithmetic overflowed!" << endl;
            break;
        case NumberStatus::NONE:
            break;
        case NumberStatus::OKAY:
            last = rst;
            cout << "<<< " << rst.toString() << endl;
            break;
        default:
            break;
        }
        cout << endl;
    }
    return 0;
}
