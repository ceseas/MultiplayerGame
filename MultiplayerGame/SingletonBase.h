#ifndef SINGLETON_BASE_H
#define SINGLETON_BASE_H

template <typename T>
class SingletonBase
{
public :
	static T &Get() 
	{
		if (_instance == nullptr)
		{
			_instance = new T();
		}
		return _instance;
	}

	void Release()
	{
		delete _instance;
	}

private :
	static T _instance;
};

template <typename T>
T *SingletonBase::_instance = nullptr;

#endif