/**
 *   @file: appointment_main2.cc
 * @author: Brody Reynolds
 *   @date: 11/19/2021
 *  @brief: A program that takes an formatted appointment and returns it in its separate categories 
 */

#include "appointment2.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cctype>

using namespace std;

main(int argc, char const *argv[])
{
    string newTime;

    ifstream in;
    in.open("agenda.txt");

    if (in.fail()) // If fails to open
    {
        cout << "Error: no file located" << endl;
        exit(0);
    }

    ofstream out;
    out.open("schedule.txt", ios::app);

    if (out.fail()) // If fails to open
    {
        cout << "Error: file not created" << endl;
        exit(0);
    }

    int i;
    string temp;

    out.close();

    ifstream in2;
    in2.open("schedule.txt");

    if (in2.fail())
    {
        cout << "Error: no file located" << endl;
        exit(0);
    }

    do // Checks file to see if its empty
    {
        getline(in2, temp);
        temp[i] = temp[i];

        if (!temp.empty())
        {
            break;
        }
        
        i++;

    } while (!in2.eof());

    if (!temp.empty()) // Won't change file if not empty
    {
        cout << "File is not empty" << endl; 
        in2.close();
        out.open("schedule.txt", ios::app);
    }
    else
    {
        cout << "File is empty" << endl; // Changes empty file to default schedule
        in2.close();
        out.open("schedule.txt");
    }

    string line, option, option2;

    option = argv[1];

    if (option == "-ps") // Prints schedule
    {
        Appointment a;
        a.printSchedule(in, out, line, temp);
    }

    option2 = argv[2];

    if (option == "-p" && !option2.empty()) // Prints only the appointments that match given time
    {
        Appointment a;
        a.printScheduleTime(in, out, line, option2, temp);
    }

    else if (option == "-a" && !option2.empty()) // Adds appointment to schedule
    {
        Appointment a;
        a.addAppointment(in, out, line, option2, temp);
    }

    else if (option == "-dt" && !option2.empty()) // Removes appointments based on given title
    {
        Appointment a;
        a.removeAppointmentTitle(in, out, line, option2, temp);
    }

    else if (option == "-dm" && !option2.empty()) // Removes appointments based on given time
    {
        Appointment a;
        a.removeAppointmentTime(in, out, line, option2, temp);
    }

    out.close();
    in.close();

    return 0;
} // main
