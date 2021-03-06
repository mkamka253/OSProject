#include <stdio.h>
#include <fatSupport.h>
#define SECTOR_SIZE = 512;
#define SUPER_VAR_SECTOR = 2722;

extern int read_sector(int sector_number, char* buffer);
/*
char findCurrentDirectory(int directoryPosition)
{
  int rootAddress;
  int currentSectorNum;
  int previousSectorNum;
  int regularDirectory;
  int holder; //manages sector numbers
  int sectorChecker; //hold the hex value of the current sector to look for the former name
  char fullString[]; //holds on to the string of the current directory
  int found; //changes when the name of the previous sector is found, or there is an error
  char holderChar;
  unsigned char *currentSector;
  rootAddress = 19; //for finding the root and checking if we are already there
  dataEntries = 32; //Because this is basically where the data sectors start
  found = 0;

  currentSectorNum = directoryPosition;
  while(currentSectorNum != rootAddress)
    {
      /* currentSector = (unsigned char*) malloc(SECTOR_SIZE *
	   sizeof(unsigned char));

      if(read_sector(currentSectorNum, currentSector) == -1)
	{
	  printf("The sector you are trying to access is broken.");
	}	
*//*
      currentSector = sectorOpener(currentSector, currentSectorNum);
      holder = ((int) currentSector[0x3A]);
      previousSectorNum = currentSectorNum;
      if(holder == 0)
	{
	  currentSectorNum = rootAddress;
	}
      else
	{
	  currentSectorNum = holder + dataEntry;
	}

      currentSector = sectorOpener(currentSector, currentSectorNum);
      sectorChecker = 0x1A;

      while(found == 0)
	{
	  holder = ((int) currentSector[sectorChecker]);
	  if(holder == previousSectorNum)
	    {
	      sectorChecker = sectorChecker - 0x1A;
	      int i;
	      for(i = 0; i < 8; i++)
		{
		  holderChar = currentSector[sectorChecker + i];
		  fullString = fullString + holderChar; 
		}
	      fullString = fullStirng + "/";
	      found = 1;
	    }
	  else 
	    {
	      sectorChecker = sectorChecker + 0x20;
	    }

	  if(currentSector[sectorChecker - 0x1A] == 0)
	    {
	      found == -1;
	      printf("The directory you are searching for doesn't exist.";
	    }
	}
    }
}
*/
unsigned char *sectorOpener(unsigned char *currentSector, int currentSectorNum)
{
  currentSectror = (unsigned char*) malloc(SECTOR_SIZE * sizeof(unsigned char));

  if(read_sector(currentSectorNum, currentSector) == -1)
    {
      printf("The sector you are trying to access is broken.");
    }

  return currentSector;
}

unsigned char *findCurrentDirectory(unsigned char *currentSector)
{
  char retrieved[1000];
  char retrieving = "0";
  int stringLocation = 0;
  int location = 0x20;
  while(retreiving != 0xF6);
  {
    retreiving = currentSector[location];
    retrieved[location] = retrieving;
    stringLocation++;
  }

  return retrieved;
}

int main(int argc, char *argv[]){
  
  
  if(argc != 1)
    {
      printf("Error: to many inputs.");
      return -1;
    }
  else
    {
      unsigned char *currentSector;
      char output[1000];

      currentSector = sectorOpener(currentSector, SUPER_VAR_SECTOR);
      output = findCurrentDirectory(currentSector);
      printf("%s", output);
    }
  return 0;
}
