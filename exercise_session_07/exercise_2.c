
//Initialization from the file
int **  M= new  int*[2];
M[0]=  new int[5]
M[1]=new int[5]

for  (int i=0; i<5; i++){
  M[0][i]=i;
  M[1][i]=5+i;
}


int** swap_reversed(int** M) {
    int** M2 = new int*[2];
    *(M2 + 0) = new int[5];
    *(M2 + 1) = new int[5];

    for (int i = 0; i < 5; ++i) {
        *(*(M2 + 0) + i) = *(*(M + 1) + (4 - i)); 
        *(*(M2 + 1) + i) = *(*(M + 0) + (4 - i)); 
    }
    return M2;
}

void print2x5(int** A) {
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 5; ++c) {
            std::cout << *(*(A + r) + c) << (c + 1 == 5 ? '\n' : ' ');
        }
    }
}

int main() {
    int** M  = initM();
    int** M2 = swap_axis0_reversed(M);
}
