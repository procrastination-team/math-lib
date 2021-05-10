namespace common
{
  namespace math
  {
    inline int factorial(int n)
    {
      int f = 1;
      for(int i = 2; i < n + 1; ++i)
        f *= i;
      return f;
    }

  } // namespace math
} // namespace common
