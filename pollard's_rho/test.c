typedef long long ll;
ll gcd(ll a,ll b)
{
  return b?gcd(b,a%b):a;
}
ll f(ll x,ll n,int a)
{
  return ((x%n)*(x%n)+a)%n;
}
ll absl(long long a)
{
  return a>=0?a:-a;
}
ll pollard_rho(ll n)
{
  ll x,y,d;
  int a;
  for(a=-1;a<2;a+=2)
  {
    x=y=2;
    for(d=1;d==1;d=gcd(n,absl(x-y)))
    {
      x=f(x,n,a);
      y=f(f(y,n,a),n,a);
    }
    if(d!=n)return d;
  }
  return d==n?0:d;
}

main()
{
  printf("%lld",pollard_rho(18991325453139LL));
}
