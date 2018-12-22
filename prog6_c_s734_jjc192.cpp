/*
   File: prog6_c_s734_jjc192.cpp

   Author: Charles Sherrow and John Cruz
   C.S.1428.002
   Lab Section: L02 and L01
   Program: #6
   Due Date: 11/30/18

   This program prints to an output file a title and column headers for a
   payroll report. It then reads an employees work record from an input file.
   The number of overtime hours worked, gross pay, state tax, federal tax,
   and net pay are calculated for each employee. The authors' personal
   identification information followed by the company payroll report is
   printed to the output file. Monetary values are displayed to two decimal
   places.

   An attempt to avoid repetitive code is made.

   An appropriate message is displayed to the console screen if either the
   input or the output file fails to open.

   An appropriate message is written to the console screen informing the
   user of the output file name to which the results have been written.

   The client file (main) calls the following void functions to process
   the data:

	  - printIdInfo prints the authors' personal information - name(s),
        class/section number, lab section number(s), due date - on the first,
        second, third and fourth lines. Two blank lines are left after the
        due date. The lecture section number is displayed in a three-digit
        field with leading zeros shown. The lab section number is displayed
        in a two-digit field with leading zeros shown. The calling routine
        determines the output stream to which the information is directed.
        (Refer to sample output below.)
	  - printReportHeadings prints to the output file the title & column
        headings for the payroll report. One blank line is left after the
        centered report title. Column headers are displayed on two lines.
        (Refer to sample output below.)
      - dataIn reads the employee ID#, hours worked and pay rate from
        an input file storing the values read into parallel arrays. The
        employee ID# is stored in a 1D array of integers. The hours worked
        and the pay rate are stored in the first and second columns of a
        2D array of reals.
	  - overTime calculates the number of overtime hours worked by the
        employee based on a 40 hour work week.
	  - grossPay calculates the employee's gross pay for the week. If the
        employee worked 40 hours or less, gross pay is the hourly pay rate
        multiplied by the number of hours worked; otherwise, the employee
        worked more than 40 hours, and they are paid the regular hourly
        rate for the first 40 hours plus time and a half for any hours
        over 40.
	  - stateTax calculates state taxes owed by the employee, which is
        calculated at a straight 6% of the employee's weekly gross pay.
        (6% is a sample tax rate. The tax rate will vary with each state.)
	  - federalTax calculates federal taxes owed by the employee. If
        weekly gross pay is $400.00 or less, the tax rate is 20%; otherwise,
        the employee's weekly gross pay is more than $400.00, and the tax
        rate is calculated at 20% for the first $400.00 and 31% for any
        amount over $400.00.
        (These rates will vary based on current federal tax regulations.)
	  - netPay calculates the employee's net pay for the week.
        (gross pay minus calculated taxes both state & federal).
	  - printReportData prints to the output file the information for each
        employee in tabular form. Monetary values are displayed to two
        digits of precision. (Refer to sample output below.)
	  - writeFileLocation prints an appropriate message to the console
        screen indicating to the user the name of the output file to which
        the results have been written. The output file name is provided by
        the calling routine.(Refer to sample output below.)


   The following named constants are declared globally:
      - the number of hours in a normal work week (40.00)
      - the state tax rate (0.06)
      - the federal tax rates (0.20; 0.31)
      - the cut off at which federal taxes increase (400.00)
      - parallel array dimensions
      - names used to reference individual columns in the payroll array

   Locally declared named constants include:
      - a string to hold the authors' names
      - a string to hold the authors' lab section number(s)
      - a string to hold the project's due date
      - an integer to hold the lecture section number
      - an integer representing the maximum string length allowed for
        input and output file names which are stored in character arrays
        of that length

==========================================================================

   Layout and content of the output are shown in the samples below.

   Input (file - prog6_00?inp.txt)
          one record per employee / each record containing three numbers

          ID#(integer)  hours worked (real)  pay rate (real)
          ...

   Constants: globally declared:
                 integer: ROWS
                          COLS
	                      (2D array column indices)
                              HRS_WRKD = 0,
                              PAYRATE = 1,
                              OVRTIME = 2,
                              GROSS = 3,
                              ST_TAX = 4,
                              FED_TAX = 5,
                              NETPAY = 6;

                 double: CUT_OFF (hours in a work week)
                         STATE_TX_RATE
                         TAX_CUT_OFF (division @ which net pay is taxed higher)
	  	                 LOW_TAX_RATE
                         HI_TAX_RATE

   Constants: locally declared:
                 string:  AUTHORS
                          LAB_SECTION
                          DUE_DATE

                 integer: LECTURE_SECTION
                          MAX_LENGTH_FN = ?  // filename's maximum length

   Output (console):
     Sample Console Output

     Authors' Names
     C.S.1428.?        // '?' represents author's 3-digit lecture section #
     Lab Section: L?   // '?' represents author's 2-digit lab section #
     --/--/--          // dashes represent due date, month/day/year
          <blank line>
          <blank line>
     Program results have been written to prog6_00?out.txt.

   Output (file: prog6_00?out.txt):
     Sample File Output

     Authors' Names
     C.S.1428.?        // '?' represents author's 3-digit lecture section #
     Lab Section: L?   // '?' represents author's 2-digit lab section #
     --/--/--          // dashes represent due date, month/day/year
          <blank line>
          <blank line>
                          Monthly Payroll Report
          <blank line>
      ID#     Hours    Hourly    Overtime   Gross    State   Federal    Net
             Worked     Rate       Hours     Pay      Tax      Tax      Pay
     1000     51.00      6.55      11.00   370.07    22.20    74.02   273.86
     ...
     1002     26.00     15.00       0.00   390.00    23.40    78.00   288.60
     ...

     =======================================================================

     <Output will vary based on actual input values.>
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>     // 4 Code::Blocks

using namespace std;

const int ROWS = 10,    // number of employees
          COLS = 7;

          // 2D array (payroll) column indices
const int HRS_WRKD = 0,
          PAYRATE = 1,
          OVRTIME = 2,
          GROSS = 3,
          ST_TAX = 4,
          FED_TAX = 5,
          NETPAY = 6;

const double CUT_OFF = 40.00,      // work week
             STATE_TX_RATE = 0.06,
             TAX_CUT_OFF = 400.00, // earnings after which taxed at a higher rate
             LOW_TAX_RATE = 0.20,
             HI_TAX_RATE = 0.31;

void printIdInfo ( ostream &out, const string AUTHORS,
                   const int LECTURE_SECTION, const string LAB_SECTION,
                   const string DUE_DATE );
void printReportHeadings ( ofstream &fout );
void dataIn ( ifstream &fin, int employees[], double payroll[][COLS] );
void overTime ( double payroll[][COLS] );
void grossPay ( double payroll[][COLS] );
void stateTax ( double payroll[][COLS] );
void federalTax ( double payroll[][COLS] );
void netPay ( double payroll[][COLS] );
void printReportData ( ofstream &fout, const int employee[],
                       const double payroll[][COLS] );
void writeFileLocation ( const char output_filename[] );

int main ( )
{
   const string AUTHORS = "Charles Sherrow and John Cruz",
                LAB_SECTION = "L02 and L01",
                DUE_DATE = "11/30/18";

   const int LECTURE_SECTION = 2,
             MAX_LENGTH_FN = 20;

   char input_filename[MAX_LENGTH_FN + 1] = "prog6_002inp.txt",
        output_filename[MAX_LENGTH_FN + 1] = "prog6_002out.txt";

   int employee[ROWS];          // employee ID#s

   double payroll[ROWS][COLS];  // payroll data

   ifstream fin;
   fin.open( input_filename );

   if ( !fin )
   {
      cout << endl << endl
           << "***Program Terminated.***" << endl << endl
           << "Input file failed to open." << endl;

      system("PAUSE>NUL");

      return 2;
   }

   ofstream fout;
   fout.open( output_filename );

   if ( !fout )
   {
      cout << endl << endl
           << "***Program Terminated.***" << endl << endl
           << "Output file failed to open." << endl;

      fin.close( );

      system("PAUSE>NUL");

      return 2;
   }

   printIdInfo( fout, AUTHORS, LECTURE_SECTION, LAB_SECTION, DUE_DATE );
   printReportHeadings ( fout );
   dataIn ( fin, employee, payroll );
   overTime ( payroll );
   grossPay ( payroll );
   stateTax ( payroll );
   federalTax ( payroll );
   netPay ( payroll );
   printReportData ( fout, employee, payroll );
   printIdInfo( cout, AUTHORS, LECTURE_SECTION, LAB_SECTION, DUE_DATE );
   writeFileLocation ( output_filename );


   fin.close( );
   fout.close( );

   system("PAUSE>NUL");

   return 0;
}

/*
      Function: printIdInfo

      The function, printIdInfo, writes the team members' identifying
      information to the output file on four separate lines
           - authors names
           - class & three digit lecture section number
           - lab section number
           - program due date.
      Two blank lines are left after the due date.

      Sample Output:
        Authors' Names
        C.S.1428.?             // '?' represents authors' lecture section #
        Lab Section: L? & L?   // '?' represents authors' lab section #s
        --/--/--               // dashes represent due date, month/day/year
              <blank line>
              <blank line>

      Receives: output file variable,
                AUTHORS (string constant), LECTURE_SECTION (integer constant),
                LAB_SECTION (string constant), DUE_DATE (string constant);
                in this order
      Constants: AUTHORS, LECTURE_SECTION, LAB_SECTION, DUE_DATE
      Returns: nothing; prints user's team identifying info to a file/console
*/

