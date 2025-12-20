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
    if (current_size < 100) {
        cout<<"YOUR ID: "<<endl;
        cin >> student_amount[current_size].id;

        cout<<"YOUR NAME: "<<endl;
        cin >> student_amount[current_size].name;

        cout<<"YOUR PRESENCE (1 for present, 0 for absent): "<<endl;
        cin >> student_amount[current_size].present;
        current_size++;

        cout << "Student status is added successfully!!!" << endl;
    } else {
        cout << "Attendance sheet is full!" << endl;
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