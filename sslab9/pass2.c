#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() 
{
    FILE * fint, * ftab, * flen, * fsym;
    int i, len, foundSym=0;

    char add[5], symadd[5], op[5], start[10], label[20];
    char mne[10], operand[10], symtab[10], opmne[10];

    fint = fopen("input.txt", "r");
    ftab = fopen("optab.txt", "r");
    fsym = fopen("symtab.txt", "r");
    fscanf(fint, "%s %s %s %s", add, label, mne, operand);
    if (strcmp(mne, "START") == 0) 
    {
        strcpy(start, operand);
    }
    printf("H^%s^%s^%d\nT^00%s^", label, start, len, start);
    fscanf(fint, " %s %s %s %s", add, label, mne, operand); 
    while (strcmp(mne,"END")!=0 && !feof(fint)) 
    {
        foundSym=0;
        fscanf(ftab, "%s %s", opmne, op);
        while (!feof(ftab)) 
        {
            if (strcmp(mne, opmne) == 0) 
            {
                fscanf(fsym, "%s %s", symadd, symtab);
                while (!feof(fsym)) 
                {
                    if (strcmp(operand, symtab) == 0) 
                    {
                        printf("%s%s^", op, symadd);
                        foundSym=1;
                        break;
                    }
                    fscanf(fsym, "%s %s", symadd, symtab);
                }
                if(!foundSym)
                {
                    printf("\nError... symbol not found");
                    exit(1);
                }
                break;
            } 
            fscanf(ftab, "%s %s", opmne, op);
        }

        if ((strcmp(mne, "BYTE") == 0) || (strcmp(mne, "WORD") == 0)) 
        {
            if (strcmp(mne, "WORD") == 0)
                printf("0000%s^", operand);
            else 
            {
                len = strlen(operand);
                for (i = 2; i < len-1; i++) 
                {
                    printf("%d", operand[i]);
                }
                printf("^");
            }
        }

        fscanf(fint, "%s %s %s %s", add, label, mne, operand);

        fseek(ftab, SEEK_SET, 0);
        fseek(fsym, SEEK_SET, 0);

    }
    printf("\nE^00%s\n", start);
    fclose(fint);
    fclose(ftab);
    fclose(fsym);
}
