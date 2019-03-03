#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<cmath>
#include <chrono>

//function to return the submatrix of a given matrix as vector
//the starting index and the size of submatrix needs are taken as arguments
float* subMatrix(float *matrix, int dimOfMatrix, int startingIndex, int subMatrixSize){
   float *subMatrix = (float *)malloc(subMatrixSize*subMatrixSize * sizeof(float));
    for(int i=0; i<subMatrixSize; i++){
        for(int j=0; j<subMatrixSize; j++){
            int index = startingIndex + i*dimOfMatrix + j;
            float temp = matrix[index];
            subMatrix[i*subMatrixSize+j]=temp;
        }
    }
    return subMatrix;
}

float* matrixMult(float* matrix1, float* matrix2, int row, int col){
  float *resultMatrix = (float *)malloc(row * sizeof(float));
  for(int i=0;i<row;i++){
      int sum=0;
      for(int j=0;j<col;j++){
          sum+=matrix1[i*col+j]*matrix2[j];
      }
      resultMatrix[i]=sum;
  }
  return resultMatrix;
}

//function take vector as input and return a vector after performing a relu operation
float * relu(float *matrix, int dimOfMatrix){
    float *reluMatrix = (float *)malloc(dimOfMatrix*dimOfMatrix * sizeof(float));
    if(dimOfMatrix>0){
    for(int i=0;i<dimOfMatrix*dimOfMatrix;i++){
        float temp = matrix[i];
        reluMatrix[i] = (std::max(0.0f,temp));
        }    
    } else 
        printf("Null size matrix\n");
    return reluMatrix;
}

//function take vector as input and return a vector after performing a tanh operation
float * tanh(float *matrix, int dimOfMatrix){
    float *tanhMatrix = (float *)malloc(dimOfMatrix*dimOfMatrix * sizeof(float));
    if(dimOfMatrix>0){
        for(int i=0;i<dimOfMatrix*dimOfMatrix;i++){
        float temp = matrix[i];
        tanhMatrix[i]=tanh(temp);
        }
    }else
        printf("Null size matrix\n");
    return tanhMatrix;
}

//function take vector as input and return a vector after performing a sigmoid operation
float * sigmoid(float *matrix, int dimOfMatrix){
    float* sigmoidMatrix = (float *)malloc(dimOfMatrix*dimOfMatrix * sizeof(float));;
    if(dimOfMatrix>0){
        for(int i=0;i<dimOfMatrix*dimOfMatrix;i++){
        float temp = matrix[i];
        sigmoidMatrix[i] = (1/(1+exp(-1*temp)));
        }
    }else 
        printf("Null size matrix");
    return sigmoidMatrix;
}

//function take vector as input and return a vector after performing a softmax operation
float* softmax(float *matrix, int dimOfMatrix){
    float sumOfExponents=0;
    float* softmaxMatrix = (float *)malloc(dimOfMatrix*dimOfMatrix * sizeof(float));
    if(dimOfMatrix>0){
        for(int i=0;i<dimOfMatrix*dimOfMatrix;i++){
        float temp = matrix[i];
        sumOfExponents+= exp(temp);
    }
    for(int i=0;i<dimOfMatrix*dimOfMatrix;i++){
        float temp = matrix[i];
        softmaxMatrix[i] = (exp(temp)/sumOfExponents);
        }
    }else 
        printf("Null size matrix");
    return softmaxMatrix;
}

//function take vector as input and return a vector after performing a maxpool operation
//takes filter size and stride size as argument
float* maxPooling(float *matrix, int dimOfMatrix,int filterSize, int strideSize){
    float *maxPoolMatrix;
    if(!dimOfMatrix|| filterSize > dimOfMatrix){
        printf("Invalid Input\n");
        return maxPoolMatrix;
    }
    int dimOfOutputMatrix = (dimOfMatrix-filterSize)/strideSize + 1;
    maxPoolMatrix = (float *)malloc(dimOfOutputMatrix*dimOfOutputMatrix * sizeof(float));
    int iterator = 0;
    for(int i=0; i<=(dimOfMatrix-filterSize); i+=strideSize){
        for(int j=0; j<=(dimOfMatrix-filterSize); j+=strideSize){
            int startIndex = i*dimOfMatrix + j;
            float *temp = subMatrix(matrix,dimOfMatrix, startIndex, filterSize);
            float maxVal = temp[0];
            for(int i=1;i<filterSize*filterSize;i++){
                maxVal = std::max(maxVal,temp[i]);
            }
            maxPoolMatrix[iterator]=maxVal;
            iterator++;
        }
    }
    return maxPoolMatrix;
}

