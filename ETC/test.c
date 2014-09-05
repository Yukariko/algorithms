putn(n,m,p)
{
  return n-(n/p%10)*p+m*p;
}
isPalin(char *a,int len)
{
  int i=len/2;
  int p,q;
  if(len%2==0)
  {
    p=i-1;q=i;
    for(;p>=0&&q<len;p--,q++)if(a[p]!=a[q])return 0;
  }
  else
  {
    p=i;q=p;    
    for(;p>=0&&q<len;p--,q++)if(a[p]!=a[q])return 0;
  }
  return 1;
}
main(){}
