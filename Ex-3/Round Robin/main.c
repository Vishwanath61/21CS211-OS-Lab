//2.Round Robin

#include<stdio.h>

void init_process(int p[],int n)
{
    for(int i=0;i<n;i++)
    {
        p[i]=i+1;
    }
}

void init_zero(int a[],int n)
{
    for(int i=0;i<n;i++)
    {
        a[i]=0;
    }
}

void get_arrival(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("Enter the arrival time of Process-%d: ",i+1);
        scanf("%d",&arr[i]);
    }
}

void get_execution(int exe[],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("Enter the execution time of Process-%d: ",i+1);
        scanf("%d",&exe[i]);
    }
}

void sort_by_arrival(int p[],int arr[],int exe[],int n)
{
    for(int i=0;i<n;i++)
    {
        int min=arr[i];
        for(int j=i+1;j<n;j++)
        {
            if(arr[i]>arr[j])
            {
                min=arr[j];
            }
            if(min!=arr[i])
            {
                int temp=p[i];
                p[i]=p[j];
                p[j]=temp;
                
                int temp1=arr[i];
                arr[i]=arr[j];
                arr[j]=temp1;
                
                int temp2=exe[i];
                exe[i]=exe[j];
                exe[j]=temp2;
            }
        }
    }
}

int execution_sum(int exe[],int n)
{
    int sum=0;
    for(int i=0;i<n;i++)
    {
        sum+=exe[i];
    }
    return sum;
}

void copy_array(int array1[],int array2[],int n)
{
    for(int i=0;i<n;i++)
    {
        array2[i]=array1[i];
    }
}

void sum_prev_execution(int exe,int slice,int *prevexe)
{
    int mod=exe%slice;
    if(mod==0)
    {
        *prevexe=exe-slice;
    }
    else
    {
        *prevexe=exe-mod;
    }
}

int latestexe(int lst,int n,int slice)
{
    int mod=n%slice;
    if(mod==0)
    {
        int sum=lst-slice;
        return sum;
    }
    else
    {
        int sum=lst-mod;
        return sum;
    }
}

void round_robin(int p[],int arr[],int exec[],int exe[],int slice,int wait[],int turn[],int n)
{
    int lst=0,lst1,prevexe;
    int sum=execution_sum(exec,n);
    printf("\nGantt Chart:\n\n");
    while(sum>0)
    {
        for(int i=0;i<n;i++)
        {
            if(exec[i]>=slice)
            {
                printf("p%d:%dms->",i+1,slice);
                exec[i]=exec[i]-slice;
                sum=sum-slice;
                lst=lst+slice;
            }
            else if(exec[i]>0)
            {
                printf("p%d:%dms->",i+1,exec[i]);
                sum=sum-exec[i];
                lst=lst+exec[i];
                exec[i]=0;
            }
            if(exec[i]==0)
            {
                sum_prev_execution(exe[i],slice,&prevexe);
                lst1=latestexe(lst,exe[i],slice);
                wait[i]=(lst1-prevexe)-arr[i];
                turn[i]=lst-arr[i];
                exec[i]=-1;
            }
        }
    }
}

void display_array(int array[],int p[],int n)
{
    printf("\n");
    for(int i=0;i<n;i++)
    {
        printf("\np[%d]= %d",p[i],array[i]);
    }
}

void main()
{
    int n,slice;
    //printf("\nEnter the number of process: ");
    //scanf("%d",&n);
    n=5;
    int p[n],execopy[n],wait[n],turn[n];
    //int arr[n],exe[n],
    init_process(p,n);
    init_zero(wait,n);
    init_zero(turn,n);
    //printf("\nEnter the arrival time of %d processes: \n\n",n);
    //get_arrival(arr,n);
    int arr[5]={0,1,2,3,4};
    //printf("\nEnter the execution time of %d Processes: \n\n",n);
    //get_execution(exe,n);
    int exe[5]={50,20,30,10,25};
    copy_array(exe,execopy,n);
    sort_by_arrival(p,arr,exe,n);
    //printf("\nEnter the time slice: ");
    //scanf("%d",&slice);
    slice=10;
    round_robin(p,arr,execopy,exe,slice,wait,turn,n);
    printf("\n\nWaiting Time:");
    display_array(wait,p,n);
    printf("\n\nTurn-Around Time:");
    display_array(turn,p,n);
}
