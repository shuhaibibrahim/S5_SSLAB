#include<stdio.h> 
// struct page{
//     int a;
//     struct page * link;
// };
int frames=3;
int find(int a[],int item)
{
    for(int i=0;i<frames;i++)
        if(a[i]==item)
            return 1;
    return 0;
}

int lru(int a[], int n)
{
    //head=NULL;
    int indexes[100];
    int pages[100];

    for(int i=0; i<100; i++)
	pages[i]=-1;

    int currentFilled=0;
    int fault=0;
    for(int i=0;i<n;i++)
    {
        if(currentFilled<frames)
        {
            if(!find(pages,a[i]))
            {
                pages[currentFilled]=a[i];
                fault++;
                currentFilled++;
            }
            indexes[a[i]]=i;
        }
        else
        {
            if(!find(pages,a[i]))
            {
                int least=indexes[pages[0]];
                int leastIndex=0;
                for(int j=0;j<frames;j++)
                {
                    if(indexes[pages[j]]<least)
                    {
                        least=indexes[pages[j]];
                        leastIndex=j;
                    }
                }
                pages[leastIndex]=a[i];
                fault++;
            }
            indexes[a[i]]=i;
        }
    }
    return fault;
}
int fifo(int a[],int n)
{
    int pages[100]; // circular queue

    for(int i=0; i<100; i++)
	pages[i]=-1;

    int front=-1,rear=-1;
    int fault=0;
    for(int i=0;i<n;i++)
    {
        if(front==-1 || (rear+1)%frames!=front)
        {
            if(!find(pages,a[i]))
            {
                rear=(rear+1)%frames;
                pages[rear]=a[i];
                if(front==-1)
                    front++;
                fault++;
            }
        }
        else
        {
            if(!find(pages,a[i]))
            {
                front=(front+1)%frames;
                rear=(rear+1)%frames;
                pages[rear]=a[i];
                fault++;
            }
        }
    }
    return fault;
}


int lfu(int a[], int n)
{
    //head=NULL;
    int frequency[100]={0};
    int pages[100];

    for(int i=0; i<100; i++)
        pages[i]=-1;

    int currentFilled=0;
    int fault=0;
    int age[100];
    for(int i=0;i<n;i++)
    {
        int fault_flag=0;

        age[a[i]]=i;
        if(currentFilled<frames)
        {
            if(!find(pages,a[i]))
            {
                pages[currentFilled]=a[i];
                fault++;
                fault_flag=1;
                currentFilled++;
            }
            frequency[a[i]]++;
        }

        else
        {
            if(!find(pages,a[i]))
            {

                fault_flag=1;
                int least=frequency[pages[0]];
                int leastIndex=0;
                for(int j=0;j<frames;j++)
                {
                    if(frequency[pages[j]]<least)
                    {
                        least=frequency[pages[j]];
                        leastIndex=j;
                    }
                    if(frequency[pages[j]]==least)
                    {

                        if(age[pages[j]]<age[pages[leastIndex]])
                        {
                            leastIndex=j;
                            least=frequency[pages[j]];
                        }
                    }
                }
                pages[leastIndex]=a[i];
                fault++;
            }
            frequency[a[i]]++;
        }

    }
    return fault;
}

int main()
{
    // int a[]={7,2,3,1,2,5,3,4,6,7,7,1,0,5,4,6,2,3,0,1};
    int a[100];
    int n;
    printf("Enter the number of frames : ");
    scanf("%d",&frames);

    printf("\nEnter the number of page requests : ");
    scanf("%d",&n);
    printf("Enter the page Requests : ");
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    int lru_fault=lru(a,n);
    int fifo_fault=fifo(a,n);
    int lfu_fault=lfu(a,n);
    printf("\nNumber of page faults in LRU : %d\n",lru_fault);
    printf("Number of page faults in FIFO : %d\n",fifo_fault);
    printf("Number of page faults in LFU : %d\n",lfu_fault);
    return 0;
}



