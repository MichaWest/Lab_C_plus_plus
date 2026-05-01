#include <iostream>
#include <ctime>

double compute(double x) {
    return x*x - x*x + x*4 - x*5 + x + x;
}

int main() {
    while(true) {
        long n; 
        std::cout << "Enter number of iterations (or non-number to exit): ";

        if (!(std::cin >> n)) {
            std::cout << "Invalid input. Exiting.\n";
            break;
        }

        double x;
        clock_t start = clock();

        for (long long i = 0; i < n; ++i) {
            volatile double res = compute(x); // volatile чтобы не оптимизировалось
        }

        clock_t end = clock();

        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        
        std::cout << "Time taken: " << seconds << " seconds\n";

        
        char again;
        std::cout << "Run again? (y/n): ";
        std::cin >> again;
        if (again != 'y' && again != 'Y') {
            break;
        }
    }
    return 0;
}
