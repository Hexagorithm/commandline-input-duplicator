/* the tool should take in arguments as command input */
/* main a 5 b 5 -> aaaaabbbbb*/
/* gonna need malloc for this */

/* sequence, duplicator */
#include <stdio.h>
#include <stdlib.h> /* malloc() free() atoi()*/
#include <string.h> /* strlen() */

int calculate_buffer_size(int pairs, char** seqs, int* dups);
int calculate_pair_size(const char* seq, const int dup);


int main(int argc, char* argv[])
{
	/* argc = (2n +1) */
	if (argc == 1)
	{
		printf(
				"Example usage:\n"
				"\t%s a 5 ->\"aaaaa\"\n"
				"\t%s b 3 c 2 -> \"bbbcc\"\n"
				"\t%s ab 3 -> \"ababab\"\n",argv[0],argv[0],argv[0]);
		return 1;
	}
	else if (argc % 2 == 0)
	{
		printf("Incorrect number of arguments!\n");
		return 1;
	}
	int operator_amount = (argc - 1	) /2;
	int* dups = (int* ) malloc(sizeof(int) * operator_amount);
	char** seqs = (char**) malloc(sizeof(char*) * operator_amount);

	/* load sequences and duplicators into their respective lists */
	for (int i = 0, seq_index = 0, dup_index = 0; i < argc - 1; ++i)
	{
		if (i % 2 == 0) /* Sequence */
			seqs[seq_index++] = *++argv;
		else /* Duplicator */
		{
			dups[dup_index++] = atoi(*++argv);
		}
	}

	int pairs = (argc - 1) / 2;
	size_t buffer_size = calculate_buffer_size(pairs,seqs,dups) + 1; /* null byte*/
	char* output = (char*) malloc(sizeof(char) * ( buffer_size ));
	output[buffer_size-1] = '\0';
	if (output == NULL)
	{
		printf("Couldn\'t allocate memory for output!\n");
		return 1;
	}
	for (int i = 0; i < pairs; ++i)
	{
		for(int _ = 0; _ < dups[i]; ++_)
		{
			strncat(output,seqs[i],strlen(seqs[i]) +1);
		}
	}
	printf("%s\n",output);
	free(output);
	return 0;
}


int calculate_buffer_size(int pairs, char** seqs, int* dups)
{
	int size = 0;
	for (int i = 0; i < pairs; ++i)
	{
		size += calculate_pair_size(seqs[i],dups[i]);
	}
	return size;
}

int calculate_pair_size(const char* seq, const int dup)
{
	return strlen(seq) * dup;
}
