#ifndef CPP_DOUBLY_LINKED_LIST_HPP_
#define CPP_DOUBLY_LINKED_LIST_HPP_

#include <cassert> 

template<typename T>
class CDoublyLinkedList
{
    template<typename TItem>
    class CDoublyLinkedListItem;


    template<typename TItem>
    class CDoublyLinkedListItem
    {
    public:


        explicit CDoublyLinkedListItem(const TItem& aValue)
        : mPrevious(nullptr)
        , mNext(nullptr)
        , mValue(aValue)
        {}

     
        CDoublyLinkedListItem(CDoublyLinkedListItem<TItem>* aPrevious,
                              CDoublyLinkedListItem<TItem>* aNext,
                              const TItem& aValue)
        : mPrevious(aPrevious)
          , mNext(aNext)
          , mValue(aValue)
        {}

        
        CDoublyLinkedListItem<TItem>* mPrevious;

    
        CDoublyLinkedListItem<TItem>* mNext;

        TItem mValue;
    };

public:
   
   
    class CDoublyLinkedListIterator
    {
        
        CDoublyLinkedListItem<T>* mPtr;
    public:

        
        explicit CDoublyLinkedListIterator(CDoublyLinkedListItem<T>* aPtr)
        : mPtr(aPtr)
        {
        }

	  
       CDoublyLinkedListIterator operator+(int aDiffIndex) const
	   {
		   CDoublyLinkedListIterator temp = *this;

		   for(int i = 0; i < aDiffIndex; i++)
		   {
			   if ( (temp.mPtr)->mNext == nullptr )
			   {
				   break;
			   }
			   else
			   {
			   (temp.mPtr) = (temp.mPtr)->mNext;
			   }
		   }

		   return temp;
	   }

       CDoublyLinkedListIterator operator-(int aDiffIndex) const
	   {
    	   CDoublyLinkedListIterator temp = *this;

		   for(int i = 0; i < aDiffIndex; i++)
		   {

			   if ( (temp.mPtr)->mPrevious == nullptr )
			   {
				   break;
			   }
			   else
			   {
			   (temp.mPtr) = (temp.mPtr)->mPrevious;
			   }
		   }

		   return temp;
	   }

	 
       CDoublyLinkedListIterator& operator++()
	   {
    	   mPtr = mPtr -> mNext;
    	   return *this;
	   }

	  
       CDoublyLinkedListIterator& operator--()
	   {
    	   mPtr = mPtr -> mPrevious;
    	   return *this;
	   }

	   
       CDoublyLinkedListIterator operator++(int)
	   {
    	   CDoublyLinkedListItem<T>* temp = mPtr;
    	   mPtr = mPtr -> mNext;
    	   return temp;
	   }

	   
       CDoublyLinkedListIterator operator--(int)
	   {
    	   CDoublyLinkedListItem<T>* temp = mPtr;
		   mPtr = mPtr -> mPrevious;
		   return temp;
	   }

	   
	   T& operator*()
	   {
		   return mPtr->mValue;
	   }

	  
	   const T& operator*() const
	   {
		   return mPtr->mValue;
	   }

	   
	   T* operator->()
	   {
		   return mPtr;
	   }

	  
	   const T* operator->() const
	   {
		   return mPtr;
	   }

	  
	   int operator-(const CDoublyLinkedListIterator& aIt) const
	   {
		   int result = 0;
		   CDoublyLinkedListItem<T> *tempL = mPtr;
		   CDoublyLinkedListItem<T> *tempR = mPtr;
		   while (tempL != nullptr || tempR != nullptr)
		   {
			   if (tempL!=nullptr && tempL == aIt)
			   {
				   break;
			   }
			   else
			   {
				   tempL = tempL->mPrevious;
			   }
			   if (tempR!=nullptr && tempR == aIt)
			   {
				   break;
			   }
			   else
			   {
				   tempR = tempR->mNext;

			   }
			   result ++;
		   }

		   return result;
	   }



	   bool operator==(const CDoublyLinkedListIterator& aIt) const
	   {
		   return (mPtr==aIt.mPtr);
	   }

	   
	   bool operator!=(const CDoublyLinkedListIterator& aIt) const
	   {
		   return (mPtr!=aIt.mPtr);
	   }


    };

    class CReverseDoublyLinkedListIterator
    {
       
        CDoublyLinkedListItem<T>* mPtr;
    public:
        
        explicit CReverseDoublyLinkedListIterator(CDoublyLinkedListItem<T>* aPtr) : mPtr(aPtr){}

       	   
        CReverseDoublyLinkedListIterator operator+(int aDiffIndex) const
		   {
        	   CReverseDoublyLinkedListIterator temp = *this;

			   for(int i = 0; (i < aDiffIndex)&&(((temp.mPtr)->mPrevious)!=nullptr); i++)
			   {
				   (temp.mPtr) = (temp.mPtr)->mPrevious;
			   }
			   return temp;
   }

