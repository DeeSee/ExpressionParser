#ifndef OPERATORPLUS_H
#define OPERATORPLUS_H

#include "BinaryOperator.h"

namespace ExpressionParser
{
  class OperatorPlus : public BinaryOperator
  {
  public:
    OperatorPlus(size_t i_nestingLevel, size_t i_position);
    double CalculateResultForOperands(const Operand& left, 
                                      const Operand& right) const;
    virtual OperatorPriority Priority() const;
  private:
    OperatorPlus();
  };
}

#endif // OPERATORPLUS_H
