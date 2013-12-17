#include <vector>
#include <assert.h>
#include "ExpressionParser.h"
#include "ExpressionItem.h"
#include "Operand.h"
#include "BinaryOperator.h"

namespace ExpressionParser
{
  const size_t kDefaultErrorPos = SIZE_MAX;

  void ClearItems(std::vector<ExpressionItem*>& io_items)
  {
    for (size_t i = 0; i < io_items.size(); ++i)
    {
      delete io_items[i];
    }
    io_items.clear();
  }

  size_t ParseExpression(const std::string& i_string,
                         std::vector<ExpressionItem*>& o_items,
                         size_t& o_maxNestingLevel)
  {
    if (i_string.size() == 0)
    {
      return 0;
    }

    size_t currentLoc = 0;
    size_t nestingLevel = 0;
    size_t maxNestingLevel = 0;
    while (currentLoc < i_string.size())
    {
      switch (i_string[currentLoc])
      {
      case '(':
        nestingLevel++;
        maxNestingLevel = (nestingLevel > maxNestingLevel) ? nestingLevel : maxNestingLevel;
        currentLoc++;
        break;
      case ')':
        nestingLevel--;
        currentLoc++;
        break;
      default:
      {
        size_t parsedSize = 0;
        ExpressionItem* item = ExpressionItem::ParseString(i_string,
                                                           currentLoc,
                                                           nestingLevel,
                                                           parsedSize);
        if (item == NULL)
        {
          ClearItems(o_items);
          return currentLoc;
        }
        currentLoc += parsedSize;
        o_items.push_back(item);
      }
      }
    }

    if (nestingLevel != 0)
    {
      ClearItems(o_items);
      return currentLoc;
    }

    o_maxNestingLevel = maxNestingLevel;

    return kDefaultErrorPos;
  }

  bool ValidateNeighboursTypes(ExpressionItemType left, ExpressionItemType right)
  {
    return left != right;
  }

  size_t ValidateExpression(const std::vector<ExpressionItem*> i_items)
  {
    if ((i_items.size() == 0) ||
        (i_items[0]->Type() == ExpressionItemTypeBinaryOperator) ||
        (i_items[i_items.size() - 1]->Type() == ExpressionItemTypeBinaryOperator))
    {
      return 0;
    }

    for (size_t i = 1; i < i_items.size(); ++i)
    {
      if (!ValidateNeighboursTypes(i_items[i - 1]->Type(), i_items[i]->Type()))
      {
        return i_items[i]->Position();
      }
    }

    return kDefaultErrorPos;
  }

  std::vector<ExpressionItem*> CalculateSequenceForPriority(const std::vector<ExpressionItem*> i_sequence,
                                                             OperatorPriority i_priority)
  {
    assert(i_sequence.size() != 0);
    std::vector<ExpressionItem*> result;

    size_t currentLoc = 0;
    while (currentLoc < i_sequence.size())
    {
      switch (i_sequence[currentLoc]->Type())
      {
      case ExpressionItemTypeOperand:
      {
        Operand* operand = dynamic_cast<Operand*>(i_sequence[currentLoc]);
        result.push_back(new Operand(operand->GetValue(), operand->NestingLevel(), 0));
        currentLoc++;
        break;
      }
      case ExpressionItemTypeBinaryOperator:
      {
        BinaryOperator* bOperator = dynamic_cast<BinaryOperator*>(i_sequence[currentLoc]);
        if (bOperator->Priority() == i_priority)
        {
          assert(result.size() != 0);
          assert(result.back()->Type() == ExpressionItemTypeOperand);
          assert(currentLoc < i_sequence.size() - 1);
          assert(i_sequence[currentLoc + 1]->Type() == ExpressionItemTypeOperand);
          Operand* left = dynamic_cast<Operand*>(result.back());
          Operand* right = dynamic_cast<Operand*>(i_sequence[currentLoc + 1]);
          double value = bOperator->CalculateResultForOperands(*left, *right);
          delete left;
          result.back() = new Operand(value, right->NestingLevel(), 0);
          currentLoc += 2;
        }
        else
        {
          result.push_back(BinaryOperator::Copy(bOperator));
          currentLoc++;
        }
        break;
      }
      default:
        assert(false);
      }
    }

    return result;
  }

