#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct dir
{
    char dirName[20];
    char files[10][20];
    int fileIndex;
};

int insert(char files[][20],char * name,int fileIndex)
{
    for(int i=0;i<fileIndex;i++)
    {
        if(strcmp(files[i],name)==0)
        {
            printf("File already exist...\n");
            return fileIndex;
        }
    }
    strcpy(files[fileIndex],name);
    fileIndex++;
    printf("File Created..\n");
    return fileIndex;
}

int delete(char files[][20],char * name,int fileIndex)
{
    for(int i=0;i<fileIndex;i++)
    {
        if(strcmp(files[i],name)==0)
        {
            strcpy(files[i],files[fileIndex--]);
            printf("File deleted..\n");
            return fileIndex;
        }
    }
    printf("File Not found...\n");
    return fileIndex;
}

int search(char files[][20],char * name,int fileIndex)
{
    for(int i=0;i<fileIndex;i++)
    {
        if(strcmp(files[i],name)==0)
        {
            printf("File Found...\n");
            return fileIndex;
        }
    }
    printf("File Not found...\n");
    return fileIndex;
}

void display(char dirName[],char files[][20],int fileIndex)
{
    int i;
    printf("%s\n",dirName);
    printf("-----------------------------\n");
    for(i=0;i<fileIndex;i++)
    {
        printf("%s ",files[i]);
    }
    printf("\n");
    if(i==0)
        printf("No files here...\n");
}
int main()
{

    int c;
    struct dir sld;
    sld.fileIndex=0;
    printf("Enter the Directory name : ");
    scanf("%[^\n]",sld.dirName);
    char name[20];

    printf("1.Create file\n2.Delete File\n3.Search File\n4.Diplay Directory\n5.Exit");
    while(1)
    {
        printf("\nEnter Your Choice : ");
        scanf("%d",&c);
        switch(c)
        {
            case 1: printf("File name to insert : ");
                    scanf(" %s",name);
                    sld.fileIndex=insert(sld.files,name,sld.fileIndex);
                    break;
            case 2: printf("File name to delete : ");
                    scanf(" %s",name);
                    sld.fileIndex=delete(sld.files,name,sld.fileIndex);
                    break;
            case 3: printf("File name to search : ");
                    scanf(" %s",name); 
                    sld.fileIndex=search(sld.files,name,sld.fileIndex);
                    break;
            case 4: display(sld.dirName,sld.files,sld.fileIndex);
                    break;
            case 5: exit(0);
        }
    }
    return 0;
}

