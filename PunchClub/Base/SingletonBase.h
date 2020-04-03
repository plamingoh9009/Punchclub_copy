#pragma once
template <typename T>
class SingletonBase
{
protected:
	//�̱��� �ν��Ͻ� �����ϱ�
	static T* Singleton;

	SingletonBase() {};
	~SingletonBase() {};

public:
	static T* get_singleton();
	void release_singleton();

};

//�̱��� �ν��Ͻ� ����
template <typename T>
T* SingletonBase<T>::Singleton = nullptr;

//�̱��� ��ü�� ��������
template<typename T>
T* SingletonBase<T>::get_singleton()
{
	//�̱��� ��ü�� ������ ���� �����ڤ�.
	if (!Singleton)Singleton = new T;

	return Singleton;
}
template<typename T>
void SingletonBase<T>::release_singleton()
{
	//�̱��� ������ ����
	if (Singleton)
	{
		delete Singleton;
		Singleton = nullptr;
	}
}