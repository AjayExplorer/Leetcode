#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    int i, addr1, j, staddr1;
    char name[10], line[50], name1[10], addr[10], rec[10], ch, staddr[10];

    printf("Enter program name: ");
    scanf("%s", name);

   fp = fopen("C:\\Users\\HP\\Desktop\\Leetcode\\mpmcprogram\\objectcode.txt", "r");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fscanf(fp, "%s", line); // Read header record

    for (i = 2, j = 0; i < 8 && j < 6; i++, j++)
        name1[j] = line[i];
    name1[j] = '\0';

    printf("Name from obj: %s\n", name1);

    if (strcmp(name, name1) == 0) {
        while (fscanf(fp, "%s", line) != EOF) {
            if (line[0] == 'T') {
                for (i = 2, j = 0; i < 8 && j < 6; i++, j++)
                    staddr[j] = line[i];
                staddr[j] = '\0';
                staddr1 = atoi(staddr);

                i = 12;
                while (line[i] != '$' && line[i] != '\0') {
                    if (line[i] != '^') {
                        printf("00%d\t%c%c\n", staddr1, line[i], line[i + 1]);
                        staddr1++;
                        i += 2;
                    } else {
                        i++;
                    }
                }
            } 
            else if (line[0] == 'E') {
                printf("Jump to execution address %s\n", &line[2]);
                break; // ✅ stop after End record
            }
        }
    } else {
        printf("Program name mismatch!\n");
    }

    fclose(fp);
    return 0;
}