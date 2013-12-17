#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

#include <string>

namespace ExpressionParser
{
  double CalculateExpression(const std::string& i_string,
                             size_t& o_errorPos);
}

#endif // EXPRESSIONPARSER_H
