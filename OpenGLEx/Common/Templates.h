#pragma once

template<typename T>
class Singleton
{
public:
	// 注意返回的是引用
	static T& GetInstance() 
	{
		static T instance; //静态局部变量
		return instance;
	}

	Singleton(T&&) = delete;  //禁止使用拷贝构造函数
	Singleton(const T&) = delete;
	void operator=(const T&) = delete; //禁止使用拷贝赋值运算符

protected:
	Singleton() = default;
	virtual ~Singleton() = default;
};