        CReverseDoublyLinkedListIterator operator-(int aDiffIndex) const
        	{
        	   CReverseDoublyLinkedListIterator temp = *this;

			   for(int i = 0; (i < aDiffIndex)&&(((temp.mPtr)->mNext)!=nullptr); i++)
			   {
				   (temp.mPtr) = (temp.mPtr)->mNext;
			   }
			   return temp;
        	}

       	   
        CReverseDoublyLinkedListIterator& operator++()
       	   {
           	   mPtr = mPtr -> mPrevious;
           	   return *this;
       	   }

       	  
        CReverseDoublyLinkedListIterator& operator--()
       	   {
           	   mPtr = mPtr -> mNext;
           	   return *this;
       	   }

       	   
        CReverseDoublyLinkedListIterator operator++(int)
       	   {
           	   CDoublyLinkedListItem<T>* temp = mPtr;
           	   mPtr = mPtr -> mPrevious;
           	   return temp;
       	   }

       	  
        CReverseDoublyLinkedListIterator operator--(int)
       	   {
           	   CDoublyLinkedListItem<T>* temp = mPtr;
       		   mPtr = mPtr -> mNext;
       		   return temp;
       	   }

       	   
       	   T& operator*()
       	   {
       		   return mPtr->mValue;
       	   }

       	   
       	   const T& operator*() const
       	   {
       		   return mPtr->mValue;
       	   }

       	   
       	   T* operator->()
       	   {
       		   return mPtr;
       	   }

       	  
       	   const T* operator->() const
       	   {
       		   return mPtr;
       	   }

       	 
       	   int operator-(const CReverseDoublyLinkedListIterator& aIt) const
       	   {
       		   int result = 0;

			   CDoublyLinkedListItem<T> *tempL = mPtr;
			   CDoublyLinkedListItem<T> *tempR = mPtr;

			   while (tempL != nullptr || tempR != nullptr)
			   {
				   if (tempL!=nullptr && tempL == aIt)
				   {
					   break;
				   }
				   else
				   {
					   tempL = tempL->mPrevious;
				   }
				   if (tempR!=nullptr && tempR == aIt)
				   {
					   break;
				   }
				   else
				   {
					   tempR = tempR->mNext;

				   }
				   result ++;
			   }

			   return result;
		   }

       	  

