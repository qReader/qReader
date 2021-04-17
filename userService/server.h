#include <gflags/gflags.h>
#include <butil/logging.h>
#include <brpc/server.h>
#include "data.hpp"
#include "userinfo.pb.h"

DEFINE_bool(echo_attachment, true, "Echo attachment as well");
DEFINE_int32(port, 8000, "TCP Port of this server");
DEFINE_int32(idle_timeout_s, -1, "Connection will be closed if there is no "
								 "read/write operations during the last `idle_timeout_s'");
DEFINE_int32(logoff_ms, 2000, "Maximum duration of server's LOGOFF state "
							  "(waiting for client to close connection before server stops)");

namespace userService
{

	class EchoServiceImpl : public EchoService
	{
	public:
		EchoServiceImpl() {};
		virtual ~EchoServiceImpl() {};
		virtual void Echo(google::protobuf::RpcController* cntl_base,
				const EchoRequest* request,
				EchoResponse* response,
				google::protobuf::Closure* done) {
				// This object helps you to call done->Run() in RAII style. If you need
				// to process the request asynchronously, pass done_guard.release().
				brpc::ClosureGuard done_guard(done);
				
				brpc::Controller* cntl =
					static_cast<brpc::Controller*>(cntl_base);
				// The purpose of following logs is to help you to understand
				// how clients interact with servers more intuitively. You should 
				// remove these logs in performance-sensitive servers.
				LOG(INFO) << "Received request[log_id=" << cntl->log_id() 
					<< "] from " << cntl->remote_side() 
					<< " to " << cntl->local_side()
					<< ": " << request->message()
					<< " (attached=" << cntl->request_attachment() << ")";

				// Fill response.
				response->set_message(request->message());

				// You can compress the response by setting Controller, but be aware
				// that compression may be costly, evaluate before turning on.
				// cntl->set_response_compress_type(brpc::COMPRESS_TYPE_GZIP);
				if (FLAGS_echo_attachment) {
					// Set attachment which is wired to network directly instead of
					// being serialized into protobuf messages.
					cntl->response_attachment().append(cntl->request_attachment());
				}
		}
	};

	class loginServiceImpl : public loginService
	{ //登录服务
	public:
		loginServiceImpl(){};
		virtual ~loginServiceImpl(){};
		virtual void loginFun(google::protobuf::RpcController *cntl_base,
							  const loginInfoReq *request,
							  common::commonResp *response,
							  google::protobuf::Closure *done)
		{ //登录函数
			// This object helps you to call done->Run() in RAII style. If you need
			// to process the request asynchronously, pass done_guard.release().
			brpc::ClosureGuard done_guard(done);

			brpc::Controller *cntl =
				static_cast<brpc::Controller *>(cntl_base);

			// The purpose of following logs is to help you to understand
			// how clients interact with servers more intuitively. You should
			// remove these logs in performance-sensitive servers.
			LOG(INFO) << "Received request[log_id=" << cntl->log_id()
					  << "] from " << cntl->remote_side()
					  << " to " << cntl->local_side()
					  << ": " << request->userid()
					  << " (attached=" << cntl->request_attachment() << ")";

			// Fill response.
			if (request->userid() != "201901" || request->userpwd() != "123456")
			{ //账号或密码有误，从数据库匹配
				response->set_code(-1);
				response->set_errorres("wrong account or password");
			}
			else
			{
				response->set_code(1);
			}

			// You can compress the response by setting Controller, but be aware
			// that compression may be costly, evaluate before turning on.
			// cntl->set_response_compress_type(brpc::COMPRESS_TYPE_GZIP);

			if (FLAGS_echo_attachment)
			{
				// Set attachment which is wired to network directly instead of
				// being serialized into protobuf messages.
				cntl->response_attachment().append(cntl->request_attachment());
			}
		}

