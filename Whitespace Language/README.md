### Whitespace language

Status: in development;


This program converts syllables to 1 or 0. And extracts strings, then extracts the last 8 bits from the string and converts them to syllables.

### Currently, there is no full support for Whitespace Language.


## Content 
1. [How does the program work?](#how-does-the-program-work)
2. [How to install and run?](#how-to-install-and-run)
    - [Linux](#linux)
    - [Windows](#windows)


## How does the program work?


You need to have the **input.txt** file in the project folder.

Run the program and the program will go through **input.txt** and extract 
``` 
' ', '\t', '\n' 
```
then convert them to 0 and 1. After that, the program will check the number of bits in the strings 
``` C
if (line_length >= 8) 
```
then it takes last 8 bytes and converts them to a character. 

Finally, the program will print the result.





## How to install and run?
### Linux

1. **Open a terminal and navigate to the folder where your project is located using the `cd` command:** 

    ```bash
    cd Whitespace\ Language/
    ```

2. **Use the G++ compiler to compile the program. Run the following command:** 

    ```bash
    g++ -o main main.cpp
    ```

3. **After compiling, run the following command to run the program:** 

    ```bash
    ./main
    ```

### Windows
1. Install linux. ^._.^
2. [Run program.](#linux)
3. ...