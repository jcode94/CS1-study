#include <stdio.h>

int blockCount(int baseLength) {
    if (baseLength == 5)
        return baseLength * baseLength;
    return blockCount(baseLength + 1) + baseLength * baseLength;
}

int main() {
    int n;
    scanf("%d", &n);
    int totalBlocks = blockCount(n);
    printf("%d", totalBlocks);
}