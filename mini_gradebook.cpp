#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

//Defining various constants
const int FAIL_THRESHOLD = 60; //The score at which a student is designated "failing"
const string STOP_WORD = "[STOP]"; //Stop word is being defined as a constant for best practices. Mostly so I can change it at a whim.
const string BAR = "------------------------------------"; //Used for organization

//Define student struct that we'll be using to store information about the students and their grades.
//Note that it's being defined outside of main to make it available to our "get_student_info" function
struct Student
{
    string name;
    double grade;
};


void get_student_roster_stats(vector<Student> student_vector)
{
    /*
    Displays the entirety of the class, names, grades, whether they passed or failed, in addition to the highest, lowest, and average score in the class 
    */
    //Highest and lowest grades are both initilized to be whatever the first student in the vector is to give the future if statement something to compare against during the first iteration
    Student highest_grade_student = student_vector[0];
    Student lowest_grade_student = student_vector[0];
    double total_grade; //This will be the summation of the students grades, which will be used to calculate average later.
    double average;
    int class_size = student_vector.size(); //Sets class size to be the size of the student vector

    cout << "\nTotal number of students: " << class_size << endl;
    cout << BAR << endl; //Seperating output
    
    string pass_or_fail;
    for (Student student : student_vector)
    {
        //The following if statement decides whether a student has passed or failed based on the "FAIL_THRESHOLD" constant
        if (student.grade <= FAIL_THRESHOLD)
        {
            pass_or_fail = "Fail";
        }
        else
        {
            pass_or_fail = "Pass";
        }
        cout << "Name: " << student.name << "\tGrade: " << student.grade << "\t" << pass_or_fail << endl;
    }

    for(Student student : student_vector)
    {
        total_grade += student.grade;

        if (student.grade > highest_grade_student.grade) //Changes student with highest score if the current student's score is higher
        {
            highest_grade_student = student;
        }
        else if (student.grade < lowest_grade_student.grade)//Changes student with lowest score if the current student's score is lower 
        {
            lowest_grade_student = student;
        }

    }
    average = total_grade / class_size; //Divide the sum of all students scores by the amount of elements in the Student vector to get average

    cout << BAR << endl; //Seperating output
    cout << "Average grade: " << showpoint << setprecision(2)<< fixed << average << endl <<
            "Highest grade: " << highest_grade_student.name << ":\t" << highest_grade_student.grade << endl <<
            "Lowest grade: " << lowest_grade_student.name << ":\t" << lowest_grade_student.grade << endl;
}


Student get_student_info(bool sentinel_mode = false) //Sentinel mode is set to false by default
/*
    The purpose of this function is garner user input to define Student structs we defined earlier.
*/
{
    Student student;
    string passing; 
    cout << "Please enter the student's name: ";
    cin.ignore();
    getline(cin,student.name);
    if (student.name == STOP_WORD && sentinel_mode == true) //Only ends student info gathering early if sentinel mode is active.
    {
        return student; //Returns student and breaks the function early
    }
    
    while (true) //loops until valid grade is given
    {
        cout << "Please enter the student's grade as a number between 0 and 100: ";
        cin >> student.grade;

        if (cin.fail() || student.grade < 0 || student.grade > 100) //Ensures users input is between 0 and 100
        {
            cout << "Try again. Please enter student grade as a number between 0 and 100\n";
            cin.clear(); //Clears cin error flags
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); //Discards the invalid user input from the input buffer
        }
        else
        {
            break; //breaks the loop when correct input has been entered
        }
    }
    return student;
}


int main()
{
    cout << "Student Gradebook\n";

    vector<Student> student_roster; //Declaring the vector will hold all of the student structs

    int loop_mode; //Initialize loop choice integer to store user menu selection
    //Present the user with menu options. Provide exposition on how the program works
    cout << "Select loop mode by inputing the associated number. 1 for Counter-Controlled. 2 for Sentinel-Controlled.\n\n"
            "1. Counter-controlled loop (For loop):\n"
            "\t- Counter-controlled loop will allow you to a specific number of students as defined by you.\n\n"
            "2. Sentinel-controlled loop (While loop):\n"
            "\t- Sentinel-controlled loop will allow you to specify an indefinite number of student until you type " << STOP_WORD << " - brackets included.\n\n"
            << "3. Quit Program.\n\n";
    cout << "Please enter a menu option ( 1 2 3 ): ";
    cin >> loop_mode;

    switch(loop_mode) // Use switch statement to define menu functionality
    {
        case 1:
            int max_students;
            cout << "You have selected \"Counter-controlled loop mode\"\n\n";
            while(true)
            {

                cout << "Please enter the amount of students whose grades you will to enter as a positive integer: ";
                cin >> max_students;
                if (cin.fail() || max_students <= 0) //Checks if the amount of students to be added is a positive integer. Uses cin.fail to account for non-integer inputs
                {

                    cout << "Please enter a positive integer.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n'); //Discards the invalid user input from the input buffer
                }
                else
                {
                    break;
                }
            }
            for (int student_counter=0;student_counter < max_students;student_counter++)
            {
                Student student = get_student_info(); //Uses custom function to initialize Student object
                student_roster.push_back(student); //Adds the user defined student of this iteration to the student_roster vector

            }
                 
            break;
        case 2:
            cout << "You have selected \"Sentinel-controlled loop mode\"\n\n";
            while(true)
            {
                cout << "If you wish to stop inputting students type in " << STOP_WORD << " with brackets as shown.\n";
                Student student = get_student_info(true);
                if (student.name == STOP_WORD) //Checks if the student's name is the stop word and breaks the while loop if true.
                {
                    break;
                }
                student_roster.push_back(student); //Adds user defined student of this iteration to student_roster vector.
            }
            break;
        case 3: //Quits the program
            cout << "Quitting program...\n";
            return 0;

        default: cout << "You must type either 1, 2, or 3 in the program. Please try again.\n";
    }

    if (student_roster.size() > 0) //Ensures that the student_roster being printed out has elements in it.
    {
        get_student_roster_stats(student_roster); //Uses custom function to display all students and their associated scores, class average, class max score, class min score
    }
    return 0;
}