		virtual void userInfoFun(google::protobuf::RpcController *cntl_base,
								 const userInfoReq *request,
								 userInfoResp *response,
								 google::protobuf::Closure *done)
		{ //获取用户数据函数
			// This object helps you to call done->Run() in RAII style. If you need
			// to process the request asynchronously, pass done_guard.release().
			brpc::ClosureGuard done_guard(done);

			brpc::Controller *cntl =
				static_cast<brpc::Controller *>(cntl_base);

			// The purpose of following logs is to help you to understand
			// how clients interact with servers more intuitively. You should
			// remove these logs in performance-sensitive servers.
			LOG(INFO) << "Received request[log_id=" << cntl->log_id()
					  << "] from " << cntl->remote_side()
					  << " to " << cntl->local_side()
					  << ": " << request->userid()
					  << " (attached=" << cntl->request_attachment() << ")";

			// Fill response.
			if (1)
			{ //获取数据库数据
				response->set_userid("201901");
				response->set_nickname("昵称");
				response->set_headimgurl("图片链接");
				response->set_male(1);
				response->set_age(17);
				response->set_profile("未设置个性签名");
			}
			else
			{//获取用户数据失败
				response->set_userid("401");
				response->set_nickname("昵称异常");
				response->set_headimgurl("头像异常");
				response->set_male(1);
				response->set_age(0);
				response->set_profile("个人简介异常");
			}

			if (FLAGS_echo_attachment)
			{
				// Set attachment which is wired to network directly instead of
				// being serialized into protobuf messages.
				cntl->response_attachment().append(cntl->request_attachment());
			}
		}

		virtual void registerFun(google::protobuf::RpcController *cntl_base,
								 const registerReq *request,
								 common::commonResp *response,
								 google::protobuf::Closure *done)
		{ //注册用户函数
			// This object helps you to call done->Run() in RAII style. If you need
			// to process the request asynchronously, pass done_guard.release().
			brpc::ClosureGuard done_guard(done);

			brpc::Controller *cntl =
				static_cast<brpc::Controller *>(cntl_base);

			// The purpose of following logs is to help you to understand
			// how clients interact with servers more intuitively. You should
			// remove these logs in performance-sensitive servers.
			LOG(INFO) << "Received request[log_id=" << cntl->log_id()
					  << "] from " << cntl->remote_side()
					  << " to " << cntl->local_side()
					  << ": " << request->userid()
					  << ": " << request->userpwd()
					  << " (attached=" << cntl->request_attachment() << ")";

			// Fill response.
			if (1)
			{ //注册并录入数据库成功
				response->set_code(1);
			}
			else
			{
				response->set_code(-1);
				response->set_errorres("注册失败....");
			}

			if (FLAGS_echo_attachment)
			{
				// Set attachment which is wired to network directly instead of
				// being serialized into protobuf messages.
				cntl->response_attachment().append(cntl->request_attachment());
			}
		}

	};



class ControlServiceImpl : public controlService {
	public:
		ControlServiceImpl() {};
		virtual ~ControlServiceImpl() {};
		virtual void getAllUserInfoFun(google::protobuf::RpcController* cntl_base,
				const getAllUserInfoReq* request,
				userInfoRespList* response,
				google::protobuf::Closure* done) {
				// This object helps you to call done->Run() in RAII style. If you need
				// to process the request asynchronously, pass done_guard.release().
				brpc::ClosureGuard done_guard(done);
				
				brpc::Controller* cntl =
					static_cast<brpc::Controller*>(cntl_base);
				// The purpose of following logs is to help you to understand
				// how clients interact with servers more intuitively. You should 
				// remove these logs in performance-sensitive servers.
				LOG(INFO) << "Received request[log_id=" << cntl->log_id() 
					<< "] from " << cntl->remote_side() 
					<< " to " << cntl->local_side()
					<< " (attached=" << cntl->request_attachment() << ")";

				// Fill response.
				vector<UserInfoTable>res;
				
				get_all_user(res);
				int cnt = 0;
				for(auto i : res){
					++cnt;
				cout << i.userId << " "<< i.userHeadImgUrl << " " << endl;
					auto user = response->add_lists();
					user->set_userid(i.userId);
					user->set_nickname(i.userNickName);
					user->set_headimgurl(i.userHeadImgUrl);
					user->set_profile(i.userProfile);
					user->set_male(i.userMale);
					user->set_age(i.userAge);
				}	
				response->set_cnt(cnt);

				// You can compress the response by setting Controller, but be aware
				// that compression may be costly, evaluate before turning on.
				// cntl->set_response_compress_type(brpc::COMPRESS_TYPE_GZIP);
				if (FLAGS_echo_attachment) {
					// Set attachment which is wired to network directly instead of
					// being serialized into protobuf messages.
					cntl->response_attachment().append(cntl->request_attachment());
				}
		}
	};
};
