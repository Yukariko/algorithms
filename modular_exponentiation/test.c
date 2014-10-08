//a^b mod c
long long mod_exp(long long a,long long b,long long c)
{
  a%=c;
  if(b==0)return 1;
  if(b==1)return a;
  if(b&1) return (a*mod_exp((a*a)%c,(b-1)/2,c))%c;
  return mod_exp((a*a)%c,b/2,c);
}

main()
{
  printf("%lld",mod_exp(2,62,1LL<<63));
}
