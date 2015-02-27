typedef long long bfData;

typedef struct bloomfilter {
	char *arr;
	int size;
	int numHashFunc;
	long long (**hashFunc)(bfData);
} bloomfilter;

bloomfilter* CreateBF(int size, int numHashFunc, long long (**hashFunc)(bfData))
{
	bloomfilter * newBF = malloc(sizeof(bloomfilter));
	newBF->size = size;
	newBF->arr = malloc(size / 8 + 1);
	memset(newBF->arr,0,size/8 + 1);
	newBF->numHashFunc = numHashFunc;
	newBF->hashFunc = hashFunc;
	
	return newBF;
}
int bfInsert(bloomfilter *bf,bfData data)
{
	int i;
	for(i=0;i<bf->numHashFunc;i++)
	{
		const long long res = bf->hashFunc[i](data);
		bf->arr[res/8] |= 1 << (res%8);
	}
	return 1;
}
int bfLookup(bloomfilter *bf,bfData data)
{
	int i;
	for(i=0;i<bf->numHashFunc;i++)
	{
		const long long res = bf->hashFunc[i](data);
		if( !(bf->arr[res/8] & (1 << (res%8))) ) return 0;
	}
	return 1;
}


long long test(bfData a){return a+1;}
long long test2(bfData a){return a+2;}
main()
{
	long long (*hashFunc[2])(bfData) = {test,test2};
	bloomfilter *bf = CreateBF(1000,2,hashFunc);
	
	printf("%d %d %f\n",bf->hashFunc[0](1),bf->hashFunc[1](1),16 * log(2));
	bfInsert(bf,1LL);
	printf("%d",bfLookup(bf,1LL));
}
