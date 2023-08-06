#ifndef PATIENT_WAITINGAREA_IMPLEMENT
#define PATIENT_WAITINGAREA_IMPLEMENT
#include <iostream>
#include <ctime>
#include <vector>
#include "Interface.h"

// Patient Struct
Patient::Patient() { 
    this->name = "N/A";
    this->diagnosis = "N/A";
    this->insured = false;
}

Patient::Patient (std::string name, std::string disc, bool insured) {
    this->name = name;
    this->diagnosis = disc;
    this->insured = insured;
    // without admit time,
    // Because it is impossible for the patient to have a time of admission
    // without being admitted to the hospital,
    // so the time of admission is determined within the hospital only.
}

// Waiting Area Class
WaitingArea::WaitingArea () {
    front = rear = priorityRear = NULL;
}

bool WaitingArea::isEmpty() {
    return (front == NULL);
}

void WaitingArea::enqueue (Patient value, bool priority = false) { 
    Node *newNode = new Node;
    newNode->info = value;
    newNode->isPriority = priority;
    // if the diagnosis is an emergency case
    if (newNode->isPriority == true) {
        if (isEmpty()) {
            front = rear = newNode;
            newNode->next = NULL;            
        }
        // if the waiting area dosen't contain emrgency cases before
        else if (priorityRear == NULL) {
            newNode->next = front;
            front = newNode;
        }
        else {
            // if waiting area contains only emergency cases
            if (priorityRear->next == NULL)
                rear = newNode;
            newNode->next = priorityRear->next;
            priorityRear->next = newNode;
        }
        priorityRear = newNode;
    }
    // if the diagnosis is not emergency
    else { 
        if (isEmpty())
            front = newNode;
        else
            rear->next = newNode;
        rear = newNode;
        newNode->next = NULL;
    }
}

void WaitingArea::dequeue () { 
    if (isEmpty())
        std::cout << "Waiting area is empty.\n";
    // if waiting area contains only 1 patient
    else if (rear == front) {
        Node *temp = front;
        rear = front = NULL;
        delete temp;
    }            
    // if waiting area contains a lot of patients
    else {
        // if waiting area contains a lot of patients
        // but it contains only 1 emergency case
        if (priorityRear == front)
            priorityRear = NULL;              
        Node *temp = front;
        front = front->next;
        delete temp;
    }
}

Patient WaitingArea::getFrontPatient() {
    return front->info;
}

#endif