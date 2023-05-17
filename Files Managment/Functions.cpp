//
// Created by HESHAM on 11/30/2022.
//
#include "Emp&Dept.h"
#include <bits/stdc++.h>

void flagEmpFile() {
    int True = 0;
    int fl;
    ifstream readfile("EmployeeData.txt", ios::in);
    readfile.seekg(0, ios::end);
    fl = readfile.tellg();
    if (fl < 1) {
        True = 1;
    }
    readfile.close();
    if (True == 1) {
        ofstream instert("EmployeeData.txt", ios::out);
        instert.seekp(0, ios::beg);
        char header[sizeof(int)];
        string Flag = to_string(-1);
        strcpy(header, Flag.c_str());
        instert.write(header, sizeof(int));
        instert.close();

    }

}

// +++++++++++++++++++++++ addEmployee ++++++++++++++++++++++
void addEmployee() {
    vector<pair<long long, int>> index;
    vector<pair<long long, int>> Sec_index;
    vector<pair<long long, int>> LL_index;
    pair<long long, int> New_PIndex;
    pair<long long, int> New_SIndex;
    pair<long long, int> New_SLLindex;
    Employee employee{};
    int byteOffset;
    cout << "Enter Employee Id:";
    cin >> employee.employee_id;
    cout << "Enter Department Id: ";
    cin >> employee.dept_id;
    cout << "Enter Employee Name: ";
    cin >> employee.employee_name;
    cout << "Enter Employee Position: ";
    cin >> employee.employee_position;
    byteOffset = writeEmployee(employee);
    //++++++++++++++ we write in primary index file +++++++++++++++++++=
    string id = (string) employee.employee_id;
    string byte = to_string(byteOffset);
    New_PIndex.first = stoll(id);
    New_PIndex.second = stoi(byte);
    index = insertionSort(New_PIndex);
    writeEmployeePrimaryIndex(index);
    //++++++++++++++ we write in Secondary index and its LinkedList file +++++++++++++++++++=
    string deptId = (string) employee.dept_id;
    LL_index = bringAllEmpDept_idL_ListIndex();
    New_SLLindex.first = stoll(id);
    New_SLLindex.second = -1;
    LL_index.push_back(New_SLLindex);
    int i = IsExist(deptId);
    if (i == -1) {
        New_SIndex.first = stoll(deptId);
        New_SIndex.second = (int) LL_index.size();
        Sec_index = insertionSortDeptid(New_SIndex);
        writeEmployeeSecondrayLinkedList(LL_index);
        writeEmployeeSecondrayIndex(Sec_index);
    } else {
        int pos = i;
        changeLinkedList(pos, LL_index);
        writeEmployeeSecondrayLinkedList(LL_index);
    }

}
// +++++++++++++++++++++++ deleteEmployee ++++++++++++++++++++++

void deleteEmployeeById(const string &Id) {
    long long EmpId = stoll(Id);
    vector<pair<long long, int >> index;
    index = bringAllEmpIDIndex();
    int byte = BinSearch(index, EmpId);
    if (byte != -1) {
        fstream file("EmployeeData.txt", ios::in | ios::out);
        file.seekg(0, ios::beg);
        char header[sizeof(int)], sizeOfRecord[sizeof(int)];
        file.read(header, sizeof(int));
        file.seekg(byte, ios::beg);
        file.read(sizeOfRecord, sizeof(int));
        file.seekg(byte, ios::beg);
        int headerByteOffset = stoi((string) header), Size = stoi((string) sizeOfRecord);
        file.put('*');
        file.write(header, sizeof(int));
        char x[1] = {' '};
        file.write(sizeOfRecord, sizeof(int));
        for (int i = 0; i < Size - 5; ++i)
            file.write(x, 1);
        file.seekg(0, ios::beg);
        char b[sizeof(int)];
        string by = to_string(byte);
        strcpy(b, by.c_str());
        file.write(b, sizeof(int));

        file.close();
    } else {
        cout << "There is no Employee has this id. " << endl;
    }
}
// +++++++++++++++++++++++ print Employee by id ++++++++++++++++++++++

