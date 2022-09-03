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
        const char current = numbers[i];
        switch(check_str)
        {
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
    return 'i';
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
    cout << "\nh1";
    char stack_top;
    if(operator_stack.size() > 0)
    {
        stack_top = operator_stack.back();
    }
    else
    {
        return false;
    }
    cout << "\nh2";
    if(current_operator == '+' || current_operator == '-')
    {
        cout << "\nh3";
        if(stack_top == '/' || stack_top == '*')
        {
            cout << "\nh4";
            return true;
        }
    }
    return false;
}

string display_vector(vector<char> thing)
{
    string display = "{";
    for(int i = 0; i < thing.size(); i++)
    {
        if(i == 0)
        {
            display += thing.at(i);
        }
        else
        {
            display += "," + thing.at(i);
        }
    }
    display += "}";
    return display;
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
        cout << "\nOperator stack: " << display_vector(operator_stack);
        cout << "\nOutput queue: " << display_vector(output_queue);
        cout << "\nToken type: " << token_type;
        cout << "\n==================================================================";
        switch (token_type)
        {
            case number:
                output_queue.push_back(input[i]);
                continue;
            case operator_:
                // Code stops inside this while loop, need to implement this differently.
                while(operator_with_greater_precedence(operator_stack, input[i]))
                {
                    output_queue.push_back(operator_stack.back());
                    operator_stack.pop_back(); // Popping the last from left to right, because the top of the stack is the last from left to right.
                }
                operator_stack.push_back(input[i]); // Pushing it into the vector from right to left.
                continue;
            case left_paren:
                operator_stack.push_back(input[i]);
                continue;
            case right_paren:
                while(operator_stack.back() != left_paren)
                {
                    output_queue.push_back(operator_stack.back());
                    operator_stack.pop_back();
                }
                operator_stack.pop_back(); // popping the left bracket cause we couldn't do it in the while loop
                continue;
        }
    }
    while(operator_stack.size() != 0)
    {
        output_queue.push_back(operator_stack.back());
        operator_stack.pop_back();
    }
    cout << "\nOperator stack: " << display_vector(operator_stack);
    cout << "\nOutput queue: " << display_vector(output_queue);
    cout << "\nToken type: " << token_type;
}