//function take vector as input and return a vector after performing a average pool operation
//takes filter size and stride size as argument
float * avgPooling(float *matrix, int dimOfMatrix, int filterSize, int strideSize){
    float *avgPoolMatrix;
    if(!dimOfMatrix|| filterSize>dimOfMatrix){
        printf("Null size matrix\n");
        return avgPoolMatrix;
    }
    int dimOfOutputMatrix = (dimOfMatrix-filterSize)/strideSize + 1;
    avgPoolMatrix = (float *)malloc(dimOfOutputMatrix*dimOfOutputMatrix * sizeof(float));
    int iterator = 0;
    for(int i=0; i<=(dimOfMatrix-filterSize); i+=strideSize){
        for(int j=0; j<=(dimOfMatrix-filterSize); j+=strideSize){
            int startIndex = i*dimOfMatrix + j;
            float *temp = subMatrix(matrix,dimOfMatrix,startIndex,filterSize);
            float sumVal= 0;
            for(int i=0;i<filterSize*filterSize;i++){
                sumVal+= temp[i];
            }
            avgPoolMatrix[iterator]=(sumVal/(pow(filterSize,2)));
            iterator++;
        }
    }
    return avgPoolMatrix;
}

// function take vector as input and return a vector after performing a convolution operation
// with the given kernel. No zero padding is done
float *  convolution_withoutpadding_matrixmult(float *matrix,int dimOfMatrix,float *kernel,int kernelSize){
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
float * convolution_withpadding_matrixmult(float *matrix,int dimOfMatrix,float *kernel,int kernelSize){
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

// function take vector as input and return a vector after performing a convolution operation
// with the given kernel. No zero padding is done
float *  convolution_withoutpadding(float *matrix,int dimOfMatrix,float *kernel,int kernelSize){
    float *convolution;
    if(kernelSize>0 && dimOfMatrix>=kernelSize){
        convolution = (float *)malloc((dimOfMatrix-kernelSize+1)*(dimOfMatrix-kernelSize+1)*sizeof(float));
        for(int i=0; i<=(dimOfMatrix-kernelSize); i++){
            for(int j=0; j<=(dimOfMatrix-kernelSize); j++){
                int startIndex = i*dimOfMatrix + j;
                float *temp = subMatrix(matrix,dimOfMatrix,startIndex,kernelSize);
                float convSum=0;
                for(int k=0;k<kernelSize*kernelSize;k++){
                    convSum+=kernel[k]*temp[k];
                }
                convolution[(i*(dimOfMatrix-kernelSize+1)+j)]=convSum;
            }
        }
    }else if(dimOfMatrix==0)
        printf("No kernel specified\n");
    else
        printf("Improper input. Kernel should be smaller than the matrix and both should have a nonzero size");
    return convolution;
}

// function take vector as input and return a vector after performing a convolution operation
// with the given kernel. Zero padding is done to return a matrix of same size

float * convolution_withpadding(float *matrix,int dimOfMatrix,float *kernel,int kernelSize){
    float *paddedMatrix,*convolution;
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
        convolution = (float *)malloc((dimOfMatrix)*(dimOfMatrix)*sizeof(float));
        for(int i=0; i<=(dimOfMatrix+topNleftPad+bottomNrightPad-kernelSize); i++){
            for(int j=0; j<=(dimOfMatrix+topNleftPad+bottomNrightPad-kernelSize); j++){
                int startIndex = i*(dimOfMatrix+topNleftPad+bottomNrightPad) + j;
                float *temp = subMatrix(paddedMatrix,dimOfMatrix+topNleftPad+bottomNrightPad,startIndex,kernelSize);
                float convSum=0;
                for(int k=0;k<kernelSize*kernelSize;k++){
                    convSum+=kernel[k]*temp[k];
                }
                convolution[(i*(dimOfMatrix+topNleftPad+bottomNrightPad-kernelSize+1)+j)]=convSum;
            }
        }
    } else if(kernelSize==0)
        printf("No kernel specified");
    else
        printf("Improper input. Kernel should be smaller than the matrix and both should have a nonzero size");
    return convolution;
}


