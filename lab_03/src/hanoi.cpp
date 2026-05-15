#include <iostream>
#include <cassert>
#include <cstdlib> 

void hanoi_move(int topN, char from, char inter, char to, std::list<std::string>& steps){
    if (topN == 1) {
        steps.push_back("Disk 1 from " + std::string(1, from) + " to " + std::string(1, to));
    } else {
        hanoi_move(topn - 1, from, to, inter); // S --> I 
        steps.push_back("Disk " + std::to_string(topN) + " from " + 
                        std::string(1, from) + " to " + std::string(1, to));
        hanoi_move(topn - 1, inter, from, to); // I --> D 
    }
}

int main(int argc, char const **argv){
    assert(argc == 2); // 
    int n = std::atof(argv[1]); 

    std::list<std::string> stepList;

    std::cout << "Решение Ханойской башни для " << n << " дисков:\n";
    std::cout << "Стержни: A (исходный), B (вспомогательный), C (целевой)\n\n";

    hanoi_move(n, 'A', 'B', 'C', stepList);

    std::cout << "=== Последовательность шагов ===\n";
    std::cout << "Всего шагов: " << stepList.size() << "\n\n";
    
    int stepNum = 1;
    for (const auto& step : stepList) {
        std::cout << stepNum++ << ". " << step << "\n";
    }
    
    stepList.clear(); 
    return 0; 
}