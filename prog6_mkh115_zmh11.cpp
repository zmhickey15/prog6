/*
   File: prog5_mkh115_zmh11.cpp

   Author: Mavrick Henderson, Zachay Hickey
   C.S.1428.002
   Lab Section: L17 &L17
   Program: #5
   Due Date: 12/02/19

   This program reads an unknown number of simple binary expressions
   of the form 'operand1 operator operand2' from an input file. Each
   expression is evaluated. Real input values are allowed.

   A sentinel value read loop is used to process as described below:

   (Named constants to 'hold' CLASS ("C.S.1428") and DUE_DATE ("--/--/--")
   are declared in the calling routine (main).)

   - A void function, getName, is called to 'get' the team members' first & last
     names using two different prompts for each team member leaving a blank
     line between sets of prompts. Four strings, one to 'hold' the first name
     and one to 'hold' the last name for each team member, are declared in the
     calling routine. A blank line is left after the last prompt.
   - A typed function, getLectureSection, is called to 'get' the team members'
     three-digit lecture section number. A string to 'hold' the lecture
     section number is declared in the calling routine. A blank line is left
     after the prompt.
   - A void function, getLabSection, is called to 'get' the team members'
     two-digit lab section numbers using two separate prompts. Strings are
     declared in the calling routine to 'hold' the lab section numbers.
   - A void function, printIdInfo, is called to print the team members' personal
     identifying information to the output file. (Refer to the sample output
     below.)
   - A void function, readExpression, is called to read from an input file
     a binary expression in the form operand1 operator operand2. One read
     statement is used to "get" the parts of the expression.
   - While the operator in the expression read is not a question mark,
     the program processes as follows:
             - A void function, echoExpression, is called to echo (print)
               the expression to the output file.
             - A void function, evaluateExpression, is called. If the
               expression currently being evaluated is valid, the results
               are calculated and written to the output file; otherwise,
               an appropriate message is written to the output file. (See
               below. *) A switch is used in the solution.
             - The void function readExpression is called to read the next
               expression of the form operand1 operator operand2.
   - Two blank lines are written to the screen in the calling routine before
     the void function printIdInfo is called to print the team members' personal
     identifying information to the console. (Refer to the sample output
     below.)
   - A void function, writeFileLocation, is called to print an appropriate
     message to the screen indicating to the user the name of the output
     file to which the results have been written. (Refer to sample output
     below.)

==========================================================================

*The expressions are checked for the addition (+), subtraction (-),
multiplication (*), and division (/) operators. Included are a check for
division by zero when the division operator is encountered and a check for
an invalid operator (e.g. 134.6 ! 23.1). Since these are mutually exclusive
events, a switch statement with a nested double-sided alternative for
handling the division operator was used to evaluate the expressions.

If division by zero is encountered, the original expression is echoed to
the output file along with the message '   Division by zero produces an
undefined result.' If an invalid operator is encountered, the original
expression is echoed to the output file along with the message
'   Encountered unknown operator.'

Every attempt is made to eliminate repetitive code!

Numeric values in output are NOT formatted!

==========================================================================

The layout and content of the file input and the file output are shown in
the samples below. An appropriate message is displayed to the screen if
either the input file or the output file fails to open.

Input (file - prog5_?inp.txt):  // '?' represents three-digit lecture number
(contains an unknown number of binary expressions)

      operand1(double)  operator(char)  operand2(double)
      ...

Constants: CLASS = "C.S.1428"    (string)
           DUE_DATE = "--/--/--" (string)

Sample Screen Display:

     Enter your first name:
     Enter your last name:
           <blank line>
     Enter your team member's first name:
     Enter your team member's last name:
           <blank line>
     Enter your three-digit lecture section number:
           <blank line>
     Enter your two-digit lab section number:
     Enter your team member's two-digit lab section number:
           <blank line>
           <blank line>
     Authors' Names
     C.S.1428.?           // '?' represents three-digit lecture section number
     Lab Section: L? & L? // '?' represents two-digit lab section number
     --/--/--             // dashes represent due date, month/day/year
           <blank line>
     <Appropriate message indicating the name of the output file.>

Sample File Output (prog5_?out.txt): //'?' represents three-digit lecture sec #

     Authors' Names
     C.S.1428.?             // '?' represents three-digit lecture section number
     Lab Section: L? & L?   // '?' represents two-digit lab section number
     --/--/--               // dashes represent due date, month/day/year
           <blank line>
     125 $ 28   Encountered unknown operator.
     123.5 + 59.3 = 182.8
     198.7 / 0   Division by zero produces an undefined result.
     ...

     ================================================

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

// REPLACE THIS COMMENT WITH PROTOTYPES.
void printIdInfo( ostream &, const string, const int, const string, const string);

void printReportHeadings ( ostream & );

void dataIn ( ifstream &, int [], double [][COLS] );

void overTime ( double [][COLS] );

void grossPay ( double [][COLS] );

void stateTax ( double [][COLS] );

void federalTax ( double [][COLS] );

void netPay ( double [] [COLS]) ;

void printReportData ( ostream &, const int[], const double[][COLS] );

int main ( )
{
   const string AUTHORS = "Mavrick Henderson, Zachary Hickey",
                LAB_SECTION = "L17 & L17",
                DUE_DATE = "12/02/19";

   const int LECTURE_SECTION = 2,
             MAX_LENGTH_FN = 20;

   char input_filename[MAX_LENGTH_FN + 1] = "test2.txt",  // REMOVE THIS COMMENT AFTER REPLACING ... WITH THE NAME OF THE INPUT FILE.
        output_filename[MAX_LENGTH_FN + 1] = "test.txt"; // REMOVE THIS COMMENT AFTER REPLACING ... WITH THE NAME OF THE OUTPUT FILE.

   int employee[ROWS];          // employee ID#s

   double payroll[ROWS][COLS];  // payroll data

   ifstream fin;
   fin.open( input_filename );

    // REPLACE THIS COMMENT WITH CODE TO VERIFY THE INPUT FILE OPENS.
    // USE THE CODE FROM THE EXAMPLE PROVIDED ON THE ASSIGNMENTS PAGE.
    // ONLY MAKE NECESSARY ADJUSTMENTS, OR POINTS WILL BE DEDUCTED.

    ofstream fout;
    fout.open ( output_filename );

    // REPLACE THIS COMMENT WITH CODE TO VERIFY THE INPUT FILE OPENS.
    // USE THE CODE FROM THE EXAMPLE PROVIDED ON THE ASSIGNMENTS PAGE.
    // ONLY MAKE NECESSARY ADJUSTMENTS, OR POINTS WILL BE DEDUCTED.

   printIdInfo( fout, AUTHORS, LECTURE_SECTION, LAB_SECTION, DUE_DATE );
   printReportHeadings ( fout );
   dataIn ( fin, employee, payroll );
   overTime ( payroll );
   grossPay ( payroll );
   stateTax ( payroll );
   federalTax ( payroll );
   netPay ( payroll );
   printReportData ( fout, employee, payroll );
   printIdInfo( cout, AUTHORS, LECTURE_SECTION, LAB_SECTION, DUE_DATE );/*
   writeFileLocation ( output_filename );

   // REPLACE THIS COMMENT WITH CODE TO CLOSE THE INPUT/OUTPUT FILES.

   system("PAUSE>NUL");*/


   return 0;
}

