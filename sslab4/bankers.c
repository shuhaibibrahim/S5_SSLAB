#include<stdio.h>

int n,m,safe[100];

int issafe(int pno,int alloc[][100],int max[][100],int avail[],int need[][100],int request[])
{


        int i, j, k, p;
        int finish[100],work[100], true=0;

        for(j=0;j<m;j++)
        {
                avail[j]-=request[j];
                alloc[pno][j]+=request[j];
                need[pno][j]-=request[j];
        }

        for(j=0;j<m;j++)
                work[j]=avail[j];

        //initialising finish vector with false
        for (k = 0; k < n; k++)
        {
                finish[k] = 0;
        }

        for (p = 0; p < n; p++)
        {
                for (i = 0; i < n; i++)
                {
                        if (finish[i] == 0)
                        {

                                int flag = 0;
                                for (j = 0; j < m; j++)
                                {
                                        if (need[i][j] > work[j])
                                        {
                                                flag = 1;
                                                break;
                                        }
                                }
                                if (flag == 0)
                                {
                                        safe[true++] = i;
                                        for (k = 0; k < m; k++)
                                                work[k] += alloc[i][k];
                                        finish[i] = 1;
                                }
                        }
                }
        }

        if(true==n)
                return 1;
        return (0);


}
void main()
{

        int i, j,flag, pno;

        int alloc[100][100],max[100][100],avail[100],need[100][100];
        int request[100]; //request vector

        printf("\nEnter the number of processes : ");
        scanf("%d",&n);
        printf("Enter the number of resources : ");
        scanf("%d",&m);

        //reading allocation matrix
        printf("\nEnter the Allocation matrix : \n");
        for(i=0;i<n;i++)
        {
                printf("Process P%d : ",i);
                for(j=0;j<m;j++)
                        scanf("%d",&alloc[i][j]);
        }

        //reading Max matrix
        printf("\nEnter the Max matrix : \n");
        for(i=0;i<n;i++)
        {
                printf("Process P%d : ",i);
                for(j=0;j<m;j++)
                        scanf("%d",&max[i][j]);
        }

        //initialising need matrix
        for (i = 0; i < n; i++)
        {
                for (j = 0; j < m; j++)
                        need[i][j] = max[i][j] - alloc[i][j];
        }


        printf("\nEnter the available number of each resources : \n");
        for(j=0;j<m;j++)
                scanf("%d",&avail[j]);

        printf("\nEnter the procees number : ");
        scanf("%d",&pno);

        printf("\nEnter the request vector for process P%d :\n",pno);
        for(j=0;j<m;j++)
                scanf("%d",&request[j]);

        //checking if request_i <= need_i
        flag=1;
        for(j=0;j<m;j++)
                if(request[j]>need[pno][j])
                {
                        printf("\nError : Process P%d has exceeded maximum claim!",pno);
                        flag=0;
                        break;
                }

        //checking if request_i <= available
        for(j=0;j<m;j++)
                if(request[j]>avail[j])
                {
                        printf("\nError : Resource currently not available..P%d must wait!",pno);
                        flag=0;
                        break;
                }

        if(flag)
        {

                if(issafe(pno,alloc,max,avail,need,request))
                {
                        printf("\nSafe : Request can be granted..\n");
                        printf("Safe sequence :\n");
                        for(i=0;i<n-1;i++)
                                printf("P%d -> ",safe[i]);
                        printf("P%d\n\n",safe[n-1]);
                }
                else
                        printf("\nUnsafe : Request cannot be granted..\n");
        }
}
