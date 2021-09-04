#include <iostream>
#include <SFML/Graphics.hpp>

int main() {

    int n;
    std::string svgPath;

    std::cout << "Number of complementing circles (n >= 1):" << std::endl;
    std::cin >> n;
    std::cout << "Path of the SVG file:" << std::endl;
    std::cin >> svgPath;

    std::map<float, int> map{ {1.0f, 1}, {3.0f, 2}, {6.0f, 2} };

    std::map<float, int>::iterator low = map.upper_bound(5.0f);

    return 0;
}