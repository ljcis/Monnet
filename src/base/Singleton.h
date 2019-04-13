/*
 * Singleton.h
 *
 *  Created on: 2018年8月22日
 *      Author: fly
 */

#ifndef SRC_SINGLETON_H_
#define SRC_SINGLETON_H_
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include "common.h"
template <typename T>
class Singleton : Noncopyable{
public:
    static T& getInstance()
	{
    	pthread_once(&once_, &Singleton::Init);
    	assert( singleton_ != NULL);

    	return ( *singleton_ );
	}
    static T* getInstancePtr()
	{
    	return ( singleton_ );
	}
    Singleton();
    virtual ~Singleton(){}
private:
    static void Init(){
    	Singleton::singleton_ = new(std::nothrow)T();
    	::atexit(Destroy);
    }
    static void Destroy(){
    	 delete singleton_;
    	 singleton_ = NULL;
    }
//    Singleton();
//    virtual ~Singleton(){}

private:
    static pthread_once_t once_;
    static T*			  singleton_;
};
template<typename T>
pthread_once_t Singleton<T>::once_ = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::singleton_ = NULL;


#endif /* SRC_APSC_CLIENT_SERVICE_SCAN_APSC_CLIENT_APSC_TOOLS_SINGLETON_H_ */
