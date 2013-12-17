#ifndef OPERATORMULTIPLY_H
#define OPERATORMULTIPLY_H

#include "BinaryOperator.h"

namespace ExpressionParser
{
  class OperatorMultiply : public BinaryOperator
  {
  public:
    OperatorMultiply(size_t i_nestingLevel, size_t i_position);
    double CalculateResultForOperands(const Operand& left, 
                                      const Operand& right) const;
    virtual OperatorPriority Priority() const;
  private:
    OperatorMultiply();
  };
}

#endif // OPERATORMULTIPLY_H
