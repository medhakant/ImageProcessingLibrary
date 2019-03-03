#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<iostream>
#include<omp.h>
#include<fstream>
#include <chrono>
#include "CIL.h" 
#define NUM_THREADS 35

using namespace std::chrono;

// function take vector as input and return a vector after performing a convolution operation
// with the given kernel. No zero padding is done
float *  convolution_withoutpadding_matrixmult_pthreads(float *matrix,int dimOfMatrix,float *kernel,int kernelSize){
    float *toeplitzMatrix;
    if(kernelSize>0 && dimOfMatrix>=kernelSize){
        toeplitzMatrix = (float *)malloc(kernelSize*kernelSize*(dimOfMatrix-kernelSize+1)*(dimOfMatrix-kernelSize+1)*sizeof(float));
        for(int i=0; i<=(dimOfMatrix-kernelSize); i++){
            for(int j=0; j<=(dimOfMatrix-kernelSize); j++){
                int startIndex = i*dimOfMatrix + j;
                float *temp = subMatrix(matrix,dimOfMatrix,startIndex,kernelSize);
                for(int k=0;k<kernelSize*kernelSize;k++){
                    toeplitzMatrix[((i*(dimOfMatrix-kernelSize+1)+j)*kernelSize*kernelSize)+k]=temp[k];
                }
            }
        }
    }else if(dimOfMatrix==0)
        printf("No kernel specified\n");
    else
        printf("Improper input. Kernel should be smaller than the matrix and both should have a nonzero size\n");
    float *convolution = matrixMult(toeplitzMatrix,kernel,(dimOfMatrix-kernelSize+1)*(dimOfMatrix-kernelSize+1),kernelSize*kernelSize);
    free(toeplitzMatrix); 
    return convolution;
}

//function take vector as input and return a vector after performing a convolution operation
//with the given kernel. Zero padding is done to return a matrix of same size
float * convolution_withpadding_matrixmult_pthreads(float *matrix,int dimOfMatrix,float *kernel,int kernelSize){
    float *paddedMatrix,*toeplitzMatrix;
    if(kernelSize>0 && dimOfMatrix>=kernelSize){
        toeplitzMatrix = (float *)malloc((dimOfMatrix)*(dimOfMatrix)*kernelSize*kernelSize*sizeof(float));
        int topNleftPad,bottomNrightPad;
        if(kernelSize & 1){
            topNleftPad = (kernelSize-1)/2;
            bottomNrightPad = (kernelSize-1)/2;
        }else {
            topNleftPad = kernelSize/2;
            bottomNrightPad = topNleftPad-1;
        }
        paddedMatrix = (float *)malloc((dimOfMatrix+topNleftPad+bottomNrightPad)*(dimOfMatrix+topNleftPad+bottomNrightPad)*sizeof(float));
        int indexOfPad = (topNleftPad + dimOfMatrix + bottomNrightPad)*topNleftPad + topNleftPad;
        for(int i=0;i<dimOfMatrix*dimOfMatrix;i++){
            paddedMatrix[indexOfPad+i]=matrix[i];
            if ((i+1)%dimOfMatrix == 0)
                indexOfPad+=topNleftPad+bottomNrightPad;
        }
        for(int i=0; i<=(dimOfMatrix+topNleftPad+bottomNrightPad-kernelSize); i++){
            for(int j=0; j<=(dimOfMatrix+topNleftPad+bottomNrightPad-kernelSize); j++){
                int startIndex = i*(dimOfMatrix+topNleftPad+bottomNrightPad) + j;
                float *temp = subMatrix(paddedMatrix,dimOfMatrix+topNleftPad+bottomNrightPad,startIndex,kernelSize);
                for(int k=0;k<kernelSize*kernelSize;k++){
                    toeplitzMatrix[((i*(dimOfMatrix+topNleftPad+bottomNrightPad-kernelSize+1)+j)*kernelSize*kernelSize)+k]=temp[k];
                }
            }
        }
    } else if(kernelSize==0)
        printf("No kernel specified\n");
    else
    printf("Improper input. Kernel should be smaller than the matrix and both should have a nonzero size\n");
   	float *convolution = matrixMult(toeplitzMatrix,kernel,dimOfMatrix*dimOfMatrix,kernelSize*kernelSize);
    free(toeplitzMatrix);
    free(paddedMatrix);
    return convolution;
}

