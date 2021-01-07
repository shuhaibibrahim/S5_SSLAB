#include <stdio.h> 
#include<string.h>

int temp;
void swap_largest(int arr[], int n, int i) 
{ 
    int largest = i; // Initialize largest as root 
    int left = 2*i + 1; 
    int right = 2*i + 2; 

    // If left child is larger than root 
    if (left < n && arr[left] > arr[largest]) 
        largest = left; 

    // If right child is larger than largest
    if (right < n && arr[right] > arr[largest]) 
        largest = right; 

    // If largest is not root
    if (largest != i) 
    { 
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively call the swap_largest 
        swap_largest(arr, n, largest); 
    } 
}

void heap_sort(int arr[], int n) 
{ 

    // Build heap from an unsorted array (rearrange array) 
    for (int i = n / 2 - 1; i >= 0; i--) 
        swap_largest(arr, n, i); 

    // One by one extract an element from heap 
    for (int i = n - 1; i >= 0; i--) 
    { 

        // Move current root to end 
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // call swap_largest on the reduced heap 
        swap_largest(arr, i, 0); 
    } 
}

//fcfs algorithm
int fcfs(int a[],int n,int initial)
{
	int curr=initial;
	int prev=curr;
	int tot=0,i=0; //total distance traveled
	while(i<n)
	{
		curr=a[i];
		tot+= curr>prev?curr-prev:prev-curr;
		prev=curr;
		i++;
	}
	return tot;
}

//scan algorithm
int scan_algo(int a[],int n,int initial,char dir[])
{
    int right[100],left[100],rindex=0,lindex=0;
    if(strcmp(dir,"left")==0)
    {
        left[0]=0;
        lindex++;
    }
    else if(strcmp(dir,"right")==0)
    {
        right[0]=199; //Assuming disk size to be 200
        rindex++;
    }
    for(int i=0;i<n;i++)
    {
        if(a[i]<initial)
        {
            left[lindex]=a[i];
            lindex++;
        }
        else
        {
            right[rindex]=a[i];
            rindex++;
        }
    }

    heap_sort(left,lindex); 
    heap_sort(right,rindex); 

    int tot=0;
    int curr=initial;
    int prev=curr;
    for(int p=0;p<2;p++) //looping 2 times for leftand right
    {
        if(strcmp(dir,"left")==0)
        {
            for(int j=lindex-1;j>=0;j--)
            {
                curr=left[j];
                tot+= curr>prev?curr-prev:prev-curr;
                prev=curr;
            }
            strcpy(dir,"right");
        }
        else if(strcmp(dir,"right")==0)
        {
            for(int j=0;j<rindex;j++)
            {
                curr=right[j];
                tot+= curr>prev?curr-prev:prev-curr;
                prev=curr;
            }
            strcpy(dir,"left");
        }
    }
    return tot;
}

//cscan algorithm
int cscan_algo(int a[],int n,int initial,char dir[])
{
    int right[100],left[100],rindex=0,lindex=0;

    left[0]=0;
    lindex++;

    right[0]=199; //Assuming disk size to be 200
    rindex++;

    for(int i=0;i<n;i++)
    {
        if(a[i]<initial)
        {
            left[lindex]=a[i];
            lindex++;
        }
        else
        {
            right[rindex]=a[i];
            rindex++;
        }
    }

    heap_sort(left,lindex); 
    heap_sort(right,rindex);

    int tot=0;
    int curr=initial;
    int prev=curr;
    if(strcmp(dir,"left")==0)
    {
        for(int j=lindex-1;j>=0;j--)
        {
            curr=left[j];
            tot+= curr>prev?curr-prev:prev-curr;
            prev=curr;
        }
        for(int j=rindex-1;j>=0;j--)
        {
            curr=right[j];
            tot+= curr>prev?curr-prev:prev-curr;
            prev=curr;
        }
    }
    else if(strcmp(dir,"right")==0)
    {
        for(int j=0;j<rindex;j++)
        {
            curr=right[j];
            tot+= curr>prev?curr-prev:prev-curr;
            prev=curr;
        }
        for(int j=0;j<lindex;j++)
        {
            curr=left[j];
            tot+= curr>prev?curr-prev:prev-curr;
            prev=curr;
        }
    }
    return tot;
}

int main()
{
    //fcfs
	//int a[]={10,22,20,2,40,6,38},n=7;
	//int initial=20;
    int a[100],n,initial,seek;

	char dir1[10],dir2[10];

    printf("Enter the number of requests : ");
    scanf("%d",&n);
	printf("Enter the request array : ");
	for(int i=0;i<n;i++)
	    scanf("%d",&a[i]);
	printf("Enter the initial position : ");
	scanf("%d",&initial);

	printf("\nEnter the direction for SCAN algorithm : ");
	scanf(" %s",dir1);
	printf("Enter the direction for C-SCAN algorithm : ");
	scanf(" %s",dir2);

	printf("\nEnter the seek time per cylinder : ");
	scanf("%d",&seek);
	const int seek_fcfs=seek*fcfs(a,n,initial);
 	const int seek_scan=seek*scan_algo(a,n,initial,dir1);
 	const int seek_cscan=seek*cscan_algo(a,n,initial,dir2);
	printf("\nFCFS algorithm seek time : %d\n",seek_fcfs);
	printf("SCAN algorithm seek time : %d\n",seek_scan);
	printf("C-SCAN algorithm seek time : %d\n",seek_cscan);
	int min=seek_fcfs<seek_scan? (seek_fcfs<seek_cscan?seek_fcfs:seek_cscan) : (seek_scan<seek_cscan?seek_scan:seek_cscan);
    printf("\nOptimal total seek time is provided by ");
    if(min==seek_fcfs) 
        printf("FCFS algorithm\n");
    else if(min==seek_scan)
        printf("SCAN algorithm\n");
    else if(min==seek_cscan)
        printf("C-SCAN algorithm\n");

}