void printEmpById(string id) {
    long long EmpId = stoll(id);
    vector<pair<long long, int >> index;
    index = bringAllEmpIDIndex();
    int byte = BinSearch(index, EmpId);
    ifstream file("EmployeeData.txt", ios::in);
    char sizeOfRecord[sizeof(int)];
    file.seekg(byte, ios::beg);
    char c;
    file.get(c);
    if (c != '*') {
        file.seekg(byte, ios::beg);
        file.read(sizeOfRecord, sizeof(int));
        char Eid[13], dept_id[30], name[50], pos[50];
        file.getline(Eid, 13, '|');
        file.getline(dept_id, 30, '|');
        file.getline(name, 50, '|');
        file.getline(pos, 50, '|');
        cout << "Employee ID: " << Eid << endl
             << "Department ID: " << dept_id << endl
             << "Employee Name: " << name << endl
             << "Employee Postion: " << pos << endl;
    }


    file.close();
}

void printEmpBNameyId(string id) {
    long long EmpId = stoll(id);
    vector<pair<long long, int >> index;
    index = bringAllEmpIDIndex();
    int byte = BinSearch(index, EmpId);
    ifstream file("EmployeeData.txt", ios::in);
    char sizeOfRecord[sizeof(int)];
    file.seekg(byte, ios::beg);
    char c;
    file.get(c);
    if (c != '*') {
        file.seekg(byte, ios::beg);
        file.read(sizeOfRecord, sizeof(int));
        char Eid[13], dept_id[30], name[50], pos[50];
        file.getline(Eid, 13, '|');
        file.getline(dept_id, 30, '|');
        file.getline(name, 50, '|');
        file.getline(pos, 50, '|');
        cout << "Employee Name: " << name << endl;
    }

    file.close();
}

// +++++++++++++++++++++++ print Employee by department id ++++++++++++++++++++++
void printEmpByDept_id(string id) {
    long long EmpId = stoll(id);
    vector<pair<long long, int >> index, Primary, LL;
    vector<long long> Pid;
    Primary = bringAllEmpIDIndex();
    index = bringAllEmpDept_idIndex();
    LL = bringAllEmpDept_idL_ListIndex();
    int byte = BinSearch(index, EmpId);
    while (byte != -1) {
        Pid.push_back(LL[byte - 1].first);
        byte = LL[byte - 1].second;
    }
    ifstream file("EmployeeData.txt", ios::in);
    char sizeOfRecord[sizeof(int)];
    int Offset;
    for (int i = 0; i < Pid.size(); ++i) {
        Offset = BinSearch(Primary, Pid[i]);
        file.seekg(Offset, ios::beg);
        char c;
        file.get(c);
        if (c != '*') {
            file.seekg(Offset, ios::beg);
            file.read(sizeOfRecord, sizeof(int));
            char Eid[13], dept_id[30], name[50], pos[50];
            file.getline(Eid, 13, '|');
            file.getline(dept_id, 30, '|');
            file.getline(name, 50, '|');
            file.getline(pos, 50, '|');
            cout << "Employee ID: " << Eid << endl
                 << "Department ID: " << dept_id << endl
                 << "Employee Name: " << name << endl
                 << "Employee Postion: " << pos << endl;
        }

    }
    file.close();
}

// +++++++++++++++++++++++ add department ++++++++++++++++++++++
void addDepartment() {
    vector<pair<long long, int>> index, in;
    vector<pair<string, int>> Sec_index;
    vector<pair<long long, int>> LL_index;
    pair<long long, int> New_PIndex;
    pair<string, int> New_SIndex;
    pair<long long, int> New_SLLindex;
    Department department{};
    int byteOffset;
    cout << "Enter Department Id: ";
    cin >> department.dept_id;
    cout << "Enter Department name: ";
    cin >> department.dept_name;
    cout << "Enter Department Manager: ";
    cin >> department.dept_manger;
    byteOffset = writeDepartment(department);
    //++++++++++++++ we write in primary index file +++++++++++++++++++=
    string id = (string) department.dept_id;
    string byte = to_string(byteOffset);
    New_PIndex.first = stoll(id);
    New_PIndex.second = stoi(byte);
    index = insertionSortDepartmentDept_Id(New_PIndex);
    writeDepartmentPrimaryIndex(index);
    //++++++++++++++ we write in Secondary index and its LinkedList file +++++++++++++++++++=
    string deptName = (string) department.dept_name;
    LL_index = bringAllDeptartmentNameL_ListIndex();
    New_SLLindex.first = stoll(id);
    New_SLLindex.second = -1;
    LL_index.push_back(New_SLLindex);
    int i = IsExistDeptartmentName(deptName);
    if (i == -1) {
        New_SIndex.first = deptName;
        New_SIndex.second = (int) LL_index.size();
        Sec_index = insertionSortDeptartmentName(New_SIndex);
        writeDepartmentSecondrayLinkedList(LL_index);
        writeDepartmentSecondrayIndex(Sec_index);
    } else {
        int pos = i;
        changeDeptartmentNameLinkedList(pos, LL_index);
        writeDepartmentSecondrayLinkedList(LL_index);
    }

}
// +++++++++++++++++++++++ deleteDepartment ++++++++++++++++++++++

