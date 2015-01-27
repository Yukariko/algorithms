binary_search(int *arr,int *orgn,int size,int num)
{
   int start=0,end=size-1,mid;
   while(start<=end)
   {
     mid=(end+start)/2;
     if(num>orgn[arr[mid]])start=mid+1;
     else if(num<orgn[arr[mid]])end=mid-1;
     else return mid;
   }
   return start;
}
LIS(int *arr,int size,int *lis)
{
  int *b=(int *)malloc(size*4);
  int *parent = (int *)malloc(size*4);
  memset(parent,-1,size*4);
  int i,j,k=0;
  for(i=0;i<size;i++)
  {
    j=binary_search(b,arr,k,arr[i]);
    if(j==k)
    {
      b[k++]=i;
      if(k>1)parent[i]=b[k-2];
    }
    else
    {
      b[j]=i;
      if(j)parent[i]=b[j-1];
    }
  }
  int child=b[k-1];
  for(i=k-1;child!=-1;i--)
  {
  	lis[i]=arr[child];
  	child=parent[child];
  }
  free(b);
  free(parent);
  return k;
}
main(){}
