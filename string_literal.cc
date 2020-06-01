#include <iostream>
#include <string>

template <int N>
void foo(const char input[N]) {
  std::cerr << input << std::endl;
}

int main() {
  // char* str1 = "str1";
  std::string str2 = "str2";
  const auto str3 = "str3";
  // foo(str1);
  // foo(str2.c_str());
  // foo(str3);
}
