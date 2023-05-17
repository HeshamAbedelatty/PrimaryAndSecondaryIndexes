//
// Created by HESHAM on 11/30/2022.
//
#include "Emp&Dept.h"
#include <bits/stdc++.h>

int writeDepartment(Department &department) {
    int length;
    char record[140];
    strcpy(record, department.dept_id);
    strcat(record, "|");
    strcat(record, department.dept_name);
    strcat(record, "|");
    strcat(record, department.dept_manger);
    strcat(record, "|");
    length = (int)strlen(record);
    string s = to_string(length);
    char len[sizeof(int)];
    strcpy(len, s.c_str());

    ofstream instert("DepartmentData.txt", ios::out | ios::app);
    instert.seekp(0, ios::end);
    int byteOffset = (int)instert.tellp();
    instert.write(len, sizeof(int));
    instert.write(record, length);
    instert.close();
    return byteOffset;


}

void readDepartment(int byteOffset) {
    ifstream readfile("DepartmentData.txt", ios::in);
    readfile.seekg(byteOffset, ios::beg);
    char length[sizeof(int)];
    readfile.read(length, sizeof(int));
    string s = (string) length;
    int len = stoi(s);
    char record[len];
    readfile.read(record, len);
    cout << record;

    readfile.close();
}

void flagDepFile() {
    int True = 0;
    int fl;
    ifstream readfile("DepartmentData.txt", ios::in);
    readfile.seekg(0, ios::end);
    fl = (int)readfile.tellg();
    if (fl < 1) {
        True = 1;
    }
    readfile.close();
    if (True == 1) {
        ofstream instert("DepartmentData.txt", ios::out);
        instert.seekp(0, ios::beg);
        char header[sizeof(int)];
        string Flag = to_string(-1);
        strcpy(header, Flag.c_str());
        instert.write(header, sizeof(int));
        instert.close();

    }

}

//***************************************DepartmentPrimaryIndex*********************************************

void writeDepartmentPrimaryIndex(vector<pair<long long, int>> &PIndex) {
    ofstream instert("PrimayIndexDeptID.txt", ios::out);
    instert.seekp(0, ios::beg);
    string id, byte;
    PI_DeptID Id{};
    for (auto & i : PIndex) {
        id = to_string(i.first);
        byte = to_string(i.second);
        strcpy(Id.id, id.c_str());
        strcpy(Id.byteoffset, byte.c_str());
        instert.write(Id.id, 30);
        instert.write(Id.byteoffset, sizeof(int));
    }

    instert.close();
}

vector<pair<long long, int >> bringAllDeptIDIndex() {
    ifstream readfile("PrimayIndexDeptID.txt", ios::in);
    readfile.seekg(0, ios::end);
    int length = (int)readfile.tellg();
    readfile.seekg(0, ios::beg);
    char indexid[30];
    char indexByteOffset[sizeof(int)];
    int numOfRecord = length / (sizeof(int) + 30);
    vector<pair<long long, int>> primaryIndex(numOfRecord + 1);
    readfile.seekg(0, ios::cur);
    for (int i = 0; i < numOfRecord; ++i) {
        readfile.read(indexid, 30);
        readfile.read(indexByteOffset, sizeof(int));
        primaryIndex[i].first = stoll((string) indexid);
        primaryIndex[i].second = stoi((string) indexByteOffset);

    }
    readfile.close();
    return primaryIndex;
}

