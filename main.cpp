#include <iostream>
#include <string>
#include <limits>

using namespace std;


//Constants 
const int MAX_ROWS = 100;
const int MAX_COLS = 10;

struct AttendanceRow {
    string cells[MAX_COLS];
};

struct Column {
    string name;
    string type; 
};

AttendanceRow sheet[MAX_ROWS];
Column columns[MAX_COLS];     
int currentRowCount = 0;     
int currentColCount = 0;      

string sheetName = "";

//Functions 

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


void initializeSheet() {
    cout << "\n===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "===========================================\n";
    cout << "Enter attendance sheet name: ";

    getline(cin, sheetName);
    
    cout << "Attendance sheet \"" << sheetName << "\" created successfully.\n";
}

void viewSheet() {
    if (currentRowCount == 0) {
        cout << "\nSheet is empty.\n";
        return;
    }

    cout << endl;
    cout << "-------------------------------------------" << endl;
    cout << "View Attendance Sheet (CSV Mode)" << endl;
    cout << "-------------------------------------------" << endl;

    // 1. Print Headers
    for (int i = 0; i < currentColCount; i++) {
        cout << columns[i].name;
        if (i < currentColCount - 1) cout << ", ";
    }
    cout << endl;

    // 2. Print Data Rows
    for (int i = 0; i < currentRowCount; i++) {
        // Inner Loop: Print each cell for this student
        for (int j = 0; j < currentColCount; j++) {
            cout << sheet[i].cells[j];
            if (j < currentColCount - 1) cout << ", ";
        }
        cout << endl;
    }
}

void insertRow() {
    if (currentColCount == 0) {
        cout << "Error: You must define columns first." << endl;
        return;
    }

    if (currentRowCount < MAX_ROWS) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n-------------------------------------------" << endl;
        cout << "Insert New Attendance Row" << endl;
        cout << "-------------------------------------------" << endl;

        // DYNAMIC LOOP: Run once for every column the user defined
        for (int i = 0; i < currentColCount; i++) {
            
            cout << "Enter " << columns[i].name << ": ";
            
            if (columns[i].type == "INT") {
                // LOGIC FOR INTEGERS (ID)
                int tempVal;
                while(!(cin >> tempVal)) {
                    cout << "Error: " << columns[i].name << " must be a number (INT). Try again: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                
                sheet[currentRowCount].cells[i] = to_string(tempVal);
                
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            } 
            else {
                // LOGIC FOR TEXT (Name)
                getline(cin, sheet[currentRowCount].cells[i]);
            }
        }

        currentRowCount++;
        cout << "Row inserted successfully." << endl;

    } else {
        cout << "Error: Sheet is full!" << endl;
    }
}


int main() {

    int choice;

    initializeSheet();

    //Main menu
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
                defineColumns();
                break;
            case 2:
                insertRow(); 
                break;
            case 3:
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