void printIdInfo ( ostream &out, const string AUTHORS,
                   const int LECTURE_SECTION, const string LAB_SECTION,
                   const string DUE_DATE )
{
    out << AUTHORS << endl
        << "C.S.1428." << setw(3) << setfill('0') << LECTURE_SECTION << endl
        << "Lab Section: " << LAB_SECTION << endl
        << DUE_DATE << endl << endl << endl;
}

/*
      Function: printReportHeadings

      The function, printReportHeadings, writes the title & column headins for
      the payroll report. One blank line is left after the centered report
      title.

      Sample Output:
                          Monthly Payroll Report
      <blank line>
      ID#     Hours    Hourly    Overtime   Gross    State   Federal    Net
             Worked     Rate       Hours     Pay      Tax      Tax      Pay

      Receives: output file variable
      Constants: none
      Returns: nothing; prints title and column heading to a file
*/

void printReportHeadings ( ofstream &fout )
{
   fout << "                     Monthly Payroll Report" << endl << endl
        << " ID#     Hours    Hourly   Overtime    Gross     State"
        << "    Federal     Net" << endl
        << "        Worked     Rate      Hours      Pay       Tax"
        << "       Tax       Pay" << endl;
}

/*
      Function: dataIn

      The function, dataIn, reads the employee ID number, hours worked and pay
      rate from an input file and stores the values into parallel arrays.

      Receives: input file variable, 1D array of integers (employee ID#s),
                2D array of reals (payroll information) / COLS
      Constants: globally declared integers:
                    ROWS - parallel arrays row dimension
                    COLS - 2D array column dimension
                 column designations in 2D array
                    HRS_WRKD, PAYRATE
      Returns: nothing; takes input values and stores in arrays
*/

