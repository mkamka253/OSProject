#include <stdio.h>

int main(int argc, char *argv[])
{
  char *fileSystem;
  char *currentDir;
  int currentSector;
  char dirName[8] = "        " ;
  int position = 0x00;//starting postion of 
  int fileIndicator; //This holds the check for if the found file is a directory or not
  int result; //for the do while loop 1 is found, -1 is error, 2 is doesn't exist 
  
  if(argc > 2)
    {
      printf("Wrong number of arguments.");
    }
  else if(argc == 1)
    {
      currentDir = "/";
      currentSector = 32;
      return 0;
    }

  int i;
  result = 0;
  do
    {
      for(i = 0; i < 8; i++)
	{
	  dirName[i] = currentDir[position+i];
	}
      fileIndicator = currentDir[position+0x10];

      if(dirName == argv[1])
	{
	  if(fileIndicator == 0x10)
	    {
	      result = 1;
	    }
	  else
	    {
	      result = -1;
	    }
	}
      else if(dirName[0] == 0x00 | dirName[0] == 0xF6)
	{
	  result = 2;
	}
      else
	{
	  position = position + 0x20;
	}
      }while(result == 0);

  
  if(result == 1)
    {
      int mostSignificantByte = (((int) currentDir[position+0x1B]) << 8);
      int leastSignificantByte = ((int) currentDir[position+0x1A]);
      currentSector = mostSignificantByte | leastSignificantByte;
      if(currentSector == 0)
	{
	  currentSector == 19;
	}
      else
	{
	  currentSector = currentSector + 19;
	}
    }
  else if(result == 2)
    {
      printf("There is no directory with that name.");
    }
  else if(result == -1)
    {
      printf("No file has this name.");
    }
  else
    {
      printf("What is Toronto?????");
    }

  //mmap stuff needs to go here.
  
  return 0;
}
