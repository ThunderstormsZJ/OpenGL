#pragma once

template<typename T>
class Singleton
{
public:
	// ע�ⷵ�ص�������
	static T& GetInstance() 
	{
		static T instance; //��̬�ֲ�����
		return instance;
	}

	Singleton(T&&) = delete;  //��ֹʹ�ÿ������캯��
	Singleton(const T&) = delete;
	void operator=(const T&) = delete; //��ֹʹ�ÿ�����ֵ�����

protected:
	Singleton() = default;
	virtual ~Singleton() = default;
};