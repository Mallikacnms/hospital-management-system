#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <bits/stdc++.h>

using namespace std;

class HospitalManagementSystem
{
private:
    int roomNumber;
    string patientName;
    string patientAddress;
    string patientPhone;
    int days;
    float totalBill;
    bool routineCheckup;

public:
    void displayMainMenu();
    void admitPatient();
    void displayPatientDetails();
    void displayAdmittedPatients();
    void updatePatientDetails();
    void performRoutineCheckup();
    bool isRoomOccupied(int roomNumber);
    void modifyPatientDetails(int roomNumber);
    void dischargePatient(int roomNumber);
};

void HospitalManagementSystem::admitPatient()
{
    cout << "\nAdmit a Patient" << endl;
    cout << "----------------" << endl;
    cout << "Room Number: ";
    cin >> roomNumber;

    if (isRoomOccupied(roomNumber))
    {
        cout << "Room " << roomNumber << " is already occupied!" << endl;
        return;
    }

    cin.ignore();
    cout << "Patient Name: ";
    getline(cin, patientName);
    cout << "Patient Address: ";
    getline(cin, patientAddress);
    cout << "Patient Phone: ";
    getline(cin, patientPhone);
    cout << "Number of Days: ";
    cin >> days;
    cout << "Total Bill: ";
    cin >> totalBill;

    routineCheckup = false;

    ofstream fout("patients.txt", ios::app);
    fout << roomNumber << "," << patientName << "," << patientAddress << "," << patientPhone << ","
         << days << "," << totalBill << "," << routineCheckup << endl;
    fout.close();

    cout << "\nPatient admitted successfully!" << endl;
}

void HospitalManagementSystem::displayPatientDetails()
{
    cout << "\nDisplay Patient Details" << endl;
    cout << "-----------------------" << endl;
    cout << "Enter the Room Number: ";
    cin >> roomNumber;

    ifstream fin("patients.txt");
    if (!fin)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    bool found = false;
    string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string token;
        getline(ss, token, ',');
        if (stoi(token) == roomNumber)
        {
            found = true;
            cout << "\nPatient Details" << endl;
            cout << "---------------" << endl;
            cout << "Room Number: " << token << endl;
            getline(ss, token, ',');
            cout << "Patient Name: " << token << endl;
            getline(ss, token, ',');
            cout << "Patient Address: " << token << endl;
            getline(ss, token, ',');
            cout << "Patient Phone: " << token << endl;
            getline(ss, token, ',');
            cout << "Number of Days: " << token << endl;
            getline(ss, token, ',');
            cout << "Total Bill: $" << token << endl;
            getline(ss, token, ',');
            bool isRoutineCheckupDone = (token == "1");
            cout << "Routine Checkup: " << (isRoutineCheckupDone ? "Done" : "Pending") << endl;
            break;
        }
    }

    if (!found)
    {
        cout << "Patient not found for Room Number " << roomNumber << "!" << endl;
    }

    fin.close();
}

void HospitalManagementSystem::displayAdmittedPatients()
{
    cout << "\nDisplay Admitted Patients" << endl;
    cout << "-------------------------" << endl;

    ifstream fin("patients.txt");
    if (!fin)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    string line;
    cout << left << setw(10) << "Room" << setw(20) << "Name" << setw(20) << "Address"
         << setw(15) << "Phone" << setw(10) << "Days" << setw(10) << "Bill" << setw(15) << "Routine Checkup" << endl;
    cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string token;
        getline(ss, token, ',');
        cout << left << setw(10) << token;

        getline(ss, token, ',');
        cout << setw(20) << token;

        getline(ss, token, ',');
        cout << setw(20) << token;

        getline(ss, token, ',');
        cout << setw(15) << token;

        getline(ss, token, ',');
        cout << setw(10) << token;

        getline(ss, token, ',');
        cout << setw(10) << "$" << token;

        getline(ss, token, ',');
        bool isRoutineCheckupDone = (token == "1");
        cout << setw(15) << (isRoutineCheckupDone ? "Done" : "Pending") << endl;
    }

    fin.close();
}

