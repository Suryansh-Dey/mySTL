# Aim
To make the you best competitive programmer on earth!
# Documentation
Read `mySTL.hpp` for documentation of the library.  
Yup I m that lzy
# mySTL.hpp
You can add 
```cpp
#include "path_to_mySTL_folder/mySTL/mySTL.hpp"
```
like any other library and thanks to `mystl.hpp.gch`, pre-compiled header, present in the same directory as `mySTL.hpp`, compilation time cutts of by 75%!!  
- That saves you 3 seconds of boring time!
- It internally includes all standard C++ libarary. No more hardwork
# mySTL.exe 
This allows you to submit your code on an online platform, which takes a single main file, by copy pasting mySTL library just above your code
## For mac or linux 
Fuck off mac or linux users, you are too fancy (delete the bin/mySTL.exe then complie the src/mySTL.cpp by running following command on terminal  
First cd to the mySTL folder then run
```
g++ -std=c++17 src/mystl.cpp -o bin/mySTL
```
and rest of everything will work the same on linux or mac device too)
## Arguments
- It takes two command line argument, your_source_file_path output_file_path  
- If only one argument of source_file_path provided, the default output_file_name is choosen to be MYSTL_source_file_name and stored at source_file_directory
## How to use
It removes first line of your code assuming it to be 
```cpp
#include "mySTL/mySTL.hpp"
```
and adds the whole source code of mySTL library only  
Example:  
On terminal run
```
mystl main.cpp
```
and you will get a `MYSTL_main.cpp` file which has 1st line replaced by mySTL source code
## Setup
To use it like a command line program from every location you will have to
following steps:
1. open All programs (window key on windows)
2. search edit environment variables and press enter
3. click on environment variables button
4. under `user variables for <user_name>` click on `Path`
5. click edit
6. paste the location of mySTL/bin folder on at last line
7. finally, hit ok.  
Now open a new terminal and run
```
mystl --version
```
If this prints `This is mySTL version <version_number>`, YOU ARE ALL SET!! else, you messed something. Try cloning the repository again and repeat the same steps
## Flags
- `--version` to get version number
- `--help` to know about arguments it takes
# Adding custom functions
We love freedom, infact that's the whole motivation behind C++ too  
You can go to `mySTL.hpp` file and within the MyStl namespace, you can add your own classes  
To write you definations to them, make a new file in src folder start defining them and THATS ALL!  
mySTL.exe will take care of them too, its not as selfish as you  
- MAKE SURE you include the defination files below `// MYSTL_ENDS` comment of `mySTL.hpp` file for eg. 
```cpp
// MYSTL_END
#include "graph.cpp"
#include "myFile.cpp"
```
Otherwise your editor will keep freeking out
