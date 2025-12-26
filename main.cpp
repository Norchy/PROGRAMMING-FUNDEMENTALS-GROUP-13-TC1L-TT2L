#include <iostream>

using namespace std;

struct Attendance
{
    int studentID;
    string name;
    int status;
};




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

