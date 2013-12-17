#include "OperatorDivide.h"

namespace ExpressionParser
{
  OperatorDivide::OperatorDivide() {}
  OperatorDivide::OperatorDivide(size_t i_nestingLevel, size_t i_position) :
    BinaryOperator(i_nestingLevel, i_position) {}
  double OperatorDivide::CalculateResultForOperands(const Operand& left,
                                                    const Operand& right) const
  {
    return left.GetValue() / right.GetValue();
  }

  OperatorPriority OperatorDivide::Priority() const
  {
    return OperatorPriorityHigh;
  }
}

