//#include "ui.h"
#include "seq.h"
#include "secondary-func.h"

int main() {
	//UI();
	int arr[6] = {1, 2, 98, 4, 5, 7};
	ListSequence<int> item = ListSequence<int>(arr, 6);
	ListSequence<int>::Iterator c = item.Count();
	ListSequence<int>::Iterator c2 = item.Count();
	std::cout << c.CurIndex() << std::endl;
	std::cout << *c << std::endl;
	c.End();
	c--;
	std::cout << c.CurIndex() << std::endl;
	std::cout << *c << std::endl;
	c.Begin();
	c++;
	std::cout << c.CurIndex() << std::endl;
	std::cout << *c << std::endl;
	c2+7;
	std::cout << *c2 << std::endl;
	std::cout << (c == c2) << std::endl;
	c.End();
	std::cout << c.CurIndex() << std::endl;
	std::cout << *c << std::endl;
	c--;
	std::cout << c.CurIndex() << std::endl;
	std::cout << *c << std::endl;
	/*LinkedList<int> dynarr = LinkedList<int>(arr, 6);
	int arr2[6] = {1, 4, 98, 4, 5, 6};
	LinkedList<int> list = LinkedList<int>(arr2, 6);
	LinkedList<int>::Iterator count = dynarr.Count();
	count++;
	LinkedList<int>::Iterator count2 = LinkedList<int>::Iterator(count);
	count+3;
	count2++;
	std::cout << (count == count2) << std::endl;

	std::cout << *count2 << std::endl;*/
	return 0;
}