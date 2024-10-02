#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

struct Token
{
    //added doubleNum as new type with index 2
    enum TokenType { open_par, number, doubleNum, oper, close_par };
    TokenType type;
    std::string val;
};

std::ostream& operator << (std::ostream& out, const Token& t)
{
    out << "Token(" << t.type << "," << t.val << ")";
    return out;
}

bool isOperator(char c)
{
    return c == '+' ||
        c == '-' ||
        c == '*' ||
        c == '/';
}

Token nextToken(std::istream& in)
{
    char c = in.peek();
    if (isdigit(c))
    {
        std::string num;
        //creating boolean to track if the number is double
        bool isDouble = false;
        char lastSymbol = c;

        //adding condition for accepting and record the '.'
        while (isdigit(c) || c == '.')
        {
            //adding a "lastSymbol" to track the last character in "num"
            lastSymbol = c;

            //if '.' is found we change the boolean expression to true and add the symbol to the result
            if (c == '.') 
            { 
                isDouble = true;
            }

            num += c;
            in.get();
            c = in.peek();
        }

        //depending of the customer preferences, if the number ends with '.' :

        if (lastSymbol == '.') 
        {
            //1)it can be considered as invalid character
            //std::cerr << "char=" << c << "\n" << std::endl;
            //throw std::runtime_error("Invalid character");

            //2)or it can be verified as an integer

            //removing '.'
            num.pop_back();
            return Token{ Token::number, num };
        }

        //in this case the returning value depends on the value of the boolean "isDouble"
        return isDouble ? Token{ Token::doubleNum, num } : Token{ Token::number, num };
    }
    else if (c == '(')
    {
        in.get();
        return Token{ Token::open_par, "(" };
    }
    else if (c == ')')
    {
        in.get();
        return Token{ Token::close_par, ")" };
    }
    else if (isOperator(c))
    {
        in.get();
        return Token{ Token::oper, std::string("") + c };
    }
    else
    {
        std::cerr << "char=" << c << "\n" << std::endl;
        throw std::runtime_error("Invalid character");
    }

}

std::vector<Token> tokenize(std::istream& in)
{
    std::vector<Token> tokens;

    //fixed "in" to "in.eof()", because the program takes the end character and while verifing returns error("Invalid charecter")
    while (!in.eof())
    {
        //removed the "in.peek() == '\n'" condition
        //added a new if statement which checks if the next character is a new line and continues, taking the following one
        if (in.peek() == '\n') 
        {
            in.get();
        }
        else
        {
            Token t = nextToken(in);
            if (in)
            {
                tokens.push_back(t);
            }
        }
    }
    return tokens;
}


int main()
{
    std::ifstream in("expression.exis");

    std::vector<Token> tokens = tokenize(in);
    // do something with parsed

    for (Token t : tokens)
    {
        std::cout << t;
    }

    std::cout << std::endl;

    return 0;
}
