#ifndef CPP_VECTOR_HPP_
#define CPP_VECTOR_HPP_

#include <cassert>

template<typename T>
class CVector
{
private:
	int size_vec;
	int capacity_vec;
	T *my_vector;

public:
	
    class CVectorIterator
    {
    private:
    	T* hold_ptr;
    public:

        CVectorIterator(T* aPtr)
    		:hold_ptr(aPtr)
    	{

    	}

        CVectorIterator operator+(int aDiffIndex) const
        {
        	T* result = hold_ptr+aDiffIndex;
        	return result;
        }

        CVectorIterator operator-(int aDiffIndex) const
        {
        	T* result = hold_ptr-aDiffIndex;
			return result;
        }

        CVectorIterator& operator++()
        {
        	++hold_ptr;
        	return *this;
        }

        CVectorIterator& operator--()
        {
        	--hold_ptr;
        	return *this;
        }

        CVectorIterator operator++(int)
        {
        	T* new_ptr = hold_ptr;
        	hold_ptr++;
        	return new_ptr;
        }

        CVectorIterator operator--(int)
        {
        	T* new_ptr = hold_ptr;
			hold_ptr--;
			return new_ptr;
        }

        T& operator*()
        {
        	return *hold_ptr;
        }

        const T& operator*() const
        {
        	return *hold_ptr;
        }

        T* operator->()
        {
        	return hold_ptr;
        }

        const T* operator->() const
        {
        	return hold_ptr;
        }

        int operator-(const CVectorIterator& aIt) const
        {
        	return (hold_ptr - aIt.hold_ptr);
        }

        bool operator<(const CVectorIterator& aIt) const
        {
        	return (hold_ptr < aIt.hold_ptr);
        }

        bool operator<=(const CVectorIterator& aIt) const
        {
        	return (hold_ptr <= aIt.hold_ptr);
        }

        bool operator>(const CVectorIterator& aIt) const
        {
        	return (hold_ptr > aIt.hold_ptr);
        }

        bool operator>=(const CVectorIterator& aIt) const
        {
        	return (hold_ptr >= aIt.hold_ptr);
        }

        bool operator==(const CVectorIterator& aIt) const
        {
        	return (hold_ptr == aIt.hold_ptr);
        }

        bool operator!=(const CVectorIterator& aIt) const
        {
        	return (hold_ptr != aIt.hold_ptr);
        }

    };

    class CReverseVectorIterator
    {
    private:
    	T* hold_ptr;
    public:
    	
        CReverseVectorIterator(T* aPtr)
    		:hold_ptr(aPtr)
    	{

    	}

        CReverseVectorIterator operator+(int aDiffIndex) const
        {
        	return hold_ptr-aDiffIndex;
        }

        CReverseVectorIterator operator-(int aDiffIndex) const
        {
        	return hold_ptr+aDiffIndex;
        }

        CReverseVectorIterator& operator++()
        {
        	hold_ptr--;
        	return *this;
        }

        CReverseVectorIterator& operator--()
        {
        	hold_ptr++;
        	return *this;
        }

        CReverseVectorIterator operator++(int)
        {
        	CReverseVectorIterator temp = *this;
        	  --hold_ptr;
        	  return temp;
        }

        CReverseVectorIterator operator--(int)
        {
        	CReverseVectorIterator temp = *this;
			  ++hold_ptr;
			  return temp;
        }

        T& operator*()
        {
        	return *hold_ptr;
        }
        
        const T& operator*() const
        {
        	return *hold_ptr;
        }
        
        T* operator->()
        {
        	return hold_ptr;
        }
        
        const T* operator->() const
        {
        	return hold_ptr;
        }

        int operator-(const CReverseVectorIterator& aIt) const
        {
        	return aIt.hold_ptr - hold_ptr;
        }
        
        bool operator<(const CReverseVectorIterator& aIt) const
        {
        	return (hold_ptr > aIt.hold_ptr);
        }

        bool operator<=(const CReverseVectorIterator& aIt) const
        {
        	return hold_ptr >= aIt.hold_ptr;
        }

        bool operator>(const CReverseVectorIterator& aIt) const
        {
        	return hold_ptr < aIt.hold_ptr;
        }

        bool operator>=(const CReverseVectorIterator& aIt) const
        {
        	return hold_ptr <= aIt.hold_ptr;
        }

        bool operator==(const CReverseVectorIterator& aIt) const
        {
        	return hold_ptr == aIt.hold_ptr;
        }

        bool operator!=(const CReverseVectorIterator& aIt) const
        {
        	return hold_ptr != aIt.hold_ptr;
        }

    };

    using DIterator = CVectorIterator;
    using DReverseIterator = CReverseVectorIterator;

    CVector(int param = 0)
    	:size_vec(param),
		 capacity_vec(2*param),
		 my_vector(new T[2*param])
    {

    }

