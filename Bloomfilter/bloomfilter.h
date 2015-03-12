#ifndef BLOOM_H
#define BLOOM_H

typedef long long bfData;

typedef struct {
	char *arr;
	int size;
	int numHash;
	long long (**hash)(bfData);
} Bloom;

Bloom *bloom_create(int size, int numHash, long long (**hash)(bfData));
int bloom_insert(Bloom *bf,bfData data);
int bloom_lookup(Bloom *bf,bfData data);
int bloom_destroy(Bloom *bf);

#endif
