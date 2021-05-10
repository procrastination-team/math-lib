#include <sstream>

#include "Gauss.hpp"

constexpr char separator = ';';

int main()
{
  try
  {
    float target;
    std::cin >> target;
    
    std::string x_str, y_str;
    std::cin >> x_str >> y_str;
    
    std::vector<float> x;
    std::vector<float> y;
    
    std::stringstream stream(x_str);
    std::string tmp;
    
    while(std::getline(stream, tmp, separator))
      x.emplace_back(std::stof(tmp));
    std::stringstream().swap(stream);
    stream << y_str;
    
    y.reserve(x.size());
    
    while(std::getline(stream, tmp, separator))
      y.emplace_back(std::stof(tmp));
    
    auto res = Gauss::forwardInterpolate<float>(target, x, y);
    std::cout << "forward interpolation: f(" << target << ") ~ " <<  res << "\n\n";

    res = Gauss::backwardInterpolate<float>(target, x, y);
    std::cout << "backward interpolation: f(" << target << ") ~ " <<  res << "\n";
    
  }
  catch(std::exception& ex) { std::cerr << ex.what() << "\n"; }
  
  return 0;
}
