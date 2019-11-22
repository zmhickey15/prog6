/*
   File: prog6_mkh115_zmh11.cpp

   Author: Mavrick Henderson, Zachary Hickey
   C.S.1428.002
   Lab Section: L17, L17
   Program: #6
   Due Date: 12/02/19

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

Input (file - prog6_?inp.txt) // '?' represents three-digit lecture section #
       one record per employee / each record containing three numbers

       ID#(integer)  hours worked (real)  pay rate (real)
       ...

Constants: globally declared:
              integer: ROWS
                       COLS
                       {2D array column indices)
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
    C.S.1428.?        // '?' represents three-digit lecture section number
    Lab Section: L?   // '?' represents two-digit lab section numbet
    --/--/--          // dashes represent due date, month/day/year
         <blank line>
         <blank line>
    Program results have been written to prog6_?out.txt.

Output (file: prog6_?out.txt): // '?' represents three-digit lecture section #
    Sample File Output

    Authors' Names
    C.S.1428.?        // '?' represents three-digit lecture section number
    Lab Section: L?   // '?' represents two-digit lab section numbet
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


void printIdInfo( ostream &, const string, const int, const string,
                  const string );

void printReportHeadings ( ostream & );

void dataIn ( ifstream &, int [], double [][COLS] );

void overTime ( double [][COLS] );

void grossPay ( double [][COLS] );

void stateTax ( double [][COLS] );

void federalTax ( double [][COLS] );

void netPay ( double [] [COLS] ) ;

void printReportData ( ostream &, const int[], const double[][COLS] );

void writeFileLocation( const char [] );

int main ( )
{
   const string AUTHORS = "Mavrick Henderson, Zachary Hickey",
                LAB_SECTION = "L17 & L17",
                DUE_DATE = "12/02/19";

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

        return 1;
    }

    ofstream fout;
    fout.open ( output_filename );

     if ( !fout )
   {
        cout << endl << endl
             << " ***Program Terminated.*** " << endl << endl
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
    Author(s): Mavrick Henderson, Zachary Hickey
    C.S.1428.002
    Lab Section: L17, L17
    Program 6 Function printIdInfo
    12/02/19

    The void function, printIdInfo, writes the team members' identifying
    information to the output file on four separate lines
        - AUTHORS
        - C.S.1428. Lecture section
        - Lab Section: LAB_SECTION
        - DUE_DATE
    one blank line is left after DUE_DATE.

        Sample Output:
        Authors' Names
        C.S.1428.?             // '?' represents three-digit lecture section #
        Lab Section: L? & L?   // '?' represents two-digit lab section #s
          --/--/--               // dashes represent due date, month/day/year
              <blank line>

    Recives: output file variable
               AUTHORS (string constant)
               LECTURE_SECTION (int constant)
               LAB_SECTION (string constant)
               DUE_DATE (string constant)
    Constants: AUTHORS, LECTURE_SECTION, LAB_SECTION, DUE_DATE
    Returns: nothing; prints user's team identifying info to a file
*/

