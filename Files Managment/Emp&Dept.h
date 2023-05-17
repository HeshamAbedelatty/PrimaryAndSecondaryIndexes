//
// Created by HESHAM on 11/30/2022.
//

#ifndef FILES_MANAGMENT_EMP_DEPT_H
#define FILES_MANAGMENT_EMP_DEPT_H

#include <bits/stdc++.h>
using namespace std;

const static int maxRecordSize = 150;
//const static int maxRecordSize_prim = 20;
//const char DFlag = '*';

// ****************Employee***************

struct Employee
{
    char employee_id[13];//primary
    char dept_id[30];//secandry key
    char employee_name[50];
    char employee_position[50];

};
int writeEmployee( Employee & );
//void readEmployee(int);
void flagEmpFile ();
//bool readHeaderFile();
// ****************EmployeePrimaryIndex***************

struct PI_EmpID
{
    char id[13];
    char byteoffset[sizeof (int)];
};
void writeEmployeePrimaryIndex(vector<pair<long long ,int>>& );
vector<pair<long long ,int >> bringAllEmpIDIndex();
int BinSearch(vector<pair<long long ,int>> , long long  );
vector<pair<long long ,int>> insertionSort( pair<long long ,int>);
// ****************EmployeeSecondaryIndex***************
struct SI_EmpDeptId
{
    char Dept_id[30];
    char RRN[sizeof (int)];
};
struct SILinkedList_EmpDeptId
{
    char Emp_id[13];
    char RRN[sizeof (int)];
};
void writeEmployeeSecondrayIndex(vector<pair<long long ,int>> & );
void writeEmployeeSecondrayLinkedList(vector<pair<long long ,int>> & );
vector<pair<long long ,int >> bringAllEmpDept_idIndex();
vector<pair<long long ,int >> bringAllEmpDept_idL_ListIndex();
vector<pair<long long ,int>> insertionSortDeptid( pair<long long ,int>);
int IsExist(const string&);
void changeLinkedList(int,vector<pair<long long ,int>>& );

// ****************Department***************

struct Department
{
    char dept_id[30];//primary key
    char dept_name[50];//secandry key
    char dept_manger[50];
};
int writeDepartment(Department & );
void readDepartment(int);
void flagDepFile();
// ****************DepartmentPrimaryIndex***************

struct PI_DeptID
{
    char id[30];
    char byteoffset[sizeof (int)];
};
void writeDepartmentPrimaryIndex(vector<pair<long long ,int>>& );
vector<pair<long long ,int >> bringAllDeptIDIndex();
vector<pair<long long ,int>> insertionSortDepartmentDept_Id( pair<long long ,int>);
struct SI_Dept_Name
{
    char dept_name[50];
    char RRN[sizeof (int)];
};
struct SILinkedList_Dept_Name
{
    char dept_id[30];
    char RRN[sizeof (int)];
};

void writeDepartmentSecondrayIndex(vector<pair<string ,int>> & );
void writeDepartmentSecondrayLinkedList(vector<pair<long long ,int>> & );
vector<pair<string ,int >> bringAllDeptartmentNameIndex();
vector<pair<long long ,int >> bringAllDeptartmentNameL_ListIndex();
vector<pair<string ,int>> insertionSortDeptartmentName( pair<string ,int>);
int IsExistDeptartmentName(const string&);
void changeDeptartmentNameLinkedList(int,vector<pair<long long ,int>>& );
// ****************Functions***************
void printEmpBNameyId(string id);
int BinSearchDeptname(vector<pair<string ,int>> , string  );
void addEmployee();
void deleteEmployeeById(const string& Id);
void printEmpById(string );
void printEmpByDept_id(string id);
void addDepartment ();
void deleteDepartmentById(const string &Id);
void printDeptById(string id);
void printDeptByDept_name(string id);
#endif //FILES_MANAGMENT_EMP_DEPT_H
