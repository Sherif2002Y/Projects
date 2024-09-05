#include <iostream>
using namespace std;
struct nodeType {
	int info;
	nodeType* next;
	nodeType(int x) : info(x), next(nullptr) {}
};
class SingleLinkedList {
private:
	
	nodeType* first;
	nodeType* last;
	int length;

public:
	SingleLinkedList() {
		first = NULL;
		last = NULL;
		length = 0;
	}

	void insertAtHead(int);
	void insertAtTail(int);
	void insertAt(int, int );
	void removeAtHead();
	void removeAtTail();
	void removeAt(int );
	int retrieveAt(int );
	void replaceAt(int , int );
	bool isExist(int  );
	bool isItemAtEqual(int, int);
	void swap(int , int ); // swap two nodes without swapping data.
	bool isEmpty();
	int linkedListSize();
	void clear();
	void print();
	void listSize(int);
	void insert(nodeType*head, int);
	nodeType* CombineNodes(nodeType* head) {
		//First value is zero, so we can delete that
		if (head->info == 0)
			head = head->next;

		nodeType* main_head = head; // main_head will contain result(sum) of merged nodes
		nodeType* temp = head; // temp will help to traverse the linked list
		int combine = 0;

		while (temp != NULL) {
			if (temp->info != 0) {
				combine += temp->info; //node is not 0, so we sum 
				temp = temp->next;//and move forward
			}
			else {
				main_head->info = combine; //we have the sum upto this point, we now update main_head's value
				main_head->next = temp->next; //main_head no need to point to its original next element, it will point to the next of temp now
				temp = temp->next;
				main_head = main_head->next;
				combine = 0;
			}
		}

		return head;
	}

	
	static nodeType* mergeTwo(nodeType* l1, nodeType* l2) {
		nodeType dummy(0);
		nodeType* tail = &dummy;

		while (l1 != nullptr && l2 != nullptr) {
			if (l1->info <= l2->info) {
				tail->next = l1;
				l1 = l1->next;
			}
			else {
				tail->next = l2;
				l2 = l2->next;
			}
			tail = tail->next;
		}

		tail->next = (l1 != nullptr) ? l1 : l2;

		return dummy.next;
	}

