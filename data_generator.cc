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
  myfile.open ("example");
  for (size_t i = 0; i < 10; i++) {
    std::string str;
    for(int z=0; z < 5; z++){
    str +=  genRandom();
    }
    myfile << str << "   " << rand()%20 << "\n";
  }

  myfile.close();
  return 0;


}
