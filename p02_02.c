#include <stdio.h>

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    int stok[1000];
    for(int i = 0; i < n; i++) {
        scanf("%d", &stok[i]);
    }
    
    int kode;
    scanf("%d", &kode);
    
    long long total = 0;
    
    if (kode == 1) {
        for(int i = 0; i < n; i += 2) {
            total += stok[i];
        }
    } else if (kode == 2) {
        for(int i = 1; i < n; i += 2) {
            total += stok[i];
        }
    }
    
    printf("%lld\n", total);
    
    return 0;
}