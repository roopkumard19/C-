#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const string INPUT_FILE_NAME = "students.txt";

typedef string   *NamePtr;   // -> a student name
typedef string   *NameArray; // -> dynamic array of student names
typedef int      *ScorePtr;  // -> a score
typedef int      *ScoreRow;  // -> dynamic array (row) of student scores
typedef ScoreRow *RowPtr;    // -> a row of student scores
typedef ScoreRow *RowArray;  // -> dynamic array of score rows

void input_course_data(ifstream& input, string& course,
                       NameArray& names, RowArray& rows);

void print_student_scores(string course, NameArray names, RowArray rows);

void delete_student_scores(NameArray names, RowArray rows);

RowArray create_score_rows_array(ifstream& input, int student_count,
                                 NameArray names);

ScoreRow create_score_row(ifstream& input, int score_count);

/**
 * Main.
 */
int main()
{
    ifstream input;
    input.open(INPUT_FILE_NAME);
    if (input.fail())
    {
        cout << "Failed to open " << INPUT_FILE_NAME << endl;
        return -1;
    }

    // Allocate here in the main.
    string course;
    NameArray names = nullptr;  // -> array of student names
    RowArray  rows  = nullptr;  // -> array of rows of student scores

    input_course_data(input, course, names, rows);  // pass by reference
    print_student_scores(course, names, rows);      // pass by value
    delete_student_scores(names, rows);
}

/**
 * Input the course name, student names, and student scores.
 * @param input the input stream.
 * @param course the course name to set.
 * @param names the dynamic array of names to set.
 * @param rows the dynamic 2-d array of student scores to set, one row per student.
 */
void input_course_data(ifstream& input, string& course,
                       NameArray& names, RowArray& rows)
{
    int student_count;
    string first_name, last_name;

    // Read the course name and student count.
    // Create the dynamic array of student names.
    input >> course >> student_count;
    names = new string[student_count];

    // Create the dynamic array of rows of student scores.
    rows = create_score_rows_array(input, student_count, names);
}

/**
 * Create the dynamic array of rows of student scores.
 * @param input the input stream.
 * @param student_count the count of students.
 * @param name_ptr pointer to the next element of the student names array.
 */
RowArray create_score_rows_array(ifstream& input, int student_count,
                                 NameArray names)
{
    int score_count;
    string first_name, last_name;
    NamePtr name_ptr = names;  // -> first element of the names array

    // Make the dynamic array one larger for the nullptr sentinel at the end.
    RowArray rows = new ScoreRow[student_count + 1];
    RowPtr row_ptr = rows;  // -> first element of the rows array

    // Loop once per student.
    while (student_count > 0)
    {
        // Read a student name and the number of assignments.
        // Use name_ptr to enter the name at the end of the name array.
        input >> first_name >> last_name >> score_count;
        *name_ptr = first_name + " " + last_name;

        // Create a dynamic integer array as a row of student scores.
        // Use row_ptr to enter it at the end of the array of score rows.
        *row_ptr = create_score_row(input, score_count);

        name_ptr++;       // -> next element of the name array
        row_ptr++;        // -> next element of the row array
        student_count--;
    }

    *row_ptr = nullptr;  // sentinel to mark the end of all the score rows
    return rows;         // -> to the head of the array of score rows
}

/**
 * Create a dynamic integer array as a row of student scores.
 * @param input the input stream.
 * @param score_count the count of scores for this student.
 * @return a pointer to the row of student scores.
 */
ScoreRow create_score_row(ifstream& input, int score_count)
{
    // Make the dynamic row one larger for the -1 sentinel at the end.
    ScoreRow scores = new int[score_count + 1];
    ScorePtr score_ptr = scores;  // -> first score of the row

    // Loop once per assignment score of the student.
    while (score_count > 0)
    {
        input >> *score_ptr;  // read the next score into the score row
        score_ptr++;          // -> next element of the score row
        score_count--;
    }

    *score_ptr = -1;  // sentinel to mark the end of this score row
    return scores;    // -> to the head of the score row
}

/**
 * Print the scores for each student in the course.
 * @param course the name of the course.
 * @param names the array of student names.
 * @param rows the 2-d array of student scores, one row per student.
 */
void print_student_scores(string course, NameArray names, RowArray rows)
{
    NamePtr name_ptr = names;  // -> first name of student names
    RowPtr row_ptr = rows;     // -> first row of student scores

    cout << "STUDENT SCORES for " << course << endl;

    // Loop once per row of student scores.
    while (*row_ptr != nullptr)
    {
        cout << endl;
        cout << *name_ptr << endl;

        int *score_ptr = *row_ptr;  // -> first score of the row

        // No scores?
        if (*score_ptr < 0)
        {
            cout << "   (none)";
        }

        // Else loop to print each score in the row.
        // Stop at the -1 sentinel.
        else while (*score_ptr >= 0)
        {
            cout << setw(5) << *score_ptr;
            score_ptr++;  // -> next score of the row
        }
        cout << endl;

        name_ptr++;  // -> next name in the name array
        row_ptr++;   // -> next row in the row array
    }
}

/**
 * Deallocate the dynamic arrays.
 * @param names the array of student names.
 * @param rows the 2-d array of student scores, one row per student.
 */
void delete_student_scores(NameArray names, RowArray rows)
{
    RowPtr row_ptr = rows;  // -> first row of student scores

    // Loop once per row of student scores.
    // Stop at the nullptr sentinel.
    while (*row_ptr != nullptr)
    {
        delete [] *row_ptr;  // delete the row of scores
        row_ptr++;           // -> next row in the row array
    }

    delete [] rows;   // delete the matrix
    delete [] names;  // delete the array of names
}
