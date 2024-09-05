#include <iostream>
using namespace std;
struct Node {
    int item;
    Node* next;
    Node* prev;
    Node(int x) : item(x), next(nullptr), prev(nullptr) {}
};
class DoublyLinkedList
{

private:

    Node* first;
    Node* last;
    int size;

public:
    DoublyLinkedList() {
        first = NULL;
        last = NULL;
        size = 0;
    }
    void append(struct Node** head_ref, int new_data);
    void insertAtHead(int element);
    void insertAtTail(int element);
    void insertAt(int element, int index);
    void insertAfter(Node* prev_node, int data);
    void removeAtHead();
    void removeAtTail();
    void removeAt(int index);
    int  retrieveAt(int index);
    void replaceAt(int newElement, int index);
    bool isExist(int element);
    bool isItemAtEqual(int element, int index);
    void swap(int firstItemIdx, int secondItemIdx);
    void reverse();
    bool isEmpty();
    int  doubleLinkedListSize();
    void clear();
    void forwardTraversal();
    void backwardTraversal();
    void printList();
    auto getHead();
    void append(int val);
    void combineNodesBetweenZeros(Node* head) {
        Node* current = head;

        while (current != nullptr) {
            if (current->item == 0) {
                Node* nextNode = current->next;
                int sum = 0;

                while (nextNode != nullptr && nextNode->item != 0) {
                    sum += nextNode->item;
                    nextNode = nextNode->next;
                }

                if (sum != 0) {
                    current->item = sum;
                    current->next = nextNode;

                    if (nextNode != nullptr) {
                        nextNode->prev = current;
                    }
                }
                else {
                    current->prev->next = nextNode;

                    if (nextNode != nullptr) {
                        nextNode->prev = current->prev;
                    }

                    Node* temp = current;
                    current = current->prev;

                    delete temp;
                }
            }

            current = current->next;
        }

        current = head;

        while (current != nullptr && current->item == 0) {
            Node* temp = current;
            current = current->next;

            delete temp;
        }

        if (current != nullptr) {
            current->prev = nullptr;
        }
    }

