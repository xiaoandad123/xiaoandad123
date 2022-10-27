#pragma once

#include <WebSocketClient.h>
#include <openssl/rc4.h>
#include <base64.h>
#include "XorString.h"
#include "recvst.h"
#include "sendst.h"
#include "utils.h"
#include "log.h"

using namespace hv;

class mspkeyapi : public WebSocketClient
{
protected:
	int login = 0;
	int isinit = 0;
	int getpram = 0;
	std::string e_msg;
	std::string msg_key = std::string(XorStrV1("mspkey"));
	std::string check_code;
	Variable vars;
	ExeData core_data;

public:
	mspkeyapi(char* exeID, char* deviceID);
	void connect(char* url);
	void disconnect();
	void Register(char* name, char* pwd, char* code);
	void GetCode();
	void Login(char* name, char* pwd);
	void CardLogin(char* sig);
	void UserPay(char* name, char* serial);
	void UpUserPwd(char* name, char* oldpwd, char* newpwd);
	void BindDeviceID(char* name, char* pwd);
	void AddBlack();
	void GetExeData();
	void GetVariable(char* var_key_name);

	int IsLogin();

	std::string ParseExeData();
	std::string ParseVariable();
	std::string ParseErrMsg();
	std::string ParseCheckCode();

	std::string UTF8_2_Asni(std::string  _SrcStr);
	std::string Asni_2_UTF8(std::string  _SrcStr);

protected:
	void msgproc(std::string msg);
	void _getParameter(char* exeID, char* deviceID);
	std::string rc4(std::string data, std::string key);
	int rc4send(std::string data);
};

