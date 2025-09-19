# Student Gradebook Program

## Overview
This program is a simple **student gradebook system** that allows users to enter student names and grades, then evaluates and displays class statistics. It supports two modes of input:
- **Counter-controlled loop**: Enter a fixed number of students.
- **Sentinel-controlled loop**: Enter students until the stop word `"[STOP]"` is typed as a student name.  

After data entry, the program prints each student’s information along with Pass/Fail status and calculates overall class statistics including the average, highest, and lowest grades.  

---

## Files
- `mini_gradebook.cpp` — Source code for the program  

---

## Requirements
- A C++ compiler such as **g++**  
- Standard C++ libraries (iostream, vector, cmath, iomanip)  

---

## Compile Instructions
Using `g++`: g++ -o gradebook main.cpp

## Run Instructions
./gradebook
---

## Usage
1. Run the program.  
2. Choose a menu option:
   - **1**: Counter-controlled loop — enter a fixed number of students.
   - **2**: Sentinel-controlled loop — enter students until the stop word `"[STOP]"` is typed.
   - **3**: Quit program.  
3. After data entry, the program displays:
   - Each student’s name, grade, and pass/fail status.  
   - Class total number of students, average, highest grade, and lowest grade.  
