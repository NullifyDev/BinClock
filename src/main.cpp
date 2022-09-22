#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

#include "utils/output.hpp"
#include "utils/split.hpp"
#include "utils/files.hpp"
#include "utils/string.hpp"
#include "instructions.hpp"
#include "lexer/lexer.hpp"

int main() {
    using namespace std;
    outputln("[Insert Script]");
    string iscript;
    getline(cin, iscript);

    if (StartsWith(iscript, "file:")) {
        string icode = ReadFile(iscript.substr(5,iscript.size()-5));
        string code;
        for (int i = 0; i < icode.size(); i++) 
        {
            switch ((int)icode[i]) {
                case 10:
                case 44:
                    code += ' ';
                    break;
            }
            if ((int)icode[i] == 10) {
                    code += ' ';
            } else {
                code += (char)icode[i];
            }
        }
        outputln("[Result 1]");
        outputln(code);

        // file:script.mc
        // file:src/yes.mc

        int space = 0;
        for (int i = 0; i < code.size(); i++) {
            outputln(i + ": " + code[i]);
            if (int(code[i]) == 32) {
                space+=1;
            } else {
                if (space > 1) {
                    // outputln("More than one space found");
                    // code.erase(i-space-1 , space-1);
                    // outputln(i + " " + space);
                    // outputln(code);
                }
            }
        }
        outputln("[Result 2]");
        outputln(code);
    }
    if (iscript == "") {
        // clear();
        // outputln("Error: no script provided. Please enter a script and try again");
        // outputln("");
        // main();
    }

    vector<char *> items = SplitStr(iscript.c_str(), " ");
    vector<int> program;
    
    for (int i = 0; i < items.size(); i++) { program.push_back(strtol(items[i], NULL, 16)); }
    // outputln("[Executing...]");
    // compareInstrns(program);
    return 0;
}