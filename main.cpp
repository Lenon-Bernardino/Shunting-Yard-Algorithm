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

char checktype_str(string check_str)
{
    string numbers[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    string operators[] = {"+", "-", "/", "*"};
    const string Lparen = "(";
    const string Rparen = ")";

    for(int i = 0; i < sizeof(numbers); i++)
    {
        const string current = numbers[i];
        if(check_str == Lparen)
        {
            return '(';
        }

        if(check_str == Rparen)
        {
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
    char stack_top;
    if(operator_stack.size() > 0)
    {
        stack_top = operator_stack.back();
    }
    else
    {
        return false;
    }
    if(current_operator == '+' || current_operator == '-')
    {
        if(stack_top == '/' || stack_top == '*')
        {
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
        string s(1, thing.at(i));
        if(i == 0)
        {
            display += s;
        }
        else
        {
            display += "," + s;
        }
    }
    display += "}";
    return display;
}

string display_str_vector(vector<string> thing)
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
    string buffer_for_stuff = "";
    vector<string> output_queue;
    char token_type;
    char new_token_type;

    const char number = 'n';
    const char operator_ = 'o';
    const char left_paren = '(';
    const char right_paren = ')';
    for(int i = 0; i < input.length(); i++)
    {
        string current_charSTR(1, input[i]);
        new_token_type = checktype(input[i]);
        if(new_token_type == 'n' && token_type == 'n')
        {
            output_queue.back() = output_queue.back() + current_charSTR;
            continue;
        }

        token_type = checktype(input[i]);
        switch (token_type)
        {
            case number:
                output_queue.push_back(current_charSTR);
                continue;
            case operator_:
                // Code stops inside this while loop, need to implement this differently.
                while(operator_with_greater_precedence(operator_stack, input[i]))
                {
                    buffer_for_stuff = string(1, operator_stack.back());
                    output_queue.push_back(buffer_for_stuff);
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
                    buffer_for_stuff = string(1, operator_stack.back());
                    output_queue.push_back(buffer_for_stuff);
                    operator_stack.pop_back();
                }
                operator_stack.pop_back(); // popping the left bracket cause we couldn't do it in the while loop
                continue;
        }
    }
    while(operator_stack.size() != 0)
    {
        buffer_for_stuff = string(1, operator_stack.back());
        output_queue.push_back(buffer_for_stuff);
        operator_stack.pop_back();
    }

    vector<string> operators = {};
    vector<string> two_numbers = {};
    string current_str;
    double first;
    double second;
    double result;
    string current_operator;
    for(int i = output_queue.size()-1; i <= output_queue.size()-1; i--)
    {
        current_str = output_queue.at(i);
        if(current_str.length() > 1)
        {
            token_type = 'n';
        }
        else
        {
            token_type = checktype_str(current_str);
        }
        if(token_type == 'o')
        {
            operators.push_back(current_str);
            output_queue.pop_back();
        }
        else
        {
            two_numbers.push_back(current_str);
        }

        if(two_numbers.size() == 2)
        {
            first = std::stod(two_numbers.back()); // (9)
            second = std::stod(two_numbers.front()); // (3)
            current_operator = operators.back();
            if(current_operator == "+")
            {
                result = first+second;
                two_numbers.pop_back();
                two_numbers.pop_back();
                output_queue.at(i) = to_string(result);
                output_queue.pop_back();
                operators.pop_back();
                i += 1;
                continue;
            }
            if(current_operator == "-")
            {
                result = first-second;
                two_numbers.pop_back();
                two_numbers.pop_back();
                output_queue.at(i) = to_string(result);
                output_queue.pop_back();
                operators.pop_back();
                i += 1;
                continue;
            }
            if(current_operator == "*")
            {
                result = first*second;
                two_numbers.pop_back();
                two_numbers.pop_back();
                output_queue.at(i) = to_string(result);
                output_queue.pop_back();
                i += 1;
                operators.pop_back();
                continue;
            }
            if(current_operator == "/")
            {
                result = first/second;
                two_numbers.pop_back();
                two_numbers.pop_back();
                output_queue.at(i) = to_string(result);
                output_queue.pop_back();
                i += 1;
                operators.pop_back();
                continue;
            }
        }
    }

    string final_result = output_queue.back();
    cout << "\n\nFINAL RESULT: " << final_result;
}