void dataIn ( ifstream &fin, int employee[], double payroll[][COLS] )
{
   for ( int row = 0; row < ROWS; row++ )
      fin >> employee[row] >> payroll[row][HRS_WRKD] >> payroll[row][PAYRATE];
}

/*
      Function: overTime

      The function, overTime, calculates the number of overtime hours worked by
      an employee based on a 40-hour work week.

      Note: The sample below assumes a standard work week of 40 hours.
            Actual values may differ.

      If employee's hours are > 40.0
         hours over 40.0 will be stored as overtime hours
      otherwise // employee's hours are < 40.0
          employee has no overtime hours

      Receives:  2D array of reals (payroll information) / COLS
      Constants: globally declared integers:
                    ROWS - parallel arrays row dimension
                    COLS - 2D array column dimension
                 column designations in 2D array
                    HRS_WRKD, OVRTIME
                 globally declared reals:
                    CUT_OFF - 40 Hour work week
      Returns: nothing, calculates number of overtime hours
*/

void overTime ( double payroll[][COLS] )
{
   for ( int row = 0; row < ROWS; row++ )
   {
      if ( payroll[row][HRS_WRKD] > CUT_OFF )
         payroll[row][OVRTIME] = payroll[row][HRS_WRKD] - 40;
      else
         payroll[row][OVRTIME] = 0;
   }
}

/*
      Function: grossPay

      The function, grossPay, calculates the gross pay for the week. If the
      employee worked over 40 hours, then the hours over 40 will be multiplied
      by pay and a half.

      Note: The sample below assumes a standard work week of 40 hours. Any time
            over 40 will be paid time and a half. Actual values may differ.

      If employees hours is < 40.0
         gross pay is hours worked  times pay rate
      otherwise // employee's weekly gross pay is > 40.0
          first 40.0 hours worked is payed at hourly rate
          and any hours greater than 40 is payed at time and a half

      Receives:  2D array of reals (payroll information) / COLS
      Constants: globally declared integers:
                    ROWS - parallel arrays row dimension
                    COLS - 2D array column dimension
                 column designations in 2D array
                    HRS_WRKD, GROSS, PAYRATE, OVRTIME
                 globally declared reals:
                    CUT_OFF - 40 Hour work week
      Returns: nothing, calculates gross pay
*/

void grossPay ( double payroll[][COLS] )
{
   for ( int row = 0; row < ROWS; row++ )
   {
      if ( payroll[row][HRS_WRKD] < CUT_OFF )
         payroll[row][GROSS] = payroll[row][HRS_WRKD] * payroll[row][PAYRATE];
      else
         payroll[row][GROSS] = ( CUT_OFF * payroll[row][PAYRATE] ) +
                               ( payroll[row][OVRTIME]  *
                               ( payroll[row][PAYRATE] * 1.5 ));
   }
}

