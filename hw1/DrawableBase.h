#pragma once
#include "Drawable.h"

template<class T>
class DrawableBase : public Drawable
{
protected:
	 bool isInit()  noexcept;
	 void AddBind(std::unique_ptr<Bindable> b);
	 void AddIndexBind(std::unique_ptr<IndexBuffer> b);
	 virtual size_t getShareCount()const noexcept override;
private:
	const std::vector<std::unique_ptr<Bindable>>& getShareBinds() const noexcept override;

private:
	static int s_IndexCount ;
	static std::vector<std::unique_ptr<Bindable>> s_binds;
	
};

template<class T>
int DrawableBase<T>::s_IndexCount;

template<class T>
std::vector<std::unique_ptr<Bindable>> DrawableBase<T>::s_binds;

template<class T>
inline void DrawableBase<T>::AddBind(std::unique_ptr<Bindable> b)
{
	assert("Add Share Bind ,Must isn't IndexBuferr Type" && typeid(*b) != typeid(IndexBuffer));

	s_binds.push_back(std::move(b));
}

template<class T>
inline void DrawableBase<T>::AddIndexBind(std::unique_ptr<IndexBuffer> b)
{
	assert("attempt add indexbuffer" && b != nullptr);

	s_IndexCount = b->getCount();

	s_binds.push_back(std::move(b));
}



template<class T>
inline bool DrawableBase<T>::isInit() noexcept
{
	return !s_binds.empty();
}

template<class T>
inline const std::vector<std::unique_ptr<Bindable>>& DrawableBase<T>::getShareBinds() const  noexcept
{
	return s_binds;
}

template<class T>
inline size_t DrawableBase<T>::getShareCount() const noexcept
{
	return s_IndexCount;
}