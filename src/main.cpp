#include <iostream>


    int main() {
        std::cout << "\33[1;31m This text is red \33[0m" << std::endl;
        std::cout << "\033[1;32mThis text is green\033[0m" << std::endl;
        std::cout << "\033[1;34mThis text is blue\033[0m" << std::endl;
        return 0;
    }

