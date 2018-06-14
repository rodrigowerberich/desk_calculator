//
// Created by Rodrigo on 07/06/2018.
//

#ifndef DESK_CALCULATOR_TOKEN_H
#define DESK_CALCULATOR_TOKEN_H

#include <istream>
#include <string>
using string = std::string;
using istream = std::istream;

double error(const string& s);

enum class Kind: char{
    name,number,end,
    plus='+',minus='-',mul='*',div='/',print=';',assign='=',lp='(',rp=')'
};

struct Token{
    Kind kind;
    string string_value;
    double number_value;
};

class Token_stream{
public:
    Token_stream(istream & s): ip{&s}, owns{false}{}
    Token_stream(istream * p): ip{p}, owns{true}{}

    ~Token_stream(){close();}


    Token get();            // read and return next token
    const Token& current(); // most recently read token

    void set_Input(istream & s){close(); ip = &s; owns = false;}
    void set_Input(istream * p){close(); ip = p; owns = false;}

private:
        void close(){if(owns) delete ip;}

        istream* ip;            // pointer to an input stream
        bool owns;              // does the Token_stream own the istream
        Token ct{Kind::end};    // current token
};

#endif //DESK_CALCULATOR_TOKEN_H
