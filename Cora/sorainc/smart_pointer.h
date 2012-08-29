// Header file for smart pointer
// Supporting both kernel mode and user mode
// Supporting aligned type

#pragma once
#include "alinew.h"

template<class _Ty>
	class aligned_smart_ptr;

template<class _Ty>
	struct aligned_smart_ptr_ref
		{	// proxy reference for aligned_smart_ptr copying
	explicit aligned_smart_ptr_ref(_Ty *_Right)
		: _Ref(_Right)
		{	// construct from generic pointer to aligned_smart_ptr ptr
		}

	_Ty *_Ref;	// generic pointer to aligned_smart_ptr ptr
	};

template<class _Ty>
	class aligned_smart_ptr
		{	// wrap an object pointer to ensure destruction
public:
	typedef aligned_smart_ptr<_Ty> _Myt;
	typedef _Ty element_type;

	explicit aligned_smart_ptr(_Ty *_Ptr = 0) throw()
		: _Myptr(_Ptr)
		{	// construct from object pointer
		}

	aligned_smart_ptr(_Myt& _Right) throw()
		: _Myptr(_Right.release())
		{	// construct by assuming pointer from _Right aligned_smart_ptr
		}

	aligned_smart_ptr(aligned_smart_ptr_ref<_Ty> _Right) throw()
		{	// construct by assuming pointer from _Right aligned_smart_ptr_ref
		_Ty *_Ptr = _Right._Ref;
		_Right._Ref = 0;	// release old
		_Myptr = _Ptr;	// reset this
		}

	template<class _Other>
		operator aligned_smart_ptr<_Other>() throw()
		{	// convert to compatible aligned_smart_ptr
		return (aligned_smart_ptr<_Other>(*this));
		}

	template<class _Other>
		operator aligned_smart_ptr_ref<_Other>() throw()
		{	// convert to compatible aligned_smart_ptr_ref
		_Other *_Cvtptr = _Myptr;	// test implicit conversion
		aligned_smart_ptr_ref<_Other> _Ans(_Cvtptr);
		_Myptr = 0;	// pass ownership to aligned_smart_ptr_ref
		return (_Ans);
		}

	template<class _Other>
		_Myt& operator=(aligned_smart_ptr<_Other>& _Right) throw()
		{	// assign compatible _Right (assume pointer)
		reset(_Right.release());
		return (*this);
		}

	template<class _Other>
		aligned_smart_ptr(aligned_smart_ptr<_Other>& _Right) throw()
		: _Myptr(_Right.release())
		{	// construct by assuming pointer from _Right
		}

	_Myt& operator=(_Myt& _Right) throw()
		{	// assign compatible _Right (assume pointer)
		reset(_Right.release());
		return (*this);
		}

	_Myt& operator=(aligned_smart_ptr_ref<_Ty> _Right) throw()
		{	// assign compatible _Right._Ref (assume pointer)
		_Ty *_Ptr = _Right._Ref;
		_Right._Ref = 0;	// release old
		reset(_Ptr);	// set new
		return (*this);
		}

	~aligned_smart_ptr()
		{	// destroy the object
		aligned_delete(_Myptr);
		}

	FINL _Ty& operator*() const throw()
		{	// return designated value
 		return (*get());
		}

	FINL _Ty *operator->() const throw()
		{	// return pointer to class object
 		return (get());
		}

	FINL _Ty *get() const throw()
		{	// return wrapped pointer
		return (_Myptr);
		}

	_Ty *release() throw()
		{	// return wrapped pointer and give up ownership
		_Ty *_Tmp = _Myptr;
		_Myptr = 0;
		return (_Tmp);
		}

	void reset(_Ty *_Ptr = 0)
		{	// destroy designated object and store new pointer
		if (_Ptr != _Myptr)
			aligned_delete(_Myptr);
		_Myptr = _Ptr;
		}

private:
	_Ty *_Myptr;	// the wrapped object pointer
	};
