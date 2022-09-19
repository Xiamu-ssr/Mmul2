#define BLCOK_SIZE 64
#define min(a,b) (((a)>(b))?(b):(a))
const char* description = "blocked ~ blocked ~ ~";

void BlockMul(float *A, float *B, float *C, int I, int J, int K, int N){
    for(int i=0; i<I; ++i){
        for(int j=0; j<J; ++j){
            float cij = C[i*N+j];
            for(int k=0; k<K; ++k){
                cij += A[i*N+k] * B[k*N+j];
            }
            C[i*N+j] = cij;
        }
    }
}

void Mmul(int N, float* A, float* B, float* C){
    for(int i=0; i<N; i+=BLCOK_SIZE){
        for(int j=0; j<N; j+=BLCOK_SIZE){
            for(int k=0; k<N; k+=BLCOK_SIZE){
                int I = min(BLCOK_SIZE, N-i);
                int J = min(BLCOK_SIZE, N-j);
                int K = min(BLCOK_SIZE, N-k);
                BlockMul(A + i*N + k, B + k*N + j, C + i*N + j, I, J, K, N);
            }
        }
    }
}