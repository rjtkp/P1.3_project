#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

// using namespace std;

static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char genRandom()  // Random string generator function.
{

    return alphanum[rand() % stringLength];
}

int main()
{
  std::fstream myfile;
  srand(time(0));
  int n;
  std::cout << "Enter the number of data that you want to generate" << '\n';
  std::cin >> n;
  std::ofstream outfile ("example");
  for (int i = 0; i < n; i++) {
    std::string str;
    for(int z=0; z < 5; z++){
    str +=  genRandom();
    }
    outfile << rand()%20 << "   " << str << "\n";
  }

  outfile.close();
  return 0;
}
