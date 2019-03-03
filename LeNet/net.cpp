#include <iostream>
#include "CIL.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include<map>

using namespace std;
vector<float> addBias (vector<float> input,float bias); // function to add bias to matrix
vector<float> sumConvolution (vector<vector<float>> conv2DVector); // function to sum up matrices of same order
vector<vector<float>> conv1 (vector<float> input, vector<float> parameters); // first convolution layer
vector<vector<float>> pool (vector<vector<float>>); //pooling layer with kernel size 2 and stride 2
vector<vector<float>> conv2 (vector<vector<float>> input, vector<float> parameters); // second covolutional layer
vector<float> fullyConnected1 (vector<vector<float>> input, vector<float> parameters); //first fully connected layer
vector<float> fullyConnected2 (vector<float> input, vector<float> parameters); // second fully connected layer
int main(int argc, char** argv){// read argument from the command line.
    vector<float> digitData;
    string line;
    if(argc ==2){ //input the data of the number
        ifstream data(argv[1]);
        while(getline(data,line)){
        istringstream ss(line);
        float num;
        ss >> num;
        while(ss){
            digitData.push_back(num);
            ss >> num;
        }
    }
}
int j=0;

    vector<float> conv1Param; //parameters for Convolution layer 1
    vector<float> conv2Param; //parameters for convolution layer 2
    vector<float> fc1Param; //parameters for fully connected layer 1
    vector<float> fc2Param; //parameters for fully connected layer 2
    ifstream conv1P("conv1.txt");
    while(getline(conv1P,line)){
        istringstream ss(line);
        float num;
        ss >> num;
        while(ss){
            conv1Param.push_back(num);
            ss >> num;
        }
    }
    ifstream conv2P("conv2.txt");
    while(getline(conv2P,line)){
        istringstream ss(line);
        float num;
        ss >> num;
        while(ss){
            conv2Param.push_back(num);
            ss >> num;
        }
    }
    ifstream fc1P("fc1.txt");
    while(getline(fc1P,line)){
        istringstream ss(line);
        float num;
        ss >> num;
        while(ss){
            fc1Param.push_back(num);
            ss >> num;
        }
    }
    ifstream fc2P("fc2.txt");
    while(getline(fc2P,line)){
        istringstream ss(line);
        float num;
        ss >> num;
        while(ss){
            fc2Param.push_back(num);
            ss >> num;
        }
    }
vector<float> probability = (softmax(fullyConnected2((fullyConnected1(pool(conv2(pool(conv1(digitData,conv1Param)),conv2Param)),fc1Param)),fc2Param))); // probability vector

// storing all the probabilities in a Map and sorting the map in descending
// Here if greater<int> is used to make sure that elements are stored in descending order of keys. 
map<float, int, greater <float> > softmax;
for(int iterator=0;iterator<10;iterator++){
    softmax.insert(make_pair(probability.at(iterator),iterator)); 
}

//printing top 3 probabilities
int i=0;
for (auto it=softmax.begin() ; it!=softmax.end(),i<3; it++,i++){
    cout << ((*it).first)*100 << " class: "<< (*it).second << endl; 
}

    return 0;
}


/* Helper functions */
// function to loop through all elements and add bias
vector<float> addBias (vector<float> input,float bias){
    vector<float> output;
    for (auto i = input.begin(); i != input.end(); ++i){
        output.push_back(*i+ (bias)); 
    }
    return output;
}

// function to loop through all matrices and find their sum
vector<float> sumConvolution (vector<vector<float>> conv2DVector){
    vector<float> result;
    for(int i=0;i<(conv2DVector.at(0)).size();i++){
        float temp=0;
        for(int j=0;j<conv2DVector.size();j++){
            temp+=(conv2DVector.at(j)).at(i);
        }
        result.push_back(temp);
    }
    return result;
}

// function to loop through all elements and find convolution of them to 20 different channels
vector<vector<float>> conv1 (vector<float> input, vector<float> parameters){
    vector<vector<float>> outputConv1;
    for(int i=0;i<20;i++){
        vector<float> kernel(&parameters[i*25],&parameters[(i+1)*25]);
        outputConv1.push_back(addBias( convolution_withoutpadding(input,kernel), parameters.at(500+i)));
        kernel.clear();
    }
    return outputConv1;
}

// function to loop through all elements and pool them
vector<vector<float>> pool (vector<vector<float>> input){
    vector<vector<float>> outputPool;
    for (auto i=input.begin();i!=input.end();++i){
        outputPool.push_back(maxPooling(*i,2,2));        
    }
    return outputPool;
}


// function to loop through all elements and find convolution, from 20 to 50 different channels
vector<vector<float>> conv2 (vector<vector<float>> input, vector<float> parameters){
    vector<vector<float>> outputConv2;
    for(int i=0;i<50;i++){
        vector<vector<float>> tempConv;
        for(int j=0;j<20;j++){
            vector<float> kernel(&parameters[(500*i+j*25)],&parameters[(500*i+(j+1)*25)]);
            tempConv.push_back( convolution_withoutpadding(input.at(j),kernel));
            kernel.clear();
        }
        outputConv2.push_back(addBias(sumConvolution(tempConv),parameters.at(25000+i)));
        tempConv.clear();
    }
    return outputConv2;
}

// function to reduce the 50 channels to 500*1 vector
vector<float> fullyConnected1 (vector<vector<float>> input, vector<float> parameters){
    vector<float> outputFc1;
    for(int i=0;i<500;i++){
        int flag =0;
        vector<vector<float>> tempConv;
        for(int j=0;j<50;j++){
            vector<float> kernel(&parameters[(800*i+j*16)],&parameters[(800*i+(j+1)*16)]);
            tempConv.push_back( convolution_withoutpadding(input.at(j),kernel));
            kernel.clear();
        }
        outputFc1.push_back(addBias(sumConvolution(tempConv),parameters.at(400000+i)).at(0));
        tempConv.clear();
    }
    return relu(outputFc1);
}

// function to loop through all elements and reduce 500*1 to 10*1 vectors
vector<float> fullyConnected2 (vector<float> input, vector<float> parameters){
    vector<float> outputFc2;
    for(int i=0;i<10;i++){
        float temp=0;
        for(int j=0;j<500;j++){
            temp+= (input.at(j))*(parameters.at((i*500)+j));
        }
        temp+=parameters.at(5000+i);
        outputFc2.push_back(temp);
    }
    return outputFc2;
}