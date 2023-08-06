#ifndef HOSPITAL_IMPLEMENT
#define HOSPITAL_IMPLEMENT
#include <iostream>
#include <ctime>
#include <vector>
#include "Patient_and_WaitingArea_Implementation.cpp"

Hospital::Hospital (std::string name, int numOfRooms) {
    rooms.resize(numOfRooms);
    this->name = name;
    fullRooms = 0;
}

std::string Hospital::getHospitalName() {
    return name;
}

void Hospital::printPatientInfos (std::string name) { 
        int roomNumber = searchPatient(name);
        std::cout << "\nPatient Name: " << rooms[roomNumber].residentPatient.name
                  << "\nWhat is patient diagnosis? " << rooms[roomNumber].residentPatient.diagnosis
                  << "\nIs the patient insured? ";
        (rooms[roomNumber].residentPatient.insured)? std::cout << "Yes\n\n" : std::cout << "No\n\n";
        std::string strTime = toStringTime(rooms[roomNumber].residentPatient.admitTime);
        std::cout << "Admission Date: " << strTime << "\n";
}

bool Hospital::isFull() {
    return fullRooms == rooms.capacity();
}

void Hospital::addToWaitingArea () {
    if (isFull())
        std::cout << "Sorry, there are no available rooms, you have to wait for any room to be available.\n";
    else {  
        std::cout << "Enter the patient's name: ";
        std::string name;
        std::cin.ignore();
        std::getline (std::cin, name);

        std::cout << "What is the patient diagnosis? ";
        std::string diagnosis;
        std::getline (std::cin, diagnosis);
            
        char yesOrNo;
        // do while loop to force the user to answer only yes or no
        do {
            std::cout << "Is the case an emergency? (y, n): ";
            std::cin >> yesOrNo;
        }
        while (tolower(yesOrNo) != 'y' && tolower(yesOrNo) != 'n');
        bool priority = tolower(yesOrNo) == 'y';

        // Its value has been changed, so that it is not taken it's value automatically on the next loop
        yesOrNo = 'm';
        do {
            std::cout << "Does patient have insurance? (y, n): ";
            std::cin >> yesOrNo;
        }
        while (tolower(yesOrNo) != 'y' && tolower(yesOrNo) != 'n');
        bool insured = tolower(yesOrNo) == 'y';

        Patient newPatient (name, diagnosis, insured);
        waitingArea.enqueue(newPatient, priority);
    }
}
    
void Hospital::addToHospital () {
    if (isFull()) {
        std::cout << "Sorry, there are no available rooms.\n";
    }
    else if (waitingArea.isEmpty())
        std::cout << "The waiting area is empty\n";
    else {
        Patient temp = waitingArea.getFrontPatient();
        waitingArea.dequeue();
        int pos = hashSystem(temp.name);
        // if the room is full go to the next empty room
        while (rooms[pos].isFull)
            pos = (pos + 1) % rooms.capacity();
        rooms[pos].isFull = true;
        rooms[pos].residentPatient = temp;
        rooms[pos].residentPatient.admitTime = std::time(NULL);
        fullRooms++;
        std::cout << "The patient name is: " << rooms[pos].residentPatient.name << ",\n"
                  << "The patient room number is: " << pos << "\n";
    }
}

int Hospital::hashSystem(std::string patientName) {
    int sum = 0;
    for (char x : patientName) // sum the ASCII of every character of the patient name
        sum += x;
    return sum % rooms.capacity();
}

int Hospital::searchPatient(std::string patientName) {
    int roomNumber = (-1);
    if (fullRooms == 0)
        roomNumber = (-1);
    else {
        int pos = hashSystem(patientName);
        int temp = pos;
        while (rooms[pos].isFull) {
            if (rooms[pos].residentPatient.name == patientName) {
                roomNumber = pos;
                break;
            }
            else {
                pos = (pos + 1) % rooms.capacity();
                if (pos == temp) {
                    roomNumber = (-1);
                    break;
                }
            }
        }
    }
    return roomNumber;
}

std::string Hospital::toStringTime(time_t time) {
    char temp[33];
    // to storing the time in cstring 
    strftime(temp, 33, "%A %Y-%m-%d %H:%M:%S", std::localtime(&time));
    // to convert "cstring" to "std::string"
    std::string strTime(temp);
    return strTime;
}

void Hospital::printBill (Patient &patient) {
    std::cout << getHospitalName() << "\n\n";
    printPatientInfos(patient.name);

    time_t dischargeTime = std::time(NULL);
    std::string strTime = toStringTime(dischargeTime);
        
    std::cout << "Discharge Date: " << strTime
              << "\nDuration of stay in hospital: "
              << difftime(dischargeTime, patient.admitTime);
    double charges = difftime(dischargeTime, patient.admitTime) * PRICE_PER_DAY;
    float discount = (patient.insured)? INSURANCE_DISCOUNT : 1;
    double total = charges * discount;

    std::cout << "\n\nPre-discount charges: " << charges
              << "\nInsurance Discount: ";
    (patient.insured)? std::cout << "50%" : std::cout << "0%";
    std::cout << "\nTotal charges: " << total << "\n\n\n";
}
    
void Hospital::discharge (std::string name) {
    // if hospital is empty
    if (fullRooms == 0)
        std::cout << "not found\n";
    else {
        int roomNumber = searchPatient(name);
        printBill(rooms[roomNumber].residentPatient);
        rooms[roomNumber].isFull = false;
        rooms[roomNumber].residentPatient.name = "N/A";
        rooms[roomNumber].residentPatient.diagnosis = "N/A";
        rooms[roomNumber].residentPatient.insured = false;
        rooms[roomNumber].residentPatient.admitTime = 0;
        fullRooms--;
    }
}

#endif