#include "BinaryOperator.h"
#include "OperatorPlus.h"
#include "OperatorMinus.h"
#include "OperatorMultiply.h"
#include "OperatorDivide.h"

namespace ExpressionParser
{
  BinaryOperator::BinaryOperator() : ExpressionItem(0, 0) {}
  BinaryOperator::BinaryOperator(size_t i_nestingLevel, size_t i_position) :
    ExpressionItem(i_nestingLevel, i_position) {}

  ExpressionItemType BinaryOperator::Type() const { return ExpressionItemTypeBinaryOperator; }
  BinaryOperator::~BinaryOperator() {}

  BinaryOperator* BinaryOperator::Copy(BinaryOperator* another)
  {
    if (another == NULL)
    {
      return NULL;
    }

    return BinaryOperatorFromChar(another->m_char,
                                  another->NestingLevel(),
                                  another->Position());
  }

  BinaryOperator* BinaryOperator::BinaryOperatorFromChar(char i_char,
                                                         size_t i_nestingLevel,
                                                         size_t i_position)
  {
    BinaryOperator* result = NULL;

    switch (i_char)
    {
    case '+':
      result = new OperatorPlus(i_nestingLevel, i_position);
      break;
    case '-':
      result = new OperatorMinus(i_nestingLevel, i_position);
      break;
    case '*':
      result = new OperatorMultiply(i_nestingLevel, i_position);
      break;
    case '/':
      result = new OperatorDivide(i_nestingLevel, i_position);
      break;
    }

    if (result != NULL)
    {
      result->m_char = i_char;
    }

    return result;
  }
}
