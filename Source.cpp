//***********************************************************
// Author: D.S. Malik
//
// Program: Postfix Calculator  
// This program evaluates postfix expressions.
//***********************************************************

#include <iostream>  
#include <iomanip>  //for input , output manipulation
#include <fstream>  //for working with files
#include "myStack.h"    //getting the functions for array based stack
using namespace std;

void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack, char& ch, bool& isExpOk); //checks validity of the expression
void evaluateOpr(ofstream& out, stackType<double>& stack, char& ch, bool& isExpOk); //checks validity of the operation
void discardExp(ifstream& in, ofstream& out, char& ch); //gets rid of bad operator
void printResult(ofstream& outF, stackType<double>& stack, bool isExpOk); //displays result

int main()
{
    bool expressionOk; // checks if the expression is valid
    char ch;           // takes char
    stackType<double> stack(100); //creates a stack with size 100
    ifstream infile;   // reads values from the file
    ofstream outfile;  // writes values to the file 

    //file found in:    http://osprey.unisa.ac.za/download/Disk/Disk%202019/src/malik_downloads/Chapter%207%20Source%20Code/Ch7_PostfixExp/RpnData.txt
    infile.open("RpnData.txt"); // open the infile

    if (!infile) //if there is nothing to read
    {
        cout << "Cannot open the input file. " << "Program terminates!" << endl;
        return 1;   //terminates
    }

    outfile.open("RpnOutput.txt"); // opens the output file

    outfile << fixed << showpoint; 
    outfile << setprecision(2);    //sets the value to be always two digits after the decimal point. 

    infile >> ch; //reading strings from input file

    while (infile) //if tehre is things to read
    {
        stack.initializeStack(); //initializes the stack
        expressionOk = true;     //expressions are initialized as true, beacuse evaluateExpression is going to be called
        outfile << ch;           //writing the result to outfile

        //checking the expression validity
        evaluateExpression(infile, outfile, stack, ch, expressionOk);

        printResult(outfile, stack, expressionOk);
        infile >> ch; //begin processing the next expression
    } //end while 

    //we don't want the console to have the file open after code compilation
    infile.close();
    outfile.close();

    return 0;

} //end main



void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack, char& ch, bool& isExpOk)
{
    double num;

    while (ch != '=') //if  "=" not found in the string
    {
        switch (ch) //using switch to check different char
        {
        case '#': //when "#" found

            inpF >> num; //continue reading
            outF << num << " ";  //writing the numbers to the ouput file, space seperated

            if (!stack.isFullStack()) { //if the end of the stack is not reached yet

                stack.push(num); // push next number on the stack
            }
            else
            {
                //if the stack is full
                cout << "Stack overflow. " << "Program terminates!" << endl;
                exit(0);  //terminate the program
            }

            break; //no more "#", then break

        default: // if "#" not found
            evaluateOpr(outF, stack, ch, isExpOk);
        }//end switch

        if (isExpOk) //if valid expression
        {
            //reading valid string from input file and writing to output file
            inpF >> ch;
            outF << ch;

            //if"#" not found, then pad with "space"
            if (ch != '#') outF << " ";
        }
        else
            //discard expression if invaid string found
            discardExp(inpF, outF, ch);
    } //end while (!= '=')
} //end evaluateExpression


void evaluateOpr(ofstream& out, stackType<double>& stack, char& ch, bool& isExpOk)
{
    double op1; //store the value of the stack below the top element of the stack
    double op2; //stores top value of the stack

    //first check if stack is empty
    if (stack.isEmptyStack())
    {
        out << " (Not enough operands)"; // empty stack has no operand
        isExpOk = false;                 // thus invalid expression
    }
    else
    {
        op2 = stack.top();              //top element of the stack is assigned
        stack.pop();                    //top element removed from the stack

        if (stack.isEmptyStack())       //if the stack is empty
        {
            out << " (Not enough operands)";//empty stack has no operand
            isExpOk = false;                //invalid expression
        }
        else //if it's not empty
        {
            op1 = stack.top();              //the value of the element below the top element is being assigned
            stack.pop();                    //removes from the stack

            switch (ch)  //check char
            {
            case '+':                      //add when "+" is found
                stack.push(op1 + op2);
                break;
            case '-':                      //subtract when "-" is found
                stack.push(op1 - op2);
                break;
            case '*':                       //multiply when "*" is found
                stack.push(op1 * op2);
                break;
            case '/':                       //divide when "/" is found
                if (op2 != 0)               //the denominator can't be 0
                    stack.push(op1 / op2);
                else
                {
                    out << " (Division by 0)"; //gives error message
                    isExpOk = false;    // dividing a number by zero is invalid
                }
                break;
            default:
                out << " (Illegal operator)";  //if the the valid operands not found
                isExpOk = false;               //the expression is invalid
            }//end switch
        } //end else
    } //end else
} //end evaluateOpr


void discardExp(ifstream& in, ofstream& out, char& ch)
{
    //copy everything from infile to outfile until "=" is found
    while (ch != '=')
    {
        in.get(ch);
        out << ch;
    }
} //end discardExp


void printResult(ofstream& outF, stackType<double>& stack, bool isExpOk)
{
    double result; //stores the result upon calculation

    if (isExpOk) //if no error, print the result
    {
        if (!stack.isEmptyStack())
        {
            result = stack.top(); //top of the stack has the calculated value
            stack.pop(); //removes it from the stack

            if (stack.isEmptyStack())   //stack should be empty as the result has been popped
                outF << result << endl;
            else
                outF << " (Error: Too many operands)" << endl;  //non empty stack would suggest error in result due to too many operands
        } //end if
        else
            outF << " (Error in the expression)" << endl;   //empty stack in this stage would suggest there is some error and we are missing the result
    }
    //if the expression is invalid
    else
        outF << " (Error in the expression)" << endl;

    outF << "_________________________________" << endl << endl;
} //end printResult

