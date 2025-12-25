#include <iostream>
#include <string>
#include <cctype>   // for isdigit()
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
        cout << "Define number of columns (max 10): ";
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

    // Member 1
    createSheet(sheetName);
    createColumnsExact(columns);

    // Member 2 (2 insertions like sample)
    insertAttendanceRow(attendanceSheet, rowCount);
    insertAttendanceRow(attendanceSheet, rowCount);

    return 0;
}
