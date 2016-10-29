#include <stdio.h>

void listDirectory(*char directoryName)
{

}

void listFile(*char filename)
{

}

void listSingleItem(*char filename)
{
  //need to open the current section here or pass it in
  char fileSelection[11];
  int position = 0x00;
  int i;
  char fileType;
  int condition = 0 ; //1 is found 0 is no such file -1 is doesn't exist
  
  do
    {
      for(i = 0; i < 11; i++)
	{
	  fileSelection[i] = currentDir[position + i];
	}

      if(fileSelection == filename)
	{
	  fileType = currentDir[position + 0x0B];
	  if(fileType == 0x10)
	    {
	      listDirectory(filename);
	    }
	  else
	    {
	      listFile(filename);
	    }
	  condition = 1;
	}
      else if(fileSelection[0] == 0x00 | fileSelection[0] == 0xF6)
	{
	  condition = -1;
	}
      else
	{
	  position = postion + 0x20;
	}
    }while(condition == 0);
  
}

void listAllFiles()
{
  //need to open the current section here or pass it in
  
}


int main(int argc, char *argv[])
{
  
  if(argc > 2)
    {
      printf("Too many elements.");
    }
  else if(argc == 2)
    {
      listSingleFile(argv[1]);
    }
  else
    {
      listAllFiles();
    }

  return 0;
}
