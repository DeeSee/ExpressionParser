#include "ExpressionItem.h"
#include "BinaryOperator.h"

namespace ExpressionParser
{
  ExpressionItem::ExpressionItem() : m_nestingLevel(0), m_position(0) {}
  ExpressionItem::ExpressionItem(size_t i_nestingLevel, size_t i_position) :
    m_nestingLevel(i_nestingLevel), m_position(i_position) {}

  size_t ExpressionItem::NestingLevel() const { return m_nestingLevel; }
  size_t ExpressionItem::Position() const { return m_position; }

  ExpressionItem* ExpressionItem::ParseString(const std::string& i_string,
                                              size_t i_startLoc,
                                              size_t i_nestingLevel,
                                              size_t& o_parsedSize)
  {
    BinaryOperator* bOperator = BinaryOperator::BinaryOperatorFromChar(i_string[i_startLoc],
                                                                       i_nestingLevel,
                                                                       i_startLoc);
    size_t operandParsedSize = 0;
    Operand* operand = Operand::OperandFromString(i_string,
                                                  i_startLoc,
                                                  i_nestingLevel,
                                                  operandParsedSize);

    ExpressionItem* result = NULL;

    if ((bOperator != NULL) && (operand != NULL))
    {
      if ((i_startLoc == 0) || (i_string[i_startLoc - 1] == '('))
      {
        result = operand;
        o_parsedSize = operandParsedSize;
      }
      else
      {
        result = bOperator;
        o_parsedSize = 1;
      }
    }
    else if (bOperator != NULL)
    {
      result = bOperator;
      o_parsedSize = 1;
    }
    else if (operand != NULL)
    {
      result = operand;
      o_parsedSize = operandParsedSize;
    }


    return result;
  }

  ExpressionItem::~ExpressionItem() {}
}

