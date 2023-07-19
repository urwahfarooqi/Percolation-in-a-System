# Percolation-in-a-System
I developed this project using c++ language and SFML library.


Percolation Simulation using SFML

This repository contains a C++ implementation of the Percolation problem with a graphical simulation using the SFML (Simple and Fast Multimedia Library). The Percolation problem is a classic computational problem in statistical physics and computer science, used to model the movement of fluids through porous materials.

Table of Contents
Introduction
Installation
Usage
Input File Format
Visualization
Dependencies
Contributing
License


Introduction
The Percolation problem involves creating an N-by-N grid of sites and randomly opening a fraction of these sites. The objective is to determine whether the top and bottom of the grid are connected through open sites (i.e., percolates) based on the random openings.

This implementation utilizes the Weighted Quick Union algorithm to efficiently model the grid's connectivity and uses SFML to provide a visual representation of the percolation process.



Installation
To run the Percolation simulation, you need to have a C++ compiler and the SFML library installed on your system.
Clone this repository to your local machine.
Make sure you have the SFML library installed.
Compile the code using your preferred C++ compiler.


Usage
After compiling the code, execute the generated binary in your terminal or command prompt. The program will prompt you to provide the path to an input file containing the grid size and the list of opened sites.


Input File Format
The input file should follow the following format:
N  -> Representing N columns and rows
row1 col1
row2 col2
...
-1 -1
N: The grid size (integer).
rowX colX: Coordinates of opened sites, one pair per line (1-indexed). For example, 3 5 means open the site at row 3 and column 5.
-1 -1: This line indicates the end of the list of opened sites.
An example of an input file:

5
1 1
2 2
2 4
3 1
4 4
-1 -1


Visualization
The SFML visualization will display a window showing the grid of sites. Blocked sites are represented by black rectangles, open sites by white rectangles, and filled (percolating) sites by blue rectangles. The visualization will be updated in real-time as the percolation process progresses.


Dependencies
SFML library: Simple and Fast Multimedia Library. Make sure it is installed on your system and properly linked to the project during compilation.
Contributing
Contributions to this project are welcome! If you find any bugs or have suggestions for improvements, feel free to open an issue or submit a pull request.


License
This project is licensed under the MIT License. Feel free to use, modify, and distribute the code for both commercial and non-commercial purposes. Attribution is appreciated but not required.
