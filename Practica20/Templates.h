#pragma once
template <class T, class U, class V>
T Clamp(T tValue, U tMin, V tMax)
{
	if(tValue < tMin)
	{
		tValue = tMin;
	}
	else if(tValue > tMax)
	{
		tValue = tMax;
	}

	return tValue;
}

template <class T, int SIZE>
class TStack
{
private:
	T m_array[SIZE];
	int currentIndex = 0;
public :
	bool Push(const T& _rIn)
	{
		if(currentIndex < SIZE)
		{
			m_array[currentIndex] = _rIn;
			currentIndex++;
			return true;
		}
		return false;
	}

	bool Pop(T& _rOut)
	{
		if(currentIndex > 0)
		{
			currentIndex--;
			_rOut = m_array[currentIndex];
			//delete current element?
			
			return true;
		}
		return false;
	}

	int Size()
	{
		return currentIndex;
	}

	bool IsEmpty()
	{
		return currentIndex > 0;
	}
};

