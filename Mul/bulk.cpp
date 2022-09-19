#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <logging.h>
#include <iostream>
#include <iomanip>
#include <string>

extern const char* description;
extern void Mmul(int, float*, float*, float*);

void fill(float *M, int n){
    for(int i=0; i<n; ++i){
        M[i] = .5f;
    }
}

int main(int argc, char** argv){
    google::InitGoogleLogging(argv[0]);  //括号内是程序名
    FLAGS_logtostderr = 1;  //输出到控制台

    LOG(INFO) << "Simple : " << description;
    
    int test_list[] = {17, 63, 64, 128, 255, 511, 512, 788, 1023, 1024};
    int tlsize = sizeof(test_list)/sizeof(int);
    int n = test_list[tlsize-1];

    float *A = (float*)malloc(n*n*sizeof(float));
    float *B = (float*)malloc(n*n*sizeof(float));
    float *C = (float*)malloc(n*n*sizeof(float));

    for(int i=0; i<tlsize; ++i){
        //init
        int nsize = test_list[i];
        fill(A, nsize*nsize);
        fill(B, nsize*nsize);
        memset(C, 0.0, nsize*nsize*sizeof(float));

        //mul
        double timeout = 2.125, seconds = 0.0, Gflops_s=0.0;
        int iter = 0;
        clock_t start = clock();
        while(1){
            iter++;
            Mmul(nsize, A, B, C);
            seconds = (double)(clock()-start)/CLOCKS_PER_SEC;
            if(seconds >= timeout){
                break;
            }
        }
        Gflops_s = 2e-9 * nsize * nsize * nsize * iter / seconds;
        LOG(INFO) << "Size: " << std::left << std::setw(6) << nsize << " Gflops/s: " << std::left << std::setprecision(4) << Gflops_s << " [iter=" << iter << ",time=" << seconds << " s]";

        //check
        for(int i=0; i<nsize*nsize; ++i){
            if(fabs(C[i]-(nsize*.25f)) > 0.001f){
                LOG(ERROR) << "***Failure***" << C[i];
                break;
            }
        }
    }

    //over
    google::ShutdownGoogleLogging();
    free(A);
    free(B);
    free(C);
    return 0;
}