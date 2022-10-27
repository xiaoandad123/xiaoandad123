#pragma once
#include <string>
#include "XorString.h"
#include <WebSocketClient.h>

using namespace hv;

class ExeInfo {
public:
	std::string ID;
	std::string AdminID;
	std::string Title;
	std::string Versions;
	bool State;
	std::string Notice;
	std::string Address;
	std::string Md5;
	std::string Data;
	std::string Key;
	bool IsDK;
	bool IsReg;
	bool IsDbg;
	bool IsBindIP;
	bool IsDeviceID;
	int64_t GiveTime;
	int64_t BindCount;
public:
	ExeInfo() {};
	~ExeInfo() {};
	ExeInfo(Json json)
	{
		ID = json[XorStrV2("Code")];
		AdminID = json[XorStrV2("AdminID")];
		Title = json[XorStrV2("Title")];
		Versions = json[XorStrV2("Versions")];
		State = json[XorStrV2("State")];
		Notice = json[XorStrV2("Notice")];
		Address = json[XorStrV2("Address")];
		Md5 = json[XorStrV2("Md5")];
		Data = json[XorStrV2("Data")];
		Key = json[XorStrV2("Key")];
		IsDK = json[XorStrV2("IsDK")];
		IsReg = json[XorStrV2("IsReg")];
		IsDbg = json[XorStrV2("IsDbg")];
		IsBindIP = json[XorStrV2("IsBindIP")];
		IsDeviceID = json[XorStrV2("IsDeviceID")];
		GiveTime = json[XorStrV2("GiveTime")];
		BindCount = json[XorStrV2("BindCount")];
	}
};

class DataKey
{
public:
	std::string key;
public:
	DataKey() {};
	~DataKey() {};
	DataKey(Json json)
	{
		key = json[XorStrV2("Key")];
	}
};

class ExeData
{
public:
	std::string data;
public:
	ExeData() {};
	~ExeData() {};
	ExeData(Json json)
	{
		data = json[XorStrV2("ExeData")];
	}
};

class Variable
{
public:
	std::string var;
public:
	Variable() {};
	~Variable() {};
	Variable(Json json)
	{
		var = json[XorStrV2("ExeData")];
	}
};

class UserInfo
{
public:
	std::string ID;
	std::string AdminID;
	std::string DeviceID;
	std::string ExeID;
	std::string Name;
	std::string Pwd;
	std::string Serial;
	bool State;
	std::string RegIP;
	std::string RegTime;
	std::string EndTime;
	std::string LoginTime;
	std::string Bak;
	std::string Sig;
	int64_t BindCont;
	std::string BindTime;
public:
	UserInfo() {};
	~UserInfo() {};
	UserInfo(Json json)
	{
		ID = json[XorStrV2("ID")];
		AdminID = json[XorStrV2("AdminID")];
		DeviceID = json[XorStrV2("DeviceID")];
		ExeID = json[XorStrV2("ExeID")];
		Name = json[XorStrV2("Name")];
		Pwd = json[XorStrV2("Pwd")];
		Serial = json[XorStrV2("Serial")];
		State = json[XorStrV2("State")];
		RegIP = json[XorStrV2("RegIP")];
		RegTime = json[XorStrV2("RegTime")];
		EndTime = json[XorStrV2("EndTime")];
		LoginTime = json[XorStrV2("LoginTime")];
		Bak = json[XorStrV2("Bak")];
		Sig = json[XorStrV2("Sig")];
		BindCont = json[XorStrV2("BindCont")];
		BindTime = json[XorStrV2("BindTime")];
	}

};
