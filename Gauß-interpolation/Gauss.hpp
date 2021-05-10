#include <iostream>
#include <span>
#include <vector>

#include "math/factorial.hpp"

namespace Gauss
{
  namespace
  {
    enum InterpolationType : uint8_t { FORWARD = 0, BACKWARD = 1 };

    inline float coefficient(float p, int n)
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

    template<typename T, uint8_t SHIFT>
    T interpolate(T target, std::span<T> x, std::span<T> y_vals)
    {
      auto n = x.size();
      std::vector<std::vector<T>> y;
      y.resize(n);

      std::size_t i, j;
      for(i = 0; i < n; ++i)
      {
        y[i].resize(n);
        y[i][0] = y_vals[i];
      }

      for(i = 1; i < n; ++i)
        for(j = 0; j < n-i; ++j)
          y[j][i] = y[j + 1][i - 1] - y[j][i - 1];

      for(auto const& row : y)
      {
        for(auto const& col : row)
          std::cout << col << " ";
        std::cout << "\n";
      }

      auto res = y[int(n/2)][0];
      auto p = (target - x[int(n/2)]) / (x[1] - x[0]);

      for(i = 1; i < n; ++i)
        res += coefficient(p, i) * y[int((n-i-SHIFT)/2)][i] / common::math::factorial(i);

      return res;
    }
  } // namespace

  template<typename T>
  T forwardInterpolate(T target, std::span<T> x, std::span<T> y_vals)
  {
    return interpolate<T, InterpolationType::FORWARD>(target, x, y_vals);
  }

  template<typename T>
  T backwardInterpolate(T target, std::span<T> x, std::span<T> y_vals)
  {
    return interpolate<T, InterpolationType::BACKWARD>(target, x, y_vals);
  }

} // namespace Gauss
