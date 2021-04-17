#ifndef _DAO_H
#define _DAO_H
#include <iostream>
#include <thread>
#include <memory>
#include "mysql.hpp"

#include "dbng.hpp"
#include "connection_pool.hpp"
#include "ormpp_cfg.hpp"
#include "entity.hpp"
using namespace std::string_literals;
using namespace ormpp;
using namespace std;
namespace ormpp {

struct UserInfoTable
{
	std::string userId;
	std::string userNickName;
	std::string userHeadImgUrl;
	std::string userPwd;
	int userMale;
	int userAge;
	std::string userProfile;
};

REFLECTION(UserInfoTable, userId, userNickName, userHeadImgUrl, userPwd, userMale, userAge, userProfile)


std::shared_ptr<dbng<mysql>> get_conn_from_pool(){
	ormpp_cfg cfg{};	
    	bool ret = config_manager::from_file(cfg, "./cfg/ormpp.cfg");
	auto& pool = connection_pool<dbng<mysql>>::instance();
    	if (!ret) {
        	cout << "cfg load filed" << endl;
    		pool.init(2, "127.0.0.1", "test", "123456789", "datadb", 2);
		return pool.get();
	}
    	try {
		//Todo
    		pool.init(cfg.db_conn_num, cfg.db_ip.data(), cfg.user_name.data(), cfg.pwd.data(), cfg.db_name.data(), cfg.timeout);
		cout << "num:" << cfg.db_conn_num << " ip: "<< cfg.db_ip.data() << " user: " << cfg.user_name.data() << cfg.pwd.data() << endl;
	}catch(const std::exception& e){
    		std::cout<<e.what()<<std::endl; 
		return NULL;
	}
	return pool.get();
}

int create_user_table() {
	auto conn = get_conn_from_pool(); 	
	if(conn == NULL){
		cout <<"FILE: " << __FILE__ << " "<< "conn is NULL" << " LINE  "<< __LINE__ << endl; 
		return -1;
	}
	conn->execute("DROP TABLE IF EXISTS UserInfoTable");
	//ormpp_auto_increment_key auto_key{"code"};
	//创建含主键和not null属性的表
	//ormpp_key key1{"userId"};
	ormpp_not_null not_null{{"id"}};
	conn->create_datatable<UserInfoTable>(not_null);
	return 1;
}

int cearte_tables() {

	return 1;
}
}

#endif
