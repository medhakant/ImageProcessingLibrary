# C++ Image Library
There are three files in the source. main.cpp, CLI.cpp and CLI.h which is the header file. To compile and run the program you just need to run the makefile which would create the required object files and link dependencies and produce an executilbe file named main. To test the program simply type -
> ./main inputMatrix.txt inputKernel.txt

Input files can contain the input in any format, each line contains a single value or all value in a single line separated by commas. The program can handle it. After the program loads, it will print the read `matrix file` and the `kernel file`. After which you can specify operations such as -

+ convolution_withpadding
+ convolution_withpadding_matrixmult
+ convolution_withoutpadding
+ convolution_withoutpadding_matrixmult
+ relu
+ tanh
+ sigmoid
+ softmax
+ avgPooling # takes argument - filterSize & strideSize default strideSize=1
+ maxPooling # takes argument - filterSize & strideSize default strideSize=1

The result is displayed on the screen in a single line and the data is processed sequentially. Here is samples output of the code-

> $ ./main matrix.txt kernel.txt
 
The input matrix <br/>
1 2 3 4 5 1 2 3 4 5 1 2 3 4 5 1 2 3 4 5 1 2 3 4 5 <br/>
The input kernel <br/>
1 -2 0 -1 2 -1 1 2 0 <br/>

> convolution_withpadding
 
 2 5 8 11 20 0 2 4 6 14 0 2 4 6 14 0 2 4 6 14 -2 -3 -4 -5 0
> avgpool 3 2
 
 3 9.66667 0.333333 4.33333

 ___
You can also type *help* during the execution of the program to show the avaiable list of operations. And to exit the program just type *exit*.  



### Author :- Medha and Mayank