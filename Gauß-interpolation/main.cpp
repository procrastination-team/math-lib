#include <iostream>
#include <sstream>
#include <vector>

constexpr char separator = ';';

int factorial(int n)
{
  int f = 1;
  for(int i = 2; i < n + 1; ++i)
    f *= i;
  return f;
}

float coefficient(float p, int n)
{
  float coeff = p;
  for(int i = 1; i < n; ++i) 
  {
    if(i % 2 == 0)
       coeff *= (p + i);
    else
      coeff *= (p - i);
  }
  return coeff;
}

int main()
{
  try
  {
    float target;
    std::cin >> target;
    
    std::string x_str, y_str;
    std::cin >> x_str >> y_str;
    
    std::vector<float> x;
    std::vector<std::vector<float>> y;
    
    std::stringstream stream(x_str);
    std::string tmp;
    
    while(std::getline(stream, tmp, separator))
      x.emplace_back(std::stof(tmp));
    std::stringstream().swap(stream);
    stream << y_str;
    
    std::size_t n = x.size();
    y.reserve(n);
    
    std::size_t i = 0, j = 0;
    
    for(i = 0; i < n; ++i)
      y[i].reserve(n-1);
    
    i = 0;
    while(std::getline(stream, tmp, separator))
    {
      y[i].emplace_back(std::stof(tmp));
      ++i;
    }
    
    for(i = 1; i < n; ++i)
      for(j = 0; j < n-i; ++j)
        y[j][i] = y[j + 1][i - 1] - y[j][i - 1];
    
    for(i = 0; i < n; ++i)
    {
      for(j = 0; j < n-i; ++j)
        std::cout << y[i][j] << " ";
      std::cout << "\n";
    }
    
    auto res = y[int(n/2)][0];
    auto p = (target - x[int(n/2)]) / (x[1] - x[0]);
    
    for(i = 1; i < n; ++i)
      res += (coefficient(p, i) * y[int((n-i)/2)][i]) / factorial(i);
      
    std::cout << res << "\n";
    
  }
  catch(std::exception& ex) { std::cerr << ex.what() << "\n"; }
  
  return 0;
}