	static nodeType* mergeK(SingleLinkedList* lists, int k) {
		if (k == 0) return nullptr;
		int interval = 1;
		while (interval < k) {
			for (int i = 0; i < k - interval; i += interval * 2) {
				lists[i].first = mergeTwo(lists[i].first, lists[i + interval].first);
			}
			interval *= 2;
		}
		return lists[0].first;
	}
};
void SingleLinkedList::insertAtHead(int item)
{
	nodeType* newNode = new nodeType(item);
	newNode->info = item;
	if (length == 0) {
		first = last = newNode;
		newNode->next = NULL;
	}
	else {
		newNode->next = first;
		first = newNode;
	}
	length++;
}
void SingleLinkedList::insertAtTail(int item)
{
	nodeType* newNode = new nodeType(item);
	newNode->info = item;
	if (length == 0) {
		first = last = newNode;
		newNode->next = NULL;
	}
	else {
		last->next = newNode;
		newNode->next = NULL;
		last = newNode;
	}
	length++;
}
void SingleLinkedList::insertAt(int loc, int item)
{
	if (loc < 0 || loc > length)
		cout << "ERROR: Out of range" << endl;
	else
	{
		nodeType* newNode = new nodeType(item);
		newNode->info = item;
		if (loc == 0) //insert at the begining
			insertAtHead(item);
		else if (loc == length) //insert at the end;
			insertAtTail(item);
		else
		{
			nodeType* current = first;
			for (int i = 1; i < loc; i++)
				current = current->next;

			newNode->next = current->next;
			current->next = newNode;
			length++;
		}

	}
}
void SingleLinkedList::removeAtHead()
{
	if (length == 0)
		cout << "ERROR: EMPTY LIST" << endl;
	else if (length == 1)
	{
		delete first;
		last = first = NULL;
		length--;
	}
	else
	{
		nodeType* current = first;
		first = first->next;
		delete current;
		length--;
	}
}
void SingleLinkedList::removeAtTail()
{
	if (length == 0)
		cout << "ERROR: EMPTY LIST" << endl;
	else if (length == 1)
	{
		delete first;
		last = first = NULL;
		length--;
	}
	else
	{
		nodeType* current = first->next;
		nodeType* trailCurrent = first;
		while (current != last)
		{
			trailCurrent = current;
			current = current->next;
		}
		delete current;
		trailCurrent->next = NULL;
		last = trailCurrent;
		length--;
	}
}
void SingleLinkedList::removeAt(int loc)
{
	if (loc < 0 || loc >= length)
		cout << "ERROR: Out of range" << endl;
	else
	{
		nodeType* current, * trailCurrent;
		if (loc == 0)
		{
			current = first;
			first = first->next;
			delete current;
			length--;
			if (length == 0)
				last = NULL;
		}
		else
		{
			current = first->next;
			trailCurrent = first;
			for (int i = 1; i < loc; i++)
			{
				trailCurrent = current;
				current = current->next;
			}

			trailCurrent->next = current->next;
			if (last == current) //delete the last item
				last = trailCurrent;
			delete current;
			length--;
		}
	}
}
int SingleLinkedList::retrieveAt(int index)
{
	nodeType* current = first;
	int count=0;

	while (current!=NULL)
	{
		if (count==index)
		{
			return (current->info);
		}
		count++;
		current = current->next;
	}
	cout << "The index which enter not found ...!" << endl;
}
void SingleLinkedList::replaceAt(int data, int index)
{
	nodeType* curr = first;
	int i = 0;
	while (curr != nullptr && i < index) {
		curr = curr->next;
		i++;
	}
	if (curr != nullptr) {
		curr->info = data;
	}
}
bool SingleLinkedList::isExist(int val)
{
	nodeType* temp = first;
	while (temp != NULL)
	{
		if (temp->info == val)
			return true;
		temp = temp->next;
		cout << "is Exist..!" << endl;

	}
	cout << "Not Found ..!" << endl;
	return false;
	cout << "isn't Exist..!" << endl;
}
bool SingleLinkedList::isItemAtEqual(int element, int index) {
	if (first == NULL) {
		// empty list
		return false;
		cout << "The ItemAt not Equal..!" << endl;
	}
	nodeType* curr = first;
	int i = 0;
	while (curr != NULL && i < index) {
		curr = curr->next;
		i++;
	}
	if (curr == NULL) {
		// index out of bounds
		return false;
		cout<<"Not Found.."<<endl;
	}
	return curr->info == element;
}
void SingleLinkedList::swap(int firstItemIdx, int secondItemIdx) {
	if (first == NULL || firstItemIdx == secondItemIdx) {
		// empty list, or same index
		return;
	}
	nodeType* prev1 = NULL;
	nodeType* curr1 = first;
	int i = 0;
	while (curr1 != NULL && i < firstItemIdx) {
		prev1 = curr1;
		curr1 = curr1->next;
		i++;
	}
	if (curr1 == NULL) {
		// first index out of bounds
		return;
	}

	nodeType* prev2 = NULL;
	nodeType* curr2 = first;
	i = 0;
	while (curr2 != NULL && i < secondItemIdx) {
		prev2 = curr2;
		curr2 = curr2->next;
		i++;
	}
	if (curr2 == NULL) {
		// second index out of bounds
		return;
	}

	if (prev1 != NULL) {
		prev1->next = curr2;
	}
	else {
		first = curr2;
	}

	if (prev2 != NULL) {
		prev2->next = curr1;
	}
	else {
		first = curr1;
	}

	nodeType* temp = curr2->next;
	curr2->next = curr1->next;
	curr1->next = temp;
}
bool SingleLinkedList::isEmpty()
{
	return (length == 0);
	cout << "Is empty ..!" << endl;
}
int SingleLinkedList::linkedListSize()
{
	return length;
}
void SingleLinkedList::clear()
{
	nodeType* current;
	while (first != NULL)
	{
		current = first;
		first = first->next;
		delete current;
	}
	last = NULL;
	length = 0;
}
void SingleLinkedList::print()
{
	nodeType* current = first;
	while (current != NULL)
	{
		cout << current->info<<" ";
		current = current->next;
	}
	cout << endl;
}
void SingleLinkedList::insert(nodeType* head, int element)//Use to combine nodes between zeros 
{
	// Traverse the linked list to find the last node
	nodeType* temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}

	// Create a new node and insert it after the last node
	nodeType* newNode = new nodeType(element);
	newNode->info = element;
	newNode->next = NULL;
	temp->next = newNode;
}