vector<pair<long long, int>> insertionSortDepartmentDept_Id(pair<long long, int> arr) {
    vector<pair<long long, int>> index;
    index = bringAllDeptIDIndex();

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

//****************************************DepartmentSecondaryIndex*********************************************
void writeDepartmentSecondrayIndex(vector<pair<string, int>> &SIndex) {
    ofstream ins("SecondaryIndexDept_Name.txt", ios::out);
    ins.seekp(0, ios::beg);
    string id, byte;
    SI_Dept_Name Id{};
    for (int i = 0; i < SIndex.size(); ++i) {
        id = SIndex[i].first;
        byte = to_string(SIndex[i].second);
        strcpy(Id.dept_name, id.c_str());
        strcpy(Id.RRN, byte.c_str());
        ins.write(Id.dept_name, 50);
        ins.write(Id.RRN, sizeof(int));
    }
    ins.close();
}

void writeDepartmentSecondrayLinkedList(vector<pair<long long, int>> &LLIndex) {
    ofstream instert("LinkedListDept_Name.txt", ios::out);
    instert.seekp(0, ios::beg);
    string Pid, rrn;
    SILinkedList_Dept_Name LL{};
    for (int i = 0; i < LLIndex.size(); ++i) {
        Pid = to_string(LLIndex[i].first);
        rrn = to_string(LLIndex[i].second);
        strcpy(LL.dept_id, Pid.c_str());
        strcpy(LL.RRN, rrn.c_str());
        instert.write(LL.dept_id, 30);
        instert.write(LL.RRN, sizeof(int));
    }
    instert.close();
}

vector<pair<string, int >> bringAllDeptartmentNameIndex() {
    ifstream readfile("SecondaryIndexDept_Name.txt", ios::in);
    readfile.seekg(0, ios::end);
    int length = readfile.tellg();
    readfile.seekg(0, ios::beg);
    char indexid[50];
    char indexByteOffset[sizeof(int)];
    int numOfRecord = length / (sizeof(int) + 50);
    vector<pair<string, int>> secondaryIndex(numOfRecord + 1);
    readfile.seekg(0, ios::cur);
    for (int i = 0; i < numOfRecord; ++i) {
        readfile.read(indexid, 50);
        readfile.read(indexByteOffset, sizeof(int));
        secondaryIndex[i].first = (string) indexid;
        secondaryIndex[i].second = stoi((string) indexByteOffset);

    }
    readfile.close();
    return secondaryIndex;
}

vector<pair<long long, int >> bringAllDeptartmentNameL_ListIndex() {
    ifstream readfile("LinkedListDept_Name.txt", ios::in);
    readfile.seekg(0, ios::end);
    int length = readfile.tellg();
    readfile.seekg(0, ios::beg);
    char indexid[30];
    char indexByteOffset[sizeof(int)];
    int numOfRecord = length / (sizeof(int) + 30);
    vector<pair<long long, int>> LinkedListIndex(numOfRecord);
    readfile.seekg(0, ios::cur);
    for (int i = 0; i < numOfRecord; ++i) {
        readfile.read(indexid, 30);
        readfile.read(indexByteOffset, sizeof(int));
        LinkedListIndex[i].first = stoll((string) indexid);
        LinkedListIndex[i].second = stoi((string) indexByteOffset);

    }
    readfile.close();
    return LinkedListIndex;
}

vector<pair<string, int>> insertionSortDeptartmentName(pair<string, int> arr) {
    vector<pair<string, int>> index;
    index = bringAllDeptartmentNameIndex();

    int i = (int) index.size() - 1;
    while (i > 0 && index[i - 1].first > arr.first) {
        index[i].first = index[i - 1].first;
        index[i].second = index[i - 1].second;
        i--;

    }
    index[i].first = arr.first;
    index[i].second = arr.second;

    return index;
}

int IsExistDeptartmentName(const string &id) {
    string dept_name = id;
    vector<pair<string, int>> index;
    index = bringAllDeptartmentNameIndex();
    for (int i = 0; i < index.size(); ++i) {
        if (index[i].first == dept_name) {
            return index[i].second;
        }
    }
    return -1;
}

void changeDeptartmentNameLinkedList(int pos, vector<pair<long long, int>> &index) {
    while (true) {
        if (index[pos - 1].second == -1) {
            index[pos - 1].second = (int) index.size();
            break;
        }
        pos = index[pos - 1].second;
    }
}
int BinSearchDeptname(vector<pair<string ,int>> arr , string X )
{
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