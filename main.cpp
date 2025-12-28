#include <iostream>
#include <string>
#include <cctype>   // for isdigit()
#include <thread> // for time delay
#include <chrono> // for time delay
#include <limits>
#include <iomanip> // csv mode alignments

// *********************************************************
// Program: main.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT2L
// Trimester: 2530
// Member_1: 252UC2425R | Arfa Mirza Bin Shamsul Safuan | arfa.mirza.shamsul1@student.edu.my | 013-268 9303
// Member_2: 252UC241Q3 | EMIL SHADIQ BIN ISKANDAR | emil.shadiq.iskandar1@mmu.student.edu.my | 011-1125-4415
// Member_3: 252UC24246 | Dairell Hannan bin Ahmad Nizam | dairell.hannan.ahmad1@student.mmu.edu.my | 019-880 6564
// Member_4: 252UC241MF | LUQMAN HAKIM BIN MUHAMMAD FAMHI | LUQMAN.HAKIM.MUHAMMAD1@student.mmu.edu.my | 013-366-8674
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
const int MAX_INPUT_ROWS = 10; // NEW: max rows user can input per sheet


// Member 2 structure
struct Attendance
{
    int studentID;
    string name;
    int status; // 1 = Present, 0 = Absent
};

struct AttendanceRow
{
    string values[MAX_COLUMNS];
};

// Member 4 - Introduction
void createSheet(string &sheetName);
int createColumnsExact(Column columns[]);
int getRowCountFromUser(); // NEW
void insertAttendanceRow(AttendanceRow sheet[], int &rowCount, Column columns[], int colCount);
void displayCSV(AttendanceRow sheet[], int rowCount, Column columns[], int colCount);

static string toLowerStr(string s)
{
    for (char &c : s)
        c = tolower(static_cast<unsigned char>(c));
    return s;
}

static bool isValidIntString(const string &s)
{
    if (s.empty()) return false;
    for (char c : s)
    {
        if (!isdigit(static_cast<unsigned char>(c)))
            return false;
    }
    return true;
}

static string trim(const string &s)
{
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

static bool parseColumnDefinition(const string &input, string &colName, string &colType)
{
    string s = trim(input);

    size_t openPos = s.find_last_of('(');
    size_t closePos = s.find_last_of(')');

    if (openPos == string::npos || closePos == string::npos || closePos < openPos)
        return false;

    string namePart = trim(s.substr(0, openPos));
    string typePart = trim(s.substr(openPos + 1, closePos - openPos - 1));

    if (namePart.empty() || typePart.empty())
        return false;

    string typeLower = toLowerStr(typePart);
    if (typeLower == "int")
        colType = "INT";
    else if (typeLower == "text")
        colType = "TEXT";
    else
        return false;

    colName = namePart;
    return true;
}

void introduction(string &sheetName, Column columns[], AttendanceRow attendanceSheet[], int &rowCount)
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
        int colCount = createColumnsExact(columns);

        // NEW: user define how many rows to insert (max 10)
        int totalRows = getRowCountFromUser();
        cin.ignore(); // consume newline after cin >>

        // Member 2 (insert based on user input rows)
        for (int i = 0; i < totalRows; i++)
        {
            insertAttendanceRow(attendanceSheet, rowCount, columns, colCount);
        }

        // Member 3
        displayCSV(attendanceSheet, rowCount, columns, colCount);

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
    cout << "=============================================\n";
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
    string numCols;
    int colCount = 0;

    while (true)
    {
        cout << "Define number of columns (max 10): ";
        cin >> numCols;

        if (!isValidIntString(numCols))
        {
            cout << "Error: Please enter a valid number.\n";
            continue;
        }

        colCount = stoi(numCols);

        if (colCount < 1 || colCount > MAX_COLUMNS)
        {
            cout << "Error: Number of columns must be between 1 and 10.\n";
            continue;
        }

        break;
    }

    cin.ignore();

    for (int i = 0; i < colCount; i++)
    {
        while (true)
        {
            cout << "\nEnter column " << (i + 1) << " name (Ensure to put (INT) or (TEXT) at the end of the name for column types): ";
            string input;
            getline(cin, input);

            string nameParsed, typeParsed;
            if (!parseColumnDefinition(input, nameParsed, typeParsed))
            {
                cout << "Error: Please use format like \"ColumnName (INT)\" or \"ColumnName (TEXT)\".\n";
                continue;
            }

            columns[i].name = nameParsed;
            columns[i].type = typeParsed;
            break;
        }
    }

    cout << "\nSheet structure created successfully.\n";
    return colCount;
}

