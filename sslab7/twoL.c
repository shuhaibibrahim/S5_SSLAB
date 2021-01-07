#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct dir
{
    char dirName[20];
    char files[10][20];
    int fileIndex;
};

int insertDir(struct dir tld[],char * name,int dirIndex)
{
    for(int i=0;i<dirIndex;i++)
    {
        if(strcmp(tld[i].dirName,name)==0)
        {
            printf("Directory already exist...\n");
            return dirIndex;
        }
    }
    strcpy(tld[dirIndex].dirName,name);
    dirIndex++;
    printf("Directory Created..\n");
    return dirIndex;
}

int insert(char files[][20],char * name,int fileIndex)
{
    for(int i=0;i<=fileIndex;i++)
    {
        if(strcmp(files[i],name)==0)
        {
            printf("File already exist...\n");
            return fileIndex;
        }
    }
    fileIndex++;
    strcpy(files[fileIndex],name);
    printf("File Created..\n");
    return fileIndex;
}

int delete(char files[][20],char * name,int fileIndex)
{
    for(int i=0;i<=fileIndex;i++)
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
    for(int i=0;i<=fileIndex;i++)
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
    int i,f=0;
    printf("%s\n",dirName);
    printf("-----------------------------\n");
    for(i=0;i<=fileIndex;i++)
    {
        f=1;
        printf("%s ",files[i]);
    }
    printf("\n");
    if(f==0)
        printf("No files here...\n");
}
int findIndex(struct dir tld[],char * name,int dirIndex)
{
    for(int i=0;i<dirIndex;i++)
    {
        if(strcmp(tld[i].dirName,name)==0)
            return i;
    }
    return -1;
}
int main()
{
    
    int c;
    struct dir tld[10];
    char name[20];
    int dirIndex=0;
    int dirFound=0;

    for(int i=0;i<10;i++)
    {
	tld[i].fileIndex=0;
    }

    printf("1.Create Directory\n2.Create file\n3.Delete File\n4.Search File\n5.Diplay Directory\n6.Exit");
    while(1)
    {
        printf("\nEnter Your Choice : ");
        scanf("%d",&c);
        switch(c)
        {
            case 1: printf("Enter the Directory name : ");
                    scanf(" %[^\n]",name);
                    dirIndex=insertDir(tld,name,dirIndex);
                    break;
            case 2: printf("Enter the Directory Name : ");
                    scanf(" %s",name);
                    dirFound=findIndex(tld,name,dirIndex);
                    if(dirFound!=-1)
                    {
                        printf("File name to insert : ");
                        scanf(" %s",name);
                        tld[dirFound].fileIndex=insert(tld[dirFound].files,name,tld[dirFound].fileIndex);
                    }
		    else
			printf("No directory found !!\n");
                    break;
            case 3: printf("Enter the Directory Name : ");
                    scanf(" %s",name);
                    dirFound=findIndex(tld,name,dirIndex);
                    if(dirFound!=-1)
                    {
                        printf("File name to delete : ");
                        scanf(" %s",name);
                        tld[dirFound].fileIndex=delete(tld[dirFound].files,name,tld[dirFound].fileIndex);
                    }
                    break;
            case 4: printf("Enter the Directory Name : ");
                    scanf(" %s",name);
                    dirFound=findIndex(tld,name,dirIndex);
                    if(dirFound!=-1)
                    {
                        printf("File name to search : ");
                        scanf(" %s",name);
                        tld[dirFound].fileIndex=search(tld[dirFound].files,name,tld[dirFound].fileIndex);
                    }
                    break;
            case 5: printf("Enter the Directory Name : ");
                    scanf(" %s",name);
                    dirFound=findIndex(tld,name,dirIndex);
                    if(dirFound!=-1)
                    {
                        display(tld[dirFound].dirName,tld[dirFound].files,tld[dirFound].fileIndex);
                    }
                    break;
            case 6: exit(0);
        }
    }
    return 0;
}

