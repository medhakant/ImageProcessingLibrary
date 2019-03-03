//
// Created by Medha Kant and Mayank Dubey on 09-01-2019.
//

#include "CIL.h"
#include<vector>
#include<iostream>
#include<cmath>

using namespace std;
//function to return the submatrix of a given matrix as vector
//the starting index and the size of submatrix needs are taken as arguments
vector<float> subMatrix(vector<float> matrix, int startingIndex, int subMatrixSize){
    int dimOfMatrix = sqrt(matrix.size());
    vector<float> subMatrix;
    for(int i=0; i<subMatrixSize; i++){
        for(int j=0; j<subMatrixSize; j++){
            int index = startingIndex + i*dimOfMatrix + j;
            float temp = matrix.at(index);
            subMatrix.push_back(temp);
        }
    }
    return subMatrix;
}

//function take vector as input and return a vector after performing a relu operation
vector<float> relu(vector<float> matrix){
    vector<float> reluMatrix;
    if(matrix.size()>0){
    for(int i=0;i<matrix.size();i++){
        float temp = matrix.at(i);
        reluMatrix.push_back(max(0.0f,temp));
        }    
    } else 
        cout << "Null size matrix"<< endl;
    return reluMatrix;
}

//function take vector as input and return a vector after performing a tanh operation
vector<float> tanh(vector<float> matrix){
    vector<float> tanhMatrix;
    if(matrix.size()>0){
        for(int i=0;i<matrix.size();i++){
        float temp = matrix.at(i);
        tanhMatrix.push_back((exp(2*temp)-1)/(exp(2*temp)+1));
        }
    }else
        cout << "Null size matrix" << endl;
    return tanhMatrix;
}

//function take vector as input and return a vector after performing a sigmoid operation
vector<float> sigmoid(vector<float> matrix){
    vector<float> sigmoidMatrix;
    if(matrix.size()>0){
        for(int i=0;i<matrix.size();i++){
        float temp = matrix.at(i);
        sigmoidMatrix.push_back(1/(1+exp(-1*temp)));
        }
    }else 
        cout << "Null size matrix" << endl;
    return sigmoidMatrix;
}

//function take vector as input and return a vector after performing a softmax operation
vector<float> softmax(vector<float> matrix){
    float sumOfExponents=0;
    vector<float> softmaxMatrix;
    if(matrix.size()>0){
        for(int i=0;i<matrix.size();i++){
        float temp = matrix.at(i);
        sumOfExponents+= exp(temp);
    }
    for(int i=0;i<matrix.size();i++){
        float temp = matrix.at(i);
        softmaxMatrix.push_back(exp(temp)/sumOfExponents);
        }
    }else 
        cout << "Null size matrix"<<endl;
    return softmaxMatrix;
}

//function take vector as input and return a vector after performing a maxpool operation
//takes filter size and stride size as argument
vector<float> maxPooling(vector<float> matrix, int filterSize, int strideSize){
    vector<float> maxPoolMatrix;
    if(!matrix.size()){
        cout << "Null size matrix" << endl;
        return maxPoolMatrix;
    }
    int dimOfMatrix = sqrt(matrix.size());
    for(int i=0; i<=(dimOfMatrix-filterSize); i+=strideSize){
        for(int j=0; j<=(dimOfMatrix-filterSize); j+=strideSize){
            int startIndex = i*dimOfMatrix + j;
            vector<float> temp = subMatrix(matrix, startIndex, filterSize);
            float maxVal = temp.at(0);
            for(int i=1;i<temp.size();i++){
                maxVal = max(maxVal,temp.at(i));
            }
            maxPoolMatrix.push_back(maxVal);
        }
    }
    return maxPoolMatrix;
}

//function take vector as input and return a vector after performing a average pool operation
//takes filter size and stride size as argument
vector<float> avgPooling(vector<float> matrix, int filterSize, int strideSize){
    vector<float> avgPoolMatrix;
    if(!matrix.size()){
        cout << "Null size matrix" << endl;
        return avgPoolMatrix;
    }
    int dimOfMatrix = sqrt(matrix.size());
    for(int i=0; i<=(dimOfMatrix-filterSize); i+=strideSize){
        for(int j=0; j<=(dimOfMatrix-filterSize); j+=strideSize){
            int startIndex = i*dimOfMatrix + j;
            vector<float> temp = subMatrix(matrix, startIndex, filterSize);
            float sumVal= 0;
            for(int i=0;i<temp.size();i++){
                sumVal+= temp.at(i);
            }
            avgPoolMatrix.push_back(sumVal/(pow(filterSize,2)));
        }
    }
    return avgPoolMatrix;
}

//function take vector as input and return a vector after performing a convolution operation
//with the given kernel. No zero padding is done
vector<float> convolution_withoutpadding_matrixmult(vector<float> matrix, vector<float> kernel){
    vector<float> convolution;
    if(kernel.size() && matrix.size()>=kernel.size()){
        int kernelSize = sqrt(kernel.size());
        int dimOfMatrix = sqrt(matrix.size());
        for(int i=0; i<=(dimOfMatrix-kernelSize); i++){
            for(int j=0; j<=(dimOfMatrix-kernelSize); j++){
                int startIndex = i*dimOfMatrix + j;
                vector<float> temp = subMatrix(matrix, startIndex, kernelSize);
                float conv= 0;
                for(int i=0;i<temp.size();i++){
                    conv+= temp.at(i)*kernel.at(i);
                }
                convolution.push_back(conv);
            }
        }
    }else if(kernel.size()==0)
        cout << "No kernel specified" << endl;
    else
        cout << "Improper input. Kernel should be smaller than the matrix and both should have a nonzero size" << endl;
    return convolution;
}

