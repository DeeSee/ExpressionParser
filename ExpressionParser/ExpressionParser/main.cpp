#include <iostream>
#include "ExpressionParser.h"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    return 1;
  }

  size_t errorPos = SIZE_MAX;
  double result = ExpressionParser::CalculateExpression(std::string(argv[1]), errorPos);

  if (errorPos == SIZE_MAX)
  {
    std::cout << "Result: " << result << std::endl;
  }
  else
  {
    std::cout << "Error at position " << errorPos << std::endl;
  }

  return 0;
}

