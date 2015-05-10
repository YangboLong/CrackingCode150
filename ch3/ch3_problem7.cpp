#include <iostream>

struct Node {
	int key;
	Node* prev;
	Node* next;
};
class AnimalQueue {
public:
	AnimalQueue() : head(NULL), tail(NULL), locator(NULL) { }
	void enqueue(Node&);
	int dequeueAny();
	int dequeueDog();
	int dequeueCat();
private:
	Node* head;
	Node* tail;
	Node* locator;
};
void AnimalQueue::enqueue(Node &node) {
	if(head == NULL) {
		head = &node;
		tail = head;
	}
	else if(head == tail) {
		node.prev = head;
		head->next = &node;
		tail = &node;
	}
	else {
		tail->next = &node;
		node.prev = tail;
		tail = &node;
	}
}
int AnimalQueue::dequeueAny() {
	if(head == NULL) {
		std::cerr << "no animal to adopt" << std::endl;
		exit(EXIT_FAILURE);
	}
	else if(head == tail) {
		int key = head->key;
		head = NULL;
		tail = NULL;
		return key;
	}
	else {
		int key = head->key;
		head = head->next;
		head->prev = NULL;
		return key;
	}
}
int AnimalQueue::dequeueCat() {
	if(head == NULL) {
		std::cerr << "no cat to adopt" << std::endl;
		exit(EXIT_FAILURE);
	}
	locator = head;
	while(locator->key % 2 == 0) {
		locator = locator->next;
		if(locator == NULL) {
			std::cerr << "no cat to adopt" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	int key = locator->key;
	if(locator->prev != NULL)
		locator->prev->next = locator->next;
	else { // locator is head
		head = locator->next;
		head->prev = NULL;
	}
	if(locator->next != NULL)
		locator->next->prev = locator->prev;
	else { // locator is tail
		tail = locator->prev;
		tail->next = NULL;
	}
	locator = head;
	return key;
}
int AnimalQueue::dequeueDog() {
	if(head == NULL) {
		std::cerr << "no dog to adopt" << std::endl;
		exit(EXIT_FAILURE);
	}
	locator = head;
	while(locator->key % 2 != 0) {
		locator = locator->next;
		if(locator == NULL) {
			std::cerr << "no dog to adopt" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	int key = locator->key;
	if(locator->prev != NULL)
		locator->prev->next = locator->next;
	else { // locator is head
		head = locator->next;
		head->prev = NULL;
	}
	if(locator->next != NULL)
		locator->next->prev = locator->prev;
	else { // locator is tail
		tail = locator->prev;
		tail->next = NULL;
	}
	locator = head;
	return key;
}

int main()
{
	AnimalQueue animals; // odd key animal is cat, even dog
	Node animal1 = {4, NULL, NULL};
	animals.enqueue(animal1);
	Node animal2 = {5, NULL, NULL};
	animals.enqueue(animal2);
	Node animal3 = {2, NULL, NULL};
	animals.enqueue(animal3);
	Node animal4 = {1, NULL, NULL};
	animals.enqueue(animal4);
	Node animal5 = {7, NULL, NULL};
	animals.enqueue(animal5);

	int dog1 = animals.dequeueAny();
	int dog2 = animals.dequeueDog();
	int cat1 = animals.dequeueCat();

	return 0;
}