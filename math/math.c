isPrime(p)
{
  int i,k=sqrt(p)+1e-6;
  //for(i=2;i*i<=p;i++)
  for(i=2;i<=k;i++)
  {
    if(p%i==0)return 0;
  }
  return 1;
}

gcd(a,b){return b?gcd(b,a%b):a;}

eratos(int *arr,int size,int n)
{
  int i,j;
  for(i=2;i<=n;i++)
  {
    for(j=i*i;j<=n;j+=i)
      arr[j]=1;
  }
}
