//
// Created by Medha Kant on 09-01-2019.
//

#ifndef CIL_CIL_H
#define CIL_CIL_H

#include <iostream>
#include <vector>
#include <iostream>
#include <cmath>

std::vector<float> convolution_withpadding(std::vector<float> matrix, std::vector<float> kernel);
std::vector<float> convolution_withpadding_matrixmult(std::vector<float> matrix, std::vector<float> kernel);
std::vector<float> convolution_withoutpadding(std::vector<float> matrix, std::vector<float> kernel);
std::vector<float> convolution_withoutpadding_matrixmult(std::vector<float> matrix, std::vector<float> kernel);
std::vector<float> relu(std::vector<float> matrix);
std::vector<float> tanh(std::vector<float> matrix);
std::vector<float> sigmoid(std::vector<float> matrix);
std::vector<float> softmax(std::vector<float> matrix);
std::vector<float> avgPooling(std::vector<float> matrix, int filterSize, int strideSize=1);
std::vector<float> maxPooling(std::vector<float> matrix, int filterSize, int strideSize=1);
std::vector<float> subMatrix(std::vector<float> matrix, int startingIndex, int subMatrixSize);
#endif //CIL_CIL_H
