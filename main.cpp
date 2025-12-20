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

void defineColumns(); 



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
                defineColumns();
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

void defineColumns() { 
    // Ask for column count 
    cout << "\nDefine number of columns (max 10): ";
    
    while (!(cin >> currentColCount) || currentColCount < 1 || currentColCount > MAX_COLS) {
        cout << "Error: Please enter a number between 1 and " << MAX_COLS << ": ";
        cin.clear(); // Clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Dump bad input
    }

    // 2. Clear buffer to remove the leftover 'Enter' key
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // Loop to make each column
    for (int i = 0; i < currentColCount; i++) 
    {
        // Since from the input we are required to Determine the 
        // column name and data type we have to split the inputs 
        bool validFormat = false; // Assume the input is false until we check it
        
        while (!validFormat) // IF true
        {
            string RawInput; // THe var for StudentID (INT)
            cout << "Enter column " << (i + 1) << " name: "; // User types: StudentID (INT)
            
            // *** FIX: Removed cin.ignore() from here so it doesn't delete your input ***
            
            getline(cin, RawInput);

            // *** FIX: Added this to handle accidental Empty Enters safely ***
            if (RawInput.empty()) continue; 

            // Locate datatpye from input
            // Find the "(" and the ")" 
            // size_t = unsigned integer for position
            size_t openBracket = RawInput.find('(');        
            size_t closeBracket = RawInput.find(')');
        
            // Check if "()" exist and is in the right order 
            if (openBracket != string::npos && closeBracket != string::npos && closeBracket > openBracket) 
            // string::npos = No position or not found 
            {
                string extractedName = RawInput.substr(0, openBracket);
                // from the string, take from index 0 to openBracket for NAME
                if (!extractedName.empty() && extractedName.back() == ' ') // Remove extra spaces
                {
                    extractedName.pop_back();
                }
            
                // Extract Type
                // Start after '(', Length = (9 - 5 - 1) = 3
                string extractedType = RawInput.substr(openBracket + 1, closeBracket - openBracket - 1);

                // 3. Clean up spaces around the type (e.g. " INT " -> "INT")
                while (!extractedType.empty() && extractedType.front() == ' ') extractedType.erase(0, 1);
                while (!extractedType.empty() && extractedType.back() == ' ') extractedType.pop_back();

                // Validate datatype
                if (extractedType == "INT" || extractedType == "TEXT") 
                {
                    columns[i].name = extractedName;
                    columns[i].type = extractedType;
                    validFormat = true; // Breaks the loop
                } 
                else 
                {
                    cout << "Error: Type must be exactly INT or TEXT inside brackets. Found: \"" << extractedType << "\"\n";
                }
            } 
            else
            {
                cout << "Error: Invalid format. Please use format: Name (TYPE). E.g., StudentID (INT)\n";
            }
        } 
    }
    cout << "\nSheet structure created successfully.\n";
}

