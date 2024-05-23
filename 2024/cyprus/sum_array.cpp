// g++ sum_array.cpp -o prog && time ./prog
// sudo perf stat -e cache-misses,branch-misses ./prog
#define ROW 40000
#define COL 40000

long sum_array_rows(long* A){
    int sum=0;

    for(long i=0; i < ROW; i++){
        for(long j=0; j< COL; j++){
            sum += A[i*COL+j];
        }
    }
    return sum;
}

long sum_array_cols(long* A){
    long sum=0;

    for(long j=0; j< COL; j++){
        for(long i=0; i < ROW; i++){
           sum += A[i*COL+j];
        }
    }
    return sum;
}


int main(){

    long* test= new long[ROW*COL];

   //sum_array_cols(test);
   sum_array_rows(test);

    delete[] test;

    return 0;
}
