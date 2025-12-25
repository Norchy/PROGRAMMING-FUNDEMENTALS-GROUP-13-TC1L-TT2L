#include <iostream>


#include <iostream>
#include <string>
#include <cctype>   // for isdigit()
using namespace std;

const int MAX_COLUMNS = 10;

struct Column {
    string name;
    string type; // INT or TEXT
};

void createSheet(string &sheetName) {
    cout << "Enter attendance sheet name: ";
    getline(cin, sheetName);

    if (sheetName.empty()) {
        cout << "Error: Sheet name cannot be empty.\n";
        createSheet(sheetName);
    } else {
        cout << "Attendance sheet \"" << sheetName << "\" created successfully.\n";
    }
}

bool isValidType(string type) {
    return (type == "INT" || type == "TEXT");
}

int createColumns(Column columns[]) {
    int numCols;
    cout << "Enter number of columns (max 10): ";
    cin >> numCols;

    if (numCols <= 0 || numCols > MAX_COLUMNS) {
        cout << "Error: Invalid number of columns.\n";
        return 0;
    }

    cin.ignore(); // clear buffer

    for (int i = 0; i < numCols; i++) {
        cout << "\nColumn " << i + 1 << " name: ";
        getline(cin, columns[i].name);

        cout << "Column " << i + 1 << " type (INT/TEXT): ";
        getline(cin, columns[i].type);

        if (!isValidType(columns[i].type)) {
            cout << "Error: Invalid data type. Use INT or TEXT only.\n";
            i--; // redo this column
        }
    }

    return numCols;
}

void displayCSVHeader(Column columns[], int numCols) {
    cout << "\nCSV View (Header Only):\n";
    for (int i = 0; i < numCols; i++) {
        cout << columns[i].name;
        if (i != numCols - 1) cout << ",";
    }
    cout << endl;
}

int main() {
    string sheetName;
    Column columns[MAX_COLUMNS];
    int columnCount;

    cout << "=============================================\n";
    cout << "STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "=============================================\n\n";

    createSheet(sheetName);
    columnCount = createColumns(columns);

    if (columnCount > 0) {
        displayCSVHeader(columns, columnCount);
    } else {
        cout << "Failed to create sheet structure.\n";
    }

    return 0;
}