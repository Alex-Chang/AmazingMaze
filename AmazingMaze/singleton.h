/*
The Alex Library
Copyright (c) 2011 by Alex, Chang
This file is a part of libary Alex.
Permission to use, copy, modify, distribute and sell this software for any 
	purpose is hereby granted without fee, provided that the above copyright 
	notice appear in all copies and that both that copyright notice and this 
	permission notice appear in supporting documentation.
The author make no representations about the suitability of this software for
	any purpose. It is provided "as is" without express or implied warranty.
About the author. I am a boy who want to become a skilled C++ programmer.
	I develop this libary because I want to record the useful code we ofen use.
	also I want to improve my skill in C++. If you think my libary has some error
	or disatvantage, or you have questions to ask me, you can send E-mal to this
	mailbox 'zhangjian19890218@163.com'. Thanks for your support. Thank you.
*/

/******************************************************************
* @FileName  : singleton.h
* @Brief     : the implemention of singleton pattern.
* @Author    : Alex, Chang
* @DateTime  : 2011-10-26 10:40:46
* @LastUpdate: 2011-10-29 13:55:58
******************************************************************/

#ifndef SINGLETON_H
#define SINGLETON_H

/*
	we provide 3 kinds of implemention of singleton pattern.
*/

// method 1 : we implement singleton by adding a nested class.
#define		SINGLETON_TYPE_NESTED_CLASS			1
// method 2 : we implement singleton by the samplest way.
#define		SINGLETON_TYPE_STATIC_INSTANCE		2

// specify we choose which method to implement singleton pattern.
#define		SINGLETON_TYPE		SINGLETON_TYPE_STATIC_INSTANCE


namespace Alex
{
#	if SINGLETON_TYPE == SINGLETON_TYPE_NESTED_CLASS

	/*
		we implement singleton pattern by add a nested class.
		each class that want to get the function of singleton must be devided from singleton<devided>.
		for example , class LogManager : public singleton<LogManager>;
		because devided class's constructor is private, the base class must be set to devided class's friend class.
	*/
	template<typename T>
	class singleton
	{
	private:
		// fibbiden operations, so only has declaration, has no definition, and is private.
		singleton(const singleton& anothor);
		singleton& operator = (const singleton<T>&);
	protected:
		// default constructor and destructor is protected, so that devided class can access them.
		singleton()	{ }
		virtual ~singleton(){ }

		static T* instance;

	public:
		/*
			get reference of the only one instance.
		*/
		static T* getsingletonptr()
		{
			if (instance == NULL)
			{
				instance = new T();
				static deleter mdeleter;
			}
			return instance;
		}

		/*
			get pointer to the only one instance.
		*/
		static T& getsingleton()
		{
			return *getsingletonptr();
		}

	private:
		class deleter
		{
		public:
			~deleter()
			{
				delete instance;
				instance = NULL;
			}
		};
	};

	template<typename T>
	T* singleton<T>::instance = NULL;

#	elif SINGLETON_TYPE == SINGLETON_TYPE_STATIC_INSTANCE
	/*
		the samplest implenmention of singleton pattern.
		each class that want to get the function of singleton must be devided from singleton<devided>.
		for example , class LogManager : public singleton<LogManager>;
		because devided class's constructor is private, the base class must be set to devided class's friend class.
	*/
	template<typename T>
	class singleton
	{
	private:
		// fibbiden operations, so only has declaration, has no definition, and is private.
		singleton(const singleton& anothor);
		singleton& operator = (const singleton<T>&);

	protected:
		// default constructor and destructor is protected, so that devided class can access them.
		singleton()	{}
		virtual ~singleton() {}

	public:
		/*
			get reference of the only one instance.
		*/
		static T& getsingleton()
		{
			static T instance;
			return instance;
		}

		/*
			get pointer to the only one instance.
		*/
		static T* getsingletonptr()
		{
			return &getsingleton();
		}
	};

#endif	// SINGLETON_TYPE
}

#endif