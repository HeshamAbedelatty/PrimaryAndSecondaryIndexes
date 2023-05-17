//
// Created by HESHAM on 11/30/2022.
//
#include "Emp&Dept.h"
#include <bits/stdc++.h>

// ****************Employee***************

int writeEmployee(Employee &employee) {
    int length, header;
    char record[maxRecordSize];
    strcpy(record, employee.employee_id);
    strcat(record, "|");
    strcat(record, employee.dept_id);
    strcat(record, "|");
    strcat(record, employee.employee_name);
    strcat(record, "|");
    strcat(record, employee.employee_position);
    strcat(record, "|");
    length = strlen(record);
    string s = to_string(length);
    char len[sizeof(int)];
    strcpy(len, s.c_str());
    ofstream instert("EmployeeData.txt", ios::out | ios::app);
    instert.seekp(0, ios::end);
    int byteOffset = instert.tellp();
    instert.write(len, sizeof(int));
    instert.write(record, length);
    instert.close();
    return byteOffset;


}

void readEmployee(int byteOffeset) {
    ifstream readfile("EmployeeData.txt", ios::in | ios::out);
    readfile.seekg(byteOffeset, ios::beg);
    char length[sizeof(int)];
    readfile.read(length, sizeof(int));
    string s = (string) length;
    int len = stoi(s);
    char record[len];
    readfile.read(record, len);
    cout << record;

    readfile.close();
}
// ****************EmployeePrimaryIndex***************

void writeEmployeePrimaryIndex(vector<pair<long long, int>> &PIndex) {
    ofstream instert("PrimayIndexEmpID.txt", ios::out);
    instert.seekp(0, ios::beg);
    int length;
    string id, byte;
    PI_EmpID Id{};
    for (int i = 0; i < PIndex.size(); ++i) {
        id = to_string(PIndex[i].first);
        byte = to_string(PIndex[i].second);
        strcpy(Id.id, id.c_str());
        strcpy(Id.byteoffset, byte.c_str());
        instert.write(Id.id, 13);
        instert.write(Id.byteoffset, sizeof(int));
    }

    instert.close();
}

vector<pair<long long, int >> bringAllEmpIDIndex() {
    ifstream readfile("PrimayIndexEmpID.txt", ios::in);
    readfile.seekg(0, ios::end);
    int length = readfile.tellg();
    readfile.seekg(0, ios::beg);
    char indexid[13];
    char indexByteOffset[sizeof(int)];
    int numOfRecord = length / (sizeof(int) + 13);
    vector<pair<long long, int>> primaryIndex(numOfRecord + 1);
    readfile.seekg(0, ios::cur);
    for (int i = 0; i < numOfRecord; ++i) {
        readfile.read(indexid, 13);
        readfile.read(indexByteOffset, sizeof(int));
        primaryIndex[i].first = stoll((string) indexid);
        primaryIndex[i].second = stoi((string) indexByteOffset);

    }
    readfile.close();
    return primaryIndex;

}

int BinSearch(vector<pair<long long, int>> arr, long long X) {
    int left = 0;
    int right = (int) arr.size() - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (X >= arr[mid].first)
            left = mid + 1;

        else right = mid;
    }
    if (left > 0 && arr[left - 1].first == X)
        return arr[left - 1].second;
    else return -1;
}

vector<pair<long long, int>> insertionSort(pair<long long, int> arr) {

    vector<pair<long long, int>> index;
    index = bringAllEmpIDIndex();

    int i = index.size() - 1;
    while (i > 0 && index[i - 1].first > arr.first) {
        index[i].first = index[i - 1].first;
        index[i].second = index[i - 1].second;
        i--;

    }
    index[i].first = arr.first;
    index[i].second = arr.second;

    return index;
}

