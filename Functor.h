#pragma once

#ifndef FUNCTOR_H
#define FUNCTOR_H
#include <initializer_list>


#ifndef OBJECT_H
#define OBJECT_H


// Object
typedef unsigned char Byte;
typedef int Int;
typedef unsigned int Uint;
typedef double Double;
typedef void* LPVoid;
typedef unsigned char* LPByte;
typedef char* LPChar;
typedef const char* LPCChar;

template <typename ... Tx> using LPActionTxA = void(*)(Tx ...);
template <typename Tout, typename ... Tx> using LPFunctionTxA = Tout(*)(Tx ...);

typedef class OBJECT_t
{
	union
	{
		Byte uByte;
		Int uInt;
		Uint uUint;
		Double uDouble;
		LPVoid uPtr;
		LPCChar uCcharPtr;
		LPChar uCharPtr;
	};

	enum TYPE_e
	{
		eNullobj = 0,
		eByte,
		eInt,
		eUint,
		eDouble,
		eLPVoid,
		eLPCChar,
		eLPChar
	};

public:
	

	OBJECT_t()          : uInt(0), type(0), valid(false) { }             // NOLINT(cppcoreguidelines-pro-type-member-init)
	OBJECT_t(Int v)     : uInt(v), type(eInt), valid(true) { }           // NOLINT(cppcoreguidelines-pro-type-member-init)
	OBJECT_t(LPCChar v) : uCcharPtr(v), type(eLPCChar), valid(true) { }  // NOLINT(cppcoreguidelines-pro-type-member-init)
	OBJECT_t(LPChar v)  : uCharPtr(v), type(eLPChar), valid(true) { }    // NOLINT(cppcoreguidelines-pro-type-member-init)
	OBJECT_t(LPVoid v)  : uPtr(v), type(eLPVoid), valid(true) { }        // NOLINT(cppcoreguidelines-pro-type-member-init)
	OBJECT_t(Double v)  : uDouble(v), type(eDouble), valid(true) { }     // NOLINT(cppcoreguidelines-pro-type-member-init)
	OBJECT_t(Uint v)    : uUint(v), type(eUint), valid(true) { }         // NOLINT(cppcoreguidelines-pro-type-member-init)   
	OBJECT_t(Byte v)    : uByte(v), type(eByte), valid(true) { }         // NOLINT(cppcoreguidelines-pro-type-member-init)

	OBJECT_t& operator=(const OBJECT_t obj)
	{
		switch (obj.type)
		{
		case eByte: return *this = static_cast<Byte>(obj);
		case eInt: return *this = static_cast<Int>(obj);
		case eUint: return *this = static_cast<Uint>(obj);
		case eDouble: return *this = static_cast<Double>(obj);
		case eLPVoid: return *this = static_cast<LPVoid>(obj);
		case eLPCChar: return *this = static_cast<LPCChar>(obj);
		case eLPChar: return *this = static_cast<LPChar>(obj);
		}
		return *this;
	}
	OBJECT_t& operator=(const Byte v)
	{
		this->uByte = v;
		this->type = eByte;
		this->valid = true;
		return *this;
	}
	OBJECT_t& operator=(const Int v)
	{
		this->uInt = v;
		this->type = eInt;
		this->valid = true;
		return *this;
	}
	OBJECT_t& operator=(const Uint v)
	{
		this->uUint = v;
		this->type = eUint;
		this->valid = true;
		return *this;
	}
	OBJECT_t& operator=(const Double v)
	{
		this->uDouble = v;
		this->type = eDouble;
		this->valid = true;
		return *this;
	}
	OBJECT_t& operator=(const LPVoid v)
	{
		this->uPtr = v;
		this->type = eLPVoid;
		this->valid = true;
		return *this;
	}
	OBJECT_t& operator=(const LPChar v)
	{
		this->uCharPtr = v;
		this->type = eLPChar;
		this->valid = true;
		return *this;
	}
	OBJECT_t& operator=(const LPCChar v)
	{
		this->uCcharPtr = v;
		this->type = eLPCChar;
		this->valid = true;
		return *this;
	}

	operator Int()     const { return uInt; }
	operator Byte()    const { return uByte; }
	operator Uint()    const { return uUint; }
	operator Double()  const { return uDouble; }
	operator LPVoid()  const { return uPtr; }
	operator LPChar()  const { return uCharPtr; }
	operator LPCChar() const { return uCcharPtr; }



	bool IsEquals(OBJECT_t other)
	{
		if (this->type == other.type)
		{
			switch (this->type)
			{
			case eByte    : return (Byte)   *this == (Byte)other;
			case eInt     : return (Int)    *this == (Int)other;
			case eUint    : return (Uint)   *this == (Uint)other;
			case eDouble  : return (Double) *this == (Double)other;
			case eLPVoid  : return (LPVoid) *this == (LPVoid)other;
			case eLPCChar : return (LPCChar)*this == (LPCChar)other;
			case eLPChar  : return (LPChar) *this == (LPChar)other;
			}
		}
		return false;
	}



	bool IsValid() const
	{
		return valid;
	}

	template<typename T>
	operator T& () { return *((T*)uPtr); }

private:
	Byte type;
	bool valid;
}Object;
#endif


// The default data structure, feel free to create/use your own data structure, it NEEDS to behave like a stack structure
// Type of data to be stored: Object ( typedef above )
//
// Functions required:
// Object Pop(); 
// ctor(std::initializer_list<T> vals);
//
// define your type as "ObjectStackA" BEFORE include this header if wish to use your own type
// NOT RECOMENDED/TESTED, change the struct at your risk


