binary_search(int *arr,int size,int num)
{
   int start=0,end=size-1,mid;
   while(start<=end)
   {
     mid=(end+start)/2;
     if(num>arr[mid])start=mid+1;
     else if(num<arr[mid])end=mid-1;
     else return mid;
   }
   return start;
}
main(){}
