#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
 
double formula1(double x) {
    return x * x - x * x + x * 4 - x * 5 + x + x;
}
 
double formula2(double x) {
    return x + x;
}
 
double formula3(double result1, double result2) {
    return result1 + result2 - result1;
}
 
void performSequentialCalculations(int iterations) {
    auto start = std::chrono::high_resolution_clock::now();
 
    double checksum = 0.0;
 
    for (int i = 1; i <= iterations; ++i) {
        double x = i;
 
        double result1 = formula1(x);
        double result2 = formula2(x);
        double result3 = formula3(result1, result2);
    }
 
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> delta = end - start;
 
    std::cout << "Sequential calculations program" << std::endl;
    std::cout << "Number of iterations: " << iterations << std::endl;
    std::cout << "Execution time: " << delta.count() << " sec." << std::endl;
    std::cout << std::endl;
}
 
void performParallelCalculations(int iterations) {
    double* results1 = new double[iterations];
    double* results2 = new double[iterations];
    double* results3 = new double[iterations];
 
    auto start = std::chrono::high_resolution_clock::now();
 
    std::thread t1([&]() {
        for (int i = 0; i < iterations; ++i) {
            double x = static_cast<double>(i + 1);
            results1[i] = formula1(x);
        }
    });
 
    std::thread t2([&]() {
        for (int i = 0; i < iterations; ++i) {
            double x = static_cast<double>(i + 1);
            results2[i] = formula2(x);
        }
    });
 
    t1.join();
    t2.join();
 
    double checksum = 0.0;
 
    for (int i = 0; i < iterations; ++i) {
        results3[i] = formula3(results1[i], results2[i]);
    }
 
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> delta = end - start;
 
    std::cout << "Parallel calculations program" << std::endl;
    std::cout << "Number of iterations: " << iterations << std::endl;
    std::cout << "Execution time: " << delta.count() << " sec." << std::endl;
    std::cout << std::endl;
}
 
void performParallelCalculationsWithProcesses(int iterations) {
    std::vector<double> results1(iterations);
    std::vector<double> results2(iterations);

    auto start = std::chrono::high_resolution_clock::now();
    auto future1 = std::async(std::launch::async, [&]() {
        for (int i = 0; i < iterations; ++i) {
            double x = i + 1;
            results1[i] = formula1(x);
        }
    });

    auto future2 = std::async(std::launch::async, [&]() {
        for (int i = 0; i < iterations; ++i) {
            double x = i + 1;
            results2[i] = formula2(x);
        }
    });

    for (int i = 0; i < iterations; ++i) {
        double result3 = formula3(results1[i], results2[i]);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> delta = end - start;

    std::cout << "Parallel calculations (processes) program" << std::endl;
    std::cout << "Number of iterations: " << iterations << std::endl;
    std::cout << "Execution time: " << delta.count() << " sec." << std::endl;
    std::cout << std::endl;
}

int main() {
    performSequentialCalculations(10000);
    performSequentialCalculations(100000);
 
    performParallelCalculations(10000);
    performParallelCalculations(100000);
 
    return 0;
}