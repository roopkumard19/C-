#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

/**
 * The WidgetReport class.
 * Print a Widget Report from an input file of widgets data.
 */
class WidgetReport
{
public:
    WidgetReport(ifstream& in);  // constructor
    void print();

private:
    ifstream& input;  // reference to the input stream
    int state_code, plant_code, dept_code;  // current codes
    int prev_state, prev_plant, prev_dept;  // previous codes
    int grand_total, state_total, plant_total, dept_total;  // totals

    void print_column_headers();
    void print_detail_lines();
    void print_dept_total();
    void print_plant_total();
    void print_state_total();
    void print_grand_total();
};

const string INPUT_FILE_NAME = "widgets.txt";

/**
 * Main
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

    // Generate and print the Widget Report.
    WidgetReport report(input);
    report.print();

    input.close();
    return 0;
}

/**
 * Constructor
 * @param in the input file stream
 */
WidgetReport::WidgetReport(ifstream& in)
    : input(in), state_code(0), plant_code(0), dept_code(0),
      prev_state(0), prev_plant(0), prev_dept(0),
      grand_total(0), state_total(0), plant_total(0), dept_total(0)
{
}

/**
 * Print the Widgets report.
 */
void WidgetReport::print()
{
    print_column_headers();
    print_detail_lines();
}

/**
 * Print the column headers.
 */
void WidgetReport::print_column_headers()
{
    string hdr_state, hdr_plant, hdr_dept, hdr_emp_id, hdr_count, hdr_name;

    // Read the header line of the input.
    input >> hdr_state >> hdr_plant >> hdr_dept
          >> hdr_emp_id >> hdr_name >> hdr_count;

    // Print the column headers.
    cout.setf(ios::left);
    cout << setw(6) << hdr_state
         << setw(6) << hdr_plant
         << setw(5) << hdr_dept
         << setw(6) << hdr_emp_id
         << setw(6) << hdr_count
         << hdr_name
         << endl << endl;
}

/**
 * Print the detail lines.
 */
void WidgetReport::print_detail_lines()
{
    bool first_detail_line = true;
    bool print_blank_line = false;

    // Loop to read the detail lines from the input.
    // The state code is the first item of each input line.
    while (input >> state_code)
    {
        int id, count;
        string name, first_name, last_name;

        // Read the rest of the input line.
        input >> plant_code >> dept_code >> id
              >> first_name >> last_name >> count;
        name = first_name + " " + last_name;

        // After the first detail line, check if any codes changed.
        // If a code changed, print the corresponding total.
        if (!first_detail_line)
        {
            // State code changed?
            if (state_code != prev_state)
            {
                cout << endl;
                print_state_total();
                print_blank_line = true;
            }

            // Plant code changed?
            else if (plant_code != prev_plant) {

                cout << endl;
                print_plant_total();
                print_blank_line = true;
            }

            // Department code changed?
            else if (dept_code != prev_dept)
            {
                cout << endl;
                print_dept_total();
                print_blank_line = true;
            }
        }

        // Print a blank line after printing totals;
        if (print_blank_line) {
            cout << endl;
            print_blank_line = false;
        }

        // Remember the codes from the line just read.
        prev_dept  = dept_code;
        prev_plant = plant_code;
        prev_state = state_code;

        // Update the totals.
        dept_total  += count;
        plant_total += count;
        state_total += count;
        grand_total += count;

        // Print a detail line.
        cout.setf(ios::right);
        cout << setw(5) << state_code
             << setw(6) << plant_code
             << setw(5) << dept_code
             << setw(6) << id
             << setw(6) << count;

        cout.setf(ios::left);
        cout << " " << name << endl;

        first_detail_line = false;
    }

    // All detail records read. Print the grand total.
    cout << endl;
    print_grand_total();
}

/**
 * Print a department total.
 */
void WidgetReport::print_dept_total()
{
    cout.setf(ios::right);
    cout << setw(28) << dept_total << " TOTAL FOR DEPT"
         << setw(4)  << prev_dept  << " *" << endl;
    dept_total = 0;
}

/**
 * Print a plant total.
 * This implies first printing a department total.
 */
void WidgetReport::print_plant_total()
{
    print_dept_total();
    cout << setw(28) << plant_total << " TOTAL FOR PLANT"
         << setw(3)  << prev_plant  << " **" << endl;
    plant_total = 0;
}

/**
 * Print a state total.
 * This implies first printing a plant total.
 */
void WidgetReport::print_state_total()
{
    print_plant_total();
    cout << setw(28) << state_total << " TOTAL FOR STATE"
         << setw(3)  << prev_state  << " ***" << endl;
    state_total = 0;
}

/**
 * Print the grand total.
 * This implies first printing a state total.
 */
void WidgetReport::print_grand_total()
{
    print_state_total();
    cout << endl;
    cout << setw(28) << grand_total << " GRAND TOTAL        ****" << endl;
}
