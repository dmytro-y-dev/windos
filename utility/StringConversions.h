#ifndef TODOS_UTILITY_STRINGCONVERSIONS_H
#define TODOS_UTILITY_STRINGCONVERSIONS_H

#include <string>

namespace todos_utility {
  std::string IntToString(int value);
  int StringToInt(const std::string& str);
}

#endif //TODOS_UTILITY_STRINGCONVERSIONS_H
