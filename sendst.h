#pragma once
#include <string>
#include "tagdef.h"
#include <WebSocketClient.h>

using namespace hv;

class GetParameterParam {
public:
	std::string ExeID;
	std::string DeviceID;
public:
	GetParameterParam(char* exeID, char* deviceID)
	{
		ExeID = exeID;
		DeviceID = deviceID;
	}
	~GetParameterParam() {};
	Json toJson() {
		Json j;
		j[XorStrV2("Type")] = TAG_GetParameter;
		j[XorStrV2("Data")][XorStrV2("ExeID")] = ExeID.c_str();
		j[XorStrV2("Data")][XorStrV2("DeviceID")] = DeviceID.c_str();
		return j;
	}
};

class RegisterParam {
public:
	std::string Name;
	std::string Pwd;
	std::string Code;
public:
	RegisterParam(char* name, char* pwd, char* code)
	{
		Name = name;
		Pwd = pwd;
		Code = code;
	}
	~RegisterParam() {};
	Json toJson() {
		Json j;
		j[XorStrV2("Type")] = TAG_Register;
		j[XorStrV2("Data")][XorStrV2("Name")] = Name.c_str();
		j[XorStrV2("Data")][XorStrV2("Pwd")] = Pwd.c_str();
		j[XorStrV2("Data")][XorStrV2("Code")] = Code.c_str();
		return j;
	}
};

class LoginParam {
public:
	std::string Name;
	std::string Pwd;
public:
	LoginParam(char* name, char* pwd)
	{
		Name = name;
		Pwd = pwd;
	}
	~LoginParam() {};
	Json toJson() {
		Json j;
		j[XorStrV2("Type")] = TAG_Login;
		j[XorStrV2("Data")][XorStrV2("Name")] = Name.c_str();
		j[XorStrV2("Data")][XorStrV2("Pwd")] = Pwd.c_str();
		return j;
	}
};

class CarLoginParam {
public:
	std::string Sig;
public:
	CarLoginParam(char* sig)
	{
		Sig = sig;
	}
	~CarLoginParam() {};
	Json toJson() {
		Json j;
		j[XorStrV2("Type")] = TAG_CarLogin;
		j[XorStrV2("Data")][XorStrV2("Serial")] = Sig.c_str();
		return j;
	}
};

class UserPayParam {
public:
	std::string Name;
	std::string Serial;
public:
	UserPayParam(char* name, char* serial)
	{
		Name = name;
		Serial = serial;
	}
	~UserPayParam() {};
	Json toJson() {
		Json j;
		j[XorStrV2("Type")] = TAG_UserPay;
		j[XorStrV2("Data")][XorStrV2("Name")] = Name.c_str();
		j[XorStrV2("Data")][XorStrV2("Serial")] = Serial.c_str();
		return j;
	}
};

class UpUserPwdParam {
public:
	std::string Name;
	std::string OldPwd;
	std::string NewPwd;
public:
	UpUserPwdParam(char* name, char* oldpwd, char* newpwd)
	{
		Name = name;
		OldPwd = oldpwd;
		NewPwd = newpwd;
	}
	~UpUserPwdParam() {};
	Json toJson() {
		Json j;
		j[XorStrV2("Type")] = TAG_UpUserPwd;
		j[XorStrV2("Data")][XorStrV2("Name")] = Name.c_str();
		j[XorStrV2("Data")][XorStrV2("OldPwd")] = OldPwd.c_str();
		j[XorStrV2("Data")][XorStrV2("NewPwd")] = NewPwd.c_str();
		return j;
	}
};

class BindDeviceIDParam {
public:
	std::string Name;
	std::string Pwd;
public:
	BindDeviceIDParam(char* name, char* pwd)
	{
		Name = name;
		Pwd = pwd;
	}
	~BindDeviceIDParam() {};
	Json toJson() {
		Json j;
		j[XorStrV2("Type")] = TAG_BindDeviceID;
		j[XorStrV2("Data")][XorStrV2("Name")] = Name.c_str();
		j[XorStrV2("Data")][XorStrV2("Pwd")] = Pwd.c_str();
		return j;
	}
};

class GetVariableParam {
public:
	std::string Key;
public:
	GetVariableParam(char* key)
	{
		Key = key;
	}
	~GetVariableParam() {};
	Json toJson() {
		Json j;
		j[XorStrV2("Type")] = TAG_GetVariable;
		j[XorStrV2("Data")][XorStrV2("Key")] = Key.c_str();
		return j;
	}
};