#ifndef OPERATORMINUS_H
#define OPERATORMINUS_H

#include "BinaryOperator.h"

namespace ExpressionParser
{
  class OperatorMinus : public BinaryOperator
  {
  public:
    OperatorMinus(size_t i_nestingLevel, size_t i_position);
    double CalculateResultForOperands(const Operand& left, 
                                      const Operand& right) const;
    virtual OperatorPriority Priority() const;
  private:
    OperatorMinus();
  };
}

#endif // OPERATORMINUS_H
