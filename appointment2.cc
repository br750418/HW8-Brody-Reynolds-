/**
 *   @file: appointment2.cc
 * @author: Brody Reynolds
 *   @date: 11/19/2021
 *  @brief: Public Classes: A program that takes an formatted appointment and returns it in its separate categories 
 */

#include "appointment2.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cctype>
#include <vector>

using namespace std;

Appointment::Appointment() // Default constructor
{
    title = "N/A";
    year = 1;
    month = 1;
    day = 1;
    time = 0;
    duration = 1;
}

Appointment::Appointment(string appData) // Finds parts on inputted string
{
    int breaks = 0;

    for (size_t i = 0; i < appData.length(); i++) // Finds breaks in the taken line
    {
        if (appData.at(i) == '|')
        {
            breaks++;
        }
    }

    title = "N/A";
    year = 1;
    month = 1;
    day = 1;
    time = 0;
    duration = 1;

    size_t first = 0, second = 0;
    string substring;

    if (breaks >= 0) // Finds Title
    {
        first = appData.find("|", 0);
        string newTitle = appData.substr(0, first);
        newTitle = spaceRemoverForStrings(newTitle);

        if (newTitle.empty())
        {
            newTitle = title;
        }

        setTitle(newTitle);
    }

    if (breaks >= 1) // Finds year
    {
        second = first + 1;
        first = appData.find("|", second);
        substring = appData.substr(second, (first - second));
        int newYear = spaceRemoverForInts(substring);

        if (newYear < 1)
        {
            newYear = year;
            year = newYear;
        }
        else
        {
            year = newYear;
        }

        setYear(newYear);
    }

    if (breaks >= 2) // Finds month
    {
        second = first + 1;
        first = appData.find("|", second);
        substring = appData.substr(second, (first - second));
        int newMonth = spaceRemoverForInts(substring);

        if (newMonth < 1 || newMonth > 12)
        {
            newMonth = month;
            month = newMonth;
        }
        else
        {
            month = newMonth;
        }

        setMonth(newMonth);
    }

    if (breaks >= 3) // Finds day
    {
        second = first + 1;
        first = appData.find("|", second);
        substring = appData.substr(second, (first - second));
        int newDay = spaceRemoverForInts(substring);

        if (newDay < 1 || newDay > 31)
        {
            newDay = day;
            day = newDay;
        }
        else
        {
            day = newDay;
        }

        setDay(newDay);
    }

    if (breaks >= 4) // Finds time
    {
        second = first + 1;
        first = appData.find("|", second);
        substring = appData.substr(second, (first - second));
        int newTime = standardToMilitary(spaceRemoverForStrings(substring));
        setTime(newTime);
    }

    if (breaks >= 5) // Finds duration
    {
        second = first + 1;
        first = appData.find("|", second);
        substring = appData.substr(second, (first - second));
        int newDuration = spaceRemoverForInts(substring);

        if (newDuration < 1)
        {
            newDuration = duration;
        }

        setDuration(newDuration);
    }

    setDate(year, month, day); // Sets date
}

string Appointment::getTitle()
{
    return title;
}

int Appointment::getYear()
{
    return year;
}

int Appointment::getMonth()
{
    return month;
}

int Appointment::getDay()
{
    return day;
}

int Appointment::getTime()
{
    return time;
}

int Appointment::getDuration()
{
    return duration;
}

void Appointment::setTitle(string newTitle)
{
    if (newTitle == " ") // Sets to default value if empty
    {
        newTitle = title;
    }

    for (size_t i = 0; i < newTitle.length(); i++)
    {
        if ((newTitle[i]) == ' ') // Removes spaces
        {
            newTitle.erase(i, 1);
            i--;
        }
        else if (newTitle[newTitle.length() - (i + 1)] == ' ') // Removes spaces
        {
            newTitle.erase(newTitle.length() - (i + 1), 1);
            i--;
        }
        else
        {
            title = newTitle;
            break;
        }
    }
}

void Appointment::setYear(int newYear)
{
    if (newYear > 1)
    {
        year = newYear; // Sets new value
    }
}

void Appointment::setMonth(int newMonth)
{
    if (newMonth > 1 && newMonth < 12)
    {
        month = newMonth; // Sets new value
    }
}

void Appointment::setDay(int newDay)
{
    if (newDay > 1 && newDay < 31)
    {
        day = newDay; // Sets new value
    }
}

