#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

char checktype(char check_str)
{
    char numbers[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    char operators[] = {'+', '-', '/', '*'};
    const char Lparen = '(';
    const char Rparen = ')';

    for(int i = 0; i < sizeof(numbers); i++)
    {
        switch(check_str)
        {
            const char current = numbers[i];
            case Lparen:
                return '(';
            case Rparen:
                return ')';
        }

        if(check_str == numbers[i])
        {
            return 'n';
        }

        if(i <= sizeof(operators))
        {
            if(check_str == operators[i])
            {
                return 'o';
            }
        }
    }
    
}

bool checkoperator(char check_str)
{
    char numbers[] = {'+', '-', '/', '*'};

    for(int i = 0; i < sizeof(numbers); i++)
    {
        if(check_str == numbers[i])
        {
            return true;
        }
    }
    return false;
}

bool operator_with_greater_precedence(vector<char> operator_stack, char current_operator)
{
    char stack_top = operator_stack.back();

    if(current_operator == '+' || current_operator == '-')
    {
        if(stack_top == '/' || stack_top == '*')
        {
            return true;
        }
    }
    return false;
}

int main()
{
    string input = "";
    cout << "Input any math operation using symbols + - / ( ): ";
    cin >> input;
    
    vector<char> operator_stack;
    vector<char> output_queue;
    char token_type;

    const char number = 'n';
    const char operator_ = 'o';
    const char left_paren = '(';
    const char right_paren = ')';

    for(int i = 0; i < input.length(); i++)
    {
        token_type = checktype(input[i]);
        switch (token_type)
        {
            case number:
                output_queue.push_back(input[i]);
                continue;
            case operator_:
                while(operator_with_greater_precedence(operator_stack, input[i]))
                {
                    operator_stack.pop_back(); // Popping the last from left to right, because the top of the stack is the last from left to right.
                }
                operator_stack.push_back(input[i]); // Pushing it into the vector from right to left.
        }
    }

    // Next up, coding the brackets.
}
