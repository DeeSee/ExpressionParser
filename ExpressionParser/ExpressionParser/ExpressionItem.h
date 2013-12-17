#ifndef EXPRESSIONITEM_H
#define EXPRESSIONITEM_H

#include <string>

namespace ExpressionParser
{
  enum ExpressionItemType
  {
    ExpressionItemTypeOperand = 0,
    ExpressionItemTypeBinaryOperator,

    ExpressionItemTypesCount
  };

  class ExpressionItem
  {
  public:
    virtual unsigned int NestingLevel() const;
    virtual unsigned int Position() const;
    virtual ExpressionItemType Type() const = 0;
    static ExpressionItem* ParseString(const std::string& i_string,
                                       size_t i_startLoc,
                                       size_t i_nestingLevel,
                                       size_t& o_parsedSize);

    virtual ~ExpressionItem();
  protected:
    ExpressionItem(size_t i_nestingLevel, size_t i_position);
  private:
    ExpressionItem();
    size_t m_nestingLevel;
    size_t m_position;
  };
}


#endif // EXPRESSIONITEM_H
