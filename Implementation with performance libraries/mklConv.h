#ifndef CIL_mklConv_H
#define CIL_mklConv_H

#include<iostream>
#include<cmath>
#include"mkl.h"
#include <chrono> 
#include<stdio.h>
#include<stdlib.h>
#include "CIL.h"

float * convolution_withoutpadding_mkl(float *matrix, int dimOfMatrix, float *kernel, int kernelSize);
float * convolution_withpadding_mkl(float *matrix, int dimOfMatrix, float *kernel, int kernelSize);
#endif