// g++ sum_array.cpp -o prog && time ./prog
#define ROW 100000
#define COL 100000

int sum_array_rows(int* A){
    int sum=0;

    for(int i=0; i < ROW; i++){
        for(int j=0; j< COL; j++){
            sum += A[i*COL+j];
        }
    }
    return sum;
}

int sum_array_cols(int* A){
    int sum=0;

    for(int j=0; j< COL; j++){
        for(int i=0; i < ROW; i++){
           sum += A[i*j];
        }
    }
    return sum;
}


int main(){

    int* test= new int[ROW*COL];

    //sum_array_cols(test);
    sum_array_rows(test);

    delete[] test;

    return 0;
}