//****************************************EmployeeSecondaryIndex*********************************************
void writeEmployeeSecondrayLinkedList(vector<pair<long long, int>> &LLIndex) {
    ofstream instert("LinkedListEmp_DeptID.txt", ios::out);
    instert.seekp(0, ios::beg);
    string Pid, rrn;
    SILinkedList_EmpDeptId LL{};
    for (int i = 0; i < LLIndex.size(); ++i) {
        Pid = to_string(LLIndex[i].first);
        rrn = to_string(LLIndex[i].second);
        strcpy(LL.Emp_id, Pid.c_str());
        strcpy(LL.RRN, rrn.c_str());
        instert.write(LL.Emp_id, 13);
        instert.write(LL.RRN, sizeof(int));
    }
    instert.close();
}

void writeEmployeeSecondrayIndex(vector<pair<long long, int>> &SIndex) {
    ofstream ins("SecondaryIndexEmp_DeptID.txt", ios::out);
    ins.seekp(0, ios::beg);
    int length;
    string id, byte;
    SI_EmpDeptId Id{};
    for (int i = 0; i < SIndex.size(); ++i) {
        id = to_string(SIndex[i].first);
        byte = to_string(SIndex[i].second);
        strcpy(Id.Dept_id, id.c_str());
        strcpy(Id.RRN, byte.c_str());
        ins.write(Id.Dept_id, 30);
        ins.write(Id.RRN, sizeof(int));
    }
    ins.close();
}

vector<pair<long long, int >> bringAllEmpDept_idIndex() {
    ifstream readfile("SecondaryIndexEmp_DeptID.txt", ios::in);
    readfile.seekg(0, ios::end);
    int length = readfile.tellg();
    readfile.seekg(0, ios::beg);
    char indexid[30];
    char indexByteOffset[sizeof(int)];
    int numOfRecord = length / (sizeof(int) + 30);
    vector<pair<long long, int>> secondaryIndex(numOfRecord + 1);
    readfile.seekg(0, ios::cur);
    for (int i = 0; i < numOfRecord; ++i) {
        readfile.read(indexid, 30);
        readfile.read(indexByteOffset, sizeof(int));
        secondaryIndex[i].first = stoll((string) indexid);
        secondaryIndex[i].second = stoi((string) indexByteOffset);

    }
    readfile.close();
    return secondaryIndex;
}

vector<pair<long long, int >> bringAllEmpDept_idL_ListIndex() {
    ifstream readfile("LinkedListEmp_DeptID.txt", ios::in);
    readfile.seekg(0, ios::end);
    int length = readfile.tellg();
    readfile.seekg(0, ios::beg);
    char indexid[13];
    char indexByteOffset[sizeof(int)];
    int numOfRecord = length / (sizeof(int) + 13);
    vector<pair<long long, int>> LinkedListIndex(numOfRecord);
    readfile.seekg(0, ios::cur);
    for (int i = 0; i < numOfRecord; ++i) {
        readfile.read(indexid, 13);
        readfile.read(indexByteOffset, sizeof(int));
        LinkedListIndex[i].first = stoll((string) indexid);
        LinkedListIndex[i].second = stoi((string) indexByteOffset);

    }
    readfile.close();
    return LinkedListIndex;
}

vector<pair<long long, int>> insertionSortDeptid(pair<long long, int> arr) {
    vector<pair<long long, int>> index;
    index = bringAllEmpDept_idIndex();

    int i = index.size() - 1;
    while (i > 0 && index[i - 1].first > arr.first) {
        index[i].first = index[i - 1].first;
        index[i].second = index[i - 1].second;
        i--;

    }
    index[i].first = arr.first;
    index[i].second = arr.second;

    return index;
}

int IsExist(const string &id) {
    long long deptId = stoll(id);
    vector<pair<long long, int>> index;
    index = bringAllEmpDept_idIndex();
    for (int i = 0; i < index.size(); ++i) {
        if (index[i].first == deptId) {
            return index[i].second;
        }
    }
    return -1;
}

void changeLinkedList(int pos, vector<pair<long long, int>> &index) {
    while (true) {
        if (index[pos - 1].second == -1) {
            index[pos - 1].second = (int) index.size();
            break;
        }
        pos = index[pos - 1].second;
    }
}

