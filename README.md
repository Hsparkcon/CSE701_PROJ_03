# CSE 701 Proj 03 - Outlier detection by Robust Regression

## Description

- The code is designed to perform following operations.

  - Computing parameters (slope and intercept) of **best line of fit** by robust linear regression with M-estimation.
  
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
> > - Please do the followings to solve the **WARNING MESSAGE**
> >
> >   ```bash
> >   make clean
> >   make
> >   ```
> >
>
> > #### For Windows environment
> >
> > - **NOTE** It is okay to ignore error message related to *ALL_BUILD*
> >
> > 1. Open CSE701_PROJ_03.sln
> > 2. Press Local Windows dubugger
> > 3. Relocate proj_r.exe under Release directory to where input data is.
> >




## Using the executable

>Please relocate the generated executable where the user want by default
>
>> #### For Linux OS
>> ```bash
>> ./proj_r weight_func detect_func observed_data.dvec
>> ```
>
>
>
>> #### For Windows OS
>> ```bash
>> ./proj_r.exe weight_func detect_func observed_data.dvec
>> ```
>
>
>
>> #### Example 1
>> - Input
>> ```bash
>> ./proj_r bisquare standardized_residual observed_data.dvec
>> ```
>> - output
>> ```bash
>> Computed slope: 2.000000e+00
>> Computed intercept: 3.000000e+00
>> Detected outliers: 22 out of 100
>> ```
>> - The above input will computes parameters for best line of fit by using Robust Regression with **bisquare** as its weight function, and differentiate **inlier** and **outlier** in the observed data point using **standardized residual** as outlier detection method.
>
>
>
>> #### Example 2
>> - Input
>> ```bash
>> ./proj_r
>> ```
>> - output
>> ```bash
>> The program is designed to perform linear regression and detect outlier.
>> 
>> First Input
>>   Weight function for robust regression
>>   Please, select one from the list from the link
>>   https://www.mathworks.com/help/stats/robustfit.html#mw_48d239e7-b4dc-4a5e-8e97-ba7c34ce85b9
>>   
>> Second Input
>>      Type of outlier detection method
>>      Please choose one between 'weight' and 'standardized_resdual'
>>      
>> Third Input & Forth Input
>>      Path to the first file - observed x data.
>> 	    Path to the second file - observed y data.
>> 	    
>> Example Input for Linux
>>   proj_r bisquare standardized_residual observed_x.dvec observed_y.dvec
>> Example Input for Windows
>>   proj_r.exe bisquare standardized_residual observed_x.dvec observed_y.dvec
>> ```
>> - Executing program without input parameter will provide basic description about how to use the program.
>
>
>
>> #### INPUTS
>> > **weight_func** 
>> >
>> > - specifies weight function which will be used in Robust Regression process to adjust effectiveness of given data point. 
>> > - The data points with weight near 1 has bigger effectiveness while the data points near 0 has smaller effectiveness. 
>> > - Please check the [link](https://www.mathworks.com/help/stats/robustfit.html?s_tid=doc_ta#mw_48d239e7-b4dc-4a5e-8e97-ba7c34ce85b9) for detail. 
>> > - The followings are list of weight function option for the program.
>> >   - andrews
>> >   - bisquare - Suggested option
>> >   - cauchy
>> >   - fair
>> >   - huber
>> >   - logistic
>> >   - talwar
>> >   - welsch
>> 
>> > **detect_func**
>> > - Specifies outlier detection function which will be used in Outlier Detection process to compute standard point of define what is outlier in the data.
>> > - The followings are list of outlier detection method for the program.
>> >   - standardized_residual - Suggested option
>> >   - weight - Not suggested option
>> 
>> > **observed_data.dvec**
>> >
>> > - The input data which contains coordinate of observed data
>> >
>> > - For example, if the given data set is a record of the amount of salary according to years of employment, 
>> >
>> >   - years of employment the collection of independent variables
>> >   - the amount of wages  the set of dependent variables.
>> >
>> >   are included in the file.
>> >
>> > - The length (= number of elements in the file) must match each other.


​     
## Using the project as part of another project

> - The following is simple explanation of how to use the classes in the project as part of another project.
>
> - To see the detailed examples of using the classes, please check the code under the example directory
>
> - The classes its name starts with FACADE keyword are the class designed for convenience of users who are not experienced in C/C++ or who want to use default setting.
>
> - The classes automatically validate inputs and initialize everything required for proceeding computation.
>
> - The classes its name does not start with FACADE requires manual initialization of input and output data such as vector size.
>
>   
>
> >   #### Robust Regression
> >   - Please includes **facade_regression.hpp**
> >   - Instantiates **FACADE_REGRESSION** object with required input variables.
> >   - Use member function **proceed_regression()** to perform regression
> >   - Use member function **get_estimates(double &m_slope, double &b_intercept)** to get estimates.
> >   - Use member function **get_w_weight(std::vector<double> &w_weight)** to get weights.
>
> 
>
> > #### Outlier Detection
> >
> > - Please includes **facade_detection.hpp**
> > - Instantiates **FACADE_DETECTION** object with required input variables.
> > - Use member function **proceed_detection(DETECTION_METHOD target_method)** to perform detection.
> > - Use member function **get_outliers(std::vector<double> &x_outliers, std::vector<double> &y_outliers)** to get outliers.
> > - Use member function **get_inliers(std::vector<double> &x_inliers, std::vector<double> &y_inliers)** to get inliers.




## Operator Overloading in Project 03

- Because user-defined data structure is not used in the project 03, none of operators are overloaded in the project 03.
  
    

## About the non-standard input format

> - Non-standard input format **.dvec** are designed for this project
> >
> >   - It is designed for store observed data of "linear system".
> >   - The first element in the file denotes **number of data points**.
> >   - The remaining elements in the file denote **observed data**.
> >   - **Left** elements are independent variables (X-Axis) of observed.
> >   - **Right** elements are dependent variables (Y-Axis) of observed.
> >
> >   ```.txt
> >   5
> >   1 5
> >   2 7
> >   3 9
> >   4 11
> >   5 13
> >   ```
> >   
> >   The above example represents
> >   
> >   - Number of elements : 5
> >   - Data Points : (1, 5), (2, 7), (3, 9), (4, 11), (5, 13)
> > 



## About the standard input format

> - Standard input format **.csv** can be used for this project
> >
> >   - The first element in the file denotes **number of data points**.
> >   - The remaining elements in the file denote **observed data**.
> >   - **Left** elements are independent variables (X-Axis) of observed.
> >   - **Right** elements are dependent variables (Y-Axis) of observed.
> >   - **Delimiter comma** uses to separate values for spreed sheet form.
> >
> >   ```.txt
> >   5
> >   1, 5
> >   2, 7
> >   3, 9
> >   4, 11
> >   5, 13
> >   ```
> >   
> >   The above example represents
> >   - Number of elements : 5
> >   - Data Points : (1, 5), (2, 7), (3, 9), (4, 11), (5, 13)