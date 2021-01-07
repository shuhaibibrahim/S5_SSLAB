#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct dir
{
    char dirName[20];
    char files[10][20];
    int fileIndex;
    int dirIndex;
    struct dir * parent;
    struct dir * directory[3];
};

void tree(struct dir * currentDir, int tab)
{
    int i,f=0;

    printf("%s\n",currentDir->dirName);

    for(i=0;i<currentDir->fileIndex;i++)
    {
        f=1;
	for(int j=0;j<tab;j++)
		printf("--");
        printf("%s\n",currentDir->files[i]);
    }

    for(i=0;i<currentDir->dirIndex;i++)
    {
        f=1;
        for(int j=0;j<tab;j++)
                printf("--");
	tree(currentDir->directory[i],tab+1);
    }

}

int insertDir(struct dir *currentDir,char * name,int dirIndex)
{
    for(int i=0;i<dirIndex;i++)
    {
        if(strcmp(currentDir->directory[i]->dirName,name)==0)
        {
            printf("Directory already exist...\n");
            return dirIndex;
        }
    }
    currentDir->directory[dirIndex]=(struct dir *)malloc(sizeof(struct dir));
    strcpy(currentDir->directory[dirIndex]->dirName,name);
    currentDir->directory[dirIndex]->fileIndex=0;
    currentDir->directory[dirIndex]->dirIndex=0;
    currentDir->directory[dirIndex]->parent=currentDir;
    dirIndex++;
    printf("Directory Created..\n");
    return dirIndex;
}

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

void display(struct dir * currentDir)
{
    int i,f=0;
    printf("%s\n",currentDir->dirName);
    printf("-----------------------------\n");
    for(i=0;i<currentDir->dirIndex;i++)
    {
        f=1;
        printf("%s ",currentDir->directory[i]->dirName);
    }
    for(i=0;i<currentDir->fileIndex;i++)
    {
        f=1;
        printf("%s ",currentDir->files[i]);
    }
    printf("\n");
    if(f==0)
        printf("Nothing here...\n");
}
int findIndex(struct dir *directory[],char * name,int dirIndex)
{
    for(int i=0;i<dirIndex;i++)
    {
        if(strcmp(directory[i]->dirName,name)==0)
            return i;
    }
    return -1;
}
int main()
{

    int c;
    struct dir root;
    char name[20];
    int dirIndex=0;
    int dirFound=0;
    struct dir *currentDir;

    strcpy(root.dirName,"Root");
    root.dirIndex=0;
    root.fileIndex=0;
    currentDir=&root;
    printf("1.Create Directory\n2.Create file\n3.Display Directory\n4.Move to subdirectory\n5.Move to parent\n6.Tree display\n7.Exit\n");

    while(1)
    {
        printf("\nDirectory : %s",currentDir->dirName);
        printf("\nEnter Your Choice : ");
        scanf("%d",&c);
        switch(c)
        {
            case 1: printf("Enter the Directory name : ");
                    scanf(" %[^\n]",name);
                    currentDir->dirIndex=insertDir(currentDir,name,currentDir->dirIndex);
                    break;
            case 2: printf("File name to insert : ");
                    scanf(" %s",name);
                    currentDir->fileIndex=insert(currentDir->files,name,currentDir->fileIndex);
                    break;
            case 3: display(currentDir);
                    break;
            case 4: printf("Enter the Directory Name : ");
                    scanf(" %s",name);
                    dirFound=findIndex(currentDir->directory,name,currentDir->dirIndex);
                    if(dirFound!=-1)
                        currentDir=currentDir->directory[dirFound];
                    break;
            case 5: currentDir=currentDir->parent;
                    break;
	    case 6: tree(&root,1);
	    case 7: exit(0);
        }
    }
    return 0;
}

