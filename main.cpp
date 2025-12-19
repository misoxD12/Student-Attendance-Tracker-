// *********************************************************
// Program: AttendanceTracker.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT3L
// Trimester: 2530
// Member_1:
// Member_2: 
// Member_3: 
// Member_4: 
// *********************************************************
// Task Distribution
// Member_1: Main Menu Loop, Initialize Sheet, Create Term, Count Rows
// Member_2: Insert Row, Update Row
// Member_3: View Sheet (CSV Format), Delete Row
// Member_4: Define Columns, File I/O (Save to File, Read from File)
// *********************************************************

// ==========================================
// SHARED GLOBAL VARIABLES & STRUCTURES
// ==========================================

#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int MAX_ROWS = 100;
const int MAX_COLS = 10;

string sheetName = "";


void initializeSheet() {
    cout << "\n===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "===========================================\n";
    cout << "Enter attendance sheet name: ";

    getline(cin, sheetName);
    
    cout << "Attendance sheet \"" << sheetName << "\" created successfully.\n";
}

int main() {

    initializeSheet();
    
    return 0;
}