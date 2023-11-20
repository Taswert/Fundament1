#include <iostream>
using namespace std;
struct Node
{
	int data;
	Node* next;
};

Node* createNode(int data)
{
	Node* newNode = new Node;
	newNode->next = nullptr;
	newNode->data = data;
	return newNode;
}

// Node clearing. Removes all elements and pointers from the node.
void clear(Node*& self)
{
	if (self)
	{
		Node* current = nullptr;
		if (self->next == nullptr)
		{
			current = self->next;
			delete self;
			self = current;
		}

		else
		{
			current = self->next;
			while (current != nullptr)
			{
				delete self;
				self = current;
				current = current->next;
			}
		}
	}
}

// Adds elements decrementally
void addElement(Node*& self, int data)
{
	if (self)
	{
		if (self->data >= data)
		{
			Node* current = self;
			bool quit = 0;
			while (!quit)
			{
				if (current->next)
				{
					if (current->next->data > data)
						current = current->next;
					else quit = 1;
				}
				else quit = 1;
			}

			Node* newNode = nullptr;
			if (current->next) newNode = current->next;

			current->next = createNode(data);
			current->next->next = newNode;
		}
		else 
		{
			Node* current = self;
			self = new Node;
			self->data = data;
			self->next = current;
		}
	}
	else
	{
		self = createNode(data);
	}
}

// Removes all occurrences of the specified element.
void deleteElement(Node*& self, int data)
{
	if (self)
	{
		Node* current = self;
		while (self && self->data == data)
		{
			current = current->next;
			delete(self);
			self = current;
		}
		if (self)
		{
			while (current->next != nullptr)
			{
				if (current->next->data == data)
				{
					Node* deletionNode = current->next;
					current->next = current->next->next;
					delete(deletionNode);
				}
				else current = current->next;
			}
		}
	}
}

// Returns element address.
Node* findElement(Node* self, int data)
{
	if (self)
	{
		while (self->next)
		{
			if (self->data == data) return self;
			else self = self->next;
		}
		if (self->data == data) return self;
		else self = self->next;
	}
	return nullptr;
}

// Writes all elements
void writeNode(Node* self)
{
	if (self)
	{
		cout << self << "(" << self->data << ")";
		while (self->next != nullptr)
		{
			self = self->next;
			cout << "->" << self << "(" << self->data << ")";
		}
		self = self->next;
		cout << "->";
	}
	cout << self << "(NULL)" << endl;
}

// Returns list that has difference of two lists
Node* difference(Node* list1, Node* list2)
{
	Node* newList = nullptr;
	if (list1 && list2)
	{
		Node* current1 = list1;
		Node* current2 = list2;
		
		while (current1)
		{
			if (!findElement(current2, current1->data)) {
				addElement(newList, current1->data);
			}
			current1 = current1->next;
		}
	}
	return newList;
}



int main()
{
	const int n = 3;
	Node* head1 = nullptr;
	Node* head2 = nullptr;
	Node* head3 = nullptr;

	for (int i = 1; i < 6; i++)
	{
		addElement(head1, i);
	}

	for (int i = 1; i < 3; i++)
	{
		addElement(head2, i);
	}
	head3 = difference(head1, head2);


	writeNode(head1);
	writeNode(head2);
	writeNode(head3);
	writeNode(difference(head1, head3));

	return 0;
}
