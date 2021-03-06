#pragma once
#include <cassert>
#include <type_traits>
#include <functional>

template <typename T>
class ISingleton
{
	static_assert(!std::is_pointer<T>::value, "Don't try making singleton with pointer type");
private:
	static inline T* mSingleTon{ nullptr };

public:
	/// <summary>
	/// Setting SingletonChangable true is not recommended
	/// </summary>
	/// <param name="takeOverSingleton">if true, this object will be Singleton even if single already exist</param>
	ISingleton(bool takeOverSingleton = false)
	{
		if (takeOverSingleton == false)
		{
			assert(mSingleTon == nullptr);
		}
		
		mSingleTon = (T*)this;
	}
	virtual ~ISingleton()
	{
		if (mSingleTon != nullptr && mSingleTon == dynamic_cast<T*>(this))
		{
			mSingleTon = nullptr;
		}
	}

	/// <summary>
	/// Why use pointer not reference
	/// To prevent mistake
	/// 
	/// Lets Think if you assign singleton to auto variable unconsciously not auto&, That will be disaster
	/// So To prevent unconsciously assign to not reference variable
	/// </summary>
	/// <returns></returns>
	static T* GetSingleton()
	{
		assert(mSingleTon != nullptr);
		return mSingleTon;
	}
};