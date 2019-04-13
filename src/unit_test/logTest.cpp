/*
 * main.cpp
 *
 *  Created on: Apr 13, 2019
 *      Author: fly
 */
#include "LogThread.h"
#include <iostream>
#include <unistd.h>
using namespace std;
int main(){
	string name("xiongshen");
	LOG_DEBUG("test debug1");
	LOG_DEBUG("test debug2");
	LOG_DEBUG("test debug3");
	LOG_DEBUG("test debug4");
	LOG_ERR("test error");
	LOG_INFO("test info");
	LOG_WARN("test warn");

	sleep(2);
}



