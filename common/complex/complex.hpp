#pragma once

#include <cmath>
#include <sstream>
#include <string_view>

#define EPSILON 1.5e-05

namespace common
{
  template< typename T >
  class Complex
  {
  public:
    constexpr Complex(const T& real = T(), const T& imag = T())
    : m_real(real),
      m_imag(imag)
    {}
    
    constexpr Complex(const Complex& other) = default;
    
    ~Complex() = default;
    
    constexpr T real() const { return m_real; }
    constexpr T imag() const { return m_imag; }
    
    constexpr void real(T val) { m_real = val; }
    constexpr void imag(T val) { m_imag = val; }
    
  private:
    T m_real;
    T m_imag;
  };
  
  template< typename T>
  std::ostream& operator<<(std::ostream& output, const Complex<T>& c)
  {
    if(c.real() != 0)
    {
      output << c.real();
      if(c.imag() > 0) output << '+';
      if(c.imag() == 0) return output;
    }
    if(c.imag() != 0)
    {
      if(c.imag() != 1)
        output << c.imag();
      output << 'i';
    }
    else output << 0;
    return output;            
  }
  
  template< typename T >
  constexpr Complex<T> parse_complex (std::string_view in)
  {
    Complex<T> res{0, 0};
    
    using namespace std::literals;
    if(in.data() == "i"s)
    {
      res.imag(1);
      return res;
    }
    if(in.data() == "-i"s)
    {
      res.imag(-1);
      return res;
    }
    
    std::stringstream input(in.data());
    std::string imag_part;
    float num;

    input >> num;
    std::getline(input, imag_part);

    int plus_pos = imag_part.find('+');
    int minus_pos = imag_part.find('-');
    int i_pos = imag_part.find('i');

    if(i_pos < 0)
    {
      res.real(num);
      return res;
    }
    
    if(plus_pos < 0 && i_pos == 0)
    {
      res.imag(num);
      return res;
    }
    
    res.real(num);
    imag_part.replace(i_pos, 1, "");
    
    if (plus_pos >= 0) 
      imag_part.replace(plus_pos, 1, "");
    if(minus_pos >= 0)
      imag_part.replace(minus_pos, 1, "");

    res.imag(atof(imag_part.c_str()));

    if (res.imag() == 0)
      res.imag(1);
    
    if(minus_pos >= 0)
      res.imag(-res.imag());

    return res;
  }
  
  /*
   * Comparison operators
   */
  template< typename T >
  constexpr bool operator==(const Complex<T>& lhs, const Complex<T>& rhs)
  {
    return (std::abs(lhs.real() - rhs.real()) < EPSILON)
    && (std::abs(lhs.imag() - rhs.imag()) < EPSILON);
  }
  
  template< typename T >
  constexpr bool operator!=(const Complex<T>& lhs, const Complex<T>& rhs)
  {
    return !(lhs == rhs);
  }
  
  /*
   * Addition operators
   */
  template< typename T >
  constexpr Complex<T> operator+(const Complex<T>& lhs, const Complex<T>& rhs)
  {
    return Complex<T>{
      lhs.real() + rhs.real(),
      lhs.imag() + rhs.imag()
    };
  }
  
  template< typename T >
  constexpr Complex<T> operator+(const Complex<T>& lhs, const T& rhs)
  {
    return Complex<T>{
      lhs.real() + rhs,
      lhs.imag()
    };
  }
  
  template< typename T >
  constexpr Complex<T> operator+(const T& lhs, const Complex<T>& rhs)
  {
    return Complex<T>{
      rhs.real() + lhs,
      rhs.imag()
    };
  }
  
  /*
   * Subtraction operators
   */
  template< typename T >
  constexpr Complex<T> operator-(const Complex<T>& lhs, const Complex<T>& rhs)
  {
    return Complex<T>{
      lhs.real() - rhs.real(),
      lhs.imag() - rhs.imag()
    };
  }
  
  template< typename T >
  constexpr Complex<T> operator-(const Complex<T>& lhs, const T& rhs)
  {
    return Complex<T>{
      lhs.real() - rhs,
      lhs.imag()
    };
  }
  
  template< typename T >
  constexpr Complex<T> operator-(const T& lhs, const Complex<T>& rhs)
  {
    return Complex<T>{
      lhs - rhs.real(),
      rhs.imag()
    };
  }
  
  /*
   * Multiplication operators
   */
  template< typename T >
  constexpr Complex<T> operator*(const Complex<T>& lhs, const Complex<T>& rhs)
  {
    auto res = Complex<T>{
      lhs.real() * rhs.real() - lhs.imag() * rhs.imag(),
      lhs.imag() * rhs.real() + lhs.real() * rhs.imag()
    };
    return res;
  }
  
  template< typename T >
  constexpr Complex<T> operator*(const Complex<T>& lhs, const T& rhs)
  {
    return Complex<T>{
      lhs.real() * rhs,
      lhs.imag() * rhs
    };
  }
  
  template< typename T >
  constexpr Complex<T> operator*(const T& lhs, const Complex<T>& rhs)
  {
    return Complex<T>{
      rhs.real() * lhs,
      rhs.imag() * lhs
    };
  }
  
  /*
   * Division operators
   */
  template< typename T >
  constexpr Complex<T> operator/(const Complex<T>& lhs, const Complex<T>& rhs)
  {
    return Complex<T>{
      (lhs.real()*rhs.real() + lhs.imag()*rhs.imag()) / (rhs.real()*rhs.real() + rhs.imag()*rhs.imag()),
      (lhs.imag()*rhs.real() - lhs.real()*rhs.imag()) / (rhs.real()*rhs.real() + rhs.imag()*rhs.imag())
    };
  }
  
  template< typename T >
  constexpr Complex<T> operator/(const Complex<T>& lhs, const T& rhs)
  {
    return Complex<T>{
      lhs.real() / rhs,
      lhs.imag() / rhs
    };
  }
  
} //namespace common