void Appointment::setTime(int newTime)
{
    string standardTime = to_string(newTime);

    if (newTime >= 0 && newTime <= 2400 && standardTime[standardTime.length() - 2] < '6')
    {
        time = newTime; // Sets new value
    }
}

void Appointment::setDuration(int newDuration)
{
    if (newDuration > 1)
    {
        duration = newDuration; // Sets new value
    }
}

void Appointment::setDate(int newYear, int newMonth, int newDay)
{
    setYear(newYear);
    setMonth(newMonth);
    setDay(newDay);
}

string Appointment::getDate()
{
    string newMonth, newDay;

    if (to_string(month).size() < 2) // If month is a single digit
    {
        newMonth = "0" + to_string(month);
    }
    else
    {
        newMonth = to_string(month);
    }

    if (to_string(day).size() < 2) // If day is a single digit
    {
        newDay = "0" + to_string(day);
    }
    else
    {
        newDay = to_string(day);
    }

    // Returns the date in ( 1-1-1 ) format
    return to_string(year) + "-" + newMonth + "-" + newDay;
}

string Appointment::getStandardTime()
{
    return militaryToStandard(getTime()); // Takes getTime to military and returns as standard time
}

int Appointment::standardToMilitary(string time)
{
    int first, second, hour1;
    string hour, minute, timeSet = "", newTime;

    first = time.find(':');             // Finds the hour
    second = time.find(' ', first + 1); // Finds minutes

    hour = time.substr(0, first);                    // Declares hour
    minute = time.substr(first + 1, second - first); // Declares minutes
    
    for (size_t i = 0; i < time.length(); i++) // Finds and declares meridiem
    {
        if (time[i] == ':' && (time[i]) == ' ') // Removes ':' and spaces
        {
            time.erase(i, 1);
            i--;
        }
        else if (isalpha(time[i])) // If it finds a character 
        {
            time[i] = tolower(time[i]);
            timeSet += time[i];
            time.erase(i, 1);
            i--;
        }
    }

    // Finds time if given meridiem is "am"
    if (timeSet == "am")
    {
        if (stoi(hour) == 12) // Sets hour to 0
        {
            hour = "00";
            newTime = hour + minute;
            newMTime = stoi(newTime);
        }
        else if (stoi(hour) > 0 && stoi(hour) < 12) // Gives given hour
        {
            newTime = hour + minute;
            newMTime = stoi(newTime);
        }
    }
    // Finds time if given meridiem is "pm"
    else if (timeSet == "pm")
    {
        if (stoi(hour) > 0 && stoi(hour) < 12) // Adds to hour by 12 to convert into military time
        {
            hour1 = stoi(hour) + 12;
            newTime = to_string(hour1) + minute;
            newMTime = stoi(newTime);
        }
        else if (stoi(hour) == 12) // Keeps 12 as is
        {
            newTime = hour + minute;
            newMTime = stoi(newTime);
        }
    }
    else if (!(timeSet == "pm" || timeSet == "am")) // No meridiem found
    {
        cout << "Error: meridiem not found" << endl;
        return 0;
    }
    
    return newMTime;
}

string Appointment::finalizedMilitarytime(int mTime)
{
    string newTime;

    if (to_string(mTime).size() == 1) // If value is 1 in length usually 0, than add 3 zeros to convert to military time
    {
        newTime = "000" + to_string(mTime);
    }
    else if (to_string(mTime).size() < 4) // If length is not equal to 4, add 0's
    {
        if (to_string(mTime).size() == 2) // Adds 2 zeros when length is only 2
        {
            newTime = "00" + to_string(mTime);
        }
        else // Adds 1 zero if length is only 3
        {
            newTime = "0" + to_string(mTime);
        }
    }
    else
    {
        newTime = to_string(mTime); // If value already has 4 in length, than return its value
    }

    return newTime;
}

