#include <iostream>
#include "CIL.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv){// read arguments from the command line.
    vector<float> mat;
    vector<float> ker;
    string line;
    if(argc ==3){// if both matrix and kernel are provided
        ifstream matrix(argv[1]);
        ifstream kernel(argv[2]);
        while(getline(matrix,line)){
        istringstream ss(line);
        int num;
        ss >> num;
        while(ss){
            mat.push_back(num);
            ss >> num;
        }
    }
        while(getline(kernel,line)){
        istringstream ss(line);
        int num;
        ss >> num;
        while(ss){
            ker.push_back(num);
            ss >> num;
            }
        }
    cout << "The input matrix\n";
    for (auto i = mat.begin(); i != mat.end(); ++i)
        cout << *i << " ";
    cout<< endl;
    cout << "The input kernel\n";
    for (auto i = ker.begin(); i != ker.end(); ++i)
        cout << *i << " ";
    cout<< endl;
    }else if(argc ==2){// if only matrix is provided
        ifstream matrix(argv[1]);
        while(getline(matrix,line)){
        istringstream ss(line);
        int num;
        ss >> num;
        while(ss){
            mat.push_back(num);
            ss >> num;
            }
        }
    cout << "The input matrix\n";
    for (auto i = mat.begin(); i != mat.end(); ++i)
        cout << *i << " ";
    cout<< endl;
    }else{
        cout << "Please specify input matrix file. Run the program in the format given below.\n";
        cout << "./main matrix.txt kernel.txt\n";
        cout << "kernel is optional, but you will need it to perform convolution operations.\n";
        return 0;
    }
    
    //repeatedly read input and perform operations.
    getline(cin,line) ;
    while(line!="exit"){
        istringstream ss(line);
        string word,argument[3];
        int i=0;
        while(ss >> word){
            argument[i]=word;
            i++;
            if(i==3)
                break;
        }
        ss.clear();
        if(argument[0]=="convolution_withpadding"){
            vector<float> conv=convolution_withpadding(mat,ker);
            mat.clear();
            mat = conv;
            conv.clear();
            for (auto i = mat.begin(); i != mat.end(); ++i)
            cout << *i << " ";
            cout<< endl;
        }else if(argument[0]=="convolution_withpadding_matrixmult"){
            vector<float> conv=convolution_withpadding_matrixmult(mat,ker);
            mat.clear();
            mat = conv;
            conv.clear();
            for (auto i = mat.begin(); i != mat.end(); ++i)
            cout << *i << " ";
            cout<< endl;

        }else if(argument[0]=="convolution_withoutpadding"){
            vector<float> conv=convolution_withoutpadding(mat,ker);
            mat.clear();
            mat = conv;
            conv.clear();
            for (auto i = mat.begin(); i != mat.end(); ++i)
            cout << *i << " ";
            cout<< endl;        
        }else if(argument[0]=="convolution_withoutpadding_matrixmult"){
            vector<float> conv=convolution_withoutpadding_matrixmult(mat,ker);
            mat.clear();
            mat = conv;
            conv.clear();
            for (auto i = mat.begin(); i != mat.end(); ++i)
            cout << *i << " ";
            cout<< endl;            
        }else if(argument[0]=="relu"){
            vector<float> rel=relu(mat);
            mat.clear();
            mat = rel;
            rel.clear();
            for (auto i = mat.begin(); i != mat.end(); ++i)
                cout << *i << " ";
            cout<< endl;            
        }else if(argument[0]=="tanh"){
            vector<float> tan=tanh(mat);
            mat.clear();
            mat = tan;
            tan.clear();
            for (auto i = mat.begin(); i != mat.end(); ++i)
                cout << *i << " ";
            cout<< endl;
            
        }else if(argument[0]=="sigmoid"){
            vector<float> sig=sigmoid(mat);
            mat.clear();
            mat = sig;
            sig.clear();
            for (auto i = mat.begin(); i != mat.end(); ++i)
                cout << *i << " ";
            cout<< endl;
            
        }else if(argument[0]=="softmax"){
            vector<float> soft=softmax(mat);
            mat.clear();
            mat = soft;
            soft.clear();
            for (auto i = mat.begin(); i != mat.end(); ++i)
                cout << *i << " ";
            cout<< endl;
            
        }else if(argument[0]=="maxpool"){
            int kernelSize =2;
            int stride =1;
            if(argument[1].length()>0){
                ss.clear();
                ss.str(argument[1]);
                ss >> kernelSize;
            }
            if(argument[2].length()>0){
                ss.clear();
                ss.str(argument[2]);
                ss >> stride;
            }
            vector<float> max=maxPooling(mat,kernelSize,stride);
            mat.clear();
            mat = max;
            max.clear();
            for (auto i = mat.begin(); i != mat.end(); ++i)
                cout << *i << " ";
            cout<< endl;
            
        }else if(argument[0]=="avgpool"){
            int kernelSize =2;
            int stride =1;
            if(argument[1].length()>0){
                ss.clear();
                ss.str(argument[1]);
                ss >> kernelSize;
            }
            if(argument[1].length()>0){
                ss.clear();
                ss.str(argument[2]);
                ss >> stride;
            }
            vector<float> avg=avgPooling(mat,kernelSize,stride);
            mat.clear();
            mat = avg;
            avg.clear();
            for (auto i = mat.begin(); i != mat.end(); ++i)
                cout << *i << " ";
            cout<< endl;
            
        }else if(argument[0]=="help"){
            cout <<"Available options are:-\n";
            cout <<"convolution_withpadding\n" ;
            cout <<"convolution_withpadding_matrixmult\n";
            cout <<"convolution_withoutpadding\n";
            cout <<"convolution_withoutpadding_matrixmult\n";
            cout <<"relu\n";
            cout <<"tanh\n";
            cout <<"sigmoid\n";
            cout <<"softmax\n";
            cout <<"avgPooling # takes argument - filterSize strideSize=1\n";
            cout <<"maxPooling # takes argument - filterSize strideSize=1\n";
        }else
            cout << "Input a valid function. For available options type help, to stop execution of the program type exit.\n";

        getline(cin,line);
    }


    return 0;
}