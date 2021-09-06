#include <iostream>
#include <SFML/Graphics.hpp>
#include "SVG/Path.h"
#include <sstream>


int main() {

    int n;
    std::string svgPath;

    //std::cout << "Number of complementing circles (n >= 1):" << std::endl;
    //std::cin >> n;
    //std::cout << "Path string of the SVG:" << std::endl;
    //std::cin >> svgPath;

    Path a("m0,0l50,0l50,50l0,50z");

    Point aois = a.Interpolate(0.9f);

    return 0;
}