string Appointment::militaryToStandard(int time)
{
    int hour, minute;
    string time_of_day;
    string newMinute;

    if (time > 1159) // Sets time to "pm"
    {
        time_of_day = "PM";
    }
    else
    {
        time_of_day = "AM";
    }

    if (time_of_day == "PM")
    {
        hour = ((time - 1200) / 100);   // Converts time into hour
        minute = ((time - 1200) % 100); // Converts time to remaining minutes
        newMinute = to_string(minute);

        if (hour == 0) // Sets hour to 12 if given 0
        {
            hour = 12;
        }

        if (minute == 0) // Sets minutes to "00" for proper formatting
        {
            newMinute = "00";
        }
        else if (minute != 0 && minute < 10) // Adds a "0" if a single digit is given
        {
            newMinute = "0" + to_string(minute);
        }
    }
    else
    {
        hour = ((time) / 100); // If "am", just return value
        minute = ((time) % 100);
        newMinute = to_string(minute);

        if (hour == 0) // Sets hour to 12 if given 0
        {
            hour = 12;
        }

        if (minute == 0) // Sets minutes to "00" for proper formatting
        {
            newMinute = "00";
        }
        else if (minute != 0 && minute < 10) // Adds a "0" if a single digit is given
        {
            newMinute = "0" + to_string(minute);
        }
    }

    return to_string(hour) + ":" + newMinute + time_of_day;
}

