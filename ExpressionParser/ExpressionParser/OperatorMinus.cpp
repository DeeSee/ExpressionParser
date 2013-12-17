#include "OperatorMinus.h"

namespace ExpressionParser
{
  OperatorMinus::OperatorMinus() {}
  OperatorMinus::OperatorMinus(size_t i_nestingLevel, size_t i_position) :
    BinaryOperator(i_nestingLevel, i_position) {}
  double OperatorMinus::CalculateResultForOperands(const Operand& left,
                                                   const Operand& right) const
  {
    return left.GetValue() - right.GetValue();
  }

  OperatorPriority OperatorMinus::Priority() const
  {
    return OperatorPriorityLow;
  }
}

