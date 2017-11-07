#pragma once

#include <exception>
#include <stdexcept>
#include <utility>

template<typename T>
class smart_ptr {

public:
	smart_ptr() ;
	explicit smart_ptr(T*);
	smart_ptr(std::nullptr_t);
	
	smart_ptr(const smart_ptr&);
	smart_ptr(smart_ptr&&);
	
	smart_ptr& operator=(const smart_ptr&);
	smart_ptr& operator=(smart_ptr&&);
	
	~smart_ptr();
	
	T* operator->() const;
	T& operator*() const;
	T* get() const;
	
	bool empty() const;
	size_t use_count() const;
	void swap(smart_ptr&);
	
private:
	struct Reference_counter;
	T* ptr = nullptr;
	Reference_counter* ref_counter = nullptr;
	
	void release();

	
	// A special struct with the inner reference counter
	struct Reference_counter {
		size_t counter = 0;
		
		void add_reference(){  ++counter; }
		
		void release_reference(){ 
			if (counter < 1){ throw std::logic_error("Attempt to delete an empty pointer"); }
			--counter;
		}
	};

};


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                        Constructors
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 template<typename T>
smart_ptr<T>::smart_ptr() 
	: ptr(nullptr)
	, ref_counter(new Reference_counter())
{
}


 template<typename T>
smart_ptr<T>::smart_ptr(std::nullptr_t) 
	: ptr(nullptr)
	, ref_counter(new Reference_counter())
{
}

template<typename T>
smart_ptr<T>::smart_ptr(T* p) 
	: ptr(p)
	, ref_counter(new Reference_counter())
{
	ref_counter->add_reference();
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
               Copy and move constructors
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
template<typename T>
smart_ptr<T>::smart_ptr(const smart_ptr& p) 
	: ptr(p.ptr)
	, ref_counter(p.ref_counter)
{
	ref_counter->add_reference();
}


template<typename T>
smart_ptr<T>::smart_ptr(smart_ptr&& p)
	: ptr(p.ptr)
	, ref_counter(p.ref_counter)
 {
	p.ptr = nullptr;
	p.ref_counter = nullptr;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
               Copy and move assignments
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

template<typename T>
smart_ptr<T>& smart_ptr<T>::operator=(const smart_ptr& p){
	if (&p == this || ptr == p.ptr){
		return *this;
	}
	
	if (!empty()){  release(); }
	
	p.ref_counter->add_reference();
	ref_counter = p.ref_counter;
	ptr = p.ptr;
	
	return *this;
}


template<typename T>
smart_ptr<T>& smart_ptr<T>::operator=(smart_ptr&& p){
	if (&p == this || ptr == p.ptr){
		return *this;
	}
	
	if (!empty()){ 	release(); }
	
	ptr = p.ptr;
	ref_counter = p.ref_counter;
	p.ptr = nullptr;
	p.ref_counter = nullptr;

	return *this;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                          Destructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
template<typename T>
smart_ptr<T>::~smart_ptr(){
	if (ref_counter){
		if (ref_counter->counter > 0){
			ref_counter->release_reference();
		}
		if (ref_counter->counter == 0){
			delete ptr;
			ptr = nullptr;
			delete ref_counter;
			ref_counter = nullptr;
		}
	}
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        Methods to extract a raw pointer
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

template<typename T>
T* smart_ptr<T>::operator->() const {
	return ptr;
}

template<typename T>
T& smart_ptr<T>::operator*() const {
	if (ptr == nullptr){ throw std::logic_error("A pointer is empty"); }
	return *ptr;
}

template<typename T>
T* smart_ptr<T>::get() const {
	return ptr;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                      Auxiliary methods
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

template<typename T>
bool smart_ptr<T>::empty() const {
	return !use_count();
}


template<typename T>
size_t smart_ptr<T>::use_count() const {
	if (ref_counter == nullptr){
		return 0;
	}
	return ref_counter->counter;
}


template<typename T>
void smart_ptr<T>::swap(smart_ptr& obj){
	std::swap(ptr, obj.ptr);
	std::swap(ref_counter, obj.ref_counter);
}


template<typename T>
void smart_ptr<T>::release(){
	if (ref_counter->counter == 1){
		delete ref_counter;
		delete ptr;
		ref_counter = nullptr;
		ptr = nullptr;
	}
	else {
		ref_counter->release_reference();
	}
}
