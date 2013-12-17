#ifndef EXPRESSIONOPERATOR_H
#define EXPRESSIONOPERATOR_H

#include "ExpressionItem.h"
#include "Operand.h"


namespace ExpressionParser
{
  enum OperatorPriority
  {
    OperatorPriorityHigh = 0,
    OperatorPriorityLow,

    OperatorPrioritiesCount
  };

  class BinaryOperator : public ExpressionItem
  {
  public:
    virtual double CalculateResultForOperands(const Operand& left,
                                              const Operand& right) const = 0;
    virtual OperatorPriority Priority() const = 0;
    virtual ExpressionItemType Type() const;
    static BinaryOperator* BinaryOperatorFromChar(char i_char,
                                                  size_t i_nestingLevel,
                                                  size_t i_position);
    static BinaryOperator* Copy(BinaryOperator* another);
    virtual ~BinaryOperator();
  protected:
    BinaryOperator(size_t i_nestingLevel, size_t i_position);
    BinaryOperator();
  private:
    char m_char;
  };
}

#endif // EXPRESSIONOPERATOR_H