       	   bool operator==(const CReverseDoublyLinkedListIterator& aIt) const
       	   {
       		   return (mPtr==aIt.mPtr);
       	   }

       	 
       	   bool operator!=(const CReverseDoublyLinkedListIterator& aIt) const
       	   {
       		   return (mPtr  != aIt.mPtr);
       	   }


    };

  
    using DIterator = CDoublyLinkedListIterator;
    using DReverseIterator = CReverseDoublyLinkedListIterator;

    
    CDoublyLinkedList()
    : mBegin(nullptr),
	  mEnd(nullptr),
	  list_size(0)
    {}

    
    CDoublyLinkedList(const CDoublyLinkedList<T>& aObj)
    {
    	if(aObj.mBegin == nullptr)
    	{
    		list_size = 0;
    		mBegin = nullptr;
    		mEnd = nullptr;
    	}
    	else
    	{
    		CDoublyLinkedListItem<T> *item = new CDoublyLinkedListItem<T>(aObj.mBegin->mValue);
    		CDoublyLinkedListItem<T> *given_item = aObj.mBegin -> mNext;
    		mBegin = item;
    		mBegin -> mPrevious = nullptr;

    		while(given_item != nullptr)
    		{
    			item -> mNext = new CDoublyLinkedListItem<T>(given_item->mValue);


    			item -> mNext -> mPrevious = item;
    			item = item -> mNext;
    			given_item = given_item ->mNext;
    		}

    		mEnd = item;
    		list_size = aObj.list_size;

    	}

    }

   
    CDoublyLinkedList<T>& operator=(const CDoublyLinkedList<T>& aObj)
    {
    	CDoublyLinkedListItem<T> *item = mBegin;
    	CDoublyLinkedListItem<T> *temp = nullptr;

    	while(item!=nullptr)
    	{
    		temp = item;
    		item = item -> mNext;
    		delete temp;
    	}
    	if(aObj.mBegin == nullptr)
		{
			list_size = 0;
			mBegin = nullptr;
			mEnd = nullptr;
		}
		else
		{
			CDoublyLinkedListItem<T> *item = new CDoublyLinkedListItem<T>(aObj.mBegin->mValue);
			CDoublyLinkedListItem<T> *given_item = aObj.mBegin -> mNext;
			mBegin = item;
			mBegin -> mPrevious = nullptr;

			while(given_item != nullptr)
			{
				item -> mNext = new CDoublyLinkedListItem<T>(given_item->mValue);

				item -> mNext -> mPrevious = item;
				item = item -> mNext;
				given_item = given_item ->mNext;
			}

			mEnd = item;
    		list_size = aObj.list_size;

		}

        return *this;
    }

    
    bool operator==(const CDoublyLinkedList<T>& aObj)
    {
    	if (this == &aObj)
    	{
    		return true;
    	}

    	bool result = true;

    	CDoublyLinkedListItem<T> *temp = aObj.mBegin;
    	CDoublyLinkedListItem<T> *item = mBegin;

    	while (item != nullptr && temp != nullptr)
    	{
    		if (item->mValue != temp->mValue)
    		{
    			result = false;
    			break;
    		}
    		item = item -> mNext;
    		temp = temp -> mNext;
    	}

        return result;
    }

   
    bool operator!=(const CDoublyLinkedList<T>& aObj)
    {
        return !(*this == aObj);
    }

    
    ~CDoublyLinkedList()
    {
    	CDoublyLinkedListItem<T> *item = mBegin;
		CDoublyLinkedListItem<T> *temp = nullptr;

		while(item!=nullptr)
		{
			temp = item;
			item = item -> mNext;
			delete temp;
		}
    }

  
    unsigned int size() const
    {
        return list_size;
    }

    
    void pushBack(const T& aValue)
    {
    	if (mBegin == nullptr)
    	{
    		mBegin = new CDoublyLinkedListItem<T>(aValue);
    		mBegin ->mNext = nullptr;
    		mBegin ->mPrevious = nullptr;
    		mEnd = mBegin;
    	}
    	else
    	{
			mEnd -> mNext =  new CDoublyLinkedListItem<T>(aValue);
			mEnd -> mNext -> mPrevious = mEnd;
			mEnd = mEnd -> mNext;
			mEnd -> mNext = nullptr;
    	}
    	list_size++;
    }

    
    T popBack()
    {
    	if(mEnd != nullptr)
    	{
			CDoublyLinkedListItem<T> * to_delete = mEnd;

			T result = mEnd->mValue;
			if(mEnd->mPrevious!=nullptr)
			{
				mEnd -> mPrevious -> mNext = nullptr;
				mEnd = mEnd -> mPrevious;
			}
			else
			{
				mEnd = nullptr;
				mBegin = nullptr;
			}
			list_size--;

			delete to_delete;

			  return result;
    	}
    	else
    	{
    		return static_cast<T>(0);
    	}
    }

   
    void pushFront(const T& aValue)
    {
    	if(mBegin == nullptr)
    	{
    		mBegin = new CDoublyLinkedListItem<T>(aValue);
    		mEnd = mBegin;
    		list_size++;
    	}
    	else
    	{
    		mBegin -> mPrevious =  new CDoublyLinkedListItem<T>(aValue);
			mBegin -> mPrevious -> mNext = mBegin;
			mBegin = mBegin -> mPrevious;
			list_size++;
    	}

    }

    
    T popFront()
    {
    	T result = 0;
    	if(mBegin != nullptr)
    	{
			CDoublyLinkedListItem<T> * to_delete = mBegin;

			result = mBegin->mValue;
			if(mBegin->mNext!=nullptr)
			{
				mBegin -> mNext -> mPrevious = nullptr;
				mBegin = mBegin -> mNext;
			}
			else
			{
				mEnd = nullptr;
				mBegin = nullptr;
			}
			list_size--;

			delete to_delete;
    	}
        return result;
    }

   
    bool contains(const T& aValue)
    {
    	bool result = false;
    	CDoublyLinkedListItem<T> *item = mBegin;
    	while(item != nullptr)
    	{
    		if(item -> mValue == aValue)
    		{
    			result = true;
    			break;
    		}
    		item = item -> mNext;
    	}
        return result;
    }

    
    bool empty() const
    {
        return (list_size == 0);
    }

   
    const T* get(unsigned int aIndex) const
    {
    	T *result = nullptr;
    	if(aIndex < list_size)
    	{
    		CDoublyLinkedListItem<T> *item = mBegin;
			for (int i = 0; i < aIndex; i++)
			{
				item = item -> mNext;
			}
			result = &(item -> mValue);
    	}
        return result;
    }

    
    void insert(unsigned int aIndex, const T& aValue)
    {
    	if(aIndex < list_size)
		{
    		if(aIndex==0)
    		{
    			mBegin -> mPrevious = new CDoublyLinkedListItem<T>(aValue);
    			mBegin -> mPrevious -> mNext = mBegin;
    			mBegin = mBegin -> mPrevious;
    		}
    		else
    		{
				CDoublyLinkedListItem<T> *item = mBegin;
				for (int i = 0; i < aIndex-1; i++)
				{
					item = item -> mNext;
				}

				CDoublyLinkedListItem<T> *temp = item -> mNext;

				item -> mNext = new CDoublyLinkedListItem<T>(aValue);
				item -> mNext -> mPrevious = item;
				item -> mNext -> mNext = temp;

				temp -> mPrevious = item -> mNext;

    		}
    		list_size++;
    	}
    }

    
    DIterator begin()
    {
        return DIterator(mBegin);
    }

   
    DIterator end()
    {
        return DIterator(mEnd->mNext);
    }

  
    DReverseIterator rbegin()
    {
        return DReverseIterator(mEnd);
    }

   
    DReverseIterator rend()
    {
        return DReverseIterator(mBegin->mPrevious);
    }

private:

    
    CDoublyLinkedListItem<T>* mBegin;
    CDoublyLinkedListItem<T>* mEnd;
    int list_size;

};

#endif //CPP_DOUBLY_LINKED_LIST_HPP_
