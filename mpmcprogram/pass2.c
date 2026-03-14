#include <stdio.h>     // For standard input/output functions
#include <string.h>    // For string handling functions like strcmp(), strcpy(), strcat()
#include <stdlib.h>    // For atoi(), sprintf(), etc.

int main() {           // Main function starts
    // Declaration of variables
    char opcode[20], operand[20], symbol[20], label[20]; // For storing instruction parts
    char code[20], mnic[25], chr, add[20], objcode[20];  // For opcode table data, address, and final object code
    int flag, flag1, locctr, location, loc;               // Flags and address counters

    // Declaration of file pointers
    FILE *fp1, *fp2, *fp3, *fp4;

    // Opening required files
    fp1 = fopen("C:\\Users\\HP\\Desktop\\Leetcode\\mpmcprogram\\out1.txt", "r");   // Intermediate file (output of Pass 1)
    fp2 = fopen("C:\\Users\\HP\\Desktop\\Leetcode\\mpmcprogram\\out2.txt", "w");   // Output file (object code)
    fp3 = fopen("C:\\Users\\HP\\Desktop\\Leetcode\\mpmcprogram\\opcode.txt", "r"); // Opcode table file
    fp4 = fopen("C:\\Users\\HP\\Desktop\\Leetcode\\mpmcprogram\\sym1.txt", "r");   // Symbol table file

    // Error handling if files not found
    if (!fp1 || !fp2 || !fp3 || !fp4) {
        printf("Error opening one or more files!\n");
        return 1;  // Exit if any file could not be opened
    }

    // Read the first line from Pass 1 output (may contain START directive)
    fscanf(fp1, "%s %s %s", label, opcode, operand);

    // If the first line contains the START directive
    if (strcmp(opcode, "START") == 0) {
        // Write the START line as it is to output file
        fprintf(fp2, "%s\t%s\t%s\n", label, opcode, operand);

        // Then read the next line (which contains actual first instruction)
        fscanf(fp1, "%d %s %s %s", &locctr, label, opcode, operand);
    }

    // Loop continues until END opcode is found
    while (strcmp(opcode, "END") != 0) {

        flag = 0;           // Reset flag before checking opcode
        rewind(fp3);        // Move to beginning of opcode table

        // Read one opcode and its machine code (mnemonic) from opcode.txt
        while (fscanf(fp3, "%s %s", code, mnic) != EOF) {
            // If opcode from program matches opcode table entry and mnemonic is not "*"
            if (strcmp(opcode, code) == 0 && strcmp(mnic, "*") != 0) {
                flag = 1;   // Opcode found
                break;      // Exit loop
            }
        }

        // ✅ If opcode was found in opcode table
        if (flag == 1) {
            flag1 = 0;          // Reset flag1
            rewind(fp4);        // Move to start of symbol table file

            // Search operand in symbol table (to get its address)
            while (fscanf(fp4, "%d %s", &loc, symbol) != EOF) {
                if (strcmp(symbol, operand) == 0) {
                    flag1 = 1;  // Operand found in symbol table
                    break;      // Stop searching
                }
            }

            if (flag1 == 1) {
                // Convert integer address to string
                sprintf(add, "%d", loc);

                // Object code = opcode mnemonic + operand address
                strcpy(objcode, mnic);
                strcat(objcode, add);
            } else {
                // If operand not found, just copy mnemonic
                strcpy(objcode, mnic);
            }
        }

        // ✅ If opcode is BYTE or WORD (data definitions)
        else if (strcmp(opcode, "BYTE") == 0 || strcmp(opcode, "WORD") == 0) {
            // BYTE operand format could be like C'X' or X'F1'
            if (operand[0] == 'C' || operand[0] == 'X') {
                chr = operand[2];        // Take the character constant
                sprintf(add, "%x", chr); // Convert it to hexadecimal
                strcpy(objcode, add);    // Copy it to object code
            } else {
                // If it’s numeric (e.g., WORD 10)
                strcpy(objcode, operand);
            }
        }

        // ✅ For directives like RESW or RESB (no object code generated)
        else {
            strcpy(objcode, " "); // Empty object code
        }

        // Write the generated line to output file (Pass 2 output)
        fprintf(fp2, "%s\t%s\t%s\t%d\t%s\n", label, opcode, operand, locctr, objcode);

        // Read next line from Pass 1 output
        if (fscanf(fp1, "%d %s %s %s", &locctr, label, opcode, operand) == EOF)
            break; // Stop if end of file reached
    }

    // Write the END line at the end of Pass 2 output
    fprintf(fp2, "%s\t%s\t%s\t%d\n", label, opcode, operand, locctr);

    // Close all files
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    printf("✅ Pass 2 completed successfully. Output written to out2.txt\n");
    return 0;
}
