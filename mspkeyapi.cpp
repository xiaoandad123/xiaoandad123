#include "mspkeyapi.h"
#include <iostream>
#include "openssl/RC4.h"

using namespace hv;

mspkeyapi::mspkeyapi(char* exeID, char* deviceID) {
	onopen = []() {};
	onclose = []() {};
	onmessage = [&, this](const std::string& msg) {
		msgproc(msg);
		if (getpram == 0)
		{
			log("[+] Call GetParameter\n");
			_getParameter(exeID, deviceID);
		}
	};
};

void mspkeyapi::connect(char* url)
{
	this->open(url);
}

void mspkeyapi::disconnect()
{
	this->close();
}

void mspkeyapi::_getParameter(char* exeID, char* deviceID)
{
	rc4send(GetParameterParam(exeID, deviceID).toJson().dump());
}

void mspkeyapi::Register(char* name, char* pwd, char* code)
{
	rc4send(RegisterParam(name, pwd, code).toJson().dump());
}

void mspkeyapi::GetCode()
{
	Json req;
	req[XorStrV2("Type")] = TAG_GetCode;
	rc4send(req.dump());
}

void mspkeyapi::Login(char* name, char* pwd)
{
	rc4send(LoginParam(name, pwd).toJson().dump());
}

void mspkeyapi::CardLogin(char* sig) {
	rc4send(CarLoginParam(sig).toJson().dump());
}

void mspkeyapi::UserPay(char* name, char* serial) {
	rc4send(UserPayParam(name, serial).toJson().dump());
}

void mspkeyapi::UpUserPwd(char* name, char* oldpwd, char* newpwd) {
	rc4send(UpUserPwdParam(name, oldpwd, newpwd).toJson().dump());
}

void mspkeyapi::BindDeviceID(char* name, char* pwd) {
	rc4send(BindDeviceIDParam(name, pwd).toJson().dump());
}

void mspkeyapi::AddBlack()
{
	Json req;
	req[XorStrV2("Type")] = TAG_AddBlack;
	rc4send(req.dump());
}

void mspkeyapi::GetExeData()
{
	Json req;
	req[XorStrV2("Type")] = TAG_GetExeData;
	rc4send(req.dump());
}

void mspkeyapi::GetVariable(char* var_key_name) {
	rc4send(GetVariableParam(var_key_name).toJson().dump());
}

int mspkeyapi::IsLogin()
{
	return login;
}

std::string mspkeyapi::ParseExeData()
{
	return vars.var;
}

std::string mspkeyapi::ParseVariable()
{
	return core_data.data;
}

std::string mspkeyapi::ParseErrMsg()
{
	return e_msg;
}

std::string mspkeyapi::ParseCheckCode()
{
	return check_code;
}

std::string mspkeyapi::UTF8_2_Asni(std::string _SrcStr)
{
	size_t buf_size = _SrcStr.size() + 1;
	char *_DstBuf = new char[buf_size];
	memset(_DstBuf, 0, buf_size);
	UTF8ToAnsi((char*)_SrcStr.c_str(), _DstBuf);
	auto s = std::string(_DstBuf);
	//memset(_DstBuf, 0, buf_size);
	//delete[] _DstBuf;
	return s;
}

std::string mspkeyapi::Asni_2_UTF8(std::string _SrcStr)
{
	size_t buf_size = _SrcStr.size() + 1;
	char* _DstBuf = new char[buf_size];
	memset(_DstBuf, 0, buf_size);
	AnsiToUTF8((char*)_SrcStr.c_str(), _DstBuf);
	auto s = std::string(_DstBuf);
	//memset(_DstBuf, 0, buf_size);
	//delete[] _DstBuf;
	return s;
}

std::string mspkeyapi::rc4(std::string data, std::string key)
{
	size_t dataLen = data.length();
	size_t key_Len = key.length();

	unsigned char* inbuf = new unsigned char[dataLen + 1];
	unsigned char* outbuf = new unsigned char[dataLen + 1];
	memset(inbuf, 0, dataLen + 1);
	memset(outbuf, 0, dataLen + 1);

	RC4_KEY s_table;
	RC4_set_key(&s_table, key_Len, (unsigned char*)key.data());   //初始化s_table
	RC4(&s_table, dataLen, (unsigned char*)data.data(), (unsigned char*)outbuf);  //加解密

	log("[+] func: rc4 - dataLen: %u key_Len: %u\n", dataLen, key_Len);

	std::string out((char*)outbuf);
	delete[]inbuf;
	delete[]outbuf;
	//return (char*)outbuf;
	return out;
}

int mspkeyapi::rc4send(std::string data)
{
	auto data_size = data.size();
	auto _data = rc4(data, msg_key);

	//auto data_size2 = data.size();
	//auto _dat2 = rc4(_data, msg_key);
	//std::cout << "[#] no crypt size: " << data_size << " data :\n    " << data << "\n";
	//std::cout << "[#] is crypt size: " << _data.size() << " data :\n    "<< _data << "\n";
	//std::cout << "[#] the decrypt size: " << _dat2.size() << " test :\n    "<< _dat2 << "\n";
	//std::cout << "[#] send to server... \n";

	return send(_data);
}

void mspkeyapi::msgproc(std::string msg)
{
	std::string err;
	auto decrtype = rc4(msg, msg_key);
	log("[+] 当前key: %s 接收到： %s\n", msg_key.c_str(), UTF8_2_Asni(decrtype).c_str());

	auto msgjson = Json::parse(decrtype);

	auto _tag = GRECV_TAG.dump();
	Json code = GRECV_CODE;
	Json data = GRECV_DATA;

	if (code == 1)
	{
		log("libkeyapi::msgproc - code:%u _tag: %s", code, _tag.c_str());
		if (_tag == XorStrV2("\"DevKey\""))
		{
			std::vector<std::string> t;
			msg_key = msgjson[XorStrV2("Data")].dump();
			StringSplit(msg_key, *"\"", t);
			msg_key = t[1];
			log(XorStrV1("[+] New key: %s\n"), msg_key.c_str());
			t.clear();
			if (isinit != 1)
			{
				isinit = msgjson[XorStrV2("Code")].get<int>();
			}
		}
		else if (_tag == XorStrV1("\"GetParameter\""))
		{
			if (getpram != 1)
			{
				getpram = msgjson[XorStrV2("Code")];
			}
		}
		else if (_tag == XorStrV1("\"GetCode\""))
		{
			check_code.clear();
			check_code = msgjson[XorStrV2("Data")].get<std::string>();
		}
		else if (_tag == XorStrV1("\"Login\""))
		{
			if (login != 1)
			{
				login = msgjson[XorStrV2("Code")];
			}
		}
		else if (_tag == XorStrV1("\"CarLogin\""))
		{
			if (login != 1)
			{
				login = msgjson[XorStrV2("Code")];
			}
		}
		else if (_tag == XorStrV1("\"GetVariable\""))
		{
			vars = Variable(data);
		}
		else if (_tag == XorStrV1("\"GetExeData\"")) {
			core_data = ExeData(data);
		}
		_tag.clear();
		code.clear();
		data.clear();
	}
	e_msg.clear();
	auto es = UTF8_2_Asni(msgjson[XorStrV2("Msg")].dump());
	e_msg = (es == XorStrV1("\"接口通讯密钥\"")) ? std::string("\0\0") : msgjson[XorStrV2("Msg")].dump();
	es.clear();
	msgjson.clear();
	decrtype.clear();
	err.clear();
}