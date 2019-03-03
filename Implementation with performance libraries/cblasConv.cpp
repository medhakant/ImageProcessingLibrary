#include "cblasConv.h"
#include<iostream>
#include<cmath>
#include<cblas.h>
#include <chrono> 
#include<stdio.h>
#include<stdlib.h>
#include "CIL.h"

// function take vector as input and return a vector after performing a convolution operation
// with the given kernel. No zero padding is done
float * convolution_withoutpadding_cblas(float *matrix,int dimOfMatrix,float *kernel,int kernelSize){
    float *toeplitzMatrix;
    float *convolution;
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
    convolution = (float *)malloc((dimOfMatrix-kernelSize+1)*(dimOfMatrix-kernelSize+1)*sizeof(float));
    int m=int(dimOfMatrix-kernelSize+1)*(dimOfMatrix-kernelSize+1);
    int k=(int)kernelSize*kernelSize;
    int n=1;
    cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,m,n,k,1,toeplitzMatrix,k,kernel,n,0,convolution,n);
    }else if(dimOfMatrix==0)
        std::cout << "No kernel specified" << std::endl;
    else
        std::cout << "Improper input. Kernel should be smaller than the matrix and both should have a nonzero size" << std::endl;
    free(toeplitzMatrix);
    return convolution;
}

//function take vector as input and return a vector after performing a convolution operation
//with the given kernel. Zero padding is done to return a matrix of same size
float * convolution_withpadding_cblas(float *matrix,int dimOfMatrix,float *kernel,int kernelSize){
    float *paddedMatrix,*toeplitzMatrix;
    float *convolution;
    if(kernelSize>0 && dimOfMatrix>=kernelSize){
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
        toeplitzMatrix = (float *)malloc((dimOfMatrix)*(dimOfMatrix)*kernelSize*kernelSize*sizeof(float));
        for(int i=0; i<=(dimOfMatrix+topNleftPad+bottomNrightPad-kernelSize); i++){
            for(int j=0; j<=(dimOfMatrix+topNleftPad+bottomNrightPad-kernelSize); j++){
                int startIndex = i*(dimOfMatrix+topNleftPad+bottomNrightPad) + j;
                float *temp = subMatrix(paddedMatrix,dimOfMatrix+topNleftPad+bottomNrightPad,startIndex,kernelSize);
                for(int k=0;k<kernelSize*kernelSize;k++){
                    toeplitzMatrix[((i*(dimOfMatrix+topNleftPad+bottomNrightPad-kernelSize+1)+j)*kernelSize*kernelSize)+k]=temp[k];
                }
            }
        }
    convolution = (float *)malloc((dimOfMatrix)*(dimOfMatrix)*sizeof(float));
    const int m=(int)(dimOfMatrix)*(dimOfMatrix);
    const int k=(int)kernelSize*kernelSize;
    const int n=1;
    cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,m,n,k,1,toeplitzMatrix,k,kernel,n,0,convolution,n);
    free(toeplitzMatrix);
    free(paddedMatrix); 
    } else if(kernelSize==0)
        std::cout << "No kernel specified" << std::endl;
    else
        std::cout << "Improper input. Kernel should be smaller than the matrix and both should have a nonzero size" << std::endl;
    return convolution;
}