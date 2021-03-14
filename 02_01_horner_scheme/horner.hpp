#pragma once

#include <cassert>
#include <cmath>
#include <iostream>
#include <span>
#include <vector>

#define EPSILON 1.5e-05

namespace horner
{
  template<class T>
  void calculate(std::span<T> coeffs)
  {
    T free_elem = coeffs.back();
    T tmp = 0;

    int len = coeffs.size()-2; 
    int n = len;
    
    std::vector<T> result;
    result.resize(n);
    for (auto& a_i : coeffs)
    {
      tmp = a_i + free_elem * tmp;
      if(n < 1)
      {
        std::cout << "; remain = x";
        if(tmp < 0) std::cout << "+" << std::abs(tmp);
        else std::cout << "-" << tmp;
        break;
      }
      result[len-n] = tmp;

      if( (n < len) && (tmp > 0) )
        std::cout << "+";
      
      std::cout << tmp;
      if(n == 1)
      {
        n--;
        continue;
      }
      std::cout << "x";
      
      if(n > 2)
        std::cout << "^" << n-1;
      n--;
    }
    std::cout << std::endl;
    
    assert(check<T>(coeffs, std::span{result}, free_elem, tmp));
  }
  
  template<class T>
  bool check(std::span<T> expected, std::span<T> result, T divisor, T remain)
  {
    auto len = result.size() + 1;
    divisor = -divisor;
    
    T previous_num = 0;
    
    for(int i = 0; i < len-1; ++i)
    {
      previous_num += result[i];
      if( std::abs(expected[i] - previous_num) > EPSILON )
        return false;

      previous_num = result[i] * divisor;
    }

    if(previous_num + remain != expected[len-1])
      return false;
    
    return true;
  }
  
}
