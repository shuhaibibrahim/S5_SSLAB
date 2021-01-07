#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main() 
{
    FILE *f1, *f2, *f3, *f4;

    int lc, sa, l, op1, value, len;
    char opcode[20], label[20], op[20], opc[20]; //op & op1 are operands

    int symValue;
    char symLabel[20];
    f1= fopen("input.txt", "r");
    f3= fopen("symtab.txt", "w+");
    f4= fopen("intermediate.txt","w");
    fscanf(f1, "%s %s %d", label, opcode, &op1);

    if (strcmp(opcode, "START") == 0) 
    {
        sa = op1;
        lc = sa;
        fprintf(f4,"\t%s\t%s\t%d\n", label, opcode, op1);
    } 
    else
        lc = 0;

    fscanf(f1, "%s %s", label, opcode);
    while (!feof(f1)) 
    {
        fscanf(f1, "%s", op);

        fprintf(f4,"%d\t%s\t%s\t%s\n", lc, label, opcode, op);
        if (strcmp(label, "-") != 0) 
        {
            fseek(f3, SEEK_SET, 0);
            fscanf(f3, "%d %s", &symValue, symLabel);
            while (!feof(f3)) 
            {
                if (strcmp(symLabel, label) == 0) 
                {
                    printf("\nError... %s is defined more than one time",label);
                    exit(1);
                }
                fscanf(f3, "%d %s", &symValue, symLabel);
            }

            fprintf(f3, "%d\t%s\n", lc, label);
        }

        f2 = fopen("optab.txt", "r");
        fscanf(f2, "%s %d", opc, &value);
        while (!feof(f2)) 
        {
            if (strcmp(opcode, opc) == 0) 
            {
                lc = lc + 3;
                break;
            }
            fscanf(f2, "%s %d", opc, &value);
        }
        fclose(f2);

        if (strcmp(opcode, "WORD") == 0)
        {
            lc = lc + 3;
        } 
        else if (strcmp(opcode, "RESW") == 0) 
        {
            op1 = atoi(op);
            lc = lc + (3 * op1);
        } 
        else if (strcmp(opcode, "BYTE") == 0) 
        {
            if (op[0] == 'X')
                lc = lc + 1;
            else 
            {
                len = strlen(op) - 3;
                lc = lc + len;

		printf("    len=%d  op=%s  ",len,op);
            }
        } 
        else if (strcmp(opcode, "RESB") == 0) 
        {
            op1 = atoi(op);
            lc = lc + op1;
        }
        fscanf(f1, "%s %s", label, opcode);
    }
    if (strcmp(opcode, "END") == 0) 
    {
        printf("\nProgram length = %d\n", lc - sa);
    }
    fclose(f1);
    fclose(f3);
    fclose(f4);
}