bool operator==(const Appointment &first, const Appointment &second)
{
    // Compares and then returns if statement is true
    if (first.title == second.title && first.year == second.year && first.month == second.month && first.day == second.day &&
        first.time == second.time && first.duration == second.duration)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string Appointment::spaceRemoverForStrings(string info)
{
    for (size_t i = 0; i < info.length(); i++)
    {
        if ((info[i]) == ' ') // Removes space
        {
            info.erase(i, 1);
            i--;
        }
        else if ((info[info.length() - (i + 1)]) == ' ') // Removes space
        {
            info.erase(info.length() - (i + 1), 1);
            i--;
        }
        else
        {
            break;
        }
    }

    return info;
}

int Appointment::spaceRemoverForInts(string info)
{
    for (size_t i = 0; i < info.length(); i++)
    {
        if (!(isdigit(info[i]))) // Removes everything besides a integer
        {
            info.erase(i, 1);
            i--;
        }
    }

    return stoi(info);
}

void Appointment::printSchedule(ifstream &in, ofstream &out, string line, string temp)
{
    if (temp.empty()) // Don't print if file is not empty
    {

        out << "Title";
        out << std::setw(6) << "Date";
        out << std::setw(6) << "Time";
        out << std::setw(10) << "Duration" << endl;
        out << "-------------------------------------------------" << endl;

        do
        {
            getline(in, line); // Reads line

            if (!line.empty()) // Prints a new schedule
            {
                Appointment a(line);
                out << a.getTitle();
                out << " | " << a.getDate();
                out << " | " << a.getTime();
                out << " | " << a.getDuration();
                out << endl;
            }

        } while (!in.eof());
    }
}

void Appointment::printScheduleTime(ifstream &in, ofstream &out, string line, string option2, string temp)
{

    if (temp.empty()) // Don't print if file is not empty
    {
        out << "Title";
        out << std::setw(6) << "Date";
        out << std::setw(6) << "Time";
        out << std::setw(10) << "Duration" << endl;
        out << "-------------------------------------------------" << endl;

        do
        {

            getline(in, line); // Reads line

            if (!line.empty()) // Prints new schedule
            {
                Appointment a(line);

                if (a.getTime() == stoi(option2)) // Removes appointments that match time
                {
                    out << a.getTitle();
                    out << " | " << a.getDate();
                    out << " | " << a.getTime();
                    out << " | " << a.getDuration();
                    out << endl;
                }
            }

        } while (!in.eof());
    }
    else
    {

        out.close();

        ifstream in2;
        in2.open("schedule.txt"); // Opens current schedule file

        ofstream out2;
        out2.open("output.txt"); // Opens temporary file

        out2 << "Title";
        out2 << std::setw(6) << "Date";
        out2 << std::setw(6) << "Time";
        out2 << std::setw(10) << "Duration" << endl;
        out2 << "-------------------------------------------------" << endl;

        do
        {
            getline(in2, line); // Reads line

            if (line.find(option2) != string::npos) // If line contains wanted time
            {
                out2 << line << endl; // Prints line with time
            }

        } while (!in2.eof());

        in2.close();
        out2.close();

        in2.open("output.txt");

        out2.open("schedule.txt");

        do // Updates schedule file
        {
            getline(in2, line); // Reads line

            out2 << line << endl;

        } while (!in2.eof());

        in2.close();
        out2.close();
    }
}

void Appointment::addAppointment(ifstream &in, ofstream &out, string line, string option2, string temp)
{
    if (temp.empty()) // Don't print if file is not empty
    {
        out << "Title";
        out << std::setw(6) << "Date";
        out << std::setw(6) << "Time";
        out << std::setw(10) << "Duration" << endl;
        out << "-------------------------------------------------" << endl;

        do
        {

            getline(in, line); // Reads line

            if (!line.empty()) // Prints new schedule
            {
                Appointment a(line);
                out << a.getTitle();
                out << " | " << a.getDate();
                out << " | " << a.getTime();
                out << " | " << a.getDuration();
                out << endl;
            }
        } while (!in.eof());

        Appointment a(option2); // Adds title to schedule
        out << a.getTitle();
        out << " | " << a.getDate();
        out << " | " << a.getTime();
        out << " | " << a.getDuration();
        out << endl;
    }
    else
    {
        Appointment a(option2); // Adds title to schedule
        out << a.getTitle();
        out << " | " << a.getDate();
        out << " | " << a.getTime();
        out << " | " << a.getDuration();
        out << endl;
    }
}

void Appointment::removeAppointmentTitle(ifstream &in, ofstream &out, string line, string option2, string temp)
{
    if (temp.empty()) // Don't print if file is not empty
    {
        out << "Title";
        out << std::setw(6) << "Date";
        out << std::setw(6) << "Time";
        out << std::setw(10) << "Duration" << endl;
        out << "-------------------------------------------------" << endl;

        do
        {

            getline(in, line); // Reads line

            if (!line.empty()) // Prints new schedule
            {
                Appointment a(line);
                string title2 = a.getTitle();

                for (size_t i = 0; i < title2.length(); i++) // Sets title to lowercase
                {
                    title2[i] = tolower(title2[i]);
                }

                for (size_t i = 0; i < option2.length(); i++) // Sets users title to lowercase
                {
                    option2[i] = tolower(option2[i]);
                }

                if (title2 != option2) // Prints appointments that don't match given title
                {
                    out << a.getTitle();
                    out << " | " << a.getDate();
                    out << " | " << a.getTime();
                    out << " | " << a.getDuration();
                    out << endl;
                }
            }
        } while (!in.eof());
    }
    else
    {
        out.close();

        ifstream in2;
        in2.open("schedule.txt"); // Opens current schedule file

        ofstream out2;
        out2.open("output.txt"); // Opens temporary file

        do
        {

            getline(in2, line); // Reads line

            for (size_t i = 0; i < line.length(); i++) // Sets users title to lowercase
            {
                line[i] = tolower(line[i]);
            }

            for (size_t i = 0; i < option2.length(); i++) // Sets users title to lowercase
            {
                option2[i] = tolower(option2[i]);
            }

            if (line.find(option2) == string::npos) // If line doesn't contain given title
            {

                out2 << line << endl; // Prints appointments that doesn't contain given title
            }

        } while (!in2.eof());

        in2.close();
        out2.close();

        in2.open("output.txt");

        out2.open("schedule.txt");

        do // Updates schedule file
        {
            getline(in2, line); // Reads line

            out2 << line << endl;

        } while (!in2.eof());

        in2.close();
        out2.close();
    }
}

void Appointment::removeAppointmentTime(ifstream &in, ofstream &out, string line, string option2, string temp)
{

    if (temp.empty()) // Don't print if file is not empty
    {
        out << "Title";
        out << std::setw(6) << "Date";
        out << std::setw(6) << "Time";
        out << std::setw(10) << "Duration" << endl;
        out << "-------------------------------------------------" << endl;

        do
        {

            string time;

            getline(in, line); // Reads line

            if (!line.empty()) // Prints new schedule
            {
                Appointment a(line);

                if (stoi(option2) != a.getTime()) // Prints appointments that don't match time given
                {
                    out << a.getTitle();
                    out << " | " << a.getDate();
                    out << " | " << a.getTime();
                    out << " | " << a.getDuration();
                    out << endl;
                }
            }
        } while (!in.eof());
    }
    else
    {
        out.close();

        ifstream in2;
        in2.open("schedule.txt"); // Opens current schedule file

        ofstream out2;
        out2.open("output.txt"); // Opens temporary file

        do
        {
            getline(in2, line); // Reads line

            if (line.find(option2) == string::npos) // If line doesn't contain given time
            {
                out2 << line << endl; // Prints appointments that doesn't contain given time
            }

        } while (!in2.eof());

        in2.close();
        out2.close();

        in2.open("output.txt");

        out2.open("schedule.txt");

        do // Updates schedule file
        {
            getline(in2, line); // Reads line

            out2 << line << endl;

        } while (!in2.eof());

        in2.close();
        out2.close();
    }
}