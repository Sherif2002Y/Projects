#include <bits/stdc++.h>
using namespace std;
//? Array-Based List.
class arrayM
{
private:
  int *arr;
  int size;
  int capacity;

public:
  // Constructor
  arrayM(int capacity = 10)
  {
    this->capacity = capacity;
    arr = new int[capacity];
    size = 0;
  };
  // insert function to insert value in array.
  void insert(int value)
  {
    if (size == capacity)
    {
      cout << "Array is full" << endl;
      return;
    }
    arr[size] = value;
    size++;
  };
  // insertAt function to insert value at specific index in array.
  void insertAt(int index, int value)
  {
    if (index < 0 || index > size)
    {
      cout << "Index out" << endl;
      return;
    }
    // check if array is full or not.
    if (size == capacity)
    {
      cout << "Array is full" << endl;
      return;
    }
    // shift values to the right.
    for (int i = size - 1; i >= index; i--)
    {
      arr[i + 1] = arr[i];
    }
    arr[index] = value;
    size++;
  };
  // removeAt function to remove value at specific index in array.
  void removeAt(int index = 0)
  {
    if (index < 0 || index > size)
    {
      cout << "Index out" << endl;
      return;
    }
    if (size == 0)
    {
      cout << "Array is empty" << endl;
      return;
    }
    for (int i = index; i < size - 1; i++)
    {
      arr[i] = arr[i + 1];
    }
    size--;
  };
  // function to replace value at specific index in array.
  void replaceAt(int index, int value)
  {
    if (index < 0 || index > size)
    {
      cout << "Index out" << endl;
    }
    arr[index] = value;
  };
  // function to check if array is empty or not.
  bool isEmpty()
  {
    if (size == 0)
    {
      cout << "Array is empty" << endl;
    }
    cout << "Array is not empty" << endl;
  };
  // function to check if array is full or not.
  bool isFull()
  {
    if (size == capacity)
    {
      cout << "Array is full" << endl;
    }
    cout << "Array is not full" << endl;
  };
  // function to print array.
  void print()
  {
    for (int i = 0; i < size; i++)
    {
      cout << arr[i] << " ";
    }
    cout << endl;
  };
  // function to clear array.
  void clear()
  {
    size = 0;
  };
  // function to return size of array.
  int listSize()
  {
    return size;
  };
  // function to check if value at specific index is equal to given value or not.
  bool isItemAtEqual(int index, int value)
  {
    if (index < 0 || index > size)
    {
      cout << "Index out" << endl;
    }
    // check if value at specific index is equal to given value or not.
    if (arr[index] == value)
    {
      cout << "Item is equal" << endl;
    }
    cout << "Item is not equal" << endl;
  };
  // function to return capacity of array.
  int maxListSize()
  {
    return capacity;
  };
  // destructor to delete array.
  ~arrayM()
  {
    delete[] arr;
  };
};
//---------------------------------------------------------------------------------------------//
//* Stack
template<class T>
class stackM
{
private:
  int *arr;
  int size;
  int capacity;

public:
  // Constructor
  stackM(int capacity = 10)
  {
    this->capacity = capacity;
    arr = new int[capacity];
    size = 0;
  };
  // function to insert value in stack.
  void push(int value)
  {
    if (size == capacity)
    {
      cout << "Stack is full" << endl;
      return;
    }
    arr[size] = value;
    size++;
  };
  // function to remove value from stack.
  void pop()
  {
    if (size == 0)
    {
      cout << "Stack is empty" << endl;
      return;
    }
    size--;
  };
  // function to return value at top of stack.
  int top()
  {
    if (size == 0)
    {
      cout << "Stack is empty" << endl;
    }
    return arr[size - 1];
  };
  // function to check if stack is empty or not.
  bool isEmpty()
  {
    if (size == 0)
    {
      cout << "Stack is empty" << endl;
    }
    cout << "Stack isn't empty" << endl;
  };
  // function to print stack.
  void print()
  {
    for (int i = 0; i < size; i++)
    {
      cout << arr[i] << " ";
    }
    cout << endl;
  };
  // function to clear stack.
  bool clear() {
    if (size == 0) {
      return true;
    }
    return false;
  }
  // function to return size of stack.
  int stackSize()
  {
    return size;
  };
  // destructor to delete stack.
  ~stackM()
  {
    delete[] arr;
  };
};

// return the length of the longest valid parentheses substring
int longestValidParentheses(string s)
{
  stackM<int> st;
  int maxLength = 0;
  int last = -1; // Index of the last invalid closing parenthesis
  for (int i = 0; i < s.length(); i++)
  {
    if (s[i] == '(')
    {
      st.push(i);
    }
    else
    {
      if (st.clear())
      {
        last = i;
      }
      else
      {
        st.pop();
        if (st.clear())
        {
          maxLength = max(maxLength, i - last);
        }
        else
        {
          maxLength = max(maxLength, i - st.top());
        }
      }
    }
  }
  return maxLength;
}
// Function to convert infix expression to postfix expression.
string infixToPostfix(string infix)
{
  // Define operator precedence
  unordered_map<char, int>precedence = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}};
  stackM<char> st;
  string postfix = "";
  for (char &c : infix)
  {
    if (isalnum(c))
    {
      postfix += c;
    }
    else if (c == '(')
    {
      st.push(c);
    }
    else if (c == ')')
    {
      while (!st.clear() && st.top() != '(')
      {
        postfix += st.top();
        st.pop();
      }
      st.pop();
    }
    else if (precedence.count(c))
    {
      while (!st.clear() && st.top() != '(' && precedence[c] <= precedence[st.top()])
      {
        postfix += st.top();
        st.pop();
      }
      st.push(c);
    }
  }
  while (!st.clear())
  {
    postfix += st.top();
    st.pop();
  }
  return postfix;
}
int main()
{
  arrayM arr(5);
  arr.insert( 1);
  arr.insert( 2);
  arr.insert(3);
  arr.insert( 4);
  arr.insert( 5);
  arr.print();
//  arr.removeAt( 2);
  arr.replaceAt( 2, 6);
  arr.print();
  //-------------------------------------
  stackM<int> st(5);
  st.push(1);
  st.push(2);
  st.push(3);
  st.push(4);
  st.push(5);
  st.print();
  st.pop();
  st.print();
  string infix = "(A + B) * (C + D)";
  string postfix = infixToPostfix(infix);
  cout << postfix << endl;
  cout << longestValidParentheses("(0") << endl;
  return 0;
}