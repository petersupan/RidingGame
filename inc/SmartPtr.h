#ifndef __SMARTPTR_H__
#define __SMARTPTR_H__

// -----------------------------------------------------------------------------
/// SmartPtr
// -----------------------------------------------------------------------------
/// \ingroup
/// A simple implementation of a reference counted pointer.
// -----------------------------------------------------------------------------
template<class T>
class SmartPtr
{
public:
    // constructors
    explicit SmartPtr(void);
    explicit SmartPtr(T *p);
	// SmartPtr(const T &r) : ptr(0) {AddRef(r);}
    //SmartPtr(const SmartPtr<T>& rhs);

    // destructor
    ~SmartPtr();

    // operators
    const T& operator*() const { return *ptr; }
    T& operator*() { return *ptr; }
    const T* operator->() const { return ptr; }
    T* operator->() { return ptr; }
    SmartPtr<T> & operator=(const SmartPtr<T>& rhs);

    const T* Get() const { return ptr; }
	// unsafe w/o const
	T* GetUnConst() { return ptr; }
	void SetPtr(T* _ptr) { ptr = _ptr; }

private:
    T *ptr;
    //void AddRef(const T &p);
};

// -----------------------------------------------------------------------------
// --------------------------- SmartPtr<T>::SmartPtr ---------------------------
// -----------------------------------------------------------------------------
template <class T>
SmartPtr<T>::SmartPtr(void)
{
    //ptr = SAFE_NEW T();
    //ptr->refCount = 1;
	ptr = NULL;
}

// -----------------------------------------------------------------------------
// --------------------------- SmartPtr<T>::SmartPtr ---------------------------
// -----------------------------------------------------------------------------
template <class T>
SmartPtr<T>::SmartPtr(T *p)
    : ptr(p)
{
    //if (ptr)
    //    ptr->refCount = 1;
}

// -----------------------------------------------------------------------------
// --------------------------- SmartPtr<T>::SmartPtr ---------------------------
// -----------------------------------------------------------------------------
//template <class T>
//SmartPtr<T>::SmartPtr(const SmartPtr<T>& rhs)
//    : ptr(rhs.ptr)
//{
//    //if (ptr)
//    //    ptr->refCount++;
//}

// -----------------------------------------------------------------------------
// --------------------------- SmartPtr<T>::~SmartPtr --------------------------
// -----------------------------------------------------------------------------
template <class T>
SmartPtr<T>::~SmartPtr()
{
    //if (ptr && --ptr->refCount == 0)
        SAFE_DELETE(ptr);
}

// -----------------------------------------------------------------------------
// ---------------------------- SmartPtr<T>::attach ----------------------------
// -----------------------------------------------------------------------------
//template <class T>
//void SmartPtr<T>::AddRef(const T &r)
//{
//    //if (ptr && --ptr->refCount == 0)
//        SAFE_DELETE(ptr);
//    if (r.refCount == 0)
//    {
//        //ASSERT(false, "Clone removed!");
//        //ptr = r.clone();
//        //ptr->refCount = 1;
//    }
//    else
//    {
//        ptr = const_cast<T *>(&r);
//       // ptr->refCount++;
//    }
//}

// -----------------------------------------------------------------------------
// --------------------------- SmartPtr<T>::operator= --------------------------
// -----------------------------------------------------------------------------
//template <class T> SmartPtr<T>&
//SmartPtr<T>::operator=(const SmartPtr<T>& rhs)
//{
//    if (ptr != rhs.ptr)
//    {
//        //if (ptr && --ptr->refCount == 0)
//        //    delete ptr;
//			//ptr = NULL;
//        ptr = rhs.ptr;
//        //if (ptr)
//            //ptr->refCount++;
//    }
//    return *this;
//}

#endif //__SMARTPTR_H__
