# ZIP

Status: in development;

This program hides the zip archive in the files.

## Content
1. [How does the program work?](#how-does-the-program-work)
2. [How to install and run?](#how-to-install-and-run)
    - [Linux](#linux)
    - [Windows](#windows)
3. [How does hide Zip algorithm work?](#how-does-hide-zip-algorithm-work)
    - [png](#hide-zip-in-png)

## How does the program work?

You need to have the **folder.zip** and **image.png** files in the project folder.

Run the program and it will create an **output.png** in which the zip will be hidden.

## How to install and run?
### Linux

1. **Open a terminal and navigate to the folder where your project is located using the `cd` command:**

    ```bash
    cd ZIP
    ```

2. **Use the GCC compiler to compile the program. Run the following command:**

    ```bash
    gcc -o main main.c
    ```

3. **After compiling, run the following command to run the program:**

    ```bash
    ./main
    ```

### Windows
1. Install linux. ^._.^
2. [Run program.](#linux)
3. ...




## How does hide Zip algorithm work?

### Hide Zip in Png

The program binary reads two files: a PNG file and a ZIP file. It then creates a new file by concatenating the bytes from the PNG file followed by the bytes from the ZIP file. As a result, the new file has the following structure:

```
newFile == png + zip
```

Since the file starts with a PNG header, it is displayed as an image. However, after the PNG data, there is a ZIP header, which can be recognized by archiver programs. These programs can then extract the ZIP contents from the end of the file.
