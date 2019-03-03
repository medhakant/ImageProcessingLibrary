//
// Created by Medha Kant on 09-01-2019.
//

#ifndef CIL_CIL_H
#define CIL_CIL_H
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<cmath>
#include <chrono>

float* subMatrix(float *matrix, int dimOfMatrix, int startingIndex, int subMatrixSize);
float * convolution_withpadding(float *matrix,int dimOfMatrix,float *kernel,int kernelSize);
float * convolution_withpadding_matrixmult(float *matrix,int dimOfMatrix,float *kernel,int kernelSize);
float * convolution_withoutpadding(float *matrix,int dimOfMatrix,float *kernel,int kernelSize);
float * convolution_withoutpadding_matrixmult(float *matrix,int dimOfMatrix,float *kernel,int kernelSize);
float * relu(float *matrix, int dimOfMatrix);
float * tanh(float *matrix, int dimOfMatrix);
float * sigmoid(float *matrix, int dimOfMatrix);
float * softmax(float *matrix, int dimOfMatrix);
float * avgPooling(float *matrix, int dimOfMatrix,int filterSize, int strideSize=1);
float * maxPooling(float *matrix, int dimOfMatrix,int filterSize, int strideSize=1);
float * subMatrix(float *matrix, int dimOfMatrix, int startingIndex, int subMatrixSize);
float* matrixMult(float* matrix1, float* matrix2, int row, int col);
#endif //CIL_CIL_H
