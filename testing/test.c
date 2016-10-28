#include <stdio.h>

unsigned char *testFunction()
{
  unsigned char *testChar2 = "Hello, World!";
  return testChar2;
}

int main()
{
  unsigned char *testChar;

  testChar = testFunction();

  printf("%s\n", testChar);
}
