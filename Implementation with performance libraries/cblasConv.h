//
// Created by Medha Kant on 09-01-2019.
//

#ifndef CIL_cblasConv_H
#define CIL_cblasConv_H

#include "cblasConv.h"
#include<iostream> 
#include<stdio.h>
#include<stdlib.h>
float * convolution_withpadding_cblas(float *matrix,int dimOfMatrix,float *kernel,int kernelSize);
float * convolution_withoutpadding_cblas(float *matrix,int dimOfMatrix,float *kernel,int kernelSize);
#endif //CIL_CIL_H
