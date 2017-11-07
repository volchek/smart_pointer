#include <iostream>
#include "smart_ptr.h"
#include <iomanip>


template<typename T>
void print_info(const char* text, smart_ptr<T>& sm){
	std::cout << text << std::endl;
	std::cout << "\tReference counter: " << sm.use_count() << "\n";
	std::cout << "\tIs empty: " << std::boolalpha <<  sm.empty() << "\n";
	try {
		std::cout << "\tSmart pointer value: " << *sm << "\n";
	}
	catch(std::exception& ex){
		std::cout << ex.what() << std::endl;
	}
}

void test_smart_ptr_1(){
	std::cout << "\n---- Test 1 -----\n";
	smart_ptr<int> sm;
	print_info("Smart pointer with a default constructor", sm);
	std::cout << "\n\n";
}

void test_smart_ptr_2(){
	std::cout << "\n---- Test 2 -----\n";
	smart_ptr<int> sm(nullptr);
	print_info("Smart pointer with nullptr value", sm);
	std::cout << "\n\n";
}

void test_smart_ptr_3(){
	std::cout << "\n---- Test 3 -----\n";
	int* first_ptr = new int;
	*first_ptr = 10;
	std::cout << "Row pointer value: " << *first_ptr << std::endl;
	smart_ptr<int> sm = smart_ptr<int>(first_ptr); 
	print_info("Smart pointer with an explicit constructor", sm);
	std::cout << "\n\n";
}

void test_smart_ptr_4(){
	std::cout << "\n---- Test 4 -----\n";
	smart_ptr<int> sm(new int(5));
	print_info("First smart pointer before moving of a new value", sm);
	smart_ptr<int> sm1 = std::move(sm);
	print_info("First smart pointer after moving of a new value", sm);
	print_info("Second smart pointer after moving of a new value", sm1);
	std::cout << "\n\n";
}

void test_smart_ptr_5(){
	std::cout << "\n---- Test 5 -----\n";
	smart_ptr<int> sm(new int(42));
	print_info("First smart pointer before copying of a new value", sm);
	smart_ptr<int> sm1 = sm;
	print_info("First smart pointer after copying of a new value", sm);
	print_info("Second smart pointer after copying of a new value", sm1);
	std::cout << "\n\n";
}

void test_smart_ptr_6(){
	std::cout << "\n---- Test 6 -----\n";
	smart_ptr<int> sm(new int(42));
	smart_ptr<int> sm1 = sm;
	smart_ptr<int> sm2(new int(15));
	print_info("First smart pointer before copying of a new value", sm);
	print_info("Second smart pointer before copying of a new value", sm1);
	print_info("Third smart pointer before copying of a new value", sm2);
	sm2 = sm1;
	print_info("First smart pointer after copying of a new value", sm);
	print_info("Second smart pointer after copying of a new value", sm1);
	print_info("Third smart pointer after copying of a new value", sm2);
	std::cout << "\n\n";
}

void test_smart_ptr_7(){
	std::cout << "\n---- Test 7 -----\n";
	smart_ptr<int> sm(new int(42));
	smart_ptr<int> sm1 = sm;
	smart_ptr<int> sm2 = sm1;
	smart_ptr<int> sm3 = sm1;
	smart_ptr<int> sm4(new int(10));
	print_info("First smart pointer before moving of a new value", sm);
	print_info("Last smart pointer before moving of a new value", sm4);
	
	sm4 = std::move(sm);
	print_info("First smart pointer after moving of a new value", sm);
	print_info("Last smart pointer after moving of a new value", sm4);
	std::cout << "\n\n";
}

void test_smart_ptr_8(){
	std::cout << "\n---- Test 8 -----\n";
	smart_ptr<int> sm(new int(42));
	smart_ptr<int> sm1 = sm;
	smart_ptr<int> sm2 = sm1;
	smart_ptr<int> sm3 = sm1;
	smart_ptr<int> sm4(new int(10));
	print_info("First smart pointer before moving of a new value", sm);	
	print_info("Last smart pointer before moving of a new value", sm4);
	
	sm = std::move(sm4);
	print_info("First smart pointer after moving of a new value", sm);
	print_info("First smart pointer after moving of a new value", sm1);
	print_info("First smart pointer after moving of a new value", sm2);
	print_info("First smart pointer after moving of a new value", sm3);
	print_info("Last smart pointer after moving of a new value", sm4);
	std::cout << "\n\n";
}

