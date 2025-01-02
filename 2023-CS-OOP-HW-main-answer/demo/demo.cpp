#include<iostream>

using namespace std;
struct Listnode {
	int val;
	Listnode* next;
	Listnode() : val(0), next(nullptr) {}
};
int main()
{
	Listnode* l3 = new Listnode;
	Listnode* p3 = l3;
	p3->val = 3;
	Listnode* newnode = new Listnode;
	p3->next = newnode;
	p3 = newnode;
	cout << p3 << endl;
	p3 = nullptr;
	cout << l3->next << endl;
	return 0;
}