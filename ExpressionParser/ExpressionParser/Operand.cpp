#include <stdlib.h>
#include "Operand.h"


namespace ExpressionParser
{
  Operand::Operand(double i_value, size_t i_nestingLevel, size_t i_position) : 
    ExpressionItem(i_nestingLevel, i_position), m_value(i_value) {}
  ExpressionItemType Operand::Type() const { return ExpressionItemTypeOperand; }
  double Operand::GetValue() const { return m_value; }

  bool IsCharValidForNumber(char i_char)
  {
    return ((i_char >= '0' && i_char <= '9') || (i_char == '.'));
  }

  Operand* Operand::OperandFromString(const std::string& i_string,
                                             size_t i_startLoc,
                                             size_t i_nestingLevel,
                                             size_t& o_parsedSize)
  {
    size_t currentLoc = ((i_string[i_startLoc] == '-') ?
                           (i_startLoc + 1) : i_startLoc);
    size_t numberOfDots = 0;

    while (currentLoc < i_string.size() &&
           IsCharValidForNumber(i_string[currentLoc]) &&
           (numberOfDots <= 1))
    {
      if (i_string[currentLoc] == '.')
      {
        numberOfDots++;
      }

      currentLoc++;
    }

    if (numberOfDots > 1 ||
        currentLoc == i_startLoc)
    {
      o_parsedSize = 0;
      return NULL;
    }

    size_t parsedSize = currentLoc - i_startLoc;
    std::string numString = std::string(i_string, i_startLoc, parsedSize);
    double parsedVal = atof(numString.c_str());

    o_parsedSize = parsedSize;
    return new Operand(parsedVal, i_nestingLevel, i_startLoc);
  }
}
