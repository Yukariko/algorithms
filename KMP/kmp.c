make_pi(int *pi,char *p)
{
  int i=1,j=0;
  for(;p[i];)
  {
    if(!j||p[i]==p[j])
    {
      j++;i++;pi[i]=j;
    }
    else j=pi[j];
  }
}
kmp(int *pi,char *p,char *q,int pi_len)
{
  int i,j;
  for(i=j=1;p[i];)
  {
    if(!j||p[i]==q[j]){i++;j++;}
    else j=pi[j];
    if(j==pi_len+1) return 1;
  }
  return 0;
}
main(){}
