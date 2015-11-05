short nCm[2001][2001];
void calc_nCm(int N, int MOD)
{
	for(int i=0; i <= N; i++)
		nCm[i][0] = nCm[i][i] = 1;
	for(int i=1; i <= N; i++)
		for(int j=1; j < i; j++)
			nCm[i][j] = (nCm[i-1][j] + nCm[i-1][j-1]) % MOD;
}

long long mod_exp(long long a,long long b,long long c)
{
	a%=c;
	if(b==0)return 1;
	if(b==1)return a;
	if(b&1) return (a*mod_exp((a*a)%c,(b-1)/2,c))%c;
	return mod_exp((a*a)%c,b/2,c);
}