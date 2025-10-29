#include <iostream>
#include <memory>
#include "Figure.hpp"
#include "Square.hpp"
#include "Rectangle.hpp"
#include "Trapezoid.hpp"
#include "Array.hpp"

void printMenu() {
    std::cout << "\n=== Figure Manager ===\n";
    std::cout << "1. Add Square\n";
    std::cout << "2. Add Rectangle\n";
    std::cout << "3. Add Trapezoid\n";
    std::cout << "4. Print all figures\n";
    std::cout << "5. Calculate total area\n";
    std::cout << "6. Remove figure by index\n";
    std::cout << "7. Show geometric center (of all figures)\n";
    std::cout << "8. Exit\n";
    std::cout << "Choice: ";
}

int main() {
    Array<Figure<double>> figures;
    int choice;

    while (true) {
        printMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input!\n";
            continue;
        }

        try {
            switch (choice) {
                case 1: {
                    auto sq = std::make_shared<Square<double>>();
                    std::cin >> *sq;
                    figures.Add(sq);
                    std::cout << "Square added!\n";
                    break;
                }
                case 2: {
                    auto rect = std::make_shared<Rectangle<double>>();
                    std::cin >> *rect;
                    figures.Add(rect);
                    std::cout << "Rectangle added!\n";
                    break;
                }
                case 3: {
                    auto trap = std::make_shared<Trapezoid<double>>();
                    std::cin >> *trap;
                    figures.Add(trap);
                    std::cout << "Trapezoid added!\n";
                    break;
                }
                case 4: {
                    figures.PrintAll(std::cout);
                    break;
                }
                case 5: {
                    std::cout << "Total area: " << figures.TotalArea() << "\n";
                    break;
                }
                case 6: {
                    size_t index;
                    std::cout << "Enter index to remove (starting from 0): ";
                    std::cin >> index;
                    figures.Remove(index);
                    std::cout << "Figure removed!\n";
                    break;
                }
                case 7: {
                    auto center = figures.CenterAll();
                    std::cout << "Global center: (" << center.first << ", " << center.second << ")\n";
                    break;
                }
                case 8: {
                    std::cout << "Goodbye!\n";
                    return 0;
                }
                default:
                    std::cout << "Invalid choice!\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}
