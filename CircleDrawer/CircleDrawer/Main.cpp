#include <iostream>
#include <SFML/Graphics.hpp>
#include "SVG/Path.h"
#include <sstream>


int main() {

    //int n;
    //std::string svgPath;

    //std::cout << "Number of complementing circles (n >= 1):" << std::endl;
    //std::cin >> n;
    //std::cout << "Path of the SVG file:" << std::endl;
    //std::cin >> svgPath;

    //std::map<float, int> map{ {1.0f, 1}, {3.0f, 2}, {6.0f, 2} };

    //std::map<float, int>::iterator low = map.upper_bound(5.0f);

    std::string str = "   -3.01,356";
    std::stringstream ss{ str };
    float a;
    ss >> a;
    ss.ignore();
    ss >> a;
    std::cout << a;

    //auto a = Path("m405.5,501c-108.56354,0 -196.5,-77.64365 -196.5,-173.5c0,-95.85635 87.93646,-173.5 196.5,-173.5c108.56354,0 196.5,77.64365 196.5,173.5c0,95.85635 -87.93646,173.5 -196.5,173.5z");

    return 0;
}