#include <iostream>
#include <map>
#include "Token.h"


std::map<string,double> table;

double expr(bool);

Token_stream ts{std::cin};

int no_of_errors;

double error(const string& s){
    no_of_errors++;
    std::cerr << "erros: " << s << '\n';
    return 1;
}

double prim(bool get){ //handle primaries
    if(get) ts.get(); // read next token

    switch (ts.current().kind){
        case Kind::number :
        {
            double v = ts.current().number_value; // floating-point constant
            ts.get();
            return v;
        }
        case Kind::name :
        {
            double & v = table[ts.current().string_value];     // find the corresponding
            if(ts.get().kind == Kind::assign) v = expr(true);  // '=" seen: assignment
            return v;

        }
        case Kind::minus : //unary minus
            return -prim(true);
        case Kind::lp :
        {
            auto e = expr(true);
            if(ts.current().kind != Kind::rp) return error("')' expected");
            ts.get();
            return e;
        }
        default:
            return error("primary expected");

    }
}

double term(bool get){ // multiply and divide
    double left = prim(get);

    for(;;){
        switch (ts.current().kind){
            case Kind::mul :
                left *= prim(true);
                break;
            case Kind::div :
                if(auto d = prim(true)){
                    left /= d;
                    break;
                }
                return error("divide by 0");
            default:
                return left;
        }
    }
}

double expr(bool get){ //add and subtract
    double left = term(get);

    for(;;){
        switch (ts.current().kind){
            case Kind::plus :
                left += term(true);
                break;
            case Kind::minus :
                left -= term(true);
                break;
            default:
                return left;
        }
    }
}

void calculate(){
    for(;;){
        ts.get();
        if(ts.current().kind == Kind::end) break;
        if(ts.current().kind == Kind::print) continue;
        std::cout << expr(false) << '\n';
    }
}

int main() {
    table["pi"] = 3.1415926535897932385;
    table["e"] = 2.7182818284590452354;

    calculate();

    return no_of_errors;
}