// REPLACE THIS COMMENT WITH DOCUMENTATION & CODE FOR THE FUNCTION DEFINITIONS.

/*
put stuff dont forget!!!!!!!!!
!!!!!!!!!!!!
!!!!!
*/

void printIdInfo ( ostream & out, const string AUTHORS, const int LECTURE_SECTION, const string LAB_SECTION, const string DUE_DATE )
{
out << AUTHORS << endl
    << "C.S.1428." << setw(3) << setfill('0') << LECTURE_SECTION << endl
    << "Lab Section: " << LAB_SECTION << endl
    << DUE_DATE << endl << endl << endl;
}

/*
add shit dont forget



*/

void printReportHeadings ( ostream & out )
{
out << "                     Monthly Payroll Report" << endl << endl
    << " ID#     Hours    Hourly   Overtime    Gross     State    Federal     Net" << endl
    << "        Worked     Rate      Hours      Pay       Tax       Tax       Pay" << endl;
}

/*
add shit or she will be mad!!!!!!


*/

void dataIn ( ifstream & fin, int employee[], double payroll[][COLS])
{

for ( int row = 0; row < ROWS; row++ )
    fin >> employee[row] >> payroll[row][HRS_WRKD] >> payroll[row][PAYRATE];
}

/*
add shit again

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
add more shit

*/

void grossPay ( double payroll[][COLS] )
{
for ( int row = 0; row < ROWS; row++ )
  if ( payroll[row][OVRTIME] > 0)
  {
    payroll[row][GROSS] = payroll[row][OVRTIME] * payroll[row][PAYRATE] * 1.5;
    payroll[row][GROSS]+= CUT_OFF * payroll[row][PAYRATE];
  }
  else
    payroll[row][GROSS] = payroll[row][HRS_WRKD] * payroll[row][PAYRATE];
}

/*
put shit here
*/

void stateTax ( double payroll[][COLS] )
{
for ( int row = 0; row < ROWS; row++ )
  payroll[row][ST_TAX] = payroll[row][GROSS] * STATE_TX_RATE;
}

/*
add stuff



*/
void federalTax ( double payroll[][COLS] )
{
for ( int row = 0; row < ROWS; row++ )
  if ( payroll[row][GROSS] <= TAX_CUT_OFF )
    payroll[row][FED_TAX] = payroll[row][GROSS] * LOW_TAX_RATE;
  else
  {
    payroll[row][FED_TAX] = TAX_CUT_OFF * LOW_TAX_RATE;
    payroll[row][FED_TAX] += ( payroll[row][GROSS] - TAX_CUT_OFF ) * HI_TAX_RATE;
  }
}

/*
stuff
*/
void netPay ( double payroll[][COLS] )
{
for ( int row = 0; row < ROWS; row++ )
  payroll[row][NETPAY] = payroll[row][GROSS] - payroll[row][ST_TAX] - payroll[row][FED_TAX];
}
/*
add stfff

*/
void printReportData ( ostream& out, const int employee[], const double payroll[][COLS])
{
  for ( int row = 0; row < ROWS; row++ )
  {
    out << employee[row];
    for ( int info = 0; info < COLS; info++ )
      out << fixed << setprecision(2) << setfill(' ') << setw(10) << payroll[row][info];
    out << endl;
  }
}
