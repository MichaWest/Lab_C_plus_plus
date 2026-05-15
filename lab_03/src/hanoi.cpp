#include <iostream>
#include <cassert>
#include <cstdlib> 
#include <list>
#include <string>

void hanoi_move(int topN, char from, char inter, char to, std::list<std::string>& steps){
    if (topN == 1) {
        steps.push_back("Disk 1 from " + std::string(1, from) + " to " + std::string(1, to));
    } else {
        hanoi_move(topN - 1, from, to, inter, steps); // S --> I 
        steps.push_back("Disk " + std::to_string(topN) + " from " + 
                        std::string(1, from) + " to " + std::string(1, to));
        hanoi_move(topN - 1, inter, from, to, steps); // I --> D 
    }
}

int main(int argc, char const **argv){
    assert(argc == 2); // 
    int n = std::atof(argv[1]); 

    std::list<std::string> stepList;

    std::cout << "The Hanoi Tower Solution for " << n << " disks:\n";
    std::cout << "Rods: A (source), B (auxiliary), C (target)\n\n";

    hanoi_move(n, 'A', 'B', 'C', stepList);

    std::cout << "=== Sequence of steps ===\n";
    std::cout << "Total of steps: " << stepList.size() << "\n\n";
    
    int stepNum = 1;
    for (const auto& step : stepList) {
        std::cout << stepNum++ << ". " << step << "\n";
    }
    
    stepList.clear(); 
    return 0; 
}