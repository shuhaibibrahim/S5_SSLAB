#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 11
struct symbol 
{
    int add;
    char label[10];
}
symTab[11];

int hashKey(char c) 
{
    int key;
    key = c % 11;
    return key;
}

void display() 
{
    FILE * fp;
    int i;
    fp = fopen("symbol.txt", "w");
    printf("\nKey\tAddress\tLabel");
    for (i = 0; i < MAX; i++) 
    {
        if(symTab[i].add!=-1)
        {
            printf("\n%d\t %d\t %s", i, symTab[i].add, symTab[i].label);
            fprintf(fp, "\n%d %d %s", i, symTab[i].add, symTab[i].label);
        }
    }
    fclose(fp);
}

void AddToSym(int key, char l[], int add) //Linear Probing
{
    int i, count = 0;
    if (symTab[key].add == -1) 
    {
        symTab[key].add = add;
        strcpy(symTab[key].label, l);
        printf("Label added..\n");
    } 
    else
    {
        int spaceFound=0;
        for(int i=key+1;count<MAX-1;i=(i+1)%MAX)
        {
            if(symTab[i].add==-1)
            {
                spaceFound=1;
                symTab[i].add=add;
                strcpy(symTab[i].label,l);
                printf("Label added..\n");
                break;
            }
            count++;
        }
        if(!spaceFound)
        {
            printf("SymTab is full!!\n");
            display();
            exit(1);
        }
    }
}


void search() 
{
    char label[10];
    int key;

    printf("Enter the label : ");
    scanf(" %s",label);

    key=hashKey(label[0]);

    int count=0,found=0;
    for(int i=key;count<MAX;i=(i+1)%MAX)
    {
        if(strcmp(symTab[i].label,label)==0)
        {
            found=1;
            printf("Symbol : %s, Address : %d\n",symTab[i].label,symTab[i].add);
            break;
        }
        count++;
    }
    if(!found)
        printf("Symbol not found!!\n");
}

void main() 
{
    int add;
    char l[10];
    int key, i, ch;
    char ans;
    for (i = 0; i < MAX; i++)
        symTab[i].add=-1;

    printf("1.Add a symbol \n2.Search a symbol \n3.Display Symtab\n4.Exit");
    while(1) 
    {
        printf("\nEnter your choice : ");
        scanf(" %d", &ch);
        switch (ch) 
        {
            case 1: printf("\nEnter The label : ");
                    scanf("%s", l);

                    key = hashKey(l[0]);

                    printf("Enter the address : ");
                    scanf("%d", & add);
                    AddToSym(key,l,add);
                    break;
            case 2: search();
                    break;
            case 3: display();
                    break;
            case 4: exit(1);
        }
    }
}
