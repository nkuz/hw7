/*
 * Simple test of formatted input/output
 */

#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

#include "LC4.h"

int address;
char *str;
FILE *outFile;
char *Name;

void openFile(char *fileName) {
  outFile = fopen (fileName, "wb");
  if (outFile == NULL) {
    printf ("Couldn't open file\n");
  }
  Name = fileName;
}

void close() {
  fclose(outFile);
}

void decodeInstruction(unsigned short currInst, int addr)
{

   address = addr-3;
  findMatchingLC4Instruction(currInst);
}

void decodeDADA(unsigned short currInst, int addr) {
  address = addr-3;


  if (currInst != 0) {
    str = malloc(sizeof(char)*(11));
    //sprintf(str,"%04X : %04X\n", address, currInst);
    fprintf(outFile,"%04X : %04X\n", address, currInst);
   // printf("%s", str);
    free(str);
  }


}

void findMatchingLC4Instruction(unsigned short currInst) {
if (currInst != 0) {
  printf("%u\n", currInst);
  if (extract(currInst, 12, 16) == 0) {
  //BR instruction
  signed short offset;
  char *instruction;
  int instLength;
    if (extract(currInst, 9, 12) == 0) {
    //NOP instruction
      instruction = "NOP";
    }
    else if (extract(currInst, 9, 12) == 1) {
    //BRP instruction
      instruction = "BRp";
    }
    else if (extract(currInst, 9, 12) == 2) {
    //BRz instruction
      instruction = "BRz";
    }
    else if (extract(currInst, 9, 12) == 3) {
    //BRzp instruction 
      instruction = "BRzp";
      offset = getOffset(currInst);
      
    }
    else if (extract(currInst, 9, 12) == 4) {
    //BRn instruction
      instruction = "BRn";
    }
    else if (extract(currInst, 9, 12) == 5) {
    //BRnp instruction
      instruction = "BRnp";
    }
    else if (extract(currInst, 9, 12) == 6) {
    //BRnz instruction
      instruction = "BRnz";
    }
    else if (extract(currInst, 9, 12) == 7) {
    //BRnzp instruction
      instruction = "BRnzp";
    }
    if (strcmp(instruction, "NOP") != 0) {
      offset = getOffset(currInst);
    }
    instLength = strlen(instruction);
   // str = malloc(sizeof(char)*(20+instLength));
   // sprintf(str,"%04X : %04X -> %s #%d \n", address, currInst, instruction, offset);
    fprintf(outFile,"%04X : %04X -> %s #%d\n", address, currInst, instruction, offset);
  }
  else if (extract(currInst, 12, 16) == 1) {
  //Arithmetic instruction
    char *instruction;
    int isIm = 0;
    if (extract(currInst, 3, 6) == 0) {
    //ADD instruction 
      instruction = "ADD";
    }
    else if (extract(currInst, 3, 6) == 1) {
    //MUL instruction
      instruction = "MUL";
    }
    else if (extract(currInst, 3, 6) == 2) {
    //SUB instruction
      instruction = "SUB";
    }
    else if (extract(currInst, 3, 6) == 3) {
    //DIV instruction
      instruction = "DIV";
    }
    else {
    //ADD (Imm5) instruction
      instruction = "ADD";
      isIm = 1;
    }
    int Rd, Rs;
    Rd = extract(currInst, 9, 12);
    Rs = extract(currInst, 6, 9);
    if (isIm == 0) {
      int Rt = extract(currInst, 0, 3);
      int instLength = strlen(instruction);
    //  str = malloc(sizeof(char)*(24+instLength));
    //  sprintf(str,"%04X : %04X -> %s R%d, R%d, R%d \n", address, currInst, instruction, Rd, Rs, Rt);
      fprintf(outFile,"%04X : %04X -> %s R%d, R%d, R%d\n", address, currInst, instruction, Rd, Rs, Rt);
    }
    else {
      signed short offset;
      if (extract(currInst, 4, 5) == 1) {
        offset = ~(extract(~currInst, 0, 5));
      }
      else {
        offset = (extract(currInst, 0, 5));
      } 
      int instLength = strlen(instruction);
    //  str = malloc(sizeof(char)*(24+instLength));
    //  sprintf(str,"%04X : %04X -> %s R%d, R%d, #%d \n", address, currInst, instruction, Rd, Rs, offset); 
      fprintf(outFile,"%04X : %04X -> %s R%d, R%d, #%d\n", address, currInst, instruction, Rd, Rs, offset);   
    }
  }
  else if ((extract(currInst, 12, 16) == 10) && (extract(currInst, 4, 6) == 3)) {
    //Mod instruction
    int Rd, Rs, Rt;
    char *instruction = "MOD";
    Rd = extract(currInst, 9, 12);
    Rs = extract(currInst, 6, 9);
    Rt = extract(currInst, 0, 3);
   // str = malloc(sizeof(char)*(29));
   // sprintf(str,"%04X : %04X -> %s R%d, R%d, #%d \n", address, currInst, instruction, Rd, Rs, Rt);
    fprintf(outFile,"%04X : %04X -> %s R%d, R%d, #%d\n", address, currInst, instruction, Rd, Rs, Rt);
  }
  else if (extract(currInst, 12, 16) == 5) {
  //Logical instruction
    char *instruction;
    int hasRt = 1;
    if (extract(currInst, 3, 6) == 0) {
    //AND instruction 
      instruction = "AND";
    }
    else if (extract(currInst, 3, 6) == 1) {
    //NOT instruction
      instruction = "NOT";
      hasRt = 0;
    }
    else if (extract(currInst, 3, 6) == 2) {
    //OR instruction
      instruction = "OR";
    }
    else if (extract(currInst, 3, 6) == 3) {
    //XOR instruction
      instruction = "XOR";
    }
    else {
    //AND instruction
      instruction = "AND";
      hasRt = 0;
    }
    int Rd, Rs;
    Rd = extract(currInst, 9, 12);
    Rs = extract(currInst, 6, 9);
    if (hasRt == 1) {
      int Rt = extract(currInst, 0, 3);
      int instLength = strlen(instruction);
    //  str = malloc(sizeof(char)*(24+instLength));
    //  sprintf(str,"%04X : %04X -> %s R%d, R%d, R%d \n", address, currInst, instruction, Rd, Rs, Rt);
      fprintf(outFile,"%04X : %04X -> %s R%d, R%d, R%d\n", address, currInst, instruction, Rd, Rs, Rt);
    }
    else {
      if (strcmp(instruction, "AND") == 0) {
        signed short offset;
        if (extract(currInst, 4, 5) == 1) {
          offset = ~(extract(~currInst, 0, 5));
        }
        else {
          offset = (extract(currInst, 0, 5));
        } 
        int instLength = strlen(instruction);
       // str = malloc(sizeof(char)*(24+instLength));
       // sprintf(str,"%04X : %04X -> %s R%d, R%d, #%d \n", address, currInst, instruction, Rd, Rs, offset);
        fprintf(outFile,"%04X : %04X -> %s R%d, R%d, #%d\n", address, currInst, instruction, Rd, Rs, offset);
      }    
      else {
	int instLength = strlen(instruction);
      //  str = malloc(sizeof(char)*(21+instLength));
     //   sprintf(str,"%04X : %04X -> %s R%d, R%d\n", address, currInst, instruction, Rd, Rs);
        fprintf(outFile,"%04X : %04X -> %s R%d, R%d\n", address, currInst, instruction, Rd, Rs);
      } 
    }
  }
  else if (extract(currInst, 12, 16) == 6) {
  //LDR instruction
    char *instruction = "LDR";
    int Rd = extract(currInst, 9, 12);
    int Rs = extract(currInst, 6, 9);
    signed short offset;
    if (extract(currInst, 5, 6) == 1) {
      offset = ~(extract(~currInst, 0, 6));
    }
    else {
      offset = (extract(currInst, 0, 6));
    } 
   // str = malloc(sizeof(char)*(28));
   // sprintf(str,"%04X : %04X -> %s R%d, R%d, #%d \n", address, currInst, instruction, Rd, Rs, offset);
    fprintf(outFile,"%04X : %04X -> %s R%d, R%d, #%d\n", address, currInst, instruction, Rd, Rs, offset);
  }
  else if (extract(currInst, 12, 16) == 7) {
  //STR instruction
    char *instruction = "STR";
    int Rt = extract(currInst, 9, 12);
    int Rs = extract(currInst, 6, 9);
    signed short offset;
    if (extract(currInst, 5, 6) == 1) {
      offset = ~(extract(~currInst, 0, 6));
    }
    else {
      offset = (extract(currInst, 0, 6));
    } 
   // str = malloc(sizeof(char)*(28));
   // sprintf(str,"%04X : %04X -> %s R%d, R%d, #%d \n", address, currInst, instruction, Rt, Rs, offset);
    fprintf(outFile,"%04X : %04X -> %s R%d, R%d, #%d\n", address, currInst, instruction, Rt, Rs, offset);
  }
  else if (extract(currInst, 12, 16) == 9) {
  //CONST instruction
    char *instruction = "CONST";
    int Rd = extract(currInst, 9, 12);
    signed short offset = getOffset(currInst);
  //  str = malloc(sizeof(char)*(29));
  //  sprintf(str,"%04X : %04X -> %s R%d, #%d \n", address, currInst, instruction, Rd, offset);
    fprintf(outFile,"%04X : %04X -> %s R%d, #%d\n", address, currInst, instruction, Rd, offset);
  }
  else if (extract(currInst, 12, 16) == 13) {
  //HICONST instruction
    char *instruction = "HICONST";
    int Rd = extract(currInst, 9, 12);
    unsigned short offset = (extract(currInst, 0, 8));
   // str = malloc(sizeof(char)*(31));
   // sprintf(str,"%04X : %04X -> %s R%d, #%d \n", address, currInst, instruction, Rd, offset);
    fprintf(outFile,"%04X : %04X -> %s R%d, #%d\n", address, currInst, instruction, Rd, offset);
  }
  else if (extract(currInst, 12, 16) == 2) {
  //Comparison instruction
    int Rs = extract(currInst, 9, 12);
    char *instruction;
    if (extract(currInst, 7, 9) == 0) {
    //CMP instruction
      instruction = "CMP";
      int Rt = extract(currInst, 0, 3);
    //  str = malloc(sizeof(char)*(27));
    //  sprintf(str,"%04X : %04X -> %s R%d, #%d \n", address, currInst, instruction, Rs, Rt);
      fprintf(outFile,"%04X : %04X -> %s R%d, R%d\n", address, currInst, instruction, Rs, Rt);
    }
    else if (extract(currInst, 7, 9) == 1) {
    //CMPU instruction
      instruction = "CMPU";
      int Rt = extract(currInst, 0, 3);
      //str = malloc(sizeof(char)*(28));
      //sprintf(str,"%04X : %04X -> %s R%d, #%d \n", address, currInst, instruction, Rs, Rt);
      fprintf(outFile,"%04X : %04X -> %s R%d, R%d\n", address, currInst, instruction, Rs, Rt);
    }
    else if (extract(currInst, 7, 9) == 2) {
    //CMPI instruction
      instruction = "CMPI";
      signed short offset;
      if (extract(currInst, 6, 7) == 1) {
        offset = ~(extract(~currInst, 0, 7));
      }
      else {
        offset = (extract(currInst, 0, 7));
      }
      //str = malloc(sizeof(char)*(28));
      //sprintf(str,"%04X : %04X -> %s R%d, #%d \n", address, currInst, instruction, Rs, offset);
      fprintf(outFile,"%04X : %04X -> %s R%d, #%d\n", address, currInst, instruction, Rs, offset);
    }
    else if (extract(currInst, 7, 9) == 3) {
    //CMPIU instruction
      instruction = "CMPIU";
      unsigned short offset = (extract(currInst, 0, 7));
     // str = malloc(sizeof(char)*(29));
    //  sprintf(str,"%04X : %04X -> %s R%d, #%d \n", address, currInst, instruction, Rs, offset);
      fprintf(outFile,"%04X : %04X -> %s R%d, #%d\n", address, currInst, instruction, Rs, offset);
    }
  }
  else if (extract(currInst, 12, 16) == 10) {
  //Shift instruction
    int Rd = extract(currInst, 9, 12);
    int Rs = extract(currInst, 6, 9);
    int UI = extract(currInst, 0, 4);
    char *instruction;
    if (extract(currInst, 4, 6) == 0) {
    //SLL instruction
      instruction = "SLL";
    }
    else if (extract(currInst, 4, 6) == 1) {
    //SRA instruction
      instruction = "SRA";
    }
    else if (extract(currInst, 4, 6) == 2) {
    //SRL instruction
      instruction = "SRL";
    }
   // str = malloc(sizeof(char)*(31));
   // sprintf(str, "%04X : %04X -> %s R%d, R%d, #%d \n", address, currInst, instruction, Rd, Rs, UI);
    fprintf(outFile, "%04X : %04X -> %s R%d, R%d, #%d\n", address, currInst, instruction, Rd, Rs, UI);
  }
  else if (extract(currInst, 12, 16) == 4) {
  //JSR & JSRR instruction
    char *instruction;
    if (extract(currInst, 11, 12) == 0) {
      instruction = "JSRR";
      int Rs = extract(currInst, 6, 9);
     // str = malloc(sizeof(char)*(22));
    //  sprintf(str,"%04X : %04X -> %s R%d\n", address, currInst, instruction, Rs);
      fprintf(outFile,"%04X : %04X -> %s R%d\n", address, currInst, instruction, Rs);
    }
    else {
      instruction = "JSR";
      signed short offset;
      if (extract(currInst, 10, 11) == 1) {
        offset = ~(extract(~currInst, 0, 11));
      }
      else {
        offset = (extract(currInst, 0, 11));
      }   
   //   str = malloc(sizeof(char)*(28));
   //   sprintf(str,"%04X : %04X -> %s #%d\n", address, currInst, instruction, offset); 
      fprintf(outFile,"%04X : %04X -> %s #%d\n", address, currInst, instruction, offset);   
    }
    
  }
  else if (extract(currInst, 12, 16) == 12) {
  //JMP instruction
    char *instruction;
    if (extract(currInst, 11, 12) == 0) {
      instruction = "JMPR";
      int Rs = extract(currInst, 6, 9);
      //str = malloc(sizeof(char)*(22));
     // sprintf(str,"%04X : %04X -> %s R%d\n", address, currInst, instruction, Rs);
      fprintf(outFile,"%04X : %04X -> %s R%d\n", address, currInst, instruction, Rs);
    }
    else {
      instruction = "JMP";
      signed short offset;
      if (extract(currInst, 10, 11) == 1) {
        offset = ~(extract(~currInst, 0, 11));
      }
      else {
        offset = (extract(currInst, 0, 11));
      }   
    //  str = malloc(sizeof(char)*(28));
    //  sprintf(str,"%04X : %04X -> %s #%d\n", address, currInst, instruction, offset);  
      fprintf(outFile,"%04X : %04X -> %s #%d\n", address, currInst, instruction, offset);   
    }
  }
  else if (extract(currInst, 12, 16) == 15) {
  //TRAP instruction
    char *instruction = "TRAP";
    unsigned short offset = (extract(currInst, 0, 8));
    //str = malloc(sizeof(char)*(22));
    //sprintf(str,"%04X : %04X -> %s #%d\n", address, currInst, instruction, offset); 
    fprintf(outFile,"%04X : %04X -> %s #%d\n", address, currInst, instruction, offset); 
  }
  else if (extract(currInst, 12, 16) == 8) {
  //RTI instruction
    char *instruction = "RTI";
    //printf("here");
    //str = malloc(sizeof(char)*(18));
   // sprintf(str,"%04X : %04X -> %s\n", address, currInst, instruction);  
    fprintf(outFile,"%04X : %04X -> %s\n", address, currInst, instruction); 
  }
  
    //  printf("%s", str);
    // free(str);
}
}


unsigned short extract(unsigned short value, int begin, int end)
{
    signed short mask = (1 << (end - begin)) - 1;
    return (value >> begin) & mask;
}

signed short getOffset(unsigned short currInst) {
  signed short offset;
  if (extract(currInst, 8, 9) == 1) {
    offset = ~(extract(~currInst, 0, 9));
  }
  else {
    offset = (extract(currInst, 0, 9));
  }
  return offset;
}

