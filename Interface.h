#ifndef HOSPITAL_INTERFACE
#define HOSPITAL_INTERFACE
#include <iostream>
#include <ctime>
#include <vector>

#define PRICE_PER_DAY 10
#define INSURANCE_DISCOUNT 0.5

// Denotes the patient who will be admitted to the hospital
struct Patient {
    std::string name;
    std::string diagnosis;
    bool insured;
    time_t admitTime;

    // Constructor to initialize values with null
    // TIME COMPLEXITY IS O(1)
    Patient();

    // constructor to initialize patient values without admit time,
    // Because it is impossible for the patient to have a time of admission
    // without being admitted to the hospital,
    // so the time of admission is determined within the hospital only.
    
    // TIME COMPLEXITY IS O(1)
    Patient (std::string name, std::string disc, bool insured);
};

// This is where the patient's condition is assessed before admission to the hospital 
class WaitingArea {
private:
    struct Node {
        Patient info;
        Node *next;
        bool isPriority;
    };
    Node *front;
    Node *rear;
    Node *priorityRear;

    public:
    // Constructor to initialize the waiting area
    // TIME COMPLEXITY IS O(1)
    WaitingArea();

    // TIME COMPLEXITY IS O(1)
    bool isEmpty();

    // TIME COMPLEXITY IS O(1)
    void enqueue (Patient value, bool priority);

    // TIME COMPLEXITY IS O(1)
    void dequeue ();

    // TIME COMPLEXITY IS O(1)
    Patient getFrontPatient();
};

class Hospital {
private:
    struct Room {
        bool isFull = false;
        Patient residentPatient;
    };
    std::string name;
    std::vector<Room> rooms;
    int fullRooms;
    WaitingArea waitingArea;

public:
    // constructor to apply our system on any hospital
    // takes name and rooms number
    // TIME COMPLEXITY IS O(1)
    Hospital (std::string name, int numOfRooms);

    // TIME COMPLEXITY IS O(1)
    std::string getHospitalName();

    // TIME COMPLEXITY IS O(1)
    void printPatientInfos (std::string name);

    // TIME COMPLEXITY IS O(1)
    bool isFull();

    // TIME COMPLEXITY IS O(1)
    void addToWaitingArea ();
    
    // TIME COMPLEXITY IS O(n)
    void addToHospital ();

    // TIME COMPLEXITY IS O(n)
    int hashSystem(std::string patientName);

    // TIME COMPLEXITY IS O(n)
    int searchPatient(std::string patientName);

    // to convert time type from "time_t" to "string"
    // TIME COMPLEXITY IS O(1)
    std::string toStringTime(time_t time);

    // TIME COMPLEXITY IS O(1)
    void printBill (Patient &patient);
    
    // TIME COMPLEXITY IS O(1)
    void discharge (std::string name);
};

#endif