# LSB

## Content
1. [How does the program work?](#how-does-the-program-work)
2. [How to install and run?](#how-to-install-and-run)

## How does the program work?

Least Significant Bit (LSB) steganography is a simple, yet effective method to hide data within image files. By modifying the least significant bits of pixel values, we can encode hidden information without significantly affecting the appearance of the image.

The provided program includes two main functions:
- `hideInPng`: Hides data from a specified file within a PNG image.
- `extractFromPng`: Extracts hidden data from a PNG image.

### Hiding Data

To hide data within a PNG image, the `hideInPng` function is used. It reads the image and the file to be hidden, modifies the least significant bits of the image pixels, and writes the modified image to a new file.

### Extracting Data

To extract hidden data from a PNG image, the `extractFromPng` function is used. It reads the modified image, retrieves the hidden data from the least significant bits of the image pixels, and writes the extracted data to a new file.

## How to install and run?

### Prerequisites

Ensure you have the necessary library for handling PNG files:

```bash
sudo apt-get install libpng-dev
```
### Compilation

Compile the provided C program using the following command:

```bash
gcc -o main main.c -lpng
```