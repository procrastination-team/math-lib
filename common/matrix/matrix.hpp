#pragma once

#include <cmath>
#include <cstddef>
#include <ostream>
#include <vector>

namespace common
{
  template<typename T>
  class Matrix
  {
  public:
    Matrix(std::size_t rows, std::size_t colls)
    : m_rows(rows),
      m_colls(colls)
    {
      m_data.resize(rows);
      for(std::size_t i = 0; i < rows; ++i)
        m_data[i].resize(colls);
    }
      
    ~Matrix() = default;
    
    constexpr std::size_t rows() const { return m_rows; }
    constexpr std::size_t colls() const { return m_colls; }
    
    constexpr T const& get(std::size_t r, std::size_t c) const { return m_data[r][c]; }
 
    class proxy
    {
    public:
      constexpr proxy(Matrix* m, std::size_t row) : m_pMatrix(m), m_row(row){}
      ~proxy() = default;

      constexpr T& operator[] (std::size_t col) { return m_pMatrix->m_data[m_row][col]; }

    private:
      Matrix<T>* m_pMatrix;
      std::size_t m_row{0};
    };
    
    constexpr proxy operator[] (std::size_t row) { return proxy{this, row}; }
    
    class iterator
    {
    public:
      iterator(Matrix* m, std::size_t row, std::size_t col)
      : m_pMatrix(m),
        m_row(row),
        m_col(col)
      {}
      ~iterator() = default;

      iterator operator++()
      {
        if(m_col == m_pMatrix->colls()-1)
        {
          m_row++;
          m_col = 0;
        }
        else m_col++;
        return *this;
      }

      bool operator==(const iterator& other) const { return (m_row == other.m_row) && (m_col == other.m_col);  }
      bool operator!=(const iterator& other) const { return (m_row != other.m_row) || (m_col != other.m_col);  }

      T& operator*() const { return m_pMatrix->m_data[m_row][m_col]; }

    private:
      Matrix<T>* m_pMatrix;
      std::size_t m_row{0};
      std::size_t m_col{0};
    };

    constexpr iterator begin() { return iterator(this, 0, 0); }
    constexpr iterator end() { return iterator(this, m_rows, 0); }
    
    constexpr Matrix<T> transpose() const
    {
      Matrix<T> res{m_rows, m_colls};
      
      for(std::size_t i = 0; i < m_rows; ++i)
        for(std::size_t j = 0; j < m_colls; ++j)
          res[j][i] = m_data[i][j];
          
      return res;
    }
    
    T det() const
    {
      if(m_rows != m_colls) return 0;
      
      std::vector<std::vector<T>> a = m_data;
      std::size_t k, j;

      T det = 1;
      for(std::size_t i = 0; i < m_rows; ++i)
      {
        k = i;
        for(j = i + 1; j < m_rows; ++j)
        {
          if(std::abs(a[j][i]) > std::abs(a[k][i]))
            k = j;
        }
        
        if(std::abs(a[k][i]) < EPSILON)
        {
          det = 0;
          break;
        }
        
        a[i].swap(a[k]);
        if (i != k)
          det = -det;
        
        det = det * a[i][i];
        
        for(j = i + 1; j < m_rows; ++j)
          a[i][j] = a[i][j] / a[i][i];
        
        for(j = 0; j < m_rows; ++j)
        {
          if((j != i) && (std::abs(a[j][i]) > EPSILON))
          {
            for (k = i + 1; k < m_rows; ++k)
              a[j][k] = a[j][k] - (a[i][k] * a[j][i]);
          }
        }
      }

      return det;
    }

  private:
    friend class proxy;
    friend class iterator;
    
    std::size_t m_rows;
    std::size_t m_colls;
    
    std::vector<std::vector<T>> m_data;
  };
  
  template< typename T>
  std::ostream& operator<<(std::ostream& output, const Matrix<T>& m)
  {
    for(std::size_t i = 0; i < m.rows(); ++i)
    {
      for(std::size_t j = 0; j < m.colls(); ++j)
        output << m.get(i, j) << ' ';
      output << std::endl;
    }
    
    return output;
  }
  
  template< typename T >
  constexpr bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs)
  {
    if( (lhs.rows() != rhs.rows()) || (lhs.colls() != rhs.colls()) )
      return false;
    
    for(std::size_t i = 0; i < lhs.rows(); ++i)
    {
      for(std::size_t j = 0; j < lhs.colls(); ++j)
      {
        if(lhs.get(i, j) != rhs.get(i, j))
          return false;
      }
    }
        
    return true;
  }
  
  template< typename T >
  constexpr Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs)
  {
    Matrix<T> res{lhs.rows(), lhs.colls()};
    if( (lhs.rows() != rhs.rows()) || (lhs.colls() != rhs.colls()) )
      return res;
    
    for(std::size_t i = 0; i < lhs.rows(); ++i)
      for(std::size_t j = 0; j < lhs.colls(); ++j)
        res[i][j] = lhs.get(i, j) + rhs.get(i, j);
    
    return res;
  }
  
  template< typename T >
  constexpr Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs)
  {
    Matrix<T> res{lhs.rows(), lhs.colls()};
    if( (lhs.rows() != rhs.rows()) || (lhs.colls() != rhs.colls()) )
      return res;
    
    for(std::size_t i = 0; i < lhs.rows(); ++i)
      for(std::size_t j = 0; j < lhs.colls(); ++j)
        res[i][j] = lhs.get(i, j) - rhs.get(i, j);
    
    return res;
  }
  
  template< typename T >
  constexpr Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs)
  {
    Matrix<T> res{lhs.rows(), rhs.colls()};
    if(lhs.colls() != rhs.rows())
      return res;
    
    for (std::size_t i = 0; i < lhs.rows(); i++)
    {
      for (std::size_t j = 0; j < rhs.colls(); j++)
      {
        res[i][j] = 0;
        for (std::size_t k = 0; k < rhs.rows(); k++)
          res[i][j] = res[i][j] + (lhs.get(i, k) * rhs.get(k, j));
      }
    }
    return res;
  }
  
  template< typename T >
  constexpr Matrix<T> operator*(const Matrix<T>& lhs, const T& rhs)
  {
    Matrix<T> res{lhs.rows(), lhs.colls()};
    
    for(std::size_t i = 0; i < lhs.rows(); ++i)
      for(std::size_t j = 0; j < lhs.colls(); ++j)
        res[i][j] = lhs.get(i, j) * rhs;
    
    return res;
  }
  
  template< typename T >
  constexpr Matrix<T> operator*(const T& lhs, const Matrix<T>& rhs)
  {
    Matrix<T> res{rhs.rows(), rhs.colls()};
    
    for(std::size_t i = 0; i < rhs.rows(); ++i)
      for(std::size_t j = 0; j < rhs.colls(); ++j)
        res[i][j] = rhs.get(i, j) * lhs;
      
    return res;
  }
  
} //namespace common
