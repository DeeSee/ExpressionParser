#include "OperatorMultiply.h"

namespace ExpressionParser
{
  OperatorMultiply::OperatorMultiply() {}
  OperatorMultiply::OperatorMultiply(size_t i_nestingLevel, size_t i_position) :
    BinaryOperator(i_nestingLevel, i_position) {}
  double OperatorMultiply::CalculateResultForOperands(const Operand& left,
                                                      const Operand& right) const
  {
    return left.GetValue() * right.GetValue();
  }

  OperatorPriority OperatorMultiply::Priority() const
  {
    return OperatorPriorityHigh;
  }
}
