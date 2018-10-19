/*
   File: prog2_c_s734_jjc192.cpp

   Author: Charles Sherrow and John Cruz
   C.S.1428.002
   Lab Section: L02 and L01
   Program: #2
   Due Date: 10/03/18

   This program prompts the user to enter the amount of a purchase (in cents).
   It then prompts the user to enter the amount received in payment (in cents).
   It calculates the amount of change due, printing the results to an output
   file. The author's identifying information is provided followed by the
   number of each coin to be given in change: the number of dollars, half
   dollars, quarters, dimes, nickels and pennies are listed in tabular form.
   Monetary amounts are displayed to two decimal places.

   An appropriate message is displayed to the console screen if the output
   file fails to open.

   An appropriate message is written to the console screen informing the
   user of the output file name to which the results have been written.
   The layout and content of the file output are shown in the sample below.

   Input (keyboard):
          purchase amount, integer (in cents)
          payment amount, integer (in cents)

   Constants: none

   Output (screen):

           Author's Name
           C.S.1428.?         // '?' represents author's lecture section #
           Lab Section: L?    // '?' represents student's lab section #
           --/--/--           // dashes represent due date, month/day/year
                <blank line>
                <blank line>
           <Appropriate message indicating the name of the output file.>

   Output (file - prog2_00?out.txt): // '?' represents author's lect sec #

           Author's Name
           C.S.1428.?         // '?' represents author's lecture section #
           Lab Section: L?    // '?' represents student's lab section #
           --/--/--           // dashes represent due date, month/day/year
                <blank line>
           Received ? for a purchase of ?
                <blank line>
              Change in coins:
           Coin           Number
           ---------------------
           Dollars          ?
           Half Dollars     ?
           Quarters         ?
           Dimes            ?
           Nickels          ?
           Pennies          ?

   ================================================

   <Output will vary based on actual input values.>
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>

using namespace std;

int main ( )
{
    int purchase_amount,
        payment_amount,
        change = 0,
        dollars = 0,
        half_dollars = 0,
        quarters = 0,
        dimes = 0,
        nickels = 0;

    ofstream fout;
    fout.open("prog2_002out.txt");

    if ( !fout )
    {
        cout << endl << endl
             << " ***Program Terminated.*** " << endl << endl
             << "Output file failed to open." << endl;

             system("PAUSE>NUL");

             return 2;
    }

    cout << "Enter the amount of the purchase ( in cents ): ";
    cin >> purchase_amount;

    cout << "Enter the amount received in payment ( in cents ): ";
    cin >> payment_amount;
    cout << endl << endl;

    change = payment_amount - purchase_amount;

    if ( change >= 100 )
    {
        dollars = change / 100;
        change = change % 100;
    }
    if ( change >= 50 )
    {
        half_dollars = change / 50;
        change = change % 50;
    }
    if ( change >= 25 )
    {
        quarters = change / 25;
        change = change % 25;
    }
    if ( change >= 10 )
    {
        dimes = change / 10;
        change = change % 10;
    }
    if ( change >= 5 )
    {
        nickels = change / 5;
        change = change % 5;
    }

    fout << "Charles Sherrow and John Cruz" << endl
         << "C.S.1428.002" << endl
         << "Lab Section: L02 and L01" << endl
         << "10/03/18" << endl << endl;

    fout << fixed << setprecision(2)
         << "Received " << payment_amount / 100.0 << " for a purchase of "
         << purchase_amount / 100.0 << "." << endl << endl

         << "   Change in coins:" << endl
         << "Coin           Number" << endl
         << "---------------------" << endl
         << "Dollars      " << setw(6) << dollars << endl
         << "Half_Dollars " << setw(6) << half_dollars << endl
         << "Quarters     " << setw(6) << quarters << endl
         << "Dimes        " << setw(6) << dimes << endl
         << "Nickels      " << setw(6) << nickels << endl
         << "Pennies      " << setw(6) << change << endl;

    cout << "Charles Sherrow and John Cruz" << endl
         << "C.S.1428.002" << endl
         << "Lab Section: L02 and L01" << endl
         << "10/03/18" << endl << endl << endl;

    cout << "Program results have been written to prog2_002out.txt." << endl;

    fout.close( );

    system("PAUSE>NUL");

    return 0;
}