void test_smart_ptr_9(){
	std::cout << "\n---- Test 9 -----\n";
	struct Foo {
		int value = 15;
		char code = 'a';
	};
	
	smart_ptr<Foo> sm(new Foo());
	std::cout << "A simple struct object\n";
	std::cout << "\tSmart pointer value: " << sm->value << " - " << sm->code << std::endl;
	std::cout << "\tSmart pointer value: " << (*sm).value << " - " << (*sm).code << std::endl;
	sm->value = 22;
	sm->code = 'b';
	std::cout << "\tSmart pointer value: " << (*sm).value << " - " << (*sm).code << std::endl;
	std::cout << "\n\n";
}

void test_smart_ptr_10(){
	std::cout << "\n---- Test 10 -----\n";
	smart_ptr<int> sm(new int(42));
	smart_ptr<int> sm1(new int(15));
	print_info("First smart pointer before swaping", sm);
	print_info("First smart pointer before swaping", sm1);
	sm.swap(sm1);
	print_info("First smart pointer after swaping", sm);
	print_info("First smart pointer after swaping", sm1);
	std::cout << "\n\n";
}

void test_smart_ptr_11(){
	std::cout << "\n---- Test 11 -----\n";
	smart_ptr<int> sm(new int(42));
	smart_ptr<int> sm1;
	print_info("First smart pointer before swaping with an empty smart pointer", sm);
	print_info("First smart pointer before swaping with an empty smart pointer", sm1);
	sm.swap(sm1);
	print_info("First smart pointer after swaping with an empty smart pointer", sm);
	print_info("First smart pointer after swaping with an empty smart pointer", sm1);
	std::cout << "\n\n";
}

void test_smart_ptr_12(){
	std::cout << "\n---- Test 12 -----\n";
	smart_ptr<int> sm(new int(42));
	smart_ptr<int> sm1 = sm;
	smart_ptr<int> sm2 = sm1;
	smart_ptr<int> sm3(new int(10));
	print_info("First smart pointer", sm);
	print_info("Second smart pointer", sm1);
	print_info("Third smart pointer", sm2);
	print_info("Fourth smart pointer", sm3);
	sm2 = sm3;
	print_info("First smart pointer", sm);
	print_info("Second smart pointer", sm1);
	print_info("Third smart pointer", sm2);
	print_info("Fourth smart pointer", sm3);
	sm1 = sm2;
	print_info("First smart pointer", sm);
	print_info("Second smart pointer", sm1);
	print_info("Third smart pointer", sm2);
	print_info("Fourth smart pointer", sm3);
	std::cout << "\n\n";
}

template<typename T>
void test(T p){
	auto sm2(p);
	auto sm3(p);
	std::cout << "\tSecond smart_ptr value: " << *sm2 << "\n";
	std::cout << "\tThird smart_ptr value: " << *sm3 << "\n";
}

void test_smart_ptr_13(){
	std::cout << "\n---- Test 13 -----\n";
	int* p = new int;
	*p = 42;
	smart_ptr<int> sm1(p);
	print_info("First smart pointer before passing as argument", sm1);
	std::cout << "\tSmart pointer value: " << *sm1 << std::endl;
	test(p);
	print_info("First smart pointer after passing as argument", sm1);
	std::cout << "\tRaw pointer value: " << *p << std::endl;
}

void test_smart_ptr_14(){
	std::cout << "\n---- Test 14 -----\n";
	int* p = new int;
	*p = 42;
	smart_ptr<int> sm1(p);
	print_info("First smart pointer before passing as argument", sm1);
	std::cout << "\tSmart pointer value: " << *sm1 << std::endl;
	test(sm1);
	print_info("First smart pointer after passing as argument", sm1);
	std::cout << "\tRaw pointer value: " << *p << std::endl;
}

void test_my_smart_ptr(){
	test_smart_ptr_1();
	test_smart_ptr_2();
	test_smart_ptr_3();
	test_smart_ptr_4();
	test_smart_ptr_5();
	test_smart_ptr_6();
	test_smart_ptr_7();
	test_smart_ptr_8();
	test_smart_ptr_9();
	test_smart_ptr_10();
	test_smart_ptr_11();
	test_smart_ptr_12();
	test_smart_ptr_13();
	test_smart_ptr_14();
}


int main(){
	test_my_smart_ptr();
	
	return 0;
}