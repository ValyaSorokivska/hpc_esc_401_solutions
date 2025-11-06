#include <cstdio>

int array_strides(int x, int y) {
    int COLS = 14;  
    int ROWS = 6;   

    if (x < 0 || x >= COLS || y < 0 || y >= ROWS) 
      return -1;

    return y * COLS + x;
}

int main() {
    for (int idx = 0; idx < 14 * 6; ++idx) {
        int y = idx / 14;
        int x = idx % 14;
        std::printf("[%d] x=%d y=%d\n", idx, x, y);
    }
    return 0;
}
