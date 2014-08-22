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
primeFactorCountOfFactorial(n,i)
{
  int result=0,j;
  for(j=i;j<=n;j*=i)result+=n/j;
  return result;
}
bigplus(char *store,char *a,char *b)
{
  char t[1001]={0};
  int i=strlen(a),j=strlen(b),p,s;
  for(p=0;i||j;p++)
  {
    s = (i?a[i-1]:'0')+(j?b[j-1]:'0')-'0'*2;
    if(s+t[p]>9)t[p+1]+=(s+t[p])/10;
    t[p] = (s+t[p])%10;
    if(i>0)i--;
    if(j>0)j--;
  }
  if(!t[p])p--;
  for(i=0;i<=p;i++)
   store[p-i]=t[i]+'0';
  store[p+1]=0;
}
main(){}
