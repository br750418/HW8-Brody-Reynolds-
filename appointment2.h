/**
 *   @file: appointment2.h
 * @author: Brody Reynolds
 *   @date: 11/19/2021
 *  @brief: Class: A program that takes an formatted appointment and returns it in its separate categories 
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cctype>
#ifndef APPOINTMENT2_H
#define APPOINTMENT2_H

using namespace std;

class Appointment
{
public:
    Appointment(); // Default constructor
    Appointment(string appData); // Finds data from inputted string

    string getTitle(); // Grabs title
    int getYear(); // Grabs year
    int getMonth(); // Grabs month
    int getDay(); // Grabs day
    int getTime(); // Grabs time into military time
    int getDuration(); // Grabs duration
    string getDate(); // Grabs the year, month, and day. Returns a date in the format 2021-11-23
    string getStandardTime(); // Grabs military time and returns to standard time

    void setTitle(string newTitle); // Sets new title
    void setYear(int newYear); // Sets new year
    void setMonth(int newMonth); // Sets new month
    void setDay(int newDay); // Sets new day
    void setTime(int newTime); // Sets new time to military time
    void setDuration(int newDuration); // Sets new duration
    void setDate(int newYear, int newMonth, int newDay); // Sets new date from the year, month, and day

    string militaryToStandard(int time); // Converts military to standard time
    int standardToMilitary(string time); // Converts standard to military time
    string finalizedMilitarytime(int mTime); // Finalizes military time to the right format
    friend bool operator== (const Appointment &first, const Appointment &second); // Checks for true or false values
    
    string spaceRemoverForStrings(string info); // Removes spaces for strings
    int spaceRemoverForInts(string info); // Removes spaces for integers
    void printSchedule(ifstream &in, ofstream &out, string line, string temp); // Prints schedule 
    void printScheduleTime(ifstream &in, ofstream &out, string line, string option2, string temp); // Prints only the appointments that match given time
    void addAppointment(ifstream &in, ofstream &out, string line, string option2, string temp); // Adds appointment to schedule 
    void removeAppointmentTitle(ifstream &in, ofstream &out, string line, string option2, string temp); // Removes appointments based on given title
    void removeAppointmentTime(ifstream &in, ofstream &out, string line, string option2, string temp); // Removes appointments based on given time

private:
    string title; 
    int year;
    int month;
    int day;
    int time;
    int duration;
    int newMTime;
};

#endif