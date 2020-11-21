/*
 * LC4.h
 */
void openFile(char *fileName);

void decodeInstruction(unsigned short CurrInst, int addr);

void findMatchingLC4Instruction(unsigned short currInst);

unsigned short extract(unsigned short value, int begin, int end);

signed short getOffset(unsigned short currInst);

void decodeDADA(unsigned short currInst, int addr);

void close();