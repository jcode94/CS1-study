// Justice Smith 2/2021
// This recursive function sums the blocks
// from each square layer of a pyramid.
// The side length of each layer is len and
// decreases by 1 as the height of pyramid
// increases by 1

# include <stdio.h>

int countBlocks(int len)
{
	if (len == 1)
		return 1;
    return (len * len) + countBlocks(len - 1);
}

int main()
{
	int len, numBlocks = 0;
	printf("Length of side of bottom layer: ");
    scanf("%d", &len);

	numBlocks = countBlocks(len);

	printf("Total blocks: %d", numBlocks);

  return 0;
}