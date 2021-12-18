# CSE 701 Proj 03 - Outlier detection by Robust Regression

## Description

- The code is designed to perform following operations.

  - Computing parameters (slope and intercept) of **best line of fit** by rubust linear regression with M-estimation.
  
  - Detecting outliers in the given data by
    - standardized residual
    - weight of each data point given during robust regression
    
  - Generating visualized result (in BMP format) that shows 
    - line of best fit for the input data
    
    - observed data points
    
    - detected outlier data points
    
    - detected inlier data points
    
      
    
## Environemnt
- Windows/Linux OS
- Command-line interface is required
- Graphic user interface is not supported
  
    
## Prerequisite
- [CMAKE](https://cmake.org/) version **3.18.1** or above 
- C/C++ compiler that supports **C++20** standard
- Any **text** file editor
- Any **iamge** viewer




## Compilation
> ```bash
> mkdir build
> cd build
> cmake ..
> ```
>
> > #### For Linux environment
> > ```bash
> > make
> > ```
> >
> > **NOTE**
> >
> > - If following **WARNING MESSAGE** is returned
> >
> >   ```bash
> >   make[2]: Warning: File 'CMakeFiles/proj_r.dir/depend.make' has modification time 0.X s in the future
> >   make[2]: warning:  Clock skew detected.  Your build may be incomplete.
> >   ```
> >
> > - Please do the follwoing to solve the **WARNING MESSAGE**
> >
> >   ```bash
> >   make clean
> >   make
> >   ```
> >
>
> > #### For Windows environment
> >
> > ```bash
> > 
> > ```
> >
> > 




## Using the executable

>Please reloacte the generated executable where the user want by default
>
>> #### For Linux OS
>> ```bash
>> ./proj_r weight_func detect_func observed_x.dvec observed_y.dvec
>> ```
>
>
>
>> #### For Windows OS
>> ```bash
>> ./proj_r.exe weight_func detect_func observed_x.dvec observed_y.dvec
>> ```
>
>
>
>> #### Example 1
>
>> - Input
>
>> ```bash
>> ./proj_r bisquare standardized_residual observed_x.dvec observed_y.dvec
>> ```
>> - output
>
>> ```bash
>> Computed slope: 2.000000e+00
>> Computed intercept: 3.000000e+00
>> Detected outliers: 22 out of 100
>> ```
>
>> - The above input will computes parameters for best line of fit by using Robust Regression with **bisquare** as its weight function, and differentiate **inlier** and **outlier** in the observed data point using **standardized residual** as outlier detection method.
>
>
>
>> #### Example 2
>
>> - Input
>
>> ```bash
>> ./proj_r
>> ```
>
>> - output
>
>> ```bash
>> The program is designed to perform linear regression and detect outlier.
>> ```
>
>> First Input
>>         Weight function for robust regression
>>         Please, select one from the list from the link
>>         https://www.mathworks.com/help/stats/robustfit.html#mw_48d239e7-b4dc-4a5e-8e97-ba7c34ce85b9
>
>> Second Input
>>         Type of outlier detection method
>>         Please choose one between 'weight' and 'standardized_resdual'
>
>> Third Input & Forth Input
>>         Path to the first file - observed x data.
>> 	    Path to the second file - observed y data.
>
>> Example Input for Linux
>>      proj_r bisquare standardized_residual observed_x.dvec observed_y.dvec
>> Example Input for Windows
>>      proj_r.exe bisquare standardized_residual observed_x.dvec observed_y.dvec
>>
>> ```
>> 
>> ```
>
>> - Excuting program without input parameter will provide basic description about how to use the program.
>
>
>
>> #### INPUTS
>> > **weight_func** 
>> >
>> > - specifies weight function which will be used in Robust Regression process to adjust effectiveness of given data point. 
>> > - The data points with weight near 1 has bigger effectiveness while the data points near 0 has smaller effecitveness. 
>> > - Please check the [link](https://www.mathworks.com/help/stats/robustfit.html?s_tid=doc_ta#mw_48d239e7-b4dc-4a5e-8e97-ba7c34ce85b9) for detail. 
>> > - The followings are list of weight function option for the program.
>> >   - andrews
>> >   - bisquare - preferred option
>> >   - cauchy
>> >   - fair
>> >   - huber
>> >   - logistic
>> >   - talwar
>> >   - welsch
>
>> > **detect_func**
>> > - specifeis outlier detection function which will be used in Outlier Detection process to compute standard point of define what is outlier in the data.
>> > - The followins are list of outlier detection method for the program.
>> >   - standardized_residual - preferred option
>> >   - weight
>> >
>
>> > **observed_x.dvec** and **observed_y.dvec**
>> >
>> > - Those are the input data which contains coordinate of observed data
>> > - For example, if the given data set is a record of the amount of salary according to years of employment, years of employment is observed_x, the collection of independent variables, and the amount of wages is observed_y which is the set of dependent variables.
>> > - The length (= number of elements in the file) must match each other.


​     
## Using the project as part of another project

> - The following is simple explanation of how to use the classes in the project as part of another project.
> - To see the detailed examples of using the classes, please check the code under the example directory
>
>>   #### Robust Regression
>>   - Please include one of 
>>     - facade_regression.hpp
>>     - robut_regression.hpp

​      

## Directories in the project
- include : Contains header files for the project
- src : Contains source files for the project
  - obj: Directory to separate object files from compilation process
  - func_confirm: Directory contains .cpp file for function test
  - performance_test : Directory contains code file for performantce test
- Project 03 contains three sections
- Main - main directory
  
  - asdasd
  - Performance benchmark section - performance_test directory
    - awdas
  - Function validation section - func_confrim directory
    - The section contains implementation of automated function validation of the functions used in the project.
    - The valdiataions must be proceeded if there is any change in **function implementation** or **constant values** used.
    - The section contains validation of follwoing classes
      - ARRAY_OPERATION class
      - DATA_IO class
      - REGRESSION_METHOD class
      - OUTLIER_DETECTION class
      - FACADE_REGRESSION class
      - FACADE_DETECTION class
    - **NOTE**
      - Validation of **REGRESSION_METHOD** and **FACADE_REGRESSION**  cannot be done with **exact value** as the result of computation is **approximated value**. Therefore, the validation of result has been done by using tolerence.
      - Validation of **OUTLIER_PLOT** and **FACADE_PLOT ** are skipped as 
  - Example section - example directory
    - The section contains examples of using project's class as a part of another project.
    - The section provides examples for following classes
      - REGRESSION_METHOD class
      - OUTLIER_DETECTION class
      - OUTLIER_PLOT class
      - FACADE_REGRESSION class
      - FACADE_DETECTION class
      - FACADE_PLOT class
    - **NOTE**
      - The classes its name starts with FACADE keyword are the class designed for convinience of users who are not experienced in C/C++ or who want to use default setting.
      - The classes automatically validate inputs and initialize everything required for proceeding computation.
      - The classes its name does not start with FACADE requires manual initialization of input and output data such as vector size.




## Operator Overloading in Project 03

- Because user-defined data structure is not used in the project 03, none of operators are overloaded in the project 03.
  
    

## Error Code in the project



## About Robust Regression

- 




## About Outlier Detection

- 



## To validate operations

> Under CSE701_Project_02/ **func_confirm** directory, type
>
> ```bash
> make run_test
> ```

> **NOTE**
>
> - The tests checks following operations
>   - Matrix I/O operations
>   - Matrix converting operations
>   - Arithmetic operations with COO/CSC/CSR
>   - Arithmetic operations with simplified COO/CSC/CSR
>   - Random sparse matrix, dense vector, and sparse vector generating process

> - The process must be done when there are modifications in the listed operations to check the updates do not make bugs.
> - The new operations need to be added to the process when a new operation is added to the listed operations.



## About the non-standard input format

> - Non-standard input format **.dvec** are designed for this project
>
> > - **.dvec**
> >
> >   - It is designed for denoting **dense vector**.
> >
> >   - The first element in the file denotes **length of vector**.
> >
> >   - The remaining elements in the file denote **elements** in the vector.
> >
> >   - To load **length of vector** by **fscanf()**, **%d** needs to be used.
> >
> >   - To load **element** by **fscanf()**, **%lg** needs to be used.
> >
> >   - To generate **.dvec** file for operation, do the followings
> >
> >   - Generate **.txt**, write contents as follow and change the format into **.dvec**
> >
> >   >```.txt
> >   >7
> >   >0
> >   >3
> >   >1
> >   >2
> >   >5
> >   >5
> >   >8
> >   >```
> >   >
> >   >The above example represents dense vector with
> >
> >   - Vector length : 7
> >   - Value : 0 3 1 2 5 5 8
> >