#ifndef ObjectStackA
#define ObjectStackA ARRAY_t<Object>
#endif


#ifndef MYARRAY_H
#define MYARRAY_H
template<typename T>
class ARRAY_t
{
public:
	ARRAY_t() {
		_size = 0;
		_ptr = 0;
		_maxSize = 32;
		_isAlloc = 0;
		tryAlloc();
	}

	ARRAY_t(std::initializer_list<T> vals) {
		_size = 0;
		_ptr = 0;
		_maxSize = vals.size();
		_isAlloc = 0;
		tryAlloc();
		for (auto& v : vals) {
			push_back(v);
		}
	}

	T* begin() const {
		return _data;
	}

	T* end() const {
		return &_data[_ptr];
	}

	constexpr int count() const {
		return _ptr;
	}

	void tryReAlloc(int newSize) {
		void* mBlock = (T*)calloc(this->_maxSize, sizeof(T));
		memcpy(mBlock, _data, sizeof(T));
		_maxSize = newSize;

		_data = (T*)calloc(this->_maxSize, sizeof(T));
		memcpy(_data, mBlock, sizeof(T));
	}

	void tryAlloc() {
		if (!_isAlloc) {
			this->_data = (T*)calloc(this->_maxSize, sizeof(T));
			_isAlloc = 1;
		}
		else {
			tryReAlloc(this->_maxSize * (this->_maxSize / 2));
		}
	}

	void tryDealloc() {
		if (_isAlloc) {
			free(this->_data);
			_isAlloc = 0;
		}
	}

	void push_back(const T& t) {
		_data[_ptr++] = t;
	}

	T& pop_back() {
		return this->_data[--_ptr];
	}

	T& get(int index) {
		if (index >= _maxSize){
			tryReAlloc(this->_maxSize * (this->_maxSize / 2));
		}
		_ptr = index > _ptr ? index : _ptr;
		return this->_data[index];
	}

	T& operator[](int index) {
		return this->get(index);
	}

private:
	T* _data = (T*)calloc(32, sizeof(T));
	int _ptr;
	int _isAlloc;
	int _size;
	int _maxSize;
};

#endif







//********************************
//
// CALLABLE INTERFACE
//
//********************************



typedef class ICALLABLE_OBJECT_t
{
public:
	virtual Object Invoke(ObjectStackA stack) = 0;
}ICallableObject,*LPCallableObject;




//********************************
//
// FUNCTION OBJECT CONTAINER
//
//********************************

template <typename ... Tx>
class ACTION_t final : public ICALLABLE_OBJECT_t
{
public:

	ACTION_t<Tx...>() : _actionTx(nullptr) { }
	ACTION_t<Tx...>(const LPActionTxA<Tx...>& func) : _actionTx(func) { }

	Object Invoke(ObjectStackA stack) override {
		_actionTx((Tx)stack.pop_back()...);
		return 0;
	}

	operator const LPActionTxA<Tx...>() {
		return _actionTx;
	}
private:
	LPActionTxA<Tx...> _actionTx;
};


template <typename Tout, typename ... Tx>
class FUNCTION_t final : public ICALLABLE_OBJECT_t
{
public:
	FUNCTION_t<Tout, Tx...>() : _functionTx(nullptr) { }
	FUNCTION_t<Tout, Tx...>(const LPFunctionTxA<Tout, Tx...>& func) : _functionTx(func) { }

	Object Invoke(ObjectStackA stack) override {
		return _functionTx((Tx)stack.pop_back()...);
	}

	operator const LPFunctionTxA<Tout, Tx...>() {
		return _functionTx;
	}
private:
	LPFunctionTxA<Tout, Tx...> _functionTx;
};







//********************************
//
// FUNCTOR OBJECT
//
//********************************

typedef class FUNCTOR_t
{

public:
	FUNCTOR_t(LPCallableObject* func) {
		_functorPtr = *func;
	}

	template <typename ... Tx> FUNCTOR_t(const LPActionTxA<Tx...>& func) {
		_functorPtr = new ACTION_t<Tx...>(func);
	}
	
	template <typename Tout, typename ... Tx> FUNCTOR_t(const LPFunctionTxA<Tout, Tx...>& func) {
		_functorPtr = new FUNCTION_t<Tout, Tx...>(func);
	}

	template<typename...Tx> Object Invoke(Tx...args) {
		return _functorPtr->Invoke({ args... });
	}

	Object Invoke(const ObjectStackA& params) const {
		return _functorPtr->Invoke(params);
	}

private:
	LPCallableObject _functorPtr;
}Functor;












//********************************
//
// INVOKER OBJECT
//
//********************************

typedef class INVOKER_t
{
public:

	INVOKER_t(Functor f) : _functor(f) { }

	void SetParams(const ObjectStackA& dat) {
		_params = dat;
	}

	// Invoke methods
	Object Invoke() const {
		return _functor.Invoke(_params);
	}

	template<typename...Tx> Object Invoke(Tx...args) {
		return sizeof...(Tx) > 0 ? _functor.Invoke(args...) : _functor.Invoke(_params);
	}

	// Function call operator overloads
	Object operator()() const {
		return  Invoke();
	}

	template<typename...Tx> Object operator()(Tx...args) {
		return Invoke(args...);
	}

private:
	ObjectStackA _params{};
	Functor _functor = 0;
}InvokerBase;







#endif


