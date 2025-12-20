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

struct AttendanceRow {
    int studentID;
    string name;
    string status; 
};

struct Column {
    string name;
    string type; // "INT" or "TEXT"
};

AttendanceRow sheet[MAX_ROWS];
Column columns[MAX_COLS];     
int currentRowCount = 0;     
int currentColCount = 0;      

string sheetName = "";


void initializeSheet() {
    cout << "\n===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "===========================================\n";
    cout << "Enter attendance sheet name: ";

    getline(cin, sheetName);
    
    cout << "Attendance sheet \"" << sheetName << "\" created successfully.\n";
}

//viewSheet (CSV Format)
void viewSheet() {

    cout << endl;
    cout << "-------------------------------------------" << endl;
    cout << "View Attendance Sheet (CSV Mode)" << endl;
    cout << "-------------------------------------------" <<endl;

    // Print column headers
    for (int i = 0; i < currentColCount; i++) {
        cout << columns[i].name;
        if (i < currentColCount - 1) cout << ", ";
    }
    cout << endl;

    // Print attendance rows
    for (int i = 0; i < currentRowCount; i++) {
        cout << sheet[i].studentID << ", ";
        cout << sheet[i].name << ", ";
        cout << sheet[i].status << endl;
    }
}

int main() {

    int choice;

    initializeSheet();

    do {
        cout << "\n-------------------------------------------";
        cout << "\nMAIN MENU";
        cout << "\n-------------------------------------------";
        cout << "\n1. Define Columns";
        cout << "\n2. Insert New Attendance Row";
        cout << "\n3. View Attendance Sheet";
        cout << "\n4. Exit";
        cout << "\n\nEnter choice: ";
        cin >> choice;

        // Validation loop to handle non-integer inputs for menu
        while(cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input. Please enter a number (1-4): ";
            cin >> choice;
        }

        switch (choice) {
            case 1:
                //defineColumns(); 
                cout << "1";
                break;
            case 2:
                //insertRow(); 
                cout << "2";   
                break;
            case 3:
                //viewSheet(); 
                viewSheet();  
                break;
            case 4:
                cout << "\nExiting program...\n";
                break;
            default:
                cout << "\nError: Invalid choice. Try again.\n";
        }

    } while (choice != 4);
    
    return 0;
}