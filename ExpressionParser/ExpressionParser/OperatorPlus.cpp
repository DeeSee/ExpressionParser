#include "OperatorPlus.h"

namespace ExpressionParser
{
  OperatorPlus::OperatorPlus() {}
  OperatorPlus::OperatorPlus(size_t i_nestingLevel, size_t i_position) :
    BinaryOperator(i_nestingLevel, i_position) {}
  double OperatorPlus::CalculateResultForOperands(const Operand& left,
                                                  const Operand& right) const
  {
    return left.GetValue() + right.GetValue();
  }

  OperatorPriority OperatorPlus::Priority() const
  {
    return OperatorPriorityLow;
  }
}
