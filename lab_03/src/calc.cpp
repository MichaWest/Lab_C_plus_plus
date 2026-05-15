#include <iostream>
#include <cstdlib>
#include <cassert>

double add(double a, double b);
double sub(double a, double b);
double pow(double a, int b);

int main(int argc, char const **argv){
    assert(argc == 4); // 

    double x1 = std::atof(argv[1]); 
    double x2 = std::atof(argv[3]);
    char op = *argv[2];

    double res = 0; 

    switch(op) {
        case '+': {
            res = add(x1, x2); 
            break;
        } 
        case '-': {
            res = sub(x1, x2); 
            break;
        }
        case '^': {
            res = pow(x1, x2); 
            break; 
        }
        default: {
            std::cout << "[ERROR] Only +, - and ^ operations can be used.";
            break;
        }
    }

    std:: cout << x1 << op << x2 << " = " << res << "\n";

    return 0; 
}

double add(double a, double b) {
    return a + b; 
}

double sub(double a, double b) {
    return a - b;
}

double pow(double a, int b){
    double ans = 1; 

    double coeff = b >= 0 ? a : (double)1 / a; 
    int abs_b = b >=0 ? b : -b; 
 
    for(int i=0; i < abs_b; i++){
        ans *= coeff; 
    }

    return ans; 
}