// NEW: let user choose how many rows to insert (max 10)
int getRowCountFromUser()
{
    string input;
    int rows = 0;

    while (true)
    {
        cout << "=============================================\n";
        cout << "Define number of rows to insert (max 10): ";
        cin >> input;

        if (!isValidIntString(input))
        {
            cout << "Error: Please enter a valid number.\n";
            continue;
        }

        rows = stoi(input);

        if (rows < 1 || rows > MAX_INPUT_ROWS)
        {
            cout << "Error: Number of rows must be between 1 and 10.\n";
            continue;
        }

        break;
    }

    return rows;
}

// ===============================
// Member 2: Insert attendance row
// ===============================
void insertAttendanceRow(AttendanceRow sheet[], int &rowCount, Column columns[], int colCount)
{
    if (rowCount >= MAX_ROWS)
    {
        cout << "Error: Attendance sheet is full.\n";
        return;
    }

    cout << "\n----------------------------------\n";
    cout << "Insert New Attendance Row\n";
    cout << "----------------------------------\n";

    for (int i = 0; i < colCount; i++)
    {
        string colNameLower = toLowerStr(columns[i].name);

        if (colNameLower == "studentid")
        {
            while (true)
            {
                cout << "Enter StudentID: " << flush;
                string v;
                getline(cin, v);
                v = trim(v);

                if (!isValidIntString(v))
                {
                    cout << "Error: Invalid INT value. Please enter a number.\n";
                    continue;
                }

                sheet[rowCount].values[i] = v;
                break;
            }
        }
        else if (colNameLower == "status")
        {
            while (true)
            {
                cout << "Enter Status (Present: 1, Absent: 0): " << flush;
                string v;
                getline(cin, v);
                v = trim(v);

                if (v != "0" && v != "1")
                {
                    cout << "Error: Status must be 0 or 1.\n";
                    continue;
                }

                sheet[rowCount].values[i] = v;
                break;
            }
        }
        else
        {
            if (columns[i].type == "INT")
            {
                while (true)
                {
                    cout << "Enter " << columns[i].name << ": " << flush;
                    string v;
                    getline(cin, v);
                    v = trim(v);

                    if (!isValidIntString(v))
                    {
                        cout << "Error: Invalid INT value. Please enter a number.\n";
                        continue;
                    }

                    sheet[rowCount].values[i] = v;
                    break;
                }
            }
            else
            {
                while (true)
                {
                    cout << "Enter " << columns[i].name << ": " << flush;
                    string v;
                    getline(cin, v);
                    v = trim(v);

                    if (v.empty())
                    {
                        cout << "Error: TEXT value cannot be empty.\n";
                        continue;
                    }

                    sheet[rowCount].values[i] = v;
                    break;
                }
            }
        }
    }

    rowCount++;
    cout << "Row inserted successfully.\n";
}

void displayCSV(AttendanceRow sheet[], int rowCount, Column columns[], int colCount)
{
    if (rowCount == 0)
        {
            cout << "-------------------------" << endl;
            cout << "Attendance sheet is empty" << endl;
            cout << "-------------------------" << endl;
            return;
        }


    cout << "=============================================\n\n";
    cout << "--------------------------------" << endl;
    cout << "VIew Attendance Sheet (CSV Mode)" << endl;
    cout << "--------------------------------" << endl;

    int width[MAX_COLUMNS];

    //Automatic determine width for each coloumn based on user input
    for (int j = 0; j < colCount; j++)
        width[j] = columns[j].name.length();

    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            int len = sheet[i].values[j].length();
            if (len > width[j])
                width[j] = len;
        }
    }

    // Padding so user input tak dekat dengan comma and centred
    for (int j = 0; j < colCount; j++)
        width[j] += 1;

    // header print
    for (int j = 0; j < colCount; j++)
    {
        cout << left << setw(width[j]) << columns[j].name;
        if (j != colCount - 1) cout << ", ";
    }
    cout << endl;

    // row printing
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            cout << left << setw(width[j]) << sheet[i].values[j];
            if (j != colCount - 1) cout << ", ";
        }
        cout << endl;
    }

}

// ===============================
// Main (Merged)
// ===============================
int main()
{
    string sheetName;
    Column columns[MAX_COLUMNS];
    AttendanceRow attendanceSheet[MAX_ROWS];
    int rowCount = 0;

    cout << "=============================================\n";
    cout << "STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "=============================================\n\n";

    introduction(sheetName, columns, attendanceSheet, rowCount);

    return 0;
}




