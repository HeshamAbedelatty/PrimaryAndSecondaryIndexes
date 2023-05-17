#include <iostream>
#include "Emp&Dept.h"

using namespace std;

void writeQurey() {

    string select, attribute, from, table, where, key, value, equal;
    cin >> select >> attribute >> from >> table >> where >> key >> equal >> value;
    if (table == "Employee") {
        if (key == "Dept_ID") {
            printEmpByDept_id(value);
        } else if (key == "Employee_ID") {
            printEmpBNameyId(value);
        }
    } else if (table == "Department") {
        if (key == "Dept_ID") {
            printDeptById(value);
        }
    }
}

int main() {
    flagEmpFile();
    flagDepFile();
    cout << "What Would You Like To Do \n";
    int y;
    bool flag = true;
    string Id ;
    while (flag) {
        cout << "\n1. Add New Employee" << endl
             << "2. Add New Department" << endl
             << "3. Delete Employee   (ID)" << endl
             << "4. Delete Department (ID)" << endl
             << "5. Print Employee (ID)" << endl
             << "6. Print Employee (Dept_ID)"<< endl
             << "7. Print Department (ID)"<<endl
             << "8. Print Department (name)"<<endl
             << "9. Write a Query"<< endl
             << "10.Exit"<<endl
             << "Number: ";
        cin >> y;
        switch (y) {
            case 1:
                addEmployee();
                break;
            case 2:
                addDepartment();
                break;
            case 3:
                cout << "Enter Employee id : ";
                cin >> Id;
                deleteEmployeeById(Id);
                break;
            case 4:
                cout << "Enter Department id : ";
                cin >> Id;
                deleteDepartmentById(Id);
                break;
            case 5:
                cout << "Enter Employee id :";
                cin >> Id;
                printEmpById(Id);
                break;

            case 6:
                cout << "Enter Department id :";
                cin >> Id;
                printEmpByDept_id(Id);
                break;
            case 7:
                cout << "Enter Department id :";
                cin >> Id;
                printDeptById(Id);
                break;
            case 8:
                cout << "Enter Department name :";
                cin >> Id;
                printDeptByDept_name(Id);
                break;
            case 9:
                cout << "select all from Employee where Dept_ID = 20201211"<<endl
                     << "select all from Department where Dept_ID = 50505050"<<endl
                     << "select Employee_Name from Employee where Employee_ID = 20201211"<<endl;
                cout << "Write Query : " << endl;
                writeQurey();
                break;
            case 10:
                flag = false;
                break;
            default:
                break;
        }
    }

    return 0;
}
