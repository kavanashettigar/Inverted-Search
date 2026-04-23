# Inverted-Search
This project implements an inverted search system to efficiently organize and retrieve words from multiple text files.
It uses a hash table to store unique words, while linked lists maintain file names and their occurrence count. The system minimizes repeated file access, improving search performance.

# Features
- Create database from multiple files
- Search for words across files
-  Display stored data
- Save database to file
- Update existing database
- Fast retrieval using hashing
  
# Technologies Used
- Advanced C
- Data Structures
- File Handling
- Pointers
- Dynamic Memory Allocation
- Structures
- Command Line Arguments
- Makefile

# How to Run
1. Compile the program using: gcc *.c -o search
2. Run the executable: ./search <file1> <file2> ...
