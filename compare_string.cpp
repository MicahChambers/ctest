// comparing apples with apples
#include <iostream>
#include <string>

int main ()
{
  std::string str1 ("green apple");
  std::string str2 ("red apple");

  if (str1.compare(str2) != 0)
    std::cout << str1 << " is not " << str2 << '\n';


  if(str1.compare(6,5,"apple") == 0)
    std::cout << "a still, " << str1 << " is an apple\n";
  if(str1.compare(str1.size()-5,std::string::npos,"apple") == 0)
    std::cout << "b still, " << str1 << " is an apple\n";
  if(str1.compare(str1.size()-6,std::string::npos,"apple") == 0)
    std::cout << "c still, " << str1 << " is an apple\n";

  for(int ii=str1.size()-1; ii>= 0; ii--) {
	  std::cout << ii << " => " << str1[ii] << std::endl;
  }

  if (str2.compare(str2.size()-5,5,"apple") == 0)
    std::cout << "and " << str2 << " is also an apple\n";

  if (str1.compare(6,5,str2,4,5) == 0)
    std::cout << "therefore, both are apples\n";

  return 0;
}
