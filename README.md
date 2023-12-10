
# AVL Trees Project

## Overview
This project focuses on constructing and evaluating height-balanced binary search trees (BSTs) using AVL tree principles. The main tasks include handling insertion and deletion operations while maintaining the height balance of the tree.

## Features
- Construction of height-balanced BSTs from a sequence of insertion and deletion operations.
- Support for duplicate keys in the tree.
- Rotation operations to maintain tree balance after each modification.
- Evaluation of tree properties including BST validation and height balance.

## Files
- Source files (.c) and header files (.h) implementing the AVL tree operations.
- `hbt.h`: Provided header file defining the tree node structure (Tnode).

## Tree Node Structure
- The tree node (`Tnode`) structure includes key and balance fields, as well as pointers to left and right child nodes.
- Key field: 29-bit signed integer.
- Balance field: 3-bit signed integer representing the balance of the node.

## How to Run
1. Compile the program using the following command:
   ```
   gcc -std=c99 -pedantic -Wvla -Wall -Wshadow -O3 *.c -o pa2
   ```
2. Building a height-balanced BST:
   ```
   ./pa2 -b operations_input_file tree_output_file
   ```
   This reads operations from `operations_input_file` and writes the tree to `tree_output_file`.

3. Evaluating a height-balanced BST:
   ```
   ./pa2 -e tree_input_file
   ```
   This evaluates the tree specified in `tree_input_file` and prints the results to stdout.