void HospitalManagementSystem::updatePatientDetails()
{
    cout << "\nUpdate Patient Details" << endl;
    cout << "----------------------" << endl;
    cout << "Enter the Room Number: ";
    cin >> roomNumber;

    fstream file("patients.txt", ios::in | ios::out);
    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    bool found = false;
    string line;
    ofstream tempFile("temp.txt", ios::out);
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        getline(ss, token, ',');
        if (stoi(token) == roomNumber)
        {
            found = true;
            cout << "\nCurrent Patient Details" << endl;
            cout << "-----------------------" << endl;
            cout << "Room Number: " << token << endl;
            getline(ss, token, ',');
            cout << "Patient Name: " << token << endl;
            getline(ss, token, ',');
            cout << "Patient Address: " << token << endl;
            getline(ss, token, ',');
            cout << "Patient Phone: " << token << endl;
            getline(ss, token, ',');
            cout << "Number of Days: " << token << endl;
            getline(ss, token, ',');
            cout << "Total Bill: $" << token << endl;

            cin.ignore();
            cout << "\nEnter New Details" << endl;
            cout << "-----------------" << endl;
            cout << "Patient Name: ";
            getline(cin, patientName);
            cout << "Patient Address: ";
            getline(cin, patientAddress);
            cout << "Patient Phone: ";
            getline(cin, patientPhone);
            cout << "Number of Days: ";
            cin >> days;
            cout << "Total Bill: ";
            cin >> totalBill;

            tempFile << roomNumber << "," << patientName << "," << patientAddress << "," << patientPhone << ","
                     << days << "," << totalBill << endl;

            cout << "\nPatient details updated successfully!" << endl;
        }
        else
        {
            tempFile << line << endl;
        }
    }

    if (!found)
    {
        cout << "Patient not found for Room Number " << roomNumber << "!" << endl;
    }

    file.close();
    tempFile.close();

    remove("patients.txt");
    rename("temp.txt", "patients.txt");
}


void HospitalManagementSystem::performRoutineCheckup()
{
    cout << "\nPerform Routine Checkup" << endl;
    cout << "-----------------------" << endl;
    cout << "Enter the Room Number: ";
    cin >> roomNumber;

    fstream file("patients.txt", ios::in | ios::out);
    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    bool found = false;
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        getline(ss, token, ',');
        if (stoi(token) == roomNumber)
        {
            found = true;
            getline(ss, token, ','); // Skip patient name
            getline(ss, token, ','); // Skip patient address
            getline(ss, token, ','); // Skip patient phone
            getline(ss, token, ','); // Skip number of days
            getline(ss, token);      // Skip total bill

            file.seekp(file.tellg()); // Move the write pointer to the current position

            file << "1" << endl; // Mark routine checkup as done

            cout << "\nRoutine Checkup performed successfully for Room Number " << roomNumber << "!" << endl;

            break;
        }
    }

    if (!found)
    {
        cout << "Patient not found for Room Number " << roomNumber << "!" << endl;
    }

    file.close();
}

bool HospitalManagementSystem::isRoomOccupied(int roomNumber)
{
    ifstream fin("patients.txt");
    if (!fin)
    {
        cout << "Error opening file!" << endl;
        return false;
    }

    string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string token;
        getline(ss, token, ',');
        if (stoi(token) == roomNumber)
        {
            fin.close();
            return true;
        }
    }

    fin.close();
    return false;
}

void HospitalManagementSystem::dischargePatient(int roomNumber)
{
    cout << "\nDischarge a Patient" << endl;
    cout << "-------------------" << endl;
    cout << "Enter the Room Number: ";
    cin >> roomNumber;

    fstream file("patients.txt", ios::in | ios::out);
    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    bool found = false;
    string line;
    ofstream tempFile("temp.txt", ios::out);
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        getline(ss, token, ',');
        if (stoi(token) == roomNumber)
        {
            found = true;
            cout << "\nDischarged Patient Details" << endl;
            cout << "--------------------------" << endl;
            cout << "Room Number: " << token << endl;
            getline(ss, token, ',');
            cout << "Patient Name: " << token << endl;
            getline(ss, token, ',');
            cout << "Patient Address: " << token << endl;
            getline(ss, token, ',');
            cout << "Patient Phone: " << token << endl;
            getline(ss, token, ',');
            cout << "Number of Days: " << token << endl;
            getline(ss, token); // Skip total bill
        }
        else
        {
            tempFile << line << endl;
        }
    }

    file.close();
    tempFile.close();

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (found)
    {
        cout << "\nPatient discharged successfully!" << endl;
    }
    else
    {
        cout << "Patient not found for Room Number " << roomNumber << "!" << endl;
    }
}

void HospitalManagementSystem::displayMainMenu()
{
    int choice;
    while (true)
    {
        cout << "\n************* Hospital Management System *************" << endl;
        cout << "1. Admit a Patient" << endl;
        cout << "2. Display Patient Details" << endl;
        cout << "3. Display Admitted Patients" << endl;
        cout << "4. Update Patient Details" << endl;
        cout << "5. Perform Routine Checkup" << endl;
        cout << "6. Discharge a Patient" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            admitPatient();
            break;
        case 2:
            displayPatientDetails();
            break;
        case 3:
            displayAdmittedPatients();
            break;
        case 4:
            updatePatientDetails();
            break;
        case 5:
            performRoutineCheckup();
            break;
        case 6:
            int roomNumber;
            cout << "Enter the Room Number to discharge the patient: ";
            cin >> roomNumber;
            dischargePatient(roomNumber);
            break;
        case 7:
            return;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
}

int main()
{
    HospitalManagementSystem hms;
    hms.displayMainMenu();
    return 0;
}
