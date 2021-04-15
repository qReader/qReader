#ifndef _DAO_H
#define _DAO_H
#include <iostream>
#include <thread>
#include <memory>
#include "mysql.hpp"

#include "dbng.hpp"
#include "connection_pool.hpp"
#include "ormpp_cfg.hpp"

//#define TEST_MAIN
//#include "unit_test.hpp"

using namespace std::string_literals;
using namespace ormpp;


std::shared_ptr<dbng<mysql>> get_conn_form_pool(){
	ormpp_cfg cfg{};
	auto& pool = connection_pool<dbng<mysql>>::instance();
    	try {
    	pool.init(cfg.db_conn_num, cfg.db_ip.data(), cfg.user_name.data(), cfg.pwd.data(), cfg.db_name.data(), cfg.timeout);
    	}catch(const std::exception& e){
    		std::cout<<e.what()<<std::endl; 
		return NULL;
	}
	return pool.get();
}

/*
struct test_tb {
	int id;
	char name[12];
};
REFLECTION(test_tb, id, name);

struct person
{
    int id;
    std::string name;
    int age;
};
REFLECTION(person, id, name, age)

struct student{
    int code;//key
    std::string name;
    char sex;
    int age;
    double dm;
    std::string classroom;
};
REFLECTION(student, code, name, sex, age, dm, classroom)

struct simple{
    int id;
    double code;
    int age;
};
REFLECTION(simple, id, code, age);

using namespace ormpp;
//const char* ip = "127.0.0.1"; //your database ip
*/
#endif
