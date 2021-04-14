#include "userInfo.h"
using namespace std;
int conn(){
	return 1;
}
/*
//TEST_CASE(mysql_performance){
//    dbng<mysql> mysql;
//
//    TEST_REQUIRE(mysql.connect(ip, "root", "12345", "testdb"));
//    TEST_REQUIRE(mysql.execute("DROP TABLE IF EXISTS student"));
//
//    ormpp_auto_increment_key auto_key{"code"};
//    TEST_REQUIRE(mysql.create_datatable<student>(auto_key));
//
//    using namespace std::chrono;
//    auto m_begin = high_resolution_clock::now();
//    for (int i = 0; i < 10000; ++i) {
//        mysql.insert(student{i, "tom", 0, i, 1.5, "classroom1"});
//    }
//    auto s = duration_cast<duration<double>>(high_resolution_clock::now() - m_begin).count();
//    std::cout<<s<<'\n';
//
//    m_begin = high_resolution_clock::now();
//    std::vector<student> v;
//    for (int i = 0; i < 10000; ++i) {
//        v.push_back(student{i, "tom", 0, i, 1.5, "classroom1"});
//    }
//    mysql.insert(v);
//    s = duration_cast<duration<double>>(high_resolution_clock::now() - m_begin).count();
//    std::cout<<s<<'\n';
//
//    m_begin = high_resolution_clock::now();
//    for (int j = 0; j < 100; ++j) {
//        TEST_REQUIRE(!mysql.query<student>("limit 1000").empty());
//    }
//    s = duration_cast<duration<double>>(high_resolution_clock::now() - m_begin).count();
//    std::cout<<s<<'\n';
//}

template<class T, size_t N>
constexpr size_t size(T(&)[N]) { return N; }

TEST_CASE(mysql_pool){
//	dbng<sqlite> sqlite;
//	sqlite.connect("testdb");
//	sqlite.create_datatable<test_tb>(ormpp_unique{ "name" });
//	test_tb tb{ 1, "aa" };
//	sqlite.insert(tb);
//	auto vt = sqlite.query<test_tb>();
//	auto vt1 = sqlite.query<std::tuple<test_tb>>("select * from test_tb");
//    auto& pool = connection_pool<dbng<mysql>>::instance();
//    try {
//        pool.init(1, ip, "root", "12345", "testdb", 2);
//    }catch(const std::exception& e){
//        std::cout<<e.what()<<std::endl;
//        return;
//    }
//	auto con = pool.get();
//	auto v = con->query<std::tuple<test_tb>>("select * from test_tb");
//	con->create_datatable<test_tb>(ormpp_unique{"name"});
//    for (int i = 0; i < 10; ++i) {
//        auto conn = pool.get();
////        conn_guard guard(conn);
//        if(conn== nullptr){
//            std::cout<<"no available conneciton"<<std::endl;
//            break;
//        }
//
//        bool r = conn->create_datatable<person>();
//    }
}

TEST_CASE(test_ormpp_cfg){
    ormpp_cfg cfg{};
    bool ret = config_manager::from_file(cfg, "./cfg/ormpp.cfg");
    if (!ret) {
        return ;
    }

#ifdef ORMPP_ENABLE_MYSQL
    auto& pool = connection_pool<dbng<mysql>>::instance();
    try {
        pool.init(cfg.db_conn_num, cfg.db_ip.data(), cfg.user_name.data(), cfg.pwd.data(), cfg.db_name.data(), cfg.timeout);
    }catch(const std::exception& e){
        std::cout<<e.what()<<std::endl;
        return;
    }

    auto conn1 = pool.get();
    auto result1 = conn1->query<student>();
    std::cout<<result1.size()<<std::endl;
#endif
}


TEST_CASE(orm_connect){
    int timeout = 5;


#ifdef ORMPP_ENABLE_MYSQL
    dbng<mysql> mysql;
    TEST_REQUIRE(mysql.connect(ip, "root", "12345", "testdb"));
    TEST_REQUIRE(mysql.disconnect());
    TEST_REQUIRE(mysql.connect(ip, "root", "12345", "testdb", timeout));
#endif

}

TEST_CASE(orm_create_table){
    ormpp_key key{"id"};
    ormpp_not_null not_null{{"id", "age"}};
    ormpp_auto_key auto_key{"id"};


#ifdef ORMPP_ENABLE_MYSQL
    dbng<mysql> mysql;
    TEST_REQUIRE(mysql.connect(ip, "root", "12345", "testdb"));
    TEST_REQUIRE(mysql.create_datatable<person>());
    TEST_REQUIRE(mysql.create_datatable<person>(key));
    TEST_REQUIRE(mysql.create_datatable<person>(not_null));
    TEST_REQUIRE(mysql.create_datatable<person>(key, not_null));
    TEST_REQUIRE(mysql.create_datatable<person>(not_null, key));
    TEST_REQUIRE(mysql.create_datatable<person>(auto_key));
    TEST_REQUIRE(mysql.create_datatable<person>(auto_key, not_null));
    TEST_REQUIRE(mysql.create_datatable<person>(not_null, auto_key));
#endif
}

TEST_CASE(orm_insert_query){
    ormpp_key key{"code"};
    ormpp_not_null not_null{{"code", "age"}};
    ormpp_auto_key auto_key{"code"};

    student s = {1, "tom", 0, 19, 1.5, "room2"};
    student s1 = {1, "jack", 1, 20, 2.5, "room3"};
    student s2 = {1, "mke", 2, 21, 3.5, "room4"};
    std::vector<student> v{s1, s2};

#ifdef ORMPP_ENABLE_MYSQL
    dbng<mysql> mysql;
    TEST_REQUIRE(mysql.connect(ip, "root", "12345", "testdb"));
    auto vv0 = mysql.query(FID(simple::id), "<", "5");
    auto vv = mysql.query(FID(simple::id), "<", 5);
    auto vv3 = mysql.query(FID(person::name), "<", "5");
    auto vv5 = mysql.query(FID(person::name), "<", 5);
    auto r = mysql.delete_records(FID(simple::id), "=", 3);
#endif


    //auto key
    {
    }

    //key
    {
#ifdef ORMPP_ENABLE_MYSQL
        TEST_REQUIRE(mysql.create_datatable<student>(auto_key, not_null));
        TEST_CHECK(mysql.insert(s)==1);
        auto result1 = mysql.query<student>();
        TEST_CHECK(result1.size()==1);
        TEST_CHECK(mysql.insert(s)==1);
        TEST_CHECK(mysql.insert(v)==2);
        auto result4 = mysql.query<student>();
        TEST_CHECK(result4.size()==4);
        auto result5 = mysql.query<student>();
        TEST_CHECK(result5.size()==4);

        TEST_REQUIRE(mysql.create_datatable<student>(key, not_null));
        v[0].code = 1;
        v[1].code = 2;
        TEST_CHECK(mysql.insert(s)==1);
        auto result11 = mysql.query<student>();
        TEST_CHECK(result11.size()==1);
        TEST_CHECK(mysql.insert(s)<0);
        TEST_CHECK(mysql.delete_records<student>());
        TEST_CHECK(mysql.insert(v)==2);
        auto result44 = mysql.query<student>();
        TEST_CHECK(result44.size()==2);
        auto result55 = mysql.query<student>();
        TEST_CHECK(result55.size()==2);
        auto result6 = mysql.query<student>();
        TEST_CHECK(result6.size()==2);
#endif
    }

}

TEST_CASE(orm_update){
    ormpp_key key{"code"};
    ormpp_not_null not_null{{"code", "age"}};
    ormpp_auto_key auto_key{"code"};

    student s = {1, "tom", 0, 19, 1.5, "room2"};
    student s1 = {2, "jack", 1, 20, 2.5, "room3"};
    student s2 = {3, "mke", 2, 21, 3.5, "room4"};
    std::vector<student> v{s, s1, s2};

#ifdef ORMPP_ENABLE_MYSQL
    dbng<mysql> mysql;
    TEST_REQUIRE(mysql.connect(ip, "root", "12345", "testdb"));
    TEST_REQUIRE(mysql.create_datatable<student>(key, not_null));
    TEST_CHECK(mysql.insert(v)==3);

    v[0].name = "test1";
    v[1].name = "test2";

    TEST_CHECK(mysql.update(v[0])==1);
    auto result = mysql.query<student>();
    TEST_CHECK(mysql.update(v[1])==1);
    auto result1 = mysql.query<student>();
#endif


}

TEST_CASE(orm_multi_update){
    ormpp_key key{"code"};
    ormpp_not_null not_null{{"code", "age"}};
    ormpp_auto_key auto_key{"code"};

    student s = {1, "tom", 0, 19, 1.5, "room2"};
    student s1 = {2, "jack", 1, 20, 2.5, "room3"};
    student s2 = {3, "mike", 2, 21, 3.5, "room4"};
    std::vector<student> v{s, s1, s2};

#ifdef ORMPP_ENABLE_MYSQL
    dbng<mysql> mysql;
    TEST_REQUIRE(mysql.connect(ip, "root", "12345", "testdb"));
    TEST_REQUIRE(mysql.create_datatable<student>(key, not_null));
    TEST_CHECK(mysql.insert(v)==3);
    v[0].name = "test1";
    v[1].name = "test2";
    v[2].name = "test3";

    TEST_CHECK(mysql.update(v)==3);
    auto result = mysql.query<student>();
    TEST_CHECK(result.size()==3);
#endif
}

TEST_CASE(orm_delete){
    ormpp_key key{"code"};
    ormpp_not_null not_null{{"code", "age"}};
    ormpp_auto_key auto_key{"code"};

    student s = {1, "tom", 0, 19, 1.5, "room2"};
    student s1 = {2, "jack", 1, 20, 2.5, "room3"};
    student s2 = {3, "mike", 2, 21, 3.5, "room4"};
    std::vector<student> v{s, s1, s2};

#ifdef ORMPP_ENABLE_MYSQL
    dbng<mysql> mysql;
    TEST_REQUIRE(mysql.connect(ip, "root", "12345", "testdb"));
    TEST_REQUIRE(mysql.create_datatable<student>(key, not_null));
    TEST_CHECK(mysql.insert(v)==3);
    TEST_REQUIRE(mysql.delete_records<student>("code=1"));
    TEST_CHECK(mysql.query<student>().size()==2);
    TEST_REQUIRE(mysql.delete_records<student>(""));
    auto result = mysql.query<student>();
    TEST_CHECK(result.size()==0);
#endif

}

TEST_CASE(orm_query){
    ormpp_key key{"id"};
    simple s1 = {1, 2.5, 3};
    simple s2 = {2, 3.5, 4};
    simple s3 = {3, 4.5, 5};
    std::vector<simple> v{s1, s2, s3};

#ifdef ORMPP_ENABLE_MYSQL
    dbng<mysql> mysql;
    TEST_REQUIRE(mysql.connect(ip, "root", "12345", "testdb"));
    TEST_REQUIRE(mysql.create_datatable<simple>(key));
    TEST_CHECK(mysql.insert(v)==3);
    auto result = mysql.query<simple>();
    TEST_CHECK(result.size()==3);
    auto result3 = mysql.query<simple>("where id=1");
    TEST_CHECK(result3.size()==1);
#endif


}

TEST_CASE(orm_query_some){
    ormpp_key key{"code"};
    ormpp_not_null not_null{{"code", "age"}};
    ormpp_auto_key auto_key{"code"};

    student s = {1, "tom", 0, 19, 1.5, "room2"};
    student s1 = {2, "jack", 1, 20, 2.5, "room3"};
    student s2 = {3, "mike", 2, 21, 3.5, "room4"};
    std::vector<student> v{s, s1, s2};

#ifdef ORMPP_ENABLE_MYSQL
    dbng<mysql> mysql;
    TEST_REQUIRE(mysql.connect(ip, "root", "12345", "testdb"));
    TEST_REQUIRE(mysql.create_datatable<student>(key, not_null));
    TEST_CHECK(mysql.insert(v)==3);
    auto result3 = mysql.query<std::tuple<int>>("select count(1) from student");
    TEST_CHECK(result3.size()==1);
    TEST_CHECK(std::get<0>(result3[0])==3);

    auto result4 = mysql.query<std::tuple<int>>("select count(1) from student");
    TEST_CHECK(result4.size()==1);
    TEST_CHECK(std::get<0>(result4[0])==3);

    auto result5 = mysql.query<std::tuple<int>>("select count(1) from student");
    TEST_CHECK(result5.size()==1);
    TEST_CHECK(std::get<0>(result5[0])==3);
    auto result = mysql.query<std::tuple<int, std::string, double>>("select code, name, dm from student");
    TEST_CHECK(result.size()==3);
#endif

}

TEST_CASE(orm_query_multi_table){
    ormpp_key key{"code"};
    ormpp_not_null not_null{{"code", "age"}};
    ormpp_auto_key auto_key{"code"};

    student s = {1, "tom", 0, 19, 1.5, "room2"};
    student s1 = {2, "jack", 1, 20, 2.5, "room3"};
    student s2 = {3, "mike", 2, 21, 3.5, "room4"};
    std::vector<student> v{s, s1, s2};

    ormpp_key key1{"id"};
    person p = {1, "test1", 2};
    person p1 = {2, "test2", 3};
    person p2 = {3, "test3", 4};
    std::vector<person> v1{p, p1, p2};

#ifdef ORMPP_ENABLE_MYSQL
    dbng<mysql> mysql;
    TEST_REQUIRE(mysql.connect(ip, "root", "12345", "testdb"));
    TEST_REQUIRE(mysql.create_datatable<student>(key, not_null));
    TEST_CHECK(mysql.insert(v)==3);
    TEST_REQUIRE(mysql.create_datatable<person>(key1, not_null));
    TEST_CHECK(mysql.insert(v1)==3);
    auto result = mysql.query<std::tuple<person, std::string, int>>("select person.*, student.name, student.age from person, student"s);
    TEST_CHECK(result.size()==9);
    auto result3 = mysql.query<std::tuple<person, student>>("select * from person, student"s);
    TEST_CHECK(result.size()==9);
#endif

}

TEST_CASE(orm_transaction){
    ormpp_key key{"code"};
    ormpp_not_null not_null{{"code", "age"}};
    ormpp_auto_key auto_key{"code"};

    student s = {1, "tom", 0, 19, 1.5, "room2"};
    student s1 = {2, "jack", 1, 20, 2.5, "room3"};
    student s2 = {3, "mike", 2, 21, 3.5, "room4"};
    std::vector<student> v{s, s1, s2};

#ifdef ORMPP_ENABLE_MYSQL
    dbng<mysql> mysql;
    TEST_REQUIRE(mysql.connect(ip, "root", "12345", "testdb"));
    TEST_REQUIRE(mysql.create_datatable<student>(key, not_null));

    TEST_REQUIRE(mysql.begin());
    for (int i = 0; i < 10; ++i) {
        student s = {i, "tom", 0, 19, 1.5, "room2"};
        if(!mysql.insert(s)){
            mysql.rollback();
            return;
        }
    }
    TEST_REQUIRE(mysql.commit());
    auto result = mysql.query<student>();
    TEST_CHECK(result.size()==10);
#endif
}

struct log{
    template<typename... Args>
    bool before(Args... args){
        std::cout<<"log before"<<std::endl;
        return true;
    }

    template<typename T, typename... Args>
    bool after(T t, Args... args){
        std::cout<<"log after"<<std::endl;
        return true;
    }
};

struct validate{
    template<typename... Args>
    bool before(Args... args){
        std::cout<<"validate before"<<std::endl;
        return true;
    }

    template<typename T, typename... Args>
    bool after(T t, Args... args){
        std::cout<<"validate after"<<std::endl;
        return true;
    }
};

TEST_CASE(orm_aop){
    //dbng<mysql> mysql;
    //auto r = mysql.wraper_connect<log, validate>("127.0.0.1", "root", "12345", "testdb");
    //TEST_REQUIRE(r);

    //r = mysql.wraper_execute("drop table if exists person");
    //TEST_REQUIRE(r);

    //r = mysql.wraper_execute<log>("drop table if exists person");
    //TEST_REQUIRE(r);

    //r = mysql.wraper_execute<validate>("drop table if exists person");
    //TEST_REQUIRE(r);

    //r = mysql.wraper_execute<validate, log>("drop table if exists person");
    //TEST_REQUIRE(r);
}
*/
