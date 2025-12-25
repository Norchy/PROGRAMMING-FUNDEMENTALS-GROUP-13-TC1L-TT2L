#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to insert a new attendance row into the attendance sheet
// attendanceSheet stores all rows (StudentID, Name, Status)
void insertAttendanceRow(vector<vector<string>> &attendanceSheet)
{
    // Variables to store user input
    string studentID, name, status;

    // Display section header
    cout << "----------------------------------\n";
    cout << "Insert New Attendance Row\n";
    cout << "----------------------------------\n";

    // ===== StudentID Input =====
    cout << "Enter StudentID: ";
    cin >> studentID;

    // Validate StudentID (must be an integer)
    for (char c : studentID)
    {
        // If any character is not a digit, input is invalid
        if (!isdigit(c))
        {
            cout << "Error: Invalid INT value. Please enter a number.\n";
            return; // Stop function if invalid input
        }
    }

    // Clear input buffer before using getline
    cin.ignore();

    // ===== Name Input =====
    cout << "Enter Name: ";
    getline(cin, name);

    // Validate Name (cannot be empty)
    if (name.empty())
    {
        cout << "Error: Name cannot be empty.\n";
        return; // Stop function if name is empty
    }

    // ===== Status Input =====
    cout << "Enter Status (Present: 1, Absent: 0): ";
    cin >> status;

    // Validate Status (must be 0 or 1)
    if (status != "0" && status != "1")
    {
        cout << "Error: Status must be 0 or 1.\n";
        return; // Stop function if invalid status
    }

    // ===== Insert Row =====
    // Create a new row for attendance data
    vector<string> newRow;

    // Add StudentID, Name, and Status to the row
    newRow.push_back(studentID);
    newRow.push_back(name);
    newRow.push_back(status);

    // Add the new row into the attendance sheet
    attendanceSheet.push_back(newRow);

    // Display success m
