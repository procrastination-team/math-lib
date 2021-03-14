#include "horner.hpp"

int main()
{
  try
  {
    float f;
    std::vector<float> input;
    while(std::cin >> f)
      input.emplace_back(f);
    
    horner::calculate(std::span{input});
  }
  catch(std::exception& ex)
  {
    std::cerr << ex.what() << std::endl;
  }
  
  return 0;
}