    CVector(const CVector& aObj)
		:size_vec(aObj.size_vec),
		 capacity_vec(aObj.capacity_vec),
		 my_vector(new T[aObj.capacity_vec])
    {
    	for(int iter=0; iter<aObj.size_vec; iter++)
    	{
    		my_vector[iter] = aObj.my_vector[iter];
    	}
    }
    
    CVector& operator=(const CVector& aObj)
    {
    	if( this != &aObj )
    	{
    		T* new_vector = new T[aObj.capacity_vec];
    		delete[] my_vector;
    		my_vector = new_vector;


    		capacity_vec = aObj.capacity_vec;
    		size_vec = aObj.size_vec;

    		for(int iter=0; iter<aObj.size_vec; iter++)
    		{
    			my_vector[iter] = aObj.my_vector[iter];
    		}
    	}
    	return *this;
    }

    bool operator==(const CVector& aObj)
    {
    	bool result = true;
    	if(aObj.size_vec != size_vec)
    	{
    		result = false;
    	}
    	else
    	{
			for(int iter=0; (iter<aObj.size_vec); iter++)
			{
				if(aObj.my_vector[iter] != my_vector[iter])
				{
					result = false;
					break;
				}
			}
    	}
    return result;
    }

    bool operator!=(const CVector& aObj)
    {

    return !(*this == aObj);
    }

    ~CVector()
    {
    	delete[] my_vector;
    }
    
    unsigned int size() const
    {
    	return size_vec;
    }

    void pushBack(const T& aValue)
    {
    	if(size_vec >= capacity_vec)
    	{
    		capacity_vec = size_vec+5;
    		T* new_vector = new T[capacity_vec];

    		for(int iter=0; iter<size_vec; iter++)
    		{
    			new_vector[iter] = my_vector[iter];
    		}

    		delete[] my_vector;
    		my_vector = new_vector;
    	}
    	my_vector[size_vec] = aValue;
    	size_vec++;
    }

    T popBack()
    {
    	T last_el = 0;

    	last_el = my_vector[size_vec-1];

    	size_vec--;

    	return last_el;
    }
    
    void pushFront(const T& aValue)
    {
    	if(size_vec == capacity_vec)
    	{
    		T* new_vector = new T[capacity_vec+=5];

    	 	for(int iter=0; iter<size_vec; iter++)
    		{
    			new_vector[iter+1] = my_vector[iter];
    		}

    	 	new_vector[0] = aValue;

    	 	delete[] my_vector;
    		my_vector = new_vector;
    		size_vec++;
    	}
    	else
    	{
			for(int i=size_vec; i>0; i--)
			{
				my_vector[i] = my_vector[i-1];
			}
			my_vector[0] = aValue;
			size_vec++;
    	}
    }
    
    T popFront()
    {
    	T fst_el = 0;

    	fst_el = my_vector[0];

    	for(int i=0; i<size_vec-1; i++)
    	{
    		my_vector[i] = my_vector[i+1];
    	}
    	size_vec--;

    	return fst_el;
    }
    
    bool contains(const T& aValue)
    {
    	bool find = false;
    	for(int i=0; i<size_vec; i++)
    	{
    		if (my_vector[i] == aValue)
    		{
    			find = true;
    			break;
    		}
    	}
    	return find;
    }
    
    bool empty() const
    {
    	return (size_vec)==0;
    }
    
    const T* get(unsigned int aIndex) const
    {
    	T* p_ele = nullptr;

    	if(aIndex < size_vec)
    	{
    		p_ele = &my_vector[aIndex];
    	}

    	return p_ele;
    }
    
    void insert(unsigned int aIndex, const T& aValue)
    {
    	if(aIndex <= size_vec)
    	{
			if(size_vec == capacity_vec)
			{
				T* new_vector = new T[capacity_vec+5];

				for(int iter=0; iter<aIndex; iter++)
				{
					new_vector[iter] = my_vector[iter];
				}

				new_vector[aIndex] = aValue;

				for(int iter=aIndex; iter<size_vec; iter++)
				{
					new_vector[iter+1] = my_vector[iter];
				}

				T *to_delete = my_vector;
				delete[] to_delete;
				my_vector = new_vector;
			}
			else
			{
				for(int i=size_vec; i>aIndex; i--)
				{
					my_vector[i] = my_vector[i-1];
				}
				my_vector[aIndex] = aValue;
    		}
			size_vec++;
    	}
    }


    DIterator begin()
    {
    	return &my_vector[0];
    }

    DIterator end()
    {
    	return &my_vector[size_vec];
    }

    DReverseIterator rbegin()
    {
    	return &my_vector[size_vec-1];
    }

    DReverseIterator rend()
    {
    	return &my_vector[-1];
    }

};

#endif // CPP_VECTOR_HPP_