    Node* mergeTwoLists(Node* l1, Node* l2) {
        Node dummy(0);
        Node* tail = &dummy;

        while (l1 != nullptr && l2 != nullptr) {
            if (l1->item <= l2->item) {
                tail->next = l1;
                l1 = l1->next;
            }
            else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        if (l1 != nullptr) {
            tail->next = l1;
        }
        else {
            tail->next = l2;
        }

        return dummy.next;
    }
    Node* mergeKLists(Node** lists, int k) {
        // Edge case: empty list
        if (k == 0) {
            return nullptr;
        }

        // Edge case: only one list
        if (k == 1) {
            return lists[0];
        }

        // Merge two lists at a time until only one list remains
        while (k > 1) {
            int i = 0; // index of first list to merge
            int j = k - 1; // index of second list to merge
            while (i < j) {
                lists[i] = mergeTwoLists(lists[i], lists[j]);
                i++;
                j--;
                if (i >= j) {
                    k = j + 1; // update k to the number of merged lists
                }
            }
        }

        return lists[0];
    }
};
void DoublyLinkedList::insertAtHead(int element) {
    Node* newNode = new Node(element);
    newNode->item = element;
    if (size == 0) {
        first = last = newNode;
        newNode->next = newNode->prev = NULL;
    }
    else {
        newNode->next = first;
        newNode->prev = NULL;
        first->prev = newNode;
        first = newNode;

    }
    size++;
}
void DoublyLinkedList::insertAtTail(int element)
{
    Node* newNode = new Node(element);
    newNode->item = element;
    if (size == 0) {
        first = last = newNode;
        newNode->next = newNode->prev = NULL;
    }
    else {
        newNode->next = NULL;
        newNode->prev = last;
        last->next = newNode;
        last = newNode;



    }
    size++;
}
void DoublyLinkedList::insertAt(int element, int index)
{
    if (index < 0 || index > size) {
        cout << "Index out of bounds" << endl;
        return;
    }
    if (index == 0) {
        insertAtHead(element);
        return;
    }
    if (index == size) {
        insertAtTail(element);
        return;
    }
    Node* curr = first;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    Node* newNode = new Node(element);
    newNode->item = element;
    newNode->prev = curr->prev;
    newNode->next = curr;
    curr->prev->next = newNode;
    curr->prev = newNode;
    size++;
}
void DoublyLinkedList::insertAfter(Node* prev_node, int element) {
    if (prev_node == NULL) {
        cout << "Previous node cannot be null" << endl;
        return;
    }
    if (prev_node == last) {
        insertAtTail(element);
        return;
    }
    Node* newNode = new Node(element);
    newNode->item = element;
    newNode->prev = prev_node;
    newNode->next = prev_node->next;
    prev_node->next->prev = newNode;
    prev_node->next = newNode;
    size++;
}
void DoublyLinkedList::removeAtHead() {
    if (size == 0)
        cout << "Empty List" << endl;
    else if (size == 1)//first == last
    {
        delete first;
        last = first = NULL;
    }
    else
    {
        Node* current = first;
        first = first->next;
        first->prev = NULL;
        delete current;
    }
    size--;
}
void DoublyLinkedList::removeAtTail() {
    if (size == 0)
        cout << "Empty List" << endl;
    else if (size == 1)
    {
        delete first; //	same delete last;
        last = first = NULL;
        size--;
    }
    else
    {
        Node* current = last;
        last = last->prev;
        last->next = NULL;
        delete current;
        size--;
    }
}
void DoublyLinkedList::removeAt(int index) {
    if (index < 0 || index >= size) {
        cout << "Out Of Range" << endl;
        return;
    }
    else if (index == 0)
    {
        removeAtHead();
    }
    else if (index == size - 1)
    {
        removeAtTail();
    }
    else {
        Node* current = first->next;


        for (int i = 1; i < index; i++)
        {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
    }
    size--;
}
int  DoublyLinkedList::retrieveAt(int index)
{
    if (index < 0 || index >= size) {
        cout << "Invalid Index.." << endl;
        return false;
    }
    Node* curr = first;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->item;
}
void DoublyLinkedList::replaceAt(int newElement, int index)
{
    if (index < 0 || index >= size) {
        cout << "Invalid index." << endl;
        return;
    }

    Node* current = first;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    current->item = newElement;
}
bool DoublyLinkedList::isExist(int element)
{
    Node* current = first;
    while (current != NULL) {
        if (current->item == element) {
            return true;
        }
        current = current->next;
    }
    return false;
}
bool DoublyLinkedList::isItemAtEqual(int element, int index)
{
    if (index < 0 || index >= size) {
        cout << "Invalid index." << endl;
        return false;
    }

    Node* current = first;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->item == element;
}
void DoublyLinkedList::swap(int firstItemIdx, int secondItemIdx)
{

    if (first == NULL) {
        return;
    }

    if (firstItemIdx == secondItemIdx) {
        return;
    }

    Node* ptr1 = first, * ptr2 = first;

    // find nodes at specified indices
    for (int i = 0; i < firstItemIdx && ptr1 != NULL; i++) {
        ptr1 = ptr1->next;
    }

    for (int i = 0; i < secondItemIdx && ptr2 != NULL; i++) {
        ptr2 = ptr2->next;
    }

    // check if either index is out of bounds
    if (ptr1 == NULL || ptr2 == NULL) {
        return;
    }

    // swap node addresses
    if (ptr1->prev != NULL) {
        ptr1->prev->next = ptr2;
    }
    else {
        first = ptr2;
    }

    if (ptr2->prev != NULL) {
        ptr2->prev->next = ptr1;
    }
    else {
        first = ptr1;
    }

    if (ptr1->next != ptr2) {
        ptr1->next->prev = ptr2;
    }

    if (ptr2->next != ptr1) {
        ptr2->next->prev = ptr1;
    }

    Node* temp = ptr1->next;
    ptr1->next = ptr2->next;
    ptr2->next = temp;

    temp = ptr1->prev;
    ptr1->prev = ptr2->prev;
    ptr2->prev = temp;

    return;
}
void DoublyLinkedList::reverse() {
    Node* curr = first;
    while (curr != NULL) {
        Node* temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }
    Node* temp = first;
    first = last;
    last = temp;
}
bool DoublyLinkedList::isEmpty() {
    return size == 0;
}
int  DoublyLinkedList::doubleLinkedListSize() {
    return size;
}
void DoublyLinkedList::clear() {
    while (first != nullptr) {
        Node* temp = first;
        first = first->next;
        delete temp;
    }
    last = nullptr;
    size = 0;
}
void DoublyLinkedList::forwardTraversal() {
    Node* curr = first;
    while (curr != nullptr) {
        cout << curr->item << " ";
        curr = curr->next;
    }
    cout << endl;
}
void DoublyLinkedList::backwardTraversal() {
    Node* curr = last;
    while (curr != nullptr) {
        cout << curr->item << " ";
        curr = curr->prev;
    }
    cout << endl;
}
void DoublyLinkedList::printList() {
    Node* current = first;
    while (current != nullptr) {
        cout << current->item << " ";
        current = current->next;
    }
    cout << endl;
}
auto DoublyLinkedList::getHead() {
    return first;
}
void DoublyLinkedList::append(int val) {
    Node* node = new Node(val);
    if (last == nullptr) {
        first = node;
        last = node;
    }
    else {
        last->next = node;
        node->prev = last;
        last = node;
    }
}


int main()
{
    // Test case 1
    DoublyLinkedList list1;
    list1.insertAtTail(0);
    list1.insertAtTail(3);
    list1.insertAtTail(1);
    list1.insertAtTail(0);
    list1.insertAtTail(4);
    list1.insertAtTail(5);
    list1.insertAtTail(2);
    list1.insertAtTail(0);
    list1.combineNodesBetweenZeros(list1.getHead());
    cout << "Test case 1: ";
    list1.printList(); // Expected output: 4 11


    // Test case 2
    DoublyLinkedList list2;
    list2.insertAtTail(0);
    list2.insertAtTail(1);
    list2.insertAtTail(0);
    list2.insertAtTail(3);
    list2.insertAtTail(0);
    list2.insertAtTail(2);
    list2.insertAtTail(2);
    list2.insertAtTail(0);
    list2.combineNodesBetweenZeros(list2.getHead());
    cout << "Test case 2: ";
    list2.printList(); // Expected output: 1 3 4
    cout << "--------------------------------------------------------------" << endl;

    DoublyLinkedList listt1;
    listt1.append(1);
    listt1.append(4);
    listt1.append(5);

    DoublyLinkedList listt2;
    listt2.append(1);
    list2.append(3);
    list2.append(4);

    DoublyLinkedList listt3;
    listt3.append(2);
    listt3.append(6);

    Node* lists[3] = { listt1.getHead(), listt2.getHead(), listt3.getHead()};

    DoublyLinkedList mergedList;
    mergedList.mergeKLists(lists, 3);

    Node* node = mergedList.getHead();
    while (node != nullptr) {
        cout << node->item << " ";
        node = node->next;
    }
    cout << endl;




    cout << "--------------------------------------------------------------" << endl;

    DoublyLinkedList myList;
    myList.insertAtTail(80);
    myList.insertAtTail(50);
    myList.insertAtTail(90);
    myList.insertAtTail(11);
    myList.insertAtTail(55);

    cout << "Forward Traversal: ";
    myList.forwardTraversal();

    cout << "Backward Traversal: ";
    myList.backwardTraversal();

    myList.removeAt(2);

    cout << "After removing element at index 2: ";
    myList.forwardTraversal();

    myList.insertAt(25, 2);

    cout << "After inserting 25 at index 2: ";
    myList.forwardTraversal();

    cout << "Element at index 3: " << myList.retrieveAt(3) << std::endl;

    myList.replaceAt(35, 3);

    cout << "After replacing element at index 3 with 35: ";
    myList.forwardTraversal();

    cout << "Is 20 in the list? " << myList.isExist(20) << std::endl;

    cout << "Is the element at index 2 equal to 30? " << myList.isItemAtEqual(30, 2) << std::endl;

    myList.swap(1, 3);

    cout << "After swapping elements at index 1 and 3: ";
    myList.forwardTraversal();

    myList.reverse();

    cout << "After reversing the list: ";
    myList.forwardTraversal();

    cout << "Size of list: " << myList.doubleLinkedListSize() << std::endl;

    myList.clear();

    cout << "After clearing the list: ";
    myList.forwardTraversal();

    return 0;
}
