# Markov Chains Text Generator

A simple text generator using Markov Chains.

## Overview

This program reads a text file, processes it using Markov Chains, and allows users to generate text based on learned patterns. The user specifies the word precision, which determines the size of word groups analyzed. The program then predicts the most likely next word for each group.

## Usage

1. **Word Precision:**
   - The user is prompted to input the `wordPrecision` variable, defining the size of word groups to analyze.

2. **Generating Text:**
   - Choose option `1` to generate text. Input the desired word count for the generated text.

3. **Display Text Details:**
   - Choose option `2` to display details for each group of words.
   
4. **Exiting:**
   - Choose option `3` to exit the program.

## How it Works

- The program reads a text file (`fileIn.txt` by default) and builds a model based on word groups of the specified precision.
- For each group, the program records the words that follow it and their probabilities of appearance.
- Users can generate text based on the learned patterns or explore details of the analyzed text.

## Implementation Details

- The source code (`main.cpp`) contains implementations of Markov Chains and menu-driven functionality.
- Dependencies: `Random.h` and `MyUtilities.h` are included.

## Getting Started

1. Clone the repository.
2. Ensure you have a text file (`fileIn.txt`) for analysis.
3. Build and run the program in a C++ environment (e.g., Visual Studio).

## Contributing

This project was created for study purposes. Contributions are welcome but not actively sought.

## License

This project is licensed under the [MIT License](LICENSE).
