#ifdef _MSC_VER
#ifdef _WIN64
#include <WinSock2.h>
#elif _WIN32
#include <winsock.h>
#endif

#endif
#include <iostream>
#include <thread>

#ifdef ORMPP_ENABLE_MYSQL
#include "mysql.hpp"
#endif

#include "dbng.hpp"
#include "connection_pool.hpp"
#include "ormpp_cfg.hpp"

//#define TEST_MAIN
//#include "unit_test.hpp"

using namespace std::string_literals;

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

int conn();
