#include <iostream> 

#include "complex/complex.hpp"
#include "matrix/matrix.hpp"

int main()
{
  try
  {
    std::string read_line;
    std::size_t rows, colls, i, j;
    std::cin >> rows >> colls;
    common::Matrix< common::Complex<int> > A{rows, colls};
    
    for(i = 0; i < rows; ++i)
    {
      for(j = 0; j < colls; ++j)
      {
        std::cin >> read_line;
        A[i][j] = common::parse_complex<int>(read_line);
      }
    }
    
    std::cin >> rows >> colls;
    common::Matrix< common::Complex<int> > B{rows, colls};
    
    for(i = 0; i < rows; ++i)
    {
      for(j = 0; j < colls; ++j)
      {
        std::cin >> read_line;
        B[i][j] = common::parse_complex<int>(read_line);
      }
    }
    
    std::cin >> read_line;
    auto scalar = common::parse_complex<int>(read_line);
    
    if( (A.rows() != B.rows()) || (A.colls() != B.colls()) )
      std::cout << "cannot sum or subtract matrices with different dimensions\n";
    else std::cout << "A + B:\n" << A + B << "\nA - B:\n" << A - B << "\n";
    
    if(A.colls() != B.rows())
      std::cout << "cannot multiply matrices with A.colls != B.rows\n";
    else std::cout << "A * B:\n" << A * B << "\n";
    
    std::cout << "A * " << scalar << ":\n" << A * scalar;

  }
  catch(std::exception& ex) { std::cerr << ex.what() << std::endl; }
  
  return 0;
}
