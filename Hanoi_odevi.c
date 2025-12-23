#include <stdio.h>

void hanoi(int n, char source, char auxiliary, char destination) {
    if (n == 1) {
        printf("Disk 1'i %c'dan %c'ye taşi\n", source, destination);
        return;
    }
    
    hanoi(n - 1, source, destination, auxiliary);
    printf("Disk %d'yi %c'dan %c'ye taşi\n", n, source, destination);
    hanoi(n - 1, auxiliary, source, destination);
}

int main() {
    int n;
    printf("Disk sayisini girin: ");
    scanf("%d", &n);
    
    printf("\n%d disk için Hanoi Kuleleri çözümü:\n\n", n);
    hanoi(n, 'A', 'B', 'C');
    
    printf("\nToplam hamle sayisi: %d\n", (1 << n) - 1);
    
    return 0;
}