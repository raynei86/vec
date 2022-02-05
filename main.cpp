#include <iostream>

#include <string>
#include "iterator.hpp"
#include "vec.hpp"

int main() {
    std::ios::sync_with_stdio(0);

    Vec<int> test = {1, 2, 3, 4, 5};
    std::cout << "Inital vector: ";
    for (std::size_t it = 0; it < test.size(); ++it) {
        std::cout << "[" << test[it] << "] ";
    }

    std::cout << "\n----------\n";

    test.push_back(6);
    test.push_back(7);
    test.push_back(8);
    std::cout << "Push back test: ";
    for (std::size_t it = 0; it < test.size(); ++it) {
        std::cout << "[" << test[it] << "] ";
    }

    std::cout << "\n----------\n";

    test.pop_back();
    std::cout << "Pop back test: ";
    for (std::size_t it = 0; it < test.size(); ++it) {
        std::cout << "[" << test[it] << "] ";
    }

    std::cout << "\n----------\n";

    Vec<int> swapTest;
    test.swap(swapTest);
    std::cout << "Swap test: ";
    for (std::size_t it = 0; it < swapTest.size(); ++it) {
        std::cout << "[" << swapTest[it] << "] ";
    }
    swapTest.swap(test);

    std::cout << "\n----------\n";

    test.erase(0);
    std::cout << "Erase test: ";
    for (std::size_t it = 0; it < test.size(); ++it) {
        std::cout << "[" << test[it] << "] ";
    }

    std::cout << "\n----------\n";

    test.resize(5);
    std::cout << "Resize test: ";
    for (std::size_t it = 0; it < test.size(); ++it) {
        std::cout << "[" << test[it] << "] ";
    }

    std::cout << "\n----------\n";

    test.insert(0, 1);
    std::cout << "Insert test: ";
    for (std::size_t it = 0; it < test.size(); ++it) {
        std::cout << "[" << test[it] << "] ";
    }
    std::cout << "\n----------\n";

    test.clear();
    std::cout << "Clear test: ";
    for (std::size_t it = 0; it < test.size(); ++it) {
        std::cout << "[" << test[it] << "] ";
    }
    std::cout << "\n----------\n";

    std::cout << "Test done.\n";
    return 0;
}