  std::vector<ExpressionItem*> CopyItems(const std::vector<ExpressionItem*>& i_items,
                                          size_t i_from,
                                          size_t i_to)
  {
    std::vector<ExpressionItem*> result;
    result.reserve(i_items.size());

    for (size_t i = i_from; i < i_to; ++i)
    {
      switch (i_items[i]->Type())
      {
      case ExpressionItemTypeOperand:
      {
        Operand* operand = dynamic_cast<Operand*>(i_items[i]);
        result.push_back(new Operand(operand->GetValue(), operand->NestingLevel(), 0));
        break;
      }
      case ExpressionItemTypeBinaryOperator:
      {
        BinaryOperator* bOperator = dynamic_cast<BinaryOperator*>(i_items[i]);
        result.push_back(BinaryOperator::Copy(bOperator));
        break;
      }
      }
    }

    return result;
  }

  double CalculateSequence(const std::vector<ExpressionItem*> i_items,
                           size_t i_startLoc,
                           size_t i_endLoc)
  {
    std::vector<ExpressionItem*> currentPriorityResult = CopyItems(i_items,
                                                                   i_startLoc,
                                                                   i_endLoc);
    for (int priority = 0;
         priority < OperatorPrioritiesCount;
         ++priority)
    {
      std::vector<ExpressionItem*> newResult = CalculateSequenceForPriority(currentPriorityResult,
                                                                            static_cast<OperatorPriority>(priority));
      ClearItems(currentPriorityResult);
      currentPriorityResult = newResult;
    }

    assert(currentPriorityResult.size() == 1);
    assert(currentPriorityResult[0]->Type() == ExpressionItemTypeOperand);

    Operand* operand = dynamic_cast<Operand*>(currentPriorityResult[0]);
    double result = operand->GetValue();
    ClearItems(currentPriorityResult);

    return result;
  }

  double CalculateExpression(const std::string& i_string,
                             size_t& o_errorPos)
  {
    std::vector<ExpressionItem*> items;
    size_t maxNestingLevel = 0;
    size_t parseResult = ParseExpression(i_string, items, maxNestingLevel);
    if (parseResult != kDefaultErrorPos)
    {
      o_errorPos = parseResult;
      return 0.0;
    }

    size_t validateResult = ValidateExpression(items);
    if (validateResult != kDefaultErrorPos)
    {
      o_errorPos = validateResult;
      return 0.0;
    }

    size_t nestingLevel = maxNestingLevel + 1;
    while (true)
    {
      nestingLevel--;

      size_t loc = 0;
      while (loc < items.size())
      {
        while (loc < items.size() &&
               (items[loc]->NestingLevel() != nestingLevel))
        {
          loc++;
        }

        if (loc >= items.size())
        {
          break;
        }

        size_t startLoc = loc;
        while (loc < items.size() &&
               (items[loc]->NestingLevel() == nestingLevel))
        {
          loc++;
        }
        size_t endLoc = loc;

        if (startLoc != endLoc)
        {
          double value = CalculateSequence(items, startLoc, endLoc);

          for (size_t i = startLoc; i < endLoc; ++i)
          {
            delete items[i];
          }
          items.erase(items.begin() + startLoc, items.begin() + (endLoc - 1));

          Operand* operand = new Operand(value, nestingLevel - 1, 0);
          items[startLoc] = operand;
        }
      }

      if (nestingLevel == 0)
      {
        break;
      }
    }

    assert(items.size() == 1);
    Operand* operand = dynamic_cast<Operand*>(items[0]);
    double result = operand->GetValue();
    delete operand;

    return result;
  }
}
