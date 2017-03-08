#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string INPUT_FILE_NAME = "GettysburgAddress.txt";

int main()
{
    string line;
    int line_count = 0;
    int character_count = 0;
    int word_count = 0;
    int lower_count = 0;
    int upper_count = 0;
    int space_count = 0;
    int punctuation_count = 0;
    bool saw_letter = false;

    ifstream input;
    input.open(INPUT_FILE_NAME);
    if (input.fail())
    {
        cout << "Failed to open " << INPUT_FILE_NAME << endl;
        return -1;
    }

    cout << "Statistics for file " << INPUT_FILE_NAME << ":" << endl;
    cout << endl;

    // Loop once per line of the input file.
    while (getline(input, line))
    {
        ++line_count;

        // Loop once per character of the line.
        // Count a word if a letter is followed
        // a space, punctuation, or end of line.
        for (int i = 0; i < line.length(); i++)
        {
            char ch = line[i];
            ++character_count;

            if ((ch >= 'a') && (ch <= 'z'))
            {
                ++lower_count;
                saw_letter = true;
            }
            else if ((ch >= 'A') && (ch <= 'Z'))
            {
                ++upper_count;
                saw_letter = true;
            }
            else if (ch == ' ')
            {
                ++space_count;
                if (saw_letter)  // letter followed by space?
                {
                    ++word_count;
                    saw_letter = false;
                }
            }
            else
            {
                ++punctuation_count;
                if (saw_letter)  // letter followed by punctuation?
                {
                    ++word_count;
                    saw_letter = false;
                }
            }
        }

        if (saw_letter)  // letter followed by end of line?
        {
            ++word_count;
            saw_letter = false;
        }
    }

    input.close();

    cout << "Lines: " << line_count << endl;
    cout << "Characters: " << character_count << endl;
    cout << "Words: " << word_count << endl;
    cout << "Lower-case letters: " << lower_count << endl;
    cout << "Upper-case letters: " << upper_count << endl;
    cout << "Spaces: " << space_count << endl;
    cout << "Punctuation marks: " << punctuation_count << endl;

    return 0;
}
