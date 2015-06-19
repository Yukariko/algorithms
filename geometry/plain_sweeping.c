#include <stdio.h>
#include <stdlib.h>

typedef double rData;
typedef struct Rectangle {
	rData x1,y1;
	rData x2,y2;
} Rectangle;

int rcmp(const void *p, const void *q)
{
	return *(rData *)p>*(rData *)q? 1: *(rData *)p<*(rData *)q? -1: 0;
}

rData plane_sweeping(Rectangle *rec, int len)
{
	rData x[len * 2 + 1];
	rData y[len * 2 + 1];

	for(int i=0;i<len;i++)
	{
		x[i*2] = rec[i].x1;
		x[i*2+1] = rec[i].x2;
		y[i*2] = rec[i].y1;
		y[i*2+1] = rec[i].y2;
	}

	int N = len * 2;
	qsort(x,N,sizeof(rData),rcmp);
	qsort(y,N,sizeof(rData),rcmp);

	rData ret = 0;

	for(int i=1;i<N;i++)
		for(int j=1;j<N;j++)
			for(int k=0;k<len;k++)
				if(rec[k].x1 <= x[i-1] && x[i] <= rec[k].x2 && rec[k].y1 <= y[j-1] && y[j] <= rec[k].y2)
				{
					ret += (x[i]-x[i-1]) * (y[j]-y[j-1]);
					break;
				}
	return ret;
}

int main()
{
	return 0;
}