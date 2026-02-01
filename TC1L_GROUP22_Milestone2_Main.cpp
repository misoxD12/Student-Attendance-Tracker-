// *********************************************************
// Program: TC1L_GROUP22_Milestone2_Main.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT3L 
// Trimester: 2530
// Member_1: 252UC242SE | CHAI MING SONG | CHAI.MING.SONG1@student.mmu.edu.my | 016-9320289
// Member_2: 252UC242ZC | LEONG KA KIT | LEONG.KA.KIT1@student.mmu.edu.my | 011-58606375
// Member_3: 252UC242YP | YIP YU ZHE | YIP.YU.ZHE1@student.mmu.edu.my | 018-2171599
// Member_4: 252UC241NW | HARSIMRANJEET SINGH SRAU A/L GURDEV SINGH |  HARSIMRANJEET.SINGH.SRAU1@student.mmu.edu.my | 011-11928326
// *********************************************************
// Task Distribution (Milestone 2 - Technical Breakdown)
// Member_1: 
// Member_2: 
// Member_3: 
// Member_4: 
// *********************************************************


#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;


//Constants 
const int MAX_ROWS = 100; //Max students
const int MAX_COLS = 10;  //Max columns

const string MASTER_TERM = "AllTerms.csv";

struct AttendanceRow {
    string cells[MAX_COLS]; //Stores cell values for each column in a row
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

string termName = "";

//Milestone 1 Functions

/*
void initializeSheet() {
    cout << "\n===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "===========================================\n";
    //cout << "Enter attendance sheet name: ";

    //getline(cin, sheetName);
    
    //cout << "Attendance sheet \"" << sheetName << "\" created successfully.\n";
}
*/

void defineColumns() { 

    cout << "\n-------------------------------------------";
    cout << "\nDefine Columns";
    cout << "\n-------------------------------------------";
    // Ask for column count 
    cout << "\nDefine number of columns (max 10): ";
    
    while (!(cin >> currentColCount) || currentColCount < 1 || currentColCount > MAX_COLS) {
        cout << "Error: Please enter a number between 1 and " << MAX_COLS << ": ";
        cin.clear(); // Clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Dump bad input
    }

    if (currentRowCount > 0) {
        cout << "Warning: Redefining columns will clear existing data.\n";
        currentRowCount = 0; // Reset row count
        cout << "Current rows cleared.\n";
    } 
    
    // Clear buffer to remove the leftover 'Enter' key entered in by the user 
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
            cout << "Enter column " << (i + 1) << " name (Format: Name (TYPE)) : "; // User types: StudentID (INT)
                        
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
            
                // Extract Type; the following is just as an exmaple for reference 
                // Start after '(', Length = (9 - 5 - 1) = 3
                string extractedType = RawInput.substr(openBracket + 1, closeBracket - openBracket - 1);

                // 3. Clean up spaces around the type (e.g. " INT " -> "INT")
                while (!extractedType.empty() && extractedType.front() == ' ') extractedType.erase(0, 1);
                while (!extractedType.empty() && extractedType.back() == ' ') extractedType.pop_back();

                // Validate datatype by user
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
                
                // We DO need cin.ignore AFTER this to clean up for the next loop
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

void viewSheet() {
    if (currentRowCount == 0) {
        cout << "\nSheet is empty.\n";
        return;
    }

    cout << endl;
    cout << "-------------------------------------------" << endl;
    cout << "View Attendance Sheet (CSV Mode)" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Sheet Name: " << sheetName << "\n";
    cout << "Total Rows: " << currentRowCount << ", Total Columns: " << currentColCount << "\n";
    cout << "-------------------------------------------" << "\n";


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

//Milestone 2 Functions

//generate attendance sheet 
string getSheetFileName() {
    if (sheetName.empty()) {
        return ""; 
    } 

    //if somehow term is missing, just use sheetname
    else if (termName.empty()) {
        return sheetName + ".csv";
    }

    //combine them: 2530_Week1.csv
    else{
        return termName + "_" + sheetName + ".csv"; 
    }
    
}

//generate term database 
string getDatabaseFileName() {
    if (termName.empty()) {
        return "";
    }

    else{
        return termName + ".csv";
    }
     
}
    

void allTerms() {
    //function to update the Master List of all terms

    // If file doesn't exist, we create it
    if (!InputFile.is_open()) {
        ofstream CreateFile(MASTER_TERM);
        if (CreateFile.is_open()) {
            cout << "[System: Main Index created for the first time]\n"; // prompt that its the first creation 
            CreateFile.close();
        } else {
            cout << "[Error: Could not create system file. Check folder permissions]\n"; // if got issue and cannot be made 
        }
        cout << "No terms have been created yet.\n";
        return; 
    }

    // If file exists, check if empty (cuz if empty then nothing to show user)
    if (InputFile.peek() == ifstream::traits_type::eof()) {
        cout << "No terms have been created yet.\n";
    } 
    // If got data in file,show it
    else {        
        string line;
        while (getline(InputFile, line)) {
            if (!line.empty()) {
                cout << " - " << line << endl;
            }
        }
    }
}

void databaseIndex(){ 
    //function to update the database index for each term


void databaseIndex(){ // 
    string sheetfile = getSheetFileName();
    string dbfile = getDatabaseFileName();
    string sheetentryname = sheetName;

    ifstream inputFile(dbfile);
    //store each line
    string line;
    bool Existsornot = false; // to see if alr in listed or not 

    if(inputFile.is_open()){
        while (getline(inputFile, line)){ 
            if(line == sheetfile){ // check if the input the user gave alr exist in the term csv we have 
                Existsornot = true;
                break; // stop if found 
            }
        }
        inputFile.close();

    }
    inputFile.close();

    if(!Existsornot){ // if dun have yet (meaining is a new one) we add on to the list 
        ofstream outputFile(dbfile, ios::app); // append to avoid overwrite the stuff inside 

        if(outputFile.is_open()){
            outputFile << sheetfile << endl; // add the new one 
            outputFile.close();
            cout << "Database Added " << sheetentryname << " to database index " << dbfile << ".\n";
        }
        else{
            cout << "Error. Unable to update file.\n"; // show error if got issue when saving 
        }
    }
}

string strip(const string& s) { // fucntion to strip whitespaces 
    //Find the index of the FIRST character that is NOT a space, tab, or newline
    size_t first = s.find_first_not_of(" \t\r\n");
    //If cannot find any non-whitespace characters 
    if (string::npos == first) return ""; // means is empty
    //Find the index of the LAST character that is NOT any kind of whitespace 
    size_t last = s.find_last_not_of(" \t\r\n");
    // return back the data from the first non whitespace to last non whitespace
    return s.substr(first, (last - first + 1));
}

void vieworcreateTerm() { // display the output 
    cout << "\n==========================================="<< endl;
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 2"<< endl;
    cout << "==========================================="<< endl;
    cout << "Create School Term (Database)" << endl;
    cout << "\n-------------------------------------------" << endl;
    cout << "All existing terms: " << endl;
    displayTerms(); // display all the avaliable terms 
    cout << "\nEnter term name: " ;
    getline(cin, termName);
    termName = strip(termName);
    bool exists = false;
    ifstream DURIAN(MASTER_TERM);
    string line;
    while(getline(DURIAN, line)) {
        if(line == termName) exists = true; // check if alr got match based on the csv  
    }
    DURIAN.close();

    if(!exists) {
        ofstream BANANA(MASTER_TERM, ios::app); // append to the csv if dont have 
        BANANA << termName << endl;
        BANANA.close();
    }

    //check or create
    ofstream outputFile(getDatabaseFileName(), ios::app); // open file in append mode 
    outputFile.close(); // close it straight away so that (bascially make sure the term file is created)
    cout << "Database " << termName <<" created and loaded"<< endl;
    cout << "Reading attendance data from file..."<< endl;

}

void updateRow() {
    if (currentRowCount == 0) {
        cout << "Error: No rows available to update.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

    string searchTerm;
    cout << "Enter " << columns[0].name << " to search: ";
    getline(cin, searchTerm);

    // Search for the row
    int rowIndex = -1;
    bool isFound = false;

    for (int i = 0; i < currentRowCount; i++) {
        // Check if the first column matches
        if (sheet[i].cells[0] == searchTerm) {
            rowIndex = i;
            isFound = true;
            break;
        }
    }

    if (!isFound) {
        cout << "Error: " << searchTerm << " does not exist." << endl;
        return;
    }

    cout << "Student found in row " << (rowIndex + 1) << ".\n";

    char continueChoice;
// loop for the updaterow
    do {
        cout << "\nWhich column do you want to update?\n";
        for (int i = 0; i < currentColCount; i++) {
            cout << (i + 1) << ". " << columns[i].name << endl;
        }

        int colChoice;
        cout << "Enter column number: ";
        while (!(cin >> colChoice) || colChoice < 1 || colChoice > currentColCount) {
            cout << "Invalid column number. Try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        int colIndex = colChoice - 1;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // clear buffer

        cout << "Enter new value for " << columns[colIndex].name
             << " (current: " << sheet[rowIndex].cells[colIndex] << "): ";

        if (columns[colIndex].type == "INT") {
            int tempVal;
            while (!(cin >> tempVal)) {
                cout << "Error: " << columns[colIndex].name << " must be a number (INT). Try again: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            sheet[rowIndex].cells[colIndex] = to_string(tempVal);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            getline(cin, sheet[rowIndex].cells[colIndex]);
        }

        cout << "Row updated successfully.\n";

        cout << "Do you want to update another data for this row? (Y/N): ";
        cin >> continueChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (continueChoice == 'Y' || continueChoice == 'y');

    cout << "Data is updated.\n";
}

void deleteRow() {
    // Check if sheet is empty
    if (currentRowCount == 0) {
        cout << "Error: Sheet is empty. Nothing to delete." << endl;
        return;
    }
    // Clear input buffer before getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string searchTerm;

    cout << "-------------------------------------------" << endl;
    cout << "Delete Attendance Row" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Enter " << columns[0].name  << " to delete: ";
    getline(cin, searchTerm);

    int foundIndex = -1;

    // Search based on FIRST COLUMN (StudentID)
    for (int i = 0; i < currentRowCount; i++) {
        if (sheet[i].cells[0] == searchTerm) {
            foundIndex = i;
            break;
        }
    }

    // If StudentID not found, show error and exit
    if (foundIndex == -1) {
        cout << "Error: StudentID does not exist." << endl;
        return;
    }

    // Shift rows up to delete whole row
    for (int i = foundIndex; i < currentRowCount - 1; i++) {
        sheet[i] = sheet[i + 1];
    }

    currentRowCount--; // Reduce row count

    cout << "Row deleted successfully." << endl; //Confirm successful deletion
}

void countRows() {
    cout << "\nCount Rows\n-----------------------";
    cout << "\nNumber of rows: " << currentRowCount << "\n";
}

void saveFile() {
    // Get the specific filename for the current sheet
    string filename = getSheetFileName();
    
    // Note: We don't use ios::app here because we want to overwrite 
    // the file with the most recent version of the data.
    ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        cout << "Error: Could not save data to " << filename << endl; //if cant open we display error 
        return;
    }

    // --- Part A: Save Headers of the data---
    for (int i = 0; i < currentColCount; i++) {
        outputFile << columns[i].name << " (" << columns[i].type << ")";
        
        // Add a comma if it's NOT the last column
        if (i < currentColCount - 1) {
            outputFile << ",";
        }
    }
    outputFile << "\n"; // New line after headers

    // --- Part B: Save Rows ---
    // Outer loop: Go through each student row
    for (int i = 0; i < currentRowCount; i++) {
        // Inner loop: Go through each cell (ID, Name, Date, etc.) for that specific student
        for (int j = 0; j < currentColCount; j++) {
            outputFile << sheet[i].cells[j];
            
            // Add a comma if it's NOT the last cell
            if (j < currentColCount - 1) {
                outputFile << ",";
            }
        }
        outputFile << "\n"; // New line after each student row
    }

    outputFile.close();
    cout << "Successfully saved to " << filename << ".\n";
}

void loadFile() {
    string filename = getSheetFileName();
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cout << "Notice: No existing data found for " << filename << ". Starting fresh.\n";
        return;
    }

    // Reset counts before loading new data
    currentRowCount = 0;
    currentColCount = 0;

    string line;
    
    // --- Part A: Load the Header (First Line) ---
    if (getline(inputFile, line)) {
        stringstream ss(line); /// Turn the line into a stream
        string colData;
        int colIdx = 0;

        while (getline(ss, colData, ',')) { //Break the line apart everywhere there is a comma
            // Logic to separate "Name" and "(TYPE)" 
            size_t openBracket = colData.find('(');
            size_t closeBracket = colData.find(')');

            if (openBracket != string::npos && closeBracket != string::npos) {
                // Extract the name (everything BEFORE the bracket)
                columns[colIdx].name = colData.substr(0, openBracket);
                // Clean up trailing space in name
                if (columns[colIdx].name.back() == ' ') columns[colIdx].name.pop_back();
                // Extract the type (everything BETWEEN the brackets)
                columns[colIdx].type = colData.substr(openBracket + 1, closeBracket - openBracket - 1);
            }
            colIdx++;
        }
        currentColCount = colIdx; // Record how many columns we found
    }

    // --- Part B: Load the Student Rows ---
    // Read every remaining line in the file
    while (getline(inputFile, line) && currentRowCount < MAX_ROWS) {
        stringstream ss(line);
        string cellData;
        int colIdx = 0;
        // Split each line by commas and put it into the 'sheet' array
        while (getline(ss, cellData, ',') && colIdx < currentColCount) {
            sheet[currentRowCount].cells[colIdx] = cellData;
            colIdx++;
        }
        currentRowCount++; //Move to the next student row
    }

    inputFile.close();
    cout << "Successfully loaded " << currentRowCount << " rows from " << filename << ".\n";
}

void loadOrCreateSheet() {
    //function to load or create attendance sheet

    cout << "\n-------------------------------------------";
    cout << "\nLoad or Create Sheet";
    cout << "\n-------------------------------------------" << endl; // ui stuff 

    string dbFile = getDatabaseFileName();
    ifstream databaseInput(dbFile);

    bool sheetExists = false;

    if (databaseInput.is_open()) {
        cout << "Available Sheets in " << termName << ":\n";
        string line;
        bool hasContent = false;
        while(getline(inputFile, line)) {
            cout << " - " << line << "\n"; 
            hasContent = true; // if file got content chanfe to true 
        }
        if (!hasContent) cout << " [No sheets in this term yet]\n"; // if file is empty 
        inputFile.close();   
    }

    cout << "\nEnter sheet name to open (e.g. Week1) or create a new one: ";
    getline(cin, sheetName);
    loadFile(); // get the data from csv 

    // Call index function to record this sheet into the Term CSV
    databaseIndex(); 
}

//MAIN 
int main() {

    int choice;

    createTerm(); 

    loadOrCreateSheet();

    
    //initializeSheet();

    //Main menu
    do {
        cout << "\n-------------------------------------------";
        cout << "\nMAIN MENU";
        cout << "\nCurrent Term: " << termName;
        cout << "\nCurrent Sheet: " << sheetName;
        cout << "\n-------------------------------------------";
        cout << "\n1. Define Columns";
        cout << "\n2. Insert New Attendance Row";
        cout << "\n3. View Attendance Sheet";
        cout << "\n4. Update Row";        
        cout << "\n5. Delete Row";
        cout << "\n6. Count Row";     
        cout << "\n7. Save & Exit";       
        cout << "\n\nEnter choice: ";
        cin >> choice;

        //Validation
        while(cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input. Please enter a number (1-7): ";
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
                updateRow();  
                viewSheet();
                break;

            case 5:
                deleteRow(); 
                viewSheet();
                break;

            case 6:
                countRows();
                break;
            
            case 7:
                saveFile();  
                cout << "\nData saved. Exiting program...\n";
                break;

            default:
                cout << "\nError: Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    
    return 0;
}   