void merge(int *a, int hN, int N)
{
	vector<int> b(N);
	int i=0, j=hN, k=0;
	while(i < hN && j < N)
	{
		while(i < hN && a[i] < a[j])
		{
			b[k++] = a[i];
			i++;
		}
		b[k++] = a[j];
		j++;
	}

	while(i < hN)
	{
		b[k++] = a[i];
		i++;
	}

	while(j < N)
	{
		b[k++] = a[j];
		j++;
	}

	i=0;
	while(i < N)
	{
		a[i] = b[i];
		i++;
	}
}

void merge_sort(int *a, int N)
{
	if(N > 1)
	{
		int hN = n / 2;
		merge_sort(a, hN);
		merge_sort(a + hN, N - hN);
		merge(a, hN, N);
	}
}