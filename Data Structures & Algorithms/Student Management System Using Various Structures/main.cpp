#include <bits/stdc++.h>
#include <queue>
using namespace std;

 // Define the binary search tree class
class BST {
// Define the student struct
struct Student {
  int id;
  string name;
  float GPA;
  string department;
  Student* left, * right;
};
private:
  Student* root;
public:
  BST() {
    root = NULL;
  }
  // Function to add a student to the BST
  void addStudent(int id, string name, float GPA, string department) {
    Student* newStudent = new Student;
    newStudent->id = id;
    newStudent->name = name;
    newStudent->GPA = GPA;
    newStudent->department = department;
    newStudent->left = NULL;
    newStudent->right = NULL;
    if (root == NULL) {
      root = newStudent;
    }
    else {
      Student* current = root;
      while (true) {
        if (id < current->id) {
          if (current->left == NULL) {
            current->left = newStudent;
            break;
          }
          else {
            current = current->left;
          }
        }
        else {
          if (current->right == NULL) {
            current->right = newStudent;
            break;
          }
          else {
            current = current->right;
          }
        }
      }
    }
  }
  // Function to remove a student from the BST
  void removeStudent(int id) {
    root = removeStudentHelper(root, id);
  }
  Student* removeStudentHelper(Student* current, int id) {
    if (current == NULL) {
      return NULL;
    }
    else if (id < current->id) {
      current->left = removeStudentHelper(current->left, id);
    }
    else if (id > current->id) {
      current->right = removeStudentHelper(current->right, id);
    }
    else {
      if (current->left == NULL && current->right == NULL) {
        delete current;
        current = NULL;
      }
      else if (current->left == NULL) {
        Student* temp = current;
        current = current->right;
        delete temp;
      }
      else if (current->right == NULL) {
        Student* temp = current;
        current = current->left;
        delete temp;
      }
      else {
        Student* temp = findMin(current->right);
        current->id = temp->id;
        current->name = temp->name;
        current->GPA = temp->GPA;
        current->department = temp->department;
        current->right = removeStudentHelper(current->right, temp->id);
      }
    }
    return current;
  }
  // Function to find the student with a given id in the BST
  void findStudent(int id) {
    Student* current = root;
    while (current != NULL && current->id != id) {
      if (id < current->id) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    if (current != NULL) {
      cout << "ID: " << current->id << endl;
      cout << "Name: " << current->name << endl;
      cout << "GPA: " << current->GPA << endl;
      cout << "Department: " << current->department << endl;
    }
    else {
      cout << "Student not found." << endl;
    }
  }
  // Function to print all students in the BST, sorted by id
  void printAllStudents() {
    int count = 0;
    printAllStudentsHelper(root, count);
    cout << "Total students: " << count << endl;
  }
  void printAllStudentsHelper(Student* current, int& count) {
    if (current != NULL) {
      printAllStudentsHelper(current->left, count);
      cout << "ID: " << current->id << endl;
      cout << "Name: " << current->name << endl;
      cout << "GPA: " << current->GPA << endl;
      cout << "Department: " << current->department << endl;
      cout << endl;
      count++;
      printAllStudentsHelper(current->right, count);
    }
  }
  // Function to find the student with the minimum id in the BST
  Student* findMin(Student* current) {
    while (current->left != NULL) {
      current = current->left;
    }
    return current;
  }
};

class studentHeap {
private:
  struct student {
    int id;
    string name;
    double gpa;
    string department;
  };
public:
  studentHeap() {}
  void insertStudentMin(int id, string name, double gpa, string department) {
    student s = { id, name, gpa, department};
    minHeap.push(s);
    departmentMap[department].push_back(s);
  }
  void insertStudentMax(int id, string name, double gpa, string department) {
    student s = { id, name, gpa, department};
    maxHeap.push(s);
    departmentMap[department].push_back(s);
  }
  void print_All_Students() {
    cout << "All Students:\n";
    vector<student> students;
    while (!minHeap.empty()) {
      students.push_back(minHeap.top());
      minHeap.pop();
    }
    sort(students.begin(), students.end(), [](const student& s1, const student& s2) {
      return s1.gpa < s2.gpa;
    });
    for (student s : students) {
      cout << "ID: " << s.id << endl << " Name: " << s.name << endl << " GPA: " << s.gpa<<endl
      << " Department: " << s.department << "\n";
    }
  }
  struct minHeapComp {
    bool operator()(const student& s1, const student& s2) const {
      return s1.id > s2.id;
    }
  };
  struct maxHeapComp {
    bool operator()(const student& s1, const student& s2) const {
      return s1.id < s2.id;
    }
  };
  priority_queue<student, vector<student>, minHeapComp> minHeap;
  priority_queue<student, vector<student>, maxHeapComp> maxHeap;
  map<string, vector<student>> departmentMap;
};

class Student {
public:
  int id;
  string name;
  double gpa;
  string department;
  Student(int i, string n, double g, string d) {
    id = i;
    name = n;
    gpa = g;
    department = d;
  }
};
class AVLTree {
private:
  struct Node {
    Student* data;
    Node* left;
    Node* right;
    int height;

