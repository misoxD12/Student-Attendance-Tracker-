// *********************************************************
// Program: AttendanceTracker.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT4L
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

using namespace std;
struct Student{      
    string id;   
    string name;
    bool present;
} ;/*this is the structure to group all the related things together*/

Student student_amount[100];/*this is an array of structures to store multiple students' data*/
int current_size = 0;

void insertRow() {
    // 1. Safety Check: Make sure columns exist first!
    if (currentColCount == 0) {
        cout << "Error: You must define columns (Option 1) before adding data." << endl;
        return;
    }

    // 2. Check if the sheet is full
    if (currentRowCount < MAX_ROWS) {
        cout << "\n-------------------------------------------" << endl;
        cout << "Insert New Attendance Row" << endl;
        cout << "-------------------------------------------" << endl;

        // --- COLUMN 1 (ID) ---
        // Instead of hardcoding "YOUR ID", we use columns[0].name
        cout << "Enter " << columns[0].name << ": "; 
        cin >> sheet[currentRowCount].studentID;

        // Error Handling for ID (Member 4/All responsibility)
        while(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number for " << columns[0].name << ": ";
            cin >> sheet[currentRowCount].studentID;
        }

        // --- COLUMN 2 (NAME) ---
        cout << "Enter " << columns[1].name << ": ";
        cin.ignore(); // Clear the buffer before getline
        getline(cin, sheet[currentRowCount].name);

        // --- COLUMN 3 (STATUS) ---
        cout << "Enter " << columns[2].name << ": ";
        cin >> sheet[currentRowCount].status;

        // Increment the counter
        currentRowCount++;
        cout << "Row inserted successfully." << endl;

    } else {
        cout << "Error: Attendance sheet is full!" << endl;
    }
}

void updateRow(){
    string id;
    bool found = false;
    cin.ignore(1000, '\n'); // Clear input buffer242uc242fc
    cout << "Enter Student ID to u want to update: "; 
    getline(cin, id);
    
    for (int i = 0; i < current_size; i++) {
        if (student_amount[i].id == id) {
            found = true;
            cout << "Record Found! Current Name: " << student_amount[i].name << endl;

            string newName;
            cout << "Enter New Name (or type 'skip' to keep current name): ";
            
            getline(cin, newName);

            if (newName != "skip") {
                student_amount[i].name = newName;
            }

            cout << "Enter new presence (1 for present, 0 for absent): ";
            cin >> student_amount[i].present;

            cout << "Changes saved successfully!" << endl;
            break;
        }
    }
    if (!found) {
        cout << "Error: ID not found." << endl;
    }
}
int main(){
    insertRow();
    updateRow();
    
    return 0;
}