void printIdInfo ( ostream & out, const string AUTHORS,
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
    Author(s): Mavrick Henderson, Zachary Hickey
    C.S.1428.002
    Lab Section: L17, L17
    Program 6 Function printReportHeadings
    12/02/19

    This void function printReportHeadings print to the output file the title
    & column headings for the payroll report. Leave one blank line after the
    centered report title. Display column headers on two lines

    Sample output:
                        Monthly Payroll Report
    ID#     Hours    Hourly   Overtime    Gross     State    Federal     Net
           Worked     Rate      Hours      Pay       Tax       Tax       Pay

    Recives: output file variable
    Constants: none
    Returns: nothing writes in output file
*/

void printReportHeadings ( ostream & out )
{
    out << "                     Monthly Payroll Report" << endl << endl
        << " ID#     Hours    Hourly   Overtime    Gross     State    Federal"
        <<"     Net" << endl
        <<"        Worked     Rate      Hours      Pay       Tax       Tax"
        <<"       Pay" << endl;
}

/*
    Function: dataIn
    Author(s): Mavrick Henderson, Zachary Hickey
    C.S.1428.002
    Lab Section: L17, L17
    Program 6 Function dataIn
    12/02/19

    This read the employee ID#, hours worked and pay rate from an input file
    (prog6_002inp.txt) storing the values read into parallel arrays. Store the
    employee ID# in a 1D array of integers. The hours worked and the pay rate
    should be stored in the first and second columns of a 2D array ofreals. A


    Reccives: input file variable, 1D array of employees, 2D array of payroll
    info
    Constants: none
    Returns: nothing reads information from file
*/

void dataIn ( ifstream & fin, int employee[], double payroll[][COLS])
{
    for ( int row = 0; row < ROWS; row++ )
        fin >> employee[row] >> payroll[row][HRS_WRKD] >> payroll[row][PAYRATE];
}

/*
    Function: overTime
    Author(s): Mavrick Henderson, Zachary Hickey
    C.S.1428.002
    Lab Section: L17, L17
    Program 6 Function overTime
    12/02/19

    This void function calculates the number of overtime hours worked by the
    employee based on a 40-hour work week and stores the number of hours of over
    time in a 2D array (column OVERTIME)

    recives: 2D array payroll
    Constants: globally declared integers:
                 ROWS - parallel arrays row dimension
              column designations in 2D array
                 HRS_WRKD
                 OVRTIME
              globally declared reals:
                 CUT_OFF
    returns: nothing
*/

void overTime ( double payroll[][COLS] )
{
    for ( int row = 0; row < ROWS; row++ )
    {
        if ( payroll[row][HRS_WRKD] > CUT_OFF )
        payroll[row][OVRTIME] = payroll[row][HRS_WRKD] - CUT_OFF;
        else
        payroll[row][OVRTIME] = 0;
    }

}

/*
    Function: grossPay
    Author(s): Mavrick Henderson, Zachary Hickey
    C.S.1428.002
    Lab Section: L17, L17
    Program 6 Function grossPay
    12/02/19

    This void function calculates the employee's gross pay for the week. If the
    employee worked 40.0 hours or less, gross pay is the hourly pay rate
    multiplied by the number of hours worked; otherwise, the employee worked
    more than 40 hours, and they are paid the regular hourly rate for the first
    40.0 hours plus time and a half for any hours over 40.

    recives: 2D array payroll
    Constants: globally declared integers:
                 ROWS - parallel arrays row dimension
               column designations in 2D array
                 GROSS
               globally declared reals:
                 CUT_OFF
               globally declared integers:
                 HRS_WRKD
                 PAYRATE
                 OVRTIME
    returns: nothing
*/

void grossPay ( double payroll[][COLS] )
{
    for ( int row = 0; row < ROWS; row++ )
        if ( payroll[row][OVRTIME] > 0)
        {
            payroll[row][GROSS] =
            payroll[row][OVRTIME] * payroll[row][PAYRATE] * 1.5;

            payroll[row][GROSS]+= CUT_OFF * payroll[row][PAYRATE];
        }
        else
            payroll[row][GROSS] =
            payroll[row][HRS_WRKD] * payroll[row][PAYRATE];
}

/*
    Function: stateTax
    Author(s): Mavrick Henderson, Zachary Hickey
    C.S.1428.002
    Lab Section: L17, L17
    Program 6 Function stateTax
    12/02/19

    This fuction calculates state taxes owed by the employee, calculated at a
    straight 6% of the employee's weekly gross pay

    recives: 2D array payroll
    Constants: globally declared integers:
                 ROWS - parallel arrays row dimension
               column designations in 2D array
                 ST_TAX
               globally declared reals:
                 STATE_TX_RATE
               globally declared integers:
                 GROSS
    returns: nothing
*/

void stateTax ( double payroll[][COLS] )
{
    for ( int row = 0; row < ROWS; row++ )
        payroll[row][ST_TAX] = payroll[row][GROSS] * STATE_TX_RATE;
}

/*
    Function: federalTax
    Author(s): Mavrick Henderson, Zachary Hickey
    C.S.1428.002
    Lab Section: L17, L17
    Program 6 Function federalTax
    12/02/19

    The void function federalTax calculates federal taxes owed by the employee.

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
        if ( payroll[row][GROSS] <= TAX_CUT_OFF )
            payroll[row][FED_TAX] = payroll[row][GROSS] * LOW_TAX_RATE;
        else
        {
            payroll[row][FED_TAX] = TAX_CUT_OFF * LOW_TAX_RATE;
            payroll[row][FED_TAX] +=
            ( payroll[row][GROSS] - TAX_CUT_OFF ) * HI_TAX_RATE;
        }
}

/*
    Function: netPay
    Author(s): Mavrick Henderson, Zachary Hickey
    C.S.1428.002
    Lab Section: L17, L17
    Program 6 Function netPay
    12/02/19

    This function calculates the employee's net pay for the week.
    (gross pay minus calculated taxes both state & federal)

    recives: 2D array payroll
    Constants: globally declared integers:
                 ROWS - parallel arrays row dimension
               column designations in 2D array
                 NETPAY
               globally declared reals:
                 STATE_TX_RATE
               globally declared integers:
                 GROSS
                 ST_TAX
                 FED_TAX
    returns: nothing
*/

void netPay ( double payroll[][COLS] )
{
    for ( int row = 0; row < ROWS; row++ )
        payroll[row][NETPAY] =
        payroll[row][GROSS] - payroll[row][ST_TAX] - payroll[row][FED_TAX];
}

/*
    Function: printReportData
    Author(s): Mavrick Henderson, Zachary Hickey
    C.S.1428.002
    Lab Section: L17, L17
    Program 6 Function printReportData
    12/02/19

    The void function printReportData prints to an output file the payroll
    information for each employee in tabular form under the appropriate column
    headers. The employee records are single spaced. Monetary values are
    displayed with two digits of precision.
    Note: The report title and column headers are printed by a previously
    called function.
    Monthly Payroll Report
    ID# Hours Hourly Overtime Gross State Federal Net
    Worked Rate Hours Pay Tax Tax Pay
    1000 51.00 6.55 11.00 370.07 22.20 74.02 273.86
    1001 40.50 6.50 0.50 264.88 15.89 52.98 196.01
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
void printReportData ( ostream& out, const int employee[],
                      const double payroll[][COLS] )
{
  for ( int row = 0; row < ROWS; row++ )
  {
    out << employee[row];
    for ( int info = 0; info < COLS; info++ )
      out << fixed << setprecision(2) << setfill(' ') << setw(10)
      << payroll[row][info];
    out << endl;
  }
}

/*
    Function: writeFileLocation
    Author(s): Mavrick Henderson, Zachary Hickey
    C.S.1428.002
    Lab Section: L17, L17
    Program 6 Function writeFileLocation
    12/02/19

    This Function prints an appropriate message to the console screen
    indicating to the user the name of the output file to which the results
    have been written.

    sample output:
        Program has been written to prog6_002out.txt.

    recives: 1D array output_file_name
    Constants: none
    returns: nothing
*/

void writeFileLocation( const char output_file_name[] )
{
    cout <<"Program has been written to " << output_file_name << "." << endl;
}