    Node(Student* s) {
      data = s;
      left = NULL;
      right = NULL;
      height = 1;
    }
  };
  Node* root;
  int height(Node* node) {
    if (node == NULL) {
      return 0;
    }
    return node->height;
  }
  int balanceFactor(Node* node) {
    if (node == NULL) {
      return 0;
    }
    return height(node->left) - height(node->right);
  }
  void updateHeight(Node* node) {
    node->height = max(height(node->left), height(node->right)) + 1;
  }
  Node* rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
  }
  Node* rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
  }
  Node* balance(Node* node) {
    updateHeight(node);
    int bf = balanceFactor(node);
    if (bf > 1) {
      if (balanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
      }
      return rotateRight(node);
    } else if (bf < -1) {
      if (balanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
      }
      return rotateLeft(node);
    }
    return node;
  }
  Node* insert(Node* node, Student* s) {
    if (node == NULL) {
      return new Node(s);
    }
    if (s->id < node->data->id) {
      node->left = insert(node->left, s);
    } else if (s->id > node->data->id) {
      node->right = insert(node->right, s);
    } else {
      // Handle duplicate id
      delete s;
      return node;
    }
    return balance(node);
  }
  Node* findMin(Node* node) {
    while (node->left != NULL) {
      node = node->left;
    }
    return node;
  }
  Node* remove(Node* node, int id) {
    if (node == NULL) {
      return NULL;
    }
    if (id < node->data->id) {
      node->left = remove(node->left, id);
    } else if (id > node->data->id) {
      node->right = remove(node->right, id);
    } else {
      if (node->left == NULL && node->right == NULL) {
        delete node;
        return NULL;
      } else if (node->left == NULL) {
        Node* right = node->right;
        delete node;
        return right;
      } else if (node->right == NULL) {
        Node* left = node->left;
        delete node;
        return left;
      } else {
        Node* minRight = findMin(node->right);
        node->data = minRight->data;
        node->right = remove(node->right, minRight->data->id);
      }
    }
    return balance(node);
  }
  void printInOrder(Node* node) {
    if (node == NULL) {
      return;
    }
    printInOrder(node->left);
    cout << node->data->id << " " << node->data->name << " " << node->data->gpa
    << " " << node->data->department << endl;
    printInOrder(node->right);
  }
public:
  AVLTree() {
    root = NULL;
  }

  void insert(Student* s) {
    root = insert(root, s);
  }

  void remove(int id) {
    root = remove(root, id);
  }
  void search(int id) {
    Node* node = root;
    while (node != NULL) {
      if (id < node->data->id) {
        node = node->left;
      } else if (id > node->data->id) {
        node = node->right;
      } else {
        cout << node->data->id << " " << node->data->name << " " << node->data->gpa
        <<" " << node->data->department << endl;
        return;
      }
    }
    cout << "Student not found" << endl;
  }
  void printAll() {
    printInOrder(root);
  }
