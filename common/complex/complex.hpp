#pragma once

#include <cmath>

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
    
    constexpr Complex(const Complex& other)
    : m_real(other.real()),
      m_imag(other.imag())
    {}
    
    template< class U >
    constexpr Complex(const Complex<U>& other)
    : m_real(reinterpret_cast<T>(other.real())),
      m_imag(reinterpret_cast<T>(other.imag()))
    {}
    
    ~Complex() = default;
    
    constexpr T real() const { return m_real; }
    constexpr T imag() const { return m_imag; }
    
    constexpr void real(T val) { m_real = val; }
    constexpr void imag(T val) { m_imag = val; }
    
  private:
    T m_real;
    T m_imag;
  };
  
  /*
   * Comparison operator
   */
  template< class T >
  constexpr bool operator==( const Complex<T>& lhs, const Complex<T>& rhs)
  {
    return (std::abs(lhs.real() - rhs.real()) < EPSILON)
    && (std::abs(lhs.imag() - rhs.imag()) < EPSILON);
  }
  
  /*
   * Addition operators
   */
  template< class T >
  constexpr Complex<T> operator+(const Complex<T>& lhs, const Complex<T>& rhs)
  {
    return Complex<T>{
      lhs.real() + rhs.real(),
      lhs.imag() + rhs.imag()
    };
  }
  
  template< class T >
  constexpr Complex<T> operator+(const Complex<T>& lhs, const T& rhs)
  {
    return Complex<T>{
      lhs.real() + rhs,
      lhs.imag()
    };
  }
  
  template< class T >
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
  template< class T >
  constexpr Complex<T> operator-(const Complex<T>& lhs, const Complex<T>& rhs)
  {
    return Complex<T>{
      lhs.real() - rhs.real(),
      lhs.imag() - rhs.imag()
    };
  }
  
  template< class T >
  constexpr Complex<T> operator-(const Complex<T>& lhs, const T& rhs)
  {
    return Complex<T>{
      lhs.real() - rhs,
      lhs.imag()
    };
  }
  
  template< class T >
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
  template< class T >
  constexpr Complex<T> operator*(const Complex<T>& lhs, const Complex<T>& rhs)
  {
    return Complex<T>{
      lhs.real() * rhs.real() - lhs.imag() * rhs.imag(),
      lhs.imag() * rhs.real() + lhs.real() * rhs.imag()
    };
  }
  
  template< class T >
  constexpr Complex<T> operator*(const Complex<T>& lhs, const T& rhs)
  {
    return Complex<T>{
      lhs.real() * rhs,
      lhs.imag() * rhs
    };
  }
  
  template< class T >
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
  template< class T >
  constexpr Complex<T> operator/(const Complex<T>& lhs, const Complex<T>& rhs)
  {
    return Complex<T>{
      (lhs.real()*rhs.real() + lhs.imag()*rhs.imag()) / (rhs.real()*rhs.real() + rhs.imag()*rhs.imag()),
      (lhs.imag()*rhs.real() - lhs.real()*rhs.imag()) / (rhs.real()*rhs.real() + rhs.imag()*rhs.imag())
    };
  }
  
  template< class T >
  constexpr Complex<T> operator/(const Complex<T>& lhs, const T& rhs)
  {
    return Complex<T>{
      lhs.real() / rhs,
      lhs.imag() / rhs
    };
  }
  
  template< class T >
  constexpr Complex<T> operator/(const T& lhs, const Complex<T>& rhs); // i'm sure no one'll ever need this useless thing
  
} //namespace common