//function take vector as input and return a vector after performing a convolution operation
//with the given kernel. Zero padding is done to return a matrix of same size
vector<float> convolution_withpadding_matrixmult(vector<float> matrix, vector<float> kernel){
    vector<float> convolution;
    if(kernel.size() && matrix.size()>=kernel.size()){
        int kernelSize = sqrt(kernel.size());
        int dimOfOriginalMatrix = sqrt(matrix.size());
        int topNleftPad,bottomNrightPad;
        if(kernelSize & 1){
            topNleftPad = (kernelSize-1)/2;
            bottomNrightPad = (kernelSize-1)/2;
        }else {
            topNleftPad = kernelSize/2;
            bottomNrightPad = topNleftPad-1;
        }
        matrix.insert(matrix.begin(),((topNleftPad+dimOfOriginalMatrix+bottomNrightPad)*topNleftPad+topNleftPad),0);
        auto it = matrix.begin();
        it+=(topNleftPad+dimOfOriginalMatrix+bottomNrightPad)*topNleftPad+topNleftPad+dimOfOriginalMatrix;
        for(int i=0;i<(dimOfOriginalMatrix-1);i++){
            matrix.insert(it,topNleftPad+bottomNrightPad,0);
            it+=dimOfOriginalMatrix+topNleftPad+bottomNrightPad;
        }
        matrix.insert(matrix.end(),((topNleftPad+dimOfOriginalMatrix+bottomNrightPad)*bottomNrightPad+bottomNrightPad),0);
        int dimOfMatrix = sqrt(matrix.size());
        for(int i=0; i<=(dimOfMatrix-kernelSize); i++){
            for(int j=0; j<=(dimOfMatrix-kernelSize); j++){
                int startIndex = i*dimOfMatrix + j;
                vector<float> temp = subMatrix(matrix, startIndex, kernelSize);
                float conv= 0;
                for(int i=0;i<temp.size();i++){
                    conv+= temp.at(i)*kernel.at(i);
                }
                convolution.push_back(conv);
            }
        }
    } else if(kernel.size()==0)
        cout << "No kernel specified" << endl;
    else
        cout << "Improper input. Kernel should be smaller than the matrix and both should have a nonzero size" << endl;
    return convolution;
}

//function take vector as input and return a vector after performing a convolution operation
//with the given kernel. No zero padding is done
vector<float> convolution_withpadding(vector<float> matrix, vector<float> kernel){
    vector<float> convolution;
    if(kernel.size() && matrix.size()>=kernel.size()){
        int kernelSize = sqrt(kernel.size());
        int dimOfOriginalMatrix = sqrt(matrix.size());
        int topNleftPad,bottomNrightPad;
        if(kernelSize & 1){
            topNleftPad = (kernelSize-1)/2;
            bottomNrightPad = (kernelSize-1)/2;
        }else {
            topNleftPad = kernelSize/2;
            bottomNrightPad = topNleftPad-1;
        }
        matrix.insert(matrix.begin(),((topNleftPad+dimOfOriginalMatrix+bottomNrightPad)*topNleftPad+topNleftPad),0);
        auto it = matrix.begin();
        it+=(topNleftPad+dimOfOriginalMatrix+bottomNrightPad)*topNleftPad+topNleftPad+dimOfOriginalMatrix;
        for(int i=0;i<(dimOfOriginalMatrix-1);i++){
            matrix.insert(it,topNleftPad+bottomNrightPad,0);
            it+=dimOfOriginalMatrix+topNleftPad+bottomNrightPad;
        }
        matrix.insert(matrix.end(),((topNleftPad+dimOfOriginalMatrix+bottomNrightPad)*bottomNrightPad+bottomNrightPad),0);
        int dimOfMatrix = sqrt(matrix.size());
        for(int i=0; i<=(dimOfMatrix-kernelSize); i++){
            for(int j=0; j<=(dimOfMatrix-kernelSize); j++){
                int startIndex = i*dimOfMatrix + j;
                vector<float> temp = subMatrix(matrix, startIndex, kernelSize);
                float conv= 0;
                for(int i=0;i<temp.size();i++){
                    conv+= temp.at(i)*kernel.at(i);
                }
                convolution.push_back(conv);
            }
        }
    } else if(kernel.size()==0)
        cout << "No kernel specified" << endl;
    else
        cout << "Improper input. Kernel should be smaller than the matrix and both should have a nonzero size" << endl;
    return convolution;
}

//function take vector as input and return a vector after performing a convolution operation
//with the given kernel. Zero padding is done to return a matrix of same size
vector<float> convolution_withoutpadding(vector<float> matrix, vector<float> kernel){
    vector<float> convolution;
    if(kernel.size() && matrix.size()>=kernel.size()){
        int kernelSize = sqrt(kernel.size());
        int dimOfMatrix = sqrt(matrix.size());
        for(int i=0; i<=(dimOfMatrix-kernelSize); i++){
            for(int j=0; j<=(dimOfMatrix-kernelSize); j++){
                int startIndex = i*dimOfMatrix + j;
                vector<float> temp = subMatrix(matrix, startIndex, kernelSize);
                float conv= 0;
                for(int i=0;i<temp.size();i++){
                    conv+= temp.at(i)*kernel.at(i);
                }
                convolution.push_back(conv);
            }
        }
    }else if(kernel.size()==0)
        cout << "No kernel specified" << endl;
    else
        cout << "Improper input. Kernel should be smaller than the matrix and both should have a nonzero size" << endl;
    return convolution;
}