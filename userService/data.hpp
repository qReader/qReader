#include <iostream>
#include <vector>
#include "../lib/dao/dao.hpp"
using namespace std;
using namespace ormpp;
/*
 * parm:
 * res: 数组结果
 * return:
 * 0:返回数目为0或者查询失败   n 返回查询成功或者共有多少数据
*/

int get_all_user(vector<UserInfoTable>& res){
	auto conn = get_conn_from_pool();
	conn_guard guard(conn);
	if(conn == NULL){
		cout <<"FILE: " << __FILE__ << " "<< "conn is NULL" << " LINE  "<< __LINE__ << endl; 
		return -1;
	}
	res = conn->query<UserInfoTable>();
	return res.size();
}

int get_user_by_id(UserInfoTable & user, const string & user_id) {	
	auto conn = get_conn_from_pool();
	conn_guard guard(conn);
	if(conn == NULL){
		cout <<"FILE: " << __FILE__ << " "<< "conn is NULL" << " LINE  "<< __LINE__ << endl; 
		return -1;
	}
	string cond = "id=" + user_id;
	auto res = conn->query<UserInfoTable>(cond);
	memcpy(&user,&res,sizeof(res)); 
	return 1;
}

int insert_user(const UserInfoTable &user) {
	auto conn = get_conn_from_pool();
	if(conn == NULL){
		cout <<"FILE: " << __FILE__ << " "<< "conn is NULL" << " LINE  "<< __LINE__ << endl; 
		return -1;
	}
	if(conn->insert(user) != 1) {
		cout << __FILE__ << " : " << __LINE__ << "insert error" << endl;
		return 0;
	}
	return 1;	
}


int insert_user(const string & usr_id, const string & user_nickname, const string & user_head_imgurl,const string & user_pwd, const int& user_male, const int& user_age,const string & user_profile){
	auto conn = get_conn_from_pool();
	conn_guard guard(conn);
	if(conn == NULL){
		cout <<"FILE: " << __FILE__ << " "<< "conn is NULL" << " LINE  "<< __LINE__ << endl; 
		return -1;
	}
	UserInfoTable user{usr_id, user_nickname, user_head_imgurl, user_pwd, user_male, user_age, user_profile};
	if(conn->insert(user) != 1) {
		cout << __FILE__ << " : " << __LINE__ << "insert error" << endl;
		return 0;
	}
	return 1;
}


int del_user(const string & user_id) {
	auto conn = get_conn_from_pool();
	if(conn == NULL){
		cout <<"FILE: " << __FILE__ << " "<< "conn is NULL" << " LINE  "<< __LINE__ << endl; 
		return -1;
	}
	string cond = "id=" + user_id;
	conn->delete_records<UserInfoTable>(cond);
	return 1;
}


int up_user(const UserInfoTable &user) {
	auto conn = get_conn_from_pool();
	if(conn == NULL){
		cout <<"FILE: " << __FILE__ << " "<< "conn is NULL" << " LINE  "<< __LINE__ << endl; 
		return -1;
	}
	if(conn->update(user) != 1) {
		cout << __FILE__ << " : " << __LINE__ << "insert error" << endl;
		return 0;
	}
	return 1;	
}


int up_user(const string & usr_id, const string & user_nickname, const string & user_head_imgurl, const string &user_pwd, const int& user_male, const int& user_age,const string & user_profile){
	auto conn = get_conn_from_pool();
	if(conn == NULL){
		cout <<"FILE: " << __FILE__ << " "<< "conn is NULL" << " LINE  "<< __LINE__ << endl; 
		return -1;
	}
	UserInfoTable user{usr_id, user_nickname, user_head_imgurl, user_pwd, user_male, user_age, user_profile};
	if(conn->update(user) != 1) {
		cout << __FILE__ << " : " << __LINE__ << "insert error" << endl;
		return 0;
	}
	return 1;
}





