#ifndef OPERATORDIVIDE_H
#define OPERATORDIVIDE_H

#include "BinaryOperator.h"

namespace ExpressionParser
{
  class OperatorDivide : public BinaryOperator
  {
  public:
    OperatorDivide(size_t i_nestingLevel, size_t i_position);
    double CalculateResultForOperands(const Operand& left, 
                                      const Operand& right) const;
    virtual OperatorPriority Priority() const;
  private:
    OperatorDivide();
  };
}

#endif // OPERATORDIVIDE_H