/*
      Function: stateTax

      The function, stateTax, calculates the state taxes owed by the employee
      based on their gross pay.

      Note: The sample below assumes a state tax rate of 6%. Actual values may
            differ.

      Weekly gross pay is taxed at 6%.

      Receives:  2D array of reals (payroll information) / COLS
      Constants: globally declared integers:
                    ROWS - parallel arrays row dimension
                    COLS - 2D array column dimension
                 column designations in 2D array
                    ST_TAX, GROSS
                 globally declared reals:
                    STATE_TX_RATE
      Returns: nothing, calculates state taxes
*/

void stateTax ( double payroll[][COLS] )
{
   for ( int row = 0; row < ROWS; row++ )
   {
      payroll[row][ST_TAX] = payroll[row][GROSS] * STATE_TX_RATE;
   }
}

/*
      Function: federalTax

      The function, federalTax, calculates federal taxes owed by the employee.

      Note: The sample below assumes a tax cut-off of 400.00 and a tax rate
            for 20% for low wage earners and a tax rate of 31% for high wage
            earners. Actual values may differ.

      If weekly gross pay is $400.00 or less,
          tax rate is 20%.
      otherwise // employee's weekly gross pay is > $400.00
          tax rate is calculated at 20% for the first $400.00
          and 31% for any amount over $400.00.

      Receives: 2D array of reals (payroll information) / COLS
      Constants: globally declared integers:
                    ROWS - parallel arrays row dimension
                    COLS - 2D array column dimension
                 column designations in 2D array
                    GROSS, FED_TAX
                 globally declared reals:
                    TAX_CUT_OFF - income level at which taxes are increased
                    LOW_TAX_RATE
                    HI_TAX_RATE
      Returns: fills the federal tax column with calculated data
*/

void federalTax ( double payroll[][COLS] )
{

   for ( int row = 0; row < ROWS; row++ )
   {
      if ( payroll[row][GROSS] <= TAX_CUT_OFF )
         payroll[row][FED_TAX] = payroll[row][GROSS] * LOW_TAX_RATE;
      else
         payroll[row][FED_TAX] = ( TAX_CUT_OFF * LOW_TAX_RATE ) +
                                 (( payroll[row][GROSS] - TAX_CUT_OFF ) *
                                  HI_TAX_RATE );
   }
}

/*
      Function: netPay

      The function, netPay, calculates the net pay of the employee by
      subtracting the sum of federal and state taxes from their gross pay.

      Note: The sample below assumes netpay is gross pay minus state and federal
            taxes. Actual values may differ.

      Net pay is equal to gross minus state and federal taxes.

      Receives:  2D array of reals (payroll information) / COLS
      Constants: globally declared integers:
                    ROWS - parallel arrays row dimension
                    COLS - 2D array column dimension
                 column designations in 2D array
                    NETPAY, GROSS, ST_TAX, FED_TAX
      Returns: nothing, calculates netpay
*/

void netPay ( double payroll[][COLS] )
{
   for ( int row = 0; row < ROWS; row++ )
   {
      payroll[row][NETPAY] = payroll[row][GROSS] - ( payroll[row][ST_TAX]
                                                 + payroll[row][FED_TAX] );
   }
}

/*
      Function: printReportData

      The void function printReportData prints to an output file the payroll
      information for each employee in tabular form under the appropriate column
      headers. The employee records are single spaced. Monetary values are
      displayed with two digits of precision.

      Note: The report title and column headers are printed by a previously
            called function.

      Sample Output:
                          Monthly Payroll Report
      <blank line>
      ID#     Hours    Hourly    Overtime   Gross    State   Federal    Net
             Worked     Rate       Hours     Pay      Tax      Tax      Pay
      1000     51.00      6.55      11.00   370.07    22.20    74.02   273.86
      1001     26.00     15.00       0.00   390.00    23.40    78.00   288.60
      ...

      Receives: output file variable, protected 1D array of integer ID#s,
                protected 2D array of reals (payroll information) / COLS;
               (in this order)
      Constants: globally declared integers:
                    ROWS - parallel arrays row dimension
                    COLS - 2D array column dimension
      Returns: nothing; prints out report data under appropriate report headings
               previously printed
*/

void printReportData ( ofstream &fout, const int employee[],
                       const double payroll[][COLS] )
{
   fout << fixed << setprecision(2) << setfill(' ');

   for ( int row = 0; row < ROWS; row++ )
   {
      fout << employee[row];

      for ( int col = 0; col < COLS; col++ )
         fout << setw(10) << payroll[row][col];

      fout << endl;
   }
}

/*
      Function: writeFileLocation

      The function, writeFileLocation, writes a message to the screen
      indicating to the user the name of the output file to which the
      results have been written.

      Sample Display:
         Program results have been written to prog6_00?out.txt.
         (The actual file name may differ.)

      Receives: output_filename (char array)
      Constants: none
      Returns: nothing, writes a message to the screen
*/

void writeFileLocation ( const char output_filename[] )
{
   cout << "Program results have been written to " << output_filename << "."
        << endl;
}
