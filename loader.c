/*
 * Reading formatted text file
 */

#include <stdio.h>
#include <stdlib.h>


int memWrite(char *fileName, unsigned short LC4_mem[])
{
  FILE *objFile;
  unsigned char byte1, byte2;
  int i = 0;;
  //Open up a file for reading
  if ((objFile = fopen(fileName, "rb")) == NULL) {
    printf ("Couldn't open file for reading\n");
    exit(1);
  }

  // Read the bytes from the file one at a time until
  // you hit EOF
  // Print each line as it is read
  while (!feof(objFile) && i < 65536) {
    byte1 = fgetc(objFile);
    byte2 = fgetc(objFile);
    if (feof(objFile)) {
      LC4_mem[i] = byte1;
    }
    else {
      LC4_mem[i] = (byte1 << 8) | byte2;   
    }
    i++;
  } 
  fclose (objFile);
  return i;

}