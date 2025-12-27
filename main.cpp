#include <iostream>
#include <string>
#include <cctype>   // for isdigit()
#include <thread> // for time delay
#include <chrono> // for time delay

// *********************************************************
// Program: YOUR_FILENAME.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT2L
// Trimester: 2530
// Member_1: ID | NAME | EMAIL | PHONE
// Member_2: ID | NAME | EMAIL | PHONE
// Member_3: ID | NAME | EMAIL | PHONE
// Member_4: 252UC241MF | LUQMAN HAKIM BIN MUHAMMAD FAMHI | EMAIL | 013-366-8674
// *********************************************************
// Task Distribution
// Member_1: Sheet Creation and Data Structure
// Member_2: Attendance Rows
// Member_3: CSV View Mode + Formatting
// Member_4: Error Handling and Documentation
// *********************************************************


using namespace std;

const int MAX_COLUMNS = 10;
const int MAX_ROWS = 100;

// Member 1 structure
struct Column
{
    string name;
    string type; // INT or TEXT
};

// Member 2 structure
struct Attendance
{
    int studentID;
    string name;
    int status; // 1 = Present, 0 = Absent
};

// Member 4 - Introduction
void createSheet(string &sheetName);
int createColumnsExact(Column columns[]);
void insertAttendanceRow(Attendance sheet[], int &rowCount);
void displayCSV(Attendance sheet[], int rowCount);


void introduction(string &sheetName, Column columns[], Attendance attendanceSheet[], int &rowCount)
{
    string option;

    cout << "\nWeclome to the 'Student Attendance Tracker'. Please select an option below. (1-3)" << endl;
    cout << "Option 1: Create Sheet" << endl;
    cout << "Option 2: What is Student Attendance Tracker" << endl;
    cout << "Option 3: Quit" << endl;

    cin >> option;

    if (option == "1")
    {
        cin.ignore();
        string answer;

        // Member 1
        createSheet(sheetName);
        createColumnsExact(columns);

        // Member 2 (2 insertions like sample)
        insertAttendanceRow(attendanceSheet, rowCount);
        insertAttendanceRow(attendanceSheet, rowCount);

        // Member 3
        displayCSV(attendanceSheet, rowCount);

        this_thread::sleep_for(chrono::seconds(2));

        while (true)
        {
            cout << "\nDo you want to create a new one?(Yes/No)" << endl;
            cin >> answer;


            for (char &c : answer) //FUNCTION TO LOWERCASE THE STRING
                c = tolower(static_cast<unsigned char>(c));


            if (answer == "yes")
            {
                introduction(sheetName, columns, attendanceSheet, rowCount);
                return;
            }

            else if (answer == "no")
            {
                cout << "Have a good day!" << endl;
                return;
            }
            else
            {
                cout << "Invalid Input. Try again." << endl;
            }
        }




    }
    else if (option == "2")
    {
        cout << "Student Attendance Tracker is a program where it stores student datas whethere they are present or absent during class session" << endl;
        this_thread::sleep_for(chrono::seconds(2));

        introduction(sheetName, columns, attendanceSheet, rowCount);
    }
    else if (option == "3")
    {
        return;
    }
    else
    {
        cout << "Invalid Input. Try again" << endl;
        introduction(sheetName, columns, attendanceSheet, rowCount);
    }
}


// ===============================
// Member 1: Create attendance sheet
// ===============================
void createSheet(string &sheetName)
{
    cout << "Enter attendance sheet name: ";
    getline(cin, sheetName);

    if (sheetName.empty())
    {
        cout << "Error: Sheet name cannot be empty.\n";
        createSheet(sheetName); // ask again
    }
    else
    {
        cout << "Attendance sheet \"" << sheetName << "\" created successfully.\n";
    }
}

/*
    Member 1 (Exact sample behaviour):
    - Only accepts 3 columns
    - Prompts for the exact 3 column "names" shown in sample output
    - Automatically sets type according to the fixed format
*/
int createColumnsExact(Column columns[])
{
    int numCols;

    // Force user to enter 3 (to match sample output)
    while (true)
    {
        cout << "Define number of columns (max 3): ";
        cin >> numCols;

        if (numCols == 3)
            break;

        cout << "Error: For Milestone 1, you must define exactly 3 columns.\n";
    }

    cin.ignore(); // clear newline before getline

    // Column 1
    cout << "Enter column 1 name: ";
    getline(cin, columns[0].name);
    columns[0].type = "INT";

    // Column 2
    cout << "Enter column 2 name: ";
    getline(cin, columns[1].name);
    columns[1].type = "TEXT";

    // Column 3
    cout << "Enter column 3 name: ";
    getline(cin, columns[2].name);
    columns[2].type = "TEXT";

    cout << "\nSheet structure created successfully.\n";
    return 3;
}

// ===============================
// Member 2: Insert attendance row
// ===============================
void insertAttendanceRow(Attendance sheet[], int &rowCount)
{
    if (rowCount >= MAX_ROWS)
    {
        cout << "Error: Attendance sheet is full.\n";
        return;
    }

    cout << "\n----------------------------------\n";
    cout << "Insert New Attendance Row\n";
    cout << "----------------------------------\n";

    // --- StudentID (validate INT) ---
    string studentIDInput;
    cout << "Enter StudentID: ";
    cin >> studentIDInput;

    for (char c : studentIDInput)
    {
        if (!isdigit(static_cast<unsigned char>(c)))
        {
            cout << "Error: Invalid INT value. Please enter a number.\n";
            return;
        }
    }

    int studentID = stoi(studentIDInput);
    cin.ignore(); // for getline after cin >>

    // --- Name (TEXT) ---
    string name;
    cout << "Enter Name: ";
    getline(cin, name);

    if (name.empty())
    {
        cout << "Error: Name cannot be empty.\n";
        return;
    }

    // --- Status (0/1) ---
    string statusInput;
    cout << "Enter Status (Present: 1, Absent: 0): ";
    cin >> statusInput;

    if (statusInput != "0" && statusInput != "1")
    {
        cout << "Error: Status must be 0 or 1.\n";
        return;
    }

    int status = stoi(statusInput);

    // Insert row
    sheet[rowCount].studentID = studentID;
    sheet[rowCount].name = name;
    sheet[rowCount].status = status;
    rowCount++;

    cout << "Row inserted successfully.\n";
}

void displayCSV(Attendance sheet[], int rowCount)
{
    if (rowCount == 0)
        {
            cout << "-------------------------" << endl;
            cout << "Attendance sheet is empty" << endl;
            cout << "-------------------------" << endl;
            return;
        }



    cout << endl;
    cout << "--------------------------------" << endl;
    cout << "VIew Attendance Sheet (CSV Mode)" << endl;
    cout << "--------------------------------" << endl;

    for (int i = 0; i < rowCount; i++)
        {
            cout << sheet[i].studentID << ", "
                 << sheet[i].name << ", "
                 << sheet[i].status << endl;
        }
}

// ===============================
// Main (Merged)
// ===============================
int main()
{
    string sheetName;
    Column columns[MAX_COLUMNS];
    Attendance attendanceSheet[MAX_ROWS];
    int rowCount = 0;

    cout << "=============================================\n";
    cout << "STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "=============================================\n\n";

    introduction(sheetName, columns, attendanceSheet, rowCount);

    return 0;
}