int main() {

	SingleLinkedList list;
	nodeType* head = new nodeType(0);

	head->next = NULL;
	head->info = 0;
	list.insert(head, 1);
	list.insert(head, 0);
	list.insert(head, 3);//	List: [0, 3, 1, 0, 4, 5, 2, 0],
	list.insert(head, 0);//List: [0, 1, 0, 3, 0, 2, 2, 0],
	list.insert(head, 2);
	list.insert(head, 2);
	list.insert(head, 0);
	cout << "Result the combine nodes :" << endl;

 	nodeType* mergedList = list.CombineNodes(head);

	// Print the merged linked list
	nodeType* temp = mergedList;
	while (temp != NULL) {
		cout << temp->info << " ";
		temp = temp->next;
	}
	cout << endl;


	//------------------------------------------------------------------------------\\

	cout << "----------------------------------------------------------" << endl;
	SingleLinkedList list1;
	list1.insertAtHead(5);
	list1.insertAtHead(3);
	list1.insertAtHead(1);

	SingleLinkedList list2;
	list2.insertAtHead(6);
	list2.insertAtHead(4);
	list2.insertAtHead(2);

	SingleLinkedList list3;
	list3.insertAtHead(9);
	list3.insertAtHead(7);

	SingleLinkedList list4;
	list4.insertAtHead(8);

	SingleLinkedList lists[] = { list1, list2, list3, list4 };
	int k = 4;

	nodeType* merged = SingleLinkedList::mergeK(lists, k);
	while (merged != nullptr) {
		cout << merged->info << " ";
		merged = merged->next;
	}
	cout << endl;

	cout << "----------------------------------------------------------" << endl;

	SingleLinkedList myList;

	// Insert elements at the head and tail of the list
	myList.insertAtHead(1);
	myList.insertAtTail(2);
	myList.insertAtHead(0);
	myList.insertAtTail(3);

	cout << " Print the contents of the list" << endl;
	myList.print(); 
	cout << "----------------------------" << endl;
	cout << "Insert an element at a specific index" << endl;
	myList.insertAt(5, 2);
	myList.print(); 
	cout << "----------------------------" << endl;

	cout << " Remove an element from the head and tail of the list" << endl;
	myList.removeAtHead();
	myList.removeAtTail();
	myList.print(); 
	cout << "----------------------------" << endl;

	cout << " Remove an element from a specific index" << endl;
	myList.removeAt(1);
	myList.print(); 
	cout << "----------------------------" << endl;

	cout << "Replace an element at a specific index" << endl;
	myList.replaceAt(3, 1);
	myList.print(); 
	cout << "----------------------------" << endl;

	cout<<"Check if an element exists in the list"<<endl;
	cout << myList.isExist(1) << endl; // Output: 1
	cout << myList.isExist(5) << endl; // Output: 0
	cout << "----------------------------" << endl;

	cout<<"check if an element at a specific index is equal to a given element"<<endl;
	cout << myList.isItemAtEqual(1, 0) << endl; 
	cout << myList.isItemAtEqual(3, 1) << endl; 
	cout << myList.isItemAtEqual(5, 1) << endl; 
	cout << "----------------------------" << endl;

	cout << "Swap two nodes in the list" << endl;
	myList.swap(0, 1);
	myList.print();  
	cout << "----------------------------" << endl;

	cout << "Clear the list" << endl;
	myList.clear();
	myList.print(); // Output:
	cout << "----------------------------" << endl;


	
}
