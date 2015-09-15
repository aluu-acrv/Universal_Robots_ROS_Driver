/*
 * ur_communication.h
 *
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <thomas.timm.dk@gmail.com> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.   Thomas Timm Andersen
 * ----------------------------------------------------------------------------
 */

#ifndef UR_COMMUNICATION_H_
#define UR_COMMUNICATION_H_

#include "robot_state.h"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <chrono>

class UrCommunication {
private:
	int sockfd_;
	struct sockaddr_in pri_serv_addr_, sec_serv_addr_;
	struct hostent *server_;
	bool keepalive_;
	std::thread comThread_;
	int flag_;
	std::recursive_mutex command_string_lock_;
	std::string command_;
	void run();

public:
	bool connected_;
	RobotState* robot_state_;

	UrCommunication(std::condition_variable& msg_cond, std::string host);
	void start();
	void halt();
	void addCommandToQueue(std::string inp);

};

#endif /* UR_COMMUNICATION_H_ */
