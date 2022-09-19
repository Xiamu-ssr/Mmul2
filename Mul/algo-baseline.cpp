const char* description = "just a Baseline";
void Mmul(int N, float* A, float* B, float* C){
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            float cij = .0f;
            for(int k=0; k<N; ++k){
                cij += A[i*N+k] * B[k*N+j];
            }
            C[i*N+j] = cij;
        }
    }
}