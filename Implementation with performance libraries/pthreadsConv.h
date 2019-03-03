#ifndef CIL_mklConv_H
#define CIL_mklConv_H

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<iostream>
#include<omp.h>
#include<fstream>
#include <chrono>
#include "CIL.h" 
#define NUM_THREADS 35


float * convolution_withoutpadding_matrixmult_pthreads(float *matrix, int dimOfMatrix, float *kernel, int kernelSize);
float * convolution_withpadding_matrixmult_pthreads(float *matrix, int dimOfMatrix, float *kernel, int kernelSize);
#endif