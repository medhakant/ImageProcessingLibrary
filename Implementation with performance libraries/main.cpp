#include <iostream>
#include "CIL.h"
#include "cblasConv.h"
#include "mklConv.h"
#include "pthreadsConv.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv){// read arguments from the command line.
    float *mat, *ker, *C;
    int m,n,i=0;
    string line;
    if(argc ==5){// if both matrix and kernel are provided
        ifstream matrix(argv[1]);
        m = atoi(argv[2]);
        ifstream kernel(argv[3]);
        n = atoi(argv[4]);
        mat = (float *)malloc(m*m * sizeof(float));
	    ker = (float *)malloc(n*n * sizeof(float));
        while(getline(matrix,line) && i < (m*m)){
        istringstream ss(line);
        int num;
        ss >> num;
        while(ss){
            mat[i]=num;
            ss >> num;
            i++;
            if(i==m*m)
                break;
        }
    }
    i=0;
        while(getline(kernel,line) && i <(n*n)){
        istringstream ss(line);
        int num;
        ss >> num;
        while(ss){
            ker[i]=num;
            ss >> num;
            i++;
            if(i==n*n)
                break;
        }}
    printf("Matrix\n");
    for (i = 0; i < (m*m); i++) {
		printf("%.2f ",mat[i]);
		if ((i+1)%m == 0)
			printf("\n");}
    printf("Kernel\n");
    for (i = 0; i < (n*n); i++) {
		printf("%.2f ", ker[i]);
		if ((i+1)%n == 0)
			printf("\n");}
    }else{
        cout << "Please specify input matrix file. Run the program in the format given below.\n";
        cout << "./main matrix.txt kernel.txt\n";
        cout << "kernel is optional, but you will need it to perform convolution operations.\n";}
        
    
    //repeatedly read input and perform operations.
    getline(cin,line) ;
    while(line!="exit"){
        istringstream ss(line);
        string word,argument[3];
        int i=0;
        while(ss >> word){
            argument[i]=word;
            i++;
            if(i==3)
                break;
        }
        ss.clear();
        if(argument[0]=="convolution_withpadding"){
            float *conv=convolution_withpadding(mat,m,ker,n);
            mat = conv;
            for(int i=0;i<m*m;i++){
                printf("%.2f ",mat[i]);
            }
            printf("\n");
        }else if(argument[0]=="convolution_withpadding_matrixmult"){
            float *conv=convolution_withpadding_matrixmult(mat,m,ker,n);
            mat = conv;
            for(int i=0;i<m*m;i++){
                printf("%.2f ",mat[i]);
            }
            printf("\n");

        }else if(argument[0]=="convolution_withoutpadding"){
            float *conv=convolution_withoutpadding(mat,m,ker,n);
            mat = conv;
            m= m-n+1;
            for(int i=0;i<m*m;i++){
                printf("%.2f ",mat[i]);
            }
            printf("\n");      
        }else if(argument[0]=="convolution_withoutpadding_matrixmult"){
            float *conv=convolution_withoutpadding_matrixmult(mat,m,ker,n);
            mat = conv;
            m= m-n+1;
            for(int i=0;i<m*m;i++){
                printf("%.2f ",mat[i]);
            }
            printf("\n");            
        }else if(argument[0]=="convolution_withoutpadding_matrixmult_pthreads"){
            float *conv=convolution_withoutpadding_matrixmult_pthreads(mat,m,ker,n);
            mat = conv;
            m= m-n+1;
            for(int i=0;i<m*m;i++){
                printf("%.2f ",mat[i]);
            }
            printf("\n");      
        }else if(argument[0]=="convolution_withpadding_matrixmult_pthreads"){
            float *conv=convolution_withpadding_matrixmult_pthreads(mat,m,ker,n);
            mat = conv;
            for(int i=0;i<m*m;i++){
                printf("%.2f ",mat[i]);
            }
            printf("\n");            
        }else if(argument[0]=="convolution_withoutpadding_mkl"){
            float *conv=convolution_withoutpadding_mkl(mat,m,ker,n);
            mat = conv;
            m= m-n+1;
            for(int i=0;i<m*m;i++){
                printf("%.2f ",mat[i]);
            }
            printf("\n");      
        }else if(argument[0]=="convolution_withpadding_mkl"){
            float *conv=convolution_withpadding_mkl(mat,m,ker,n);
            mat = conv;
            for(int i=0;i<m*m;i++){
                printf("%.2f ",mat[i]);
            }
            printf("\n");            
        }else if(argument[0]=="convolution_withoutpadding_cblas"){
            float *conv=convolution_withoutpadding_cblas(mat,m,ker,n);
            mat = conv;
            m= m-n+1;
            for(int i=0;i<m*m;i++){
                printf("%.2f ",mat[i]);
            }
            printf("\n");      
        }else if(argument[0]=="convolution_withpadding_cblas"){
            float *conv=convolution_withpadding_cblas(mat,m,ker,n);
            mat = conv;
            for(int i=0;i<m*m;i++){
                printf("%.2f ",mat[i]);
            }
            printf("\n");            
        }else if(argument[0]=="relu"){
            float* rel=relu(mat,m);
            mat = rel;
            for(int i=0;i<m*m;i++){
                printf("%.2f ",mat[i]);
            }
            printf("\n");           
        }else if(argument[0]=="tanh"){
            float* tanhMat=tanh(mat,m);
            mat = tanhMat;
            for(int i=0;i<m*m;i++){
                printf("%.2f ",mat[i]);
            }
            printf("\n");            
        }else if(argument[0]=="sigmoid"){
            float* sig=sigmoid(mat,m);
            mat = sig;
            for(int i=0;i<m*m;i++){
                printf("%.2f ",mat[i]);
            }
            printf("\n");            
        }else if(argument[0]=="softmax"){
            float* soft=softmax(mat,m);
            mat = soft;
            for(int i=0;i<m*m;i++){
                printf("%.2f ",mat[i]);
            }
            printf("\n");            
        }else if(argument[0]=="maxpool"){
            int kernelSize =2;
            int stride =1;
            if(argument[1].length()>0){
                ss.clear();
                ss.str(argument[1]);
                ss >> kernelSize;
            }
            if(argument[2].length()>0){
                ss.clear();
                ss.str(argument[2]);
                ss >> stride;
            }
            float* max=maxPooling(mat,m,kernelSize,stride);
            mat = max;
            m=(m-kernelSize)/stride + 1;
            for(int i=0;i<m*m;i++){
                printf("%.2f ",mat[i]);
            }
            printf("\n");            
        }else if(argument[0]=="avgpool"){
            int kernelSize =2;
            int stride =1;
            if(argument[1].length()>0){
                ss.clear();
                ss.str(argument[1]);
                ss >> kernelSize;
            }
            if(argument[1].length()>0){
                ss.clear();
                ss.str(argument[2]);
                ss >> stride;
            }
            float* avg=avgPooling(mat,m,kernelSize,stride);
            mat = avg;
            m=(m-kernelSize)/stride + 1;
            for(int i=0;i<m*m;i++){
                printf("%.2f ",mat[i]);
            }
            printf("\n");             
        }else if(argument[0]=="help"){
            cout <<"Available options are:-\n";
            cout <<"convolution_withpadding\n" ;
            cout <<"convolution_withpadding_matrixmult\n";
            cout <<"convolution_withoutpadding\n";
            cout <<"convolution_withoutpadding_matrixmult\n";
            cout <<"convolution_withpadding_mkl\n" ;
            cout <<"convolution_withoutpadding_mkl\n";
            cout <<"convolution_withpadding_cblas\n" ;
            cout <<"convolution_withoutpadding_cblas\n";
            cout <<"convolution_withpadding_matrixmult_pthreads\n" ;
            cout <<"convolution_withoutpadding_matrixmult_pthreads\n";
            cout <<"relu\n";
            cout <<"tanh\n";
            cout <<"sigmoid\n";
            cout <<"softmax\n";
            cout <<"avgPooling # takes argument - filterSize strideSize=1\n";
            cout <<"maxPooling # takes argument - filterSize strideSize=1\n";
        }else
            cout << "Input a valid function. For available options type help, to stop execution of the program type exit.\n";

        getline(cin,line);
    }

    return 0;
    }