#pragma once
template <typename T>
class SingletonBase
{
protected:
	//싱글톤 인스턴스 선언하기
	static T* Singleton;

	SingletonBase() {};
	~SingletonBase() {};

public:
	static T* get_singleton();
	void release_singleton();

};

//싱글톤 인스턴스 선언
template <typename T>
T* SingletonBase<T>::Singleton = nullptr;

//싱글톤 객체를 가져오자
template<typename T>
T* SingletonBase<T>::get_singleton()
{
	//싱글톤 객체가 없으면 새로 만들자ㅏ.
	if (!Singleton)Singleton = new T;

	return Singleton;
}
template<typename T>
void SingletonBase<T>::release_singleton()
{
	//싱글톤 있으면 해제
	if (Singleton)
	{
		delete Singleton;
		Singleton = nullptr;
	}
}