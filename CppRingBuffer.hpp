#ifndef CPP_RingBuffer_HPP_
#define CPP_RingBuffer_HPP_

#include <cassert>
#include <iostream>

class CRingBuffer
{

public:

CRingBuffer(int x = 100)
{
	buffor = new char(x);
	mReadPtr = buffor;
	mWritePtr = buffor;
	mMaxSize = x-1;
	mEnd = &buffor[x-1];
	mBegin = &buffor[0];
}

~CRingBuffer()
{
	delete[] buffor;
}

template <typename T>
	bool read_data (T& aDest)
	{
		bool result = true;

		if( !empty() )
		{
			unsigned int data_size = sizeof(aDest);
			unsigned int size_of_dest_size = sizeof(data_size);

			char * const secured_mReadPtr = mReadPtr;

			unsigned int size_from_buffor = 0;
			char *p_size_from_buffor = reinterpret_cast<char *>(&size_from_buffor);

			for(int i = 0; (i < size_of_dest_size) && !empty() ; i++)
			{
				*p_size_from_buffor = *mReadPtr;
				p_size_from_buffor++;

				if(mReadPtr==mEnd)
				{
					mReadPtr = mBegin;
				}
				else
				{
					mReadPtr++;
				}


			}

			if( size_from_buffor == size_of_dest_size)
			{
				char *p_aDest = reinterpret_cast<char *>(&aDest);

				for(int i = 0; i < data_size && !empty(); i++)
				{
					*p_aDest = *mReadPtr;
					p_aDest++;
					if(mReadPtr==mEnd)
					{
						mReadPtr = mBegin;
					}
					else
					{
						mReadPtr++;
					}
				}
			}
			else
			{
				mReadPtr = secured_mReadPtr;
				result = false;
			}
		}
		else
		{
			result = false;
		}
		return result;

	}

template <typename T>
	bool write_data (T aData)
	{
		bool result = true;

		unsigned int data_size = sizeof(aData);
		unsigned int size_of_data_size = sizeof(data_size);

		if( free_space() > (data_size + size_of_data_size) )
		{
			for(int i = 0; i < size_of_data_size; i++)
			{
				*mWritePtr = (reinterpret_cast<char*>(&data_size)[i]);

				if(mWritePtr==mEnd)
				{
					mWritePtr = mBegin;
				}
				else
				{
					mWritePtr++;
				}

				if(mWritePtr == mReadPtr)
				{
					if( mWritePtr == mBegin)
					{
						mWritePtr = mEnd;
						break;
					}
					else
					{
						mWritePtr--;
						break;
					}
				}
			}

			for(int i = 0; i < data_size; i++)
			{
				*mWritePtr = (reinterpret_cast<char*>(&aData)[i]);
				if(mWritePtr==mEnd)
				{
					mWritePtr = mBegin;
				}
				else
				{
					mWritePtr++;
				}

				if(mWritePtr == mReadPtr)
					{
						if( mWritePtr == mBegin)
						{
							mWritePtr = mEnd;
							break;
						}
						else
						{
							mWritePtr--;
							break;
						}
					}
			}
		}
		else
		{
			result = false;
		}

		return result;
	}

unsigned int free_space ()
{
	unsigned int result = 0;

	if(mReadPtr>mWritePtr)
	{
		result = mReadPtr - mWritePtr;
	}
	else
	{
		result = mWritePtr - mReadPtr;
		result = mMaxSize - result;
	}

	return result;
}

bool empty()
{
	return ( mWritePtr == mReadPtr );
}

private:
char* buffor;
char* mReadPtr;
char* mWritePtr;
char* mEnd;
char* mBegin;
unsigned int mMaxSize;

};

#endif // CPP_RingBuffer_HPP_
