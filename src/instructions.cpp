#include "instructions.hpp"
#include "utils/output.hpp"

std::vector<int> stack;
int p = 0;

void compareInstrns(std::vector<int> program) {
    outputln((int)program.size());
    for (int i = 0; i < program.size(); i++) {
        switch (program[p]) {
            case 0x00:
                outputln("0x00");
                exit(0);
                break;
            case 0x01:
                outputln("0x01");
                p++;
                break;
            case 0x02:
                outputln("0x02");
                p--;
                break;
            case 0x03:
                outputln("0x03");
                stack[p]++;
                break;
            case 0x04:
                outputln("0x04");
                stack[p]--;
                break;
            case 0x05:
                outputln("0x05");
                //  Set the variable into the value of the specified position relative to current position   
                int jmpTo = stack[p+1]; // Jump if condition is true/matches
                int pos   = stack[p+2]; // Position of target bit we are trying to check 
                int bit   = stack[p+3]; // what we are looking for within the pos

                if (stack[pos] == bit) {
                    p = jmpTo;
                } else {
                    p += 4;
                }
                break;
        }
    }
}