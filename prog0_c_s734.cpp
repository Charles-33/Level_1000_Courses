/*
   File: prog0_c_s734.cpp

   Author: Charles Sherrow
   C.S.1428.002
   Lab Section: L02
   Program: #0
   Due Date: 09/05/18

   This program
       - writes the student's first and last names on the 1st line of output
         e.g. John Smith
       - writes 'C.S.1428.#' (without quotation marks) on the 2nd line of
         output with the student's lecture section number in place of the
         # sign
       - writes 'Lab Section: L?' (without quotation marks) on the 3rd line of
         output with the student's lab section number in place of the question
         mark
       - writes this program's due date on the fourth line of output
       - leaves line five blank
       - writes 'Major: <student's major>'(without quotation marks)
         on the 6th line of output with the student's major in place of
         <student's major>
       - writes 'Minor: <student's minor or specialization>' (without quotation
         marks)on the 7th line of output with the student's minor or
         specialization in place of <student's minor or specialization>
         Note: The keyword 'Minor:' might be replaced with the keyword
         'Specialization:' or 'Concentration:' depending on the student.
       - leaves line eight blank
       - writes 'Favorite Food: <student's favorite food>'
         (without quotation marks) on the 9th line of output with the student's
         favorite food in place of <student's favorite food>

   Input: none
   Constants: none
   Output (screen): Sample Output:

                 Betty Boop
                 C.S.1428.?        // '?' represents student's lecture section #
                 Lab Section: L?   // '?' represents student's lab section #
                 --/--/--          // dashes represent due date, month/day/year
                    <blank line>
                 Major: ?
                 Minor: ?
                    <blank line>
                 Favorite Food: ?
*/

#include <iostream>

using namespace std;

int main ( )
{
   cout << "Charles Sherrow" << endl
        << "C.S.1428.002" << endl
        << "Lab Section: L02" << endl
        << "09/05/18" << endl << endl;

   cout << "Major: Computer Science" << endl
        << "Minor: Mathematics" << endl << endl;

   cout << "Favorite Food: Pizza" << endl;

   return 0;
}
