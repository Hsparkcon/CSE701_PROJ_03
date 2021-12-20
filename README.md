# CSE 701 Project 03 - Outlier detection by Robust Regression

## Description
>
> - The code is designed to perform following operations.
>
> - Computing parameters (slope and intercept) of **best line of fit** by robust linear regression with M-estimation.
>
> - Detecting outliers in the given data by
>   - standardized residual
>   - weight of each data point given during robust regression
>
> - Generating visualized result (in BMP format) that shows
>   - line of best fit for the input data
>   - observed data points
>   - detected outlier data points
>   - detected inlier data points

&nbsp;

## Environment
>
> - Windows/Linux OS
> - Command-line interface is required
> - Graphic user interface is not supported

&nbsp;

## Prerequisite
>
> - [CMAKE](https://cmake.org/) version **3.18.1** or above
> - C/C++ compiler that supports **C++20** standard
> - Any **text** file editor
> - Any **iamge** viewer

&nbsp;

## Compilation
>
>```bash
>mkdir build
>cd build
>cmake ..
>```
>
>
>### For Linux environment
>
> > ```bash
> > make
>> ```
>> **NOTE**
>> - If following **WARNING MESSAGE** is returned
>>   ```bash
>>   make[2]: Warning: File 'CMakeFiles/proj_r.dir/depend.make' has modification time 0.X s in the future
>>   make[2]: warning:  Clock skew detected.  Your build may be incomplete.
>>   ```
>> - Please do the followings to solve the **WARNING MESSAGE**
>>   ```bash
>>   make clean
>>   make
>>   ```
>
>### For Windows environment
>
>> - **NOTE** It is okay to ignore error message related to *ALL_BUILD*
>> 1. Open CSE701_PROJ_03.sln
> > 2. Press Local Windows debugger
> > 3. Relocate proj_r.exe under Release directory to where input data is.

&nbsp;

## Using the executable

>Please relocate the generated executable where the user want by default
>
>### For Linux OS
>> ```bash
>> ./proj_r weight_func detect_func observed_data.dvec
>> ```
>
> ### For Windows OS
> 
>> ```bash
>> ./proj_r.exe weight_func detect_func observed_data.dvec
>> ```
>
>### Example 1
>
> > - Input
> > ```bash
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
>### Example 2
>
>> - Input
>> ```bash
> > ./proj_r
> > ```
>> - output
>> ```bash
>> The program is designed to perform linear regression and detect outlier.
>> First Input
>> Weight function for robust regression
>> Please, select one from the list from the link
>> https://www.mathworks.com/help/stats/robustfit.html#mw_48d239e7-b4dc-4a5e-8e97-ba7c34ce85b9
>> Second Input
>> Type of outlier detection method
>> Please choose one between 'weight' and 'standardized_resdual'
>> Third Input
>> Path to the first file - observed x data.
>> Path to the second file - observed y data.
>> Example Input for Linux
>> proj_r bisquare standardized_residual observed_data.dvec
>> Example Input for Windows
>> proj_r.exe bisquare standardized_residual observed_data.dvec
>> ```
>
>### INPUTS
>
>> **weight_func**
>> - specifies weight function which will be used in Robust Regression process to adjust effectiveness of given data point.
>> - The data points with weight near 1 has bigger effectiveness while the data points near 0 has smaller effectiveness.
>> - Please check the [link](https://www.mathworks.com/help/stats/robustfit.html?s_tid=doc_ta#mw_48d239e7-b4dc-4a5e-8e97-ba7c34ce85b9) for detail.
> > - The followings are list of weight function option for the program.
> >   - andrews   
>>   - bisquare - Suggested option
>>   - cauchy   
>>   - fair
>>   - huber
>>   - logistic
>>   - talwar
>>   - welsch
>
>>   **detect_func**
>> - Specifies outlier detection function which will be used in Outlier Detection process to compute standard point of define what is outlier in the data.
>> - The followings are list of outlier detection method for the program.
>>  - standardized_residual - Suggested option
>>  - weight - Not suggested option
>>   
>> **observed_data.dvec**
>> - The input data which contains coordinate of observed data.
>> - For example, if the given data set is a record of the amount of salary according to years of employment,
>>   - years of employment the collection of independent variables
>>   - amount of wages  the set of dependent variables.
>> - The length (= number of elements in the file) must match each other.
>

&nbsp;

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
> ### Robust Regression
> 
> > - Please includes **facade_regression.hpp**
> > - Instantiates **FACADE_REGRESSION** object with required input variables.
>> - Use member function **proceed_regression()** to perform regression
>> - Use member function **get_estimates()** to get estimates.
>> - Use member function **get_w_weight()** to get weights.
>
> #### Outlier Detection
> 
> > - Please includes **facade_detection.hpp**
> > - Instantiates **FACADE_DETECTION** object with required input variables.
> > - Use member function **proceed_detection()** to perform detection.
> > - Use member function **get_outliers()** to get outliers.
>> - Use member function **get_inliers()** to get inliers.

&nbsp;

## Operator Overloading in Project 03

> - Because user-defined data structure is not used in the project 03, none of operators are overloaded in the project 03.

&nbsp;

## Error codes in Project 03

 ### READ ERROR
>
>Error code starts with READ ERROR is defined in DATA_READ class
>
>#### FILE DOES NOT EXIST
>
>> - It happens when there is no file exist at the given path.
>> - It generally happens due to a word mismatch between an actual file name and a provided file name.
>> - Please check the file name and the command-line arguments.
>
>#### INCORRECT INPUT
>
>> - It happens when the given path is not a file.
>> - Please ensure that the path is a file, not a directory.
>
>#### INCORRECT FILE FORMAT
>
>> - It happens when the target file's format is not one of .dvec or .csv
>> - Please ensure that the file format is .dvec or .csv
>
>#### FAILED TO OPEN A FILE
>
>> - It happens when the target file cannot be opened.
>> - Please check that the file is not damaged.

### WRITE ERROR

> Error code starts with WRITE ERROR is defined in DATA_WRITE class
>
> #### NOTHING TO WRITE
>
> > - If happens when empty array is received.
> > - Please ensure that input array is not empty.
>
> #### VECTOR LENGTH MISMATCH
>
> > - It happens when the length of two arrays are not matching.
> > - Please ensure that the input arrays' lengths is matching.
>
> #### INCORRECT FILE FORMAT
>
> > - It happens when a file format denoted at file name is not supported.
> > - Please ensure that file format contained in the output file is .dvec or .csv
>
> #### FAILED TO CREATE A FILE TO WRITE RESULT
>
> > - It happens when a file writes out result cannot be generated.
> > - Unknown reason.

### BMP WRITE ERROR

> Error code starts with BMP WRITE ERROR is defined in BMP_OUT class
>
> #### CANNOT ACCESS THE TARGETED COORDINATE
>
> > - It happens when the targeted coordinate is larger than the image size.
> > - Please ensure that the targeted coordinate is not larger than the image size.
>
> #### NO DATA TO GENERATE .BMP FILE
>
> > - It happens when the array storing pixel colour data is empty.
> > - Please ensure that the pixel data array is filled with data.
>
> #### INCORRECT FILE FORMAT
>
> > - It happens when a file format denoted at file name is not supported.
> > - Please ensure that file format contained in the output file is .bmp
>
> #### FAILED TO CREATE A BMP FILE TO PLOT RESULT
>
> > - It happens when a file to write-out pixel data cannot be generated.
> > - Unknown reason.

### OUTLIER DETECTION ERROR

> Error code starts with OUTLIER DETECTION ERROR is defined in OUTLIER_DETECTION class.
>
> #### VECTOR LENGTH MISMATCH
>
> > - It happens when the length of two arrays are not matching.
> > - Please ensure that the input arrays' lengths is matching.

### OUTLIER PLOT ERROR

> Error code starts with OUTLIER PLOT ERROR is defined in OUTLIER_PLOT class.
>
> #### VECTOR LENGTH MISMATCH
>
> > - It happens when the length of two arrays are not matching.
> > - Please ensure that the input arrays' lengths is matching.

### FACADE REGRESSION ERROR

> Error code starts with FACADE REGRESSION ERROR  is defined in FACADE_REGRESSION class.
>
> #### DATA NOT INITIALIZED
>
> > - It happens when data to compute robust regression is not given/initialized.
> > - Please ensure that the required variables are initialized before computation.
>
> #### WEIGHT FUNCTION NOT CHOSEN
>
> > - It happens when required data is initialized but the weight function is not selected.
> > - Please ensure that the weight method is selected.

### FACADE DETECTION ERROR

> Error code starts with FACADE DETECTION ERROR  is defined in DETECTION class.
>
> #### CANNOT PROCEED OUTLIER DETECTION BY STANDARDIZED RESIDUAL
>
> > - It happens when data to proceed outlier detection by standardized residual is not given/initialized.
> > - Please ensure that the required data is initialized.
>
> #### CANNOT PROCEED OUTLIER DETECTION BY WEIGHT
>
> > - It happens when data to proceed outlier detection by weight data is not given/initialized.
> > - Please ensure that the required data is initialized.

&nbsp;

## About the non-standard input format

> - Non-standard input format **.dvec** are designed for this project
> - It is designed for store observed data of "linear system".
> - The first element in the file denotes **number of data points**.
> - The remaining elements in the file denote **observed data**.
> - **Left** elements are independent variables (X-Axis) of observed.
> - **Right** elements are dependent variables (Y-Axis) of observed.
> - Example
>   - Number of elements : 5
>   - Data Points : (1, 5), (2, 7), (3, 9), (4, 11), (5, 13)
> 
>   ```.txt
>   5
>   1 5
>   2 7
>   3 9
>   4 11
>   5 13
>   ```
>

&nbsp;

## About the standard input format

> - Standard input format **.csv** can be used for this project
> - The first element in the file denotes **number of data points**.
> - The remaining elements in the file denote **observed data**.
> - **Left** elements are independent variables (X-Axis) of observed.
> - **Right** elements are dependent variables (Y-Axis) of observed.
> - **Delimiter comma** uses to separate values for spreed sheet form.
> - Example
>   - Number of elements : 5
>   - Data Points : (1, 5), (2, 7), (3, 9), (4, 11), (5, 13)
>
>   ```.txt
>   5
>   1, 5
>   2, 7
>   3, 9
>   4, 11
>   5, 13
>   ```