private:
  void countDepartments(Node* node, map<string, int>& departmentCounts) {
    if (node == NULL) {
      return;
    }
    countDepartments(node->left, departmentCounts);
    departmentCounts[node->data->department]++;
    countDepartments(node->right, departmentCounts);
  }
};
int main() {
  AVLTree tree;
  BST bst;
  studentHeap sh;
  // Read from input file and add students to the Trees and Heap.
  ifstream inputFile("input.txt");
  int numStudents;
  inputFile >> numStudents;
  for (int i = 0; i < numStudents; i++) {
    int id;
    string name, department;
    float GPA;
    inputFile >> id;
    getline(inputFile >> ws, name);
    inputFile >> GPA;
    getline(inputFile >> ws, department);
    bst.addStudent(id, name, GPA, department);
    sh.insertStudentMin(id, name, GPA, department);
    sh.insertStudentMax(id, name, GPA, department);
    Student* s = new Student(id, name, GPA, department);
      tree.insert(s);
  }
  // Show the main menu
  int choice;
  while (true) {
    cout << "((First Menu - Main menu))" << endl;
    cout << "Choose Data Structure:" << endl;
    cout << "1. BST" << endl;
    cout << "2. Heap" << endl;
    cout << "3. AVL" << endl;
    cout << "4. Exit" << endl;
    cin >> choice;
    if (choice == 1) {
      // Show the BST menu
      while (true) {
        cout << "((BST menu))" << endl;
        cout << "Choose an operation:" << endl;
        cout << "1. Add a student" << endl;
        cout << "2. Remove a student" << endl;
        cout << "3. Search for a student" << endl;
        cout << "4. Print all students" << endl;
        cout << "5. Back to main menu" << endl;
        cin >> choice;
        if (choice == 1) {
          int id;
          string name, department;
          float GPA;
          cout << "Enter the student's ID: ";
          cin >> id;
          cout << "Enter the student's name: ";
          getline(cin >> ws, name);
          cout << "Enter the student's GPA: ";
          cin >> GPA;
          cout << "Enter the student's department: ";
          getline(cin >> ws, department);
          bst.addStudent(id, name, GPA, department);
          cout << " The students is added. " << endl;
        }
        else if (choice == 2) {
          int id;
          cout << "Enter the ID of the student to remove: ";
          cin >> id;
          bst.removeStudent(id);
        }
        else if (choice == 3) {
          int id;
          cout << "Enter the ID of the student to search for: ";
          cin >> id;
          bst.findStudent(id);
        }
        else if (choice == 4) {
          bst.printAllStudents();
        }
        else if (choice == 5) {
          break;
        }
        else {
          cout << "Invalid choice. Please try again." << endl;
        }
      }
    }
    else if (choice == 2) {
      while (true) {
        cout << "((Heap menu))" << endl;
        cout << "Choose an operation:" << endl;
        cout << "1. Add a student with minHeap" << endl;
        cout << "2. Add a student with maxHeap" << endl;
        cout << "3. Print all students" << endl;
        cout << "4. Back to main menu" << endl;
        cin >> choice;
        if (choice == 1) {
          int id;
          string name, department;
          float GPA;
          cout << "Enter the student's ID: ";
          cin >> id;
          cout << "Enter the student's name: ";
          getline(cin >> ws, name);
          cout << "Enter the student's GPA: ";
          cin >> GPA;
          cout << "Enter the student's department: "<<endl;
          getline(cin >> ws, department);
          sh.insertStudentMin(id, name, GPA, department);
          cout << " The students is added. " << endl;
        }
        else if  (choice == 2) {
          int id;
          string name, department;
          float GPA;
          cout << "Enter the student's ID: ";
          cin >> id;
          cout << "Enter the student's name: ";
          getline(cin >> ws, name);
          cout << "Enter the student's GPA: ";
          cin >> GPA;
          cout << "Enter the student's department: "<< endl;
          getline(cin >> ws, department);
          sh.insertStudentMax(id, name, GPA, department);
          cout << " The students is added. " << endl;
        }
        else if (choice == 3) {
          sh.print_All_Students();
        }
        else if (choice == 4) {
          break;
        }
      }
    }
    else if (choice == 3) {
      while (choice != 5) {
        cout << "AVL Menu:" << endl;
        cout << "1. Add a student" << endl;
        cout << "2. Remove a student" << endl;
        cout << "3. Search for a student" << endl;
        cout << "4. Print all students" << endl;
        cout << "5. Back to main menu" << endl;
        cin >> choice;
          if (choice == 1) {
            int id;
            string name, department;
            float GPA;
            cout << "Enter the student's ID: ";
            cin >> id;
            cout << "Enter the student's name: ";
            getline(cin >> ws, name);
            cout << "Enter the student's GPA: ";
            cin >> GPA;
            cout << "Enter the student's department: "<< endl;
            getline(cin >> ws, department);
            Student* s = new Student(id, name, GPA, department);
            tree.insert(s);
            cout << " The students is added. " << endl;
          }
          else if (choice == 2) {
            int id;
            cout << "Enter student id to remove:" << endl;
            cin >> id;
            tree.remove(id);
          }
          else if (choice == 3) {
            int id;
            cout << "Enter student id to search for:" << endl;
            cin >> id;
            tree.search(id);
          }
          else if (choice == 4) {
            tree.printAll();
          }
          else if (choice == 5) {
            break;
          }
          else {
            cout << "Invalid choice. Please try again." << endl;
          }
      }
    }
    else
    {
      cout << "invalid" << endl;
    }
  }
  return 0;
}