#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main() 
{
    FILE * fp;

    int i, j;
    int iStaddr, iRecLength;
    char name[10], line[50], name1[10], staddr[10], recLength[2];

    printf("Enter the program name : ");
    scanf("%s", name);
    printf("\n");

    fp = fopen("objProgram.txt", "r");
    fscanf(fp, "%s", line);

    for (i = 2, j = 0; i < 8; i++, j++)
        name1[j] = line[i];
    name1[j] = '\0';

    if (strcmp(name, name1) == 0) 
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s", line);
            if (line[0] == 'T') 
            {

                for (i = 2, j = 0; i < 8, j < 6; i++, j++)
                    staddr[j] = line[i];
                staddr[j] = '\0';
                iStaddr = atoi(staddr);

                i++; // ^ separator
                recLength[0]=line[i];
                i++;
                recLength[1]=line[i];
                i++;
                recLength[3]='\0';

                iRecLength=atoi(recLength);

                i++;// ^ separator

                while(iRecLength>0) 
                {
                    if (line[i] != '^') 
                    {
                        printf("00%d \t %c%c\n", iStaddr, line[i], line[i+1]);
                        iStaddr++;
                        i = i + 2;

                        iRecLength--; //1 byte
                    } 
                    else 
                        i++;
                }
            } 
            else if (line[0] = 'E')
            {
                for (i = 2, j = 0; i < 8; i++, j++)
                    staddr[j] = line[i];
                staddr[j] = '\0';
                iStaddr = atoi(staddr); //Moving to the start address specified in end record
            }
        } 
    }

    fclose(fp);

}
