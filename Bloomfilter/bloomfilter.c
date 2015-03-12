#include <stdlib.h>
#include <memory.h>
#include "bloomfilter.h"

#define SETBIT(a,n) (a[n>>3] |= (1 << (n&7)))
#define GETBIT(a,n) (a[n>>3] & (1 << (n&7)))

Bloom *bloom_create(int size, int numHash, long long (**hash)(bfData))
{
	Bloom *newBF = malloc(sizeof(Bloom));
	newBF->size = size;
	newBF->arr = malloc(size / 8 + 1);
	memset(newBF->arr,0,size/8 + 1);
	newBF->numHash = numHash;
	newBF->hash = hash;
	
	return newBF;
}
int bloom_insert(Bloom *bf,bfData data)
{
	int i;
	for(i=0;i<bf->numHash;i++)
	{
		const long long res = bf->hash[i](data) % bf->size;
		SETBIT(bf->arr,res);
	}
	return 1;
}
int bloom_lookup(Bloom *bf,bfData data)
{
	int i;
	for(i=0;i<bf->numHash;i++)
	{
		const long long res = bf->hash[i](data) % bf->size;
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

long long test(bfData a){return a*997*1499;}
long long test2(bfData a){return a*1009*1361;}
long long test3(bfData a){return a*1013*1327;}
long long test4(bfData a){return a*1019*1321;}
long long test5(bfData a){return a*1021*1319;}
long long test6(bfData a){return a*1031*1307;}
long long test7(bfData a){return a*1063*1277;}
long long test8(bfData a){return a*1093*1217;}
long long test9(bfData a){return a*1129*1201;}
long long test10(bfData a){return a*1153*1193;}
long long test11(bfData a){return a*1163*1171;}

int main()
{
	long long (*hashFunc[11])(bfData) = {test,test2,test3,test4,test5,test6,test7,test8,test9,test10,test11};
	Bloom *bf = bloom_create(1024*1024,11,hashFunc);
	bloom_insert(bf,1LL);
	bloom_lookup(bf,1LL);
}
