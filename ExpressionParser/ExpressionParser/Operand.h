#ifndef OPERAND_H
#define OPERAND_H

#include <string>
#include "ExpressionItem.h"

namespace ExpressionParser
{
  class Operand : public ExpressionItem
  {
  public:
    double GetValue() const;
    virtual ExpressionItemType Type() const;
    static Operand* OperandFromString(const std::string& i_string,
                                      size_t i_startLoc,
                                      size_t i_nestingLevel,
                                      size_t& o_parsedSize);
    Operand(double i_value, size_t i_nestingLevel, size_t i_position);
  private:
    Operand();
    double m_value;
  };
}

#endif // OPERAND_H
