/*
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "loader.h"
#include "LC4.h"

#define MAX_ENTRIES 65536
unsigned short LC4_mem[MAX_ENTRIES];

void clearMemory() {
  //Clear all LC4 memory to 0
  for (int i = 0; i < MAX_ENTRIES; i++) {
    LC4_mem[i] = 0;
  }
}

int main (int argc, char* argv[])
{
  int numSkip;
  int pastMax = 0;
  int curMax = 0;

  int new_size;
  openFile(argv[1]);
  for (int j = 2; j < argc; j++) {
    clearMemory();
    new_size = memWrite(argv[j], LC4_mem);
  
  int curMax = new_size;
  for (int i = 0; i < curMax; i++) {
      char *str;
      numSkip = 0;
      unsigned short currentEntry = LC4_mem[i];
      if (currentEntry != 0) {
        printf("currentEntry:%04X : memory num: %d\n", LC4_mem[i], i);
        if (currentEntry == 50103) {
        //hit symbol header
          //
           numSkip = LC4_mem[i+2]/2;
        }
        else if (currentEntry == 61822) {
        //hit file name header
           numSkip = LC4_mem[i+1]/2;
        }
        else if (currentEntry == 29022) {
        //hit line number header
           numSkip = 3;
        }
        else if (currentEntry == 56026 || (extract(currentEntry,0,8) == 218 && (extract(LC4_mem[i+1],8,16) == 218))) {
         //if current word is DADA or ??DA DA??

          numSkip = LC4_mem[i+2];
          for (int instNum = 0; instNum < LC4_mem[i+2]; instNum++) {
            decodeDADA(LC4_mem[i+3+instNum], LC4_mem[i+1]+instNum+3);
          }
        }
	      else if (currentEntry == 51934 || (extract(currentEntry,0,8) == 202 && (extract(LC4_mem[i+1],8,16) == 222))) {
          //if current word is CADE or ??CA DE??
	       numSkip = LC4_mem[i+2];
	       for (int instNum = 0; instNum < LC4_mem[i+2]; instNum++) {
	        decodeInstruction(LC4_mem[i+3+instNum], LC4_mem[i+1]+3+instNum);
	        //decodeInstruction takes in one instruction at at time, with instructions starting 3 elements 
          //from the CADE marker
	       }

	      }
        
	      i+= numSkip;
      }
   } 
  }
  close();
  return 0;
}

