#include <cassert>
#include <iostream>
#include <regex>

// Update the input string.
std::string expandEnvironmentVariables(const std::string& iText) {
  static const std::regex envRegex(
      R"xx(\$\{ *([a-zA-Z0-9_]*) *\}|\$([a-zA-Z0-9_]*))xx");

  std::string expanded = "";
  size_t finalPos = 0;
  for (auto it = std::sregex_iterator(iText.begin(), iText.end(), envRegex);
       it != std::sregex_iterator(); ++it) {
    const std::smatch& match = *it;
    expanded += match.prefix();
    finalPos = match.position() + match.length();

    assert(match.size() == 3);
    const char* envVar = nullptr;
    if (match[1].length() > 0) envVar = std::getenv(match[1].str().c_str());
    if (match[2].length() > 0) envVar = std::getenv(match[2].str().c_str());
    expanded += (envVar == NULL ? "" : envVar);
  }

  // add final suffix
  if (finalPos < iText.length()) {
    expanded += iText.substr(finalPos);
  }
  return expanded;
}

int main() {
  std::string toExpand =
      "a${HISTSIZE}b${ HISTSIZE }c${ HISTSIZE}d${ HISTSIZE}e$HISTSIZE f";
  std::string out = expandEnvironmentVariables(toExpand);
  std::cerr << toExpand << std::endl;
  std::cerr << out << std::endl;
}
