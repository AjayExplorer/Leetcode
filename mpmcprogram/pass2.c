#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char opcode[20], operand[20], symbol[20], label[20];
    char code[20], mnic[25], chr, add[20], objcode[40];
    int flag, flag1, locctr, location, loc;

    FILE *fp1, *fp2, *fp3, *fp4;

    fp1 = fopen("C:\\Users\\HP\\Desktop\\Leetcode\\mpmcprogram\\out1.txt", "r");    // Intermediate file
    fp2 = fopen("C:\\Users\\HP\\Desktop\\Leetcode\\mpmcprogram\\out2.txt", "w");    // Output file
    fp3 = fopen("C:\\Users\\HP\\Desktop\\Leetcode\\mpmcprogram\\opcode.txt", "r");  // Opcode table
    fp4 = fopen("C:\\Users\\HP\\Desktop\\Leetcode\\mpmcprogram\\sym1.txt", "r");    // Symbol table  

    if (!fp1 || !fp2 || !fp3 || !fp4) {
        printf("Error opening one or more files.\n");
        return 1;
    }

    fscanf(fp1, "%s %s %s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        fprintf(fp2, "%-8s %-8s %-8s\n", label, opcode, operand);
        fscanf(fp1, "%d %s %s %s", &locctr, label, opcode, operand);
    }

    while (strcmp(opcode, "END") != 0) {
        flag = 0;
        flag1 = 0;
        strcpy(objcode, "");  // reset objcode for each line

        // --- Search in opcode table ---
        rewind(fp3);
        while (fscanf(fp3, "%s %s", code, mnic) != EOF) {
            if (strcmp(opcode, code) == 0) {
                flag = 1;
                break;
            }
        }

        // --- If opcode found in table ---
        if (flag == 1) {
            rewind(fp4);
            while (fscanf(fp4, "%d %s", &loc, symbol) != EOF) {
                if (strcmp(symbol, operand) == 0) {
                    flag1 = 1;
                    break;
                }
            }
            if (flag1 == 1) {
                sprintf(add, "%d", loc);
                strcpy(objcode, mnic);
                strcat(objcode, add);  // combine opcode + address
            } else {
                strcpy(objcode, mnic);
                strcat(objcode, "0000"); // default address if symbol not found
            }
        }
        // --- BYTE or WORD directives ---
        else if (strcmp(opcode, "BYTE") == 0) {
            if (operand[0] == 'C' && operand[1] == '\'') {
                // Convert character constant to hex
                sprintf(objcode, "%02X", operand[2]);
            } else if (operand[0] == 'X' && operand[1] == '\'') {
                // Directly use the hex value inside quotes
                strncpy(objcode, &operand[2], strlen(operand) - 3);
                objcode[strlen(operand) - 3] = '\0';
            }
        }
        else if (strcmp(opcode, "WORD") == 0) {
            sprintf(objcode, "%06d", atoi(operand));  // convert decimal to 6-digit
        }
        else {
            strcpy(objcode, "");  // no object code for RESW, RESB, etc.
        }

        fprintf(fp2, "%-8s %-8s %-8s %-8d %-8s\n",
                label, opcode, operand, locctr, objcode);

        fscanf(fp1, "%d %s %s %s", &locctr, label, opcode, operand);
    }

    fprintf(fp2, "%-8s %-8s %-8s %-8d\n", label, opcode, operand, locctr);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    printf("Pass 2 completed successfully. Output written to out2.txt\n");
    return 0;
}