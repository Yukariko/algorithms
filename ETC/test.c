long long digitCount(long long n,int i)
{
	long long res,j,k,t;
	res=0;
	for(t=0,j=1;j<=n;j*=10,t++)
	{
		k=(n/j)%10;
		if(i==0)
		{
			if(!k)
			{
				res-=j-1;
				res+=n%j;
			}
		}
		else if(i<k)res+=j;
		else if(i==k)res+=n%j+1;
		res+=k*t*(j/10);
	}
	return res;
}
int putn(n,m,p)
{
	return n-(n/p%10)*p+m*p;
}
int isPalin(char *a,int len)
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
