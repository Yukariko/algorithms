#include <stdlib.h>
#include <memory.h>
#include "bloomfilter.h"

#define SETBIT(a,n) (a[n>>3] |= (1 << (n&7)))
#define GETBIT(a,n) (a[n>>3] & (1 << (n&7)))

Bloom *bloom_create(int size, int numHashFunc, long long (**hashFunc)(bfData))
{
	Bloom *newBF = malloc(sizeof(Bloom));
	newBF->size = size;
	newBF->arr = malloc(size / 8 + 1);
	memset(newBF->arr,0,size/8 + 1);
	newBF->numHashFunc = numHashFunc;
	newBF->hashFunc = hashFunc;
	
	return newBF;
}
int bloom_insert(Bloom *bf,bfData data)
{
	int i;
	for(i=0;i<bf->numHashFunc;i++)
	{
		const long long res = bf->hashFunc[i](data) % bf->size;
		SETBIT(bf->arr,res);
	}
	return 1;
}
int bloom_lookup(Bloom *bf,bfData data)
{
	int i;
	for(i=0;i<bf->numHashFunc;i++)
	{
		const long long res = bf->hashFunc[i](data) % bf->size;
		if(!GETBIT(bf->arr,res)) return 0;
	}
	return 1;
}

int bloom_destroy(Bloom *bf)
{
	free(bf->arr);
	free(bf);
	return 0;
}

long long test(bfData a){return a+1;}
long long test2(bfData a){return a+2;}
int main()
{
	long long (*hashFunc[2])(bfData) = {test,test2};
	Bloom *bf = bloom_create(1000,2,hashFunc);
	bloom_insert(bf,1LL);
	bloom_lookup(bf,1LL);
}