void deleteDepartmentById(const string &Id) {
    long long EmpId = stoll(Id);
    vector<pair<long long, int >> index;
    index = bringAllDeptIDIndex();
    int byte = BinSearch(index, EmpId);
    if (byte != -1) {
        fstream file("DepartmentData.txt", ios::in | ios::out);
        file.seekg(0, ios::beg);
        char header[sizeof(int)], sizeOfRecord[sizeof(int)];
        file.read(header, sizeof(int));
        file.seekg(byte, ios::beg);
        file.read(sizeOfRecord, sizeof(int));
        file.seekg(byte, ios::beg);
        int Size = stoi((string) sizeOfRecord);
        file.put('*');
        file.write(header, sizeof(int));
        char x[1] = {' '};
        file.write(sizeOfRecord, sizeof(int));
        for (int i = 0; i < Size - 5; ++i)
            file.write(x, 1);
        file.seekg(0, ios::beg);
        char b[sizeof(int)];
        string by = to_string(byte);
        strcpy(b, by.c_str());
        file.write(b, sizeof(int));

        file.close();
    } else {
        cout << "There is no Department has this id. " << endl;
    }
}

// +++++++++++++++++++++++ print Department by id ++++++++++++++++++++++
void printDeptById(string id) {
    long long DeptId = stoll(id);
    vector<pair<long long, int >> index;
    index = bringAllDeptIDIndex();
    int byte = BinSearch(index, DeptId);
    ifstream file("DepartmentData.txt", ios::in);
    char sizeOfRecord[sizeof(int)];
    file.seekg(byte, ios::beg);
    char c;
    file.get(c);
    if (c != '*') {
        file.seekg(byte, ios::beg);
        file.read(sizeOfRecord, sizeof(int));
        char dept_id[30], name[50], manager[50];
        file.getline(dept_id, 30, '|');
        file.getline(name, 50, '|');
        file.getline(manager, 50, '|');
        cout << "Department ID: " << dept_id << endl
             << "Department Name: " << name << endl
             << "Department Manager: " << manager << endl;
    }

    file.close();
}

// +++++++++++++++++++++++ print Employee by department id ++++++++++++++++++++++
void printDeptByDept_name(string id) {
    string Deptname = id;
    vector<pair<long long, int >> Primary, LL;
    vector<pair<string, int >> index;
    vector<long long> did;
    Primary = bringAllDeptIDIndex();
    index = bringAllDeptartmentNameIndex();
    LL = bringAllDeptartmentNameL_ListIndex();
    int byte = BinSearchDeptname(index, Deptname);

    while (byte != -1) {
        did.push_back(LL[byte - 1].first);
        byte = LL[byte - 1].second;
    }
    ifstream file("DepartmentData.txt", ios::in);
    char sizeOfRecord[sizeof(int)];
    int Offset;
    for (int i = 0; i < did.size(); ++i) {
        Offset = BinSearch(Primary, did[i]);
        file.seekg(Offset, ios::beg);
        char c;
        file.get(c);
        if (c != '*') {
            file.seekg(Offset, ios::beg);
            file.read(sizeOfRecord, sizeof(int));
            char dept_id[30], name[50], manager[50];
            file.getline(dept_id, 30, '|');
            file.getline(name, 50, '|');
            file.getline(manager, 50, '|');
            cout << "Department ID: " << dept_id << endl
                << "Department Name: " << name << endl
                << "Department Manager: " << manager << endl;
        }

    }
    file.close();
}