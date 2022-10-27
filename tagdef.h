#pragma once
#include "XorString.h"

#define GRECV_TAG msgjson[XorStrV2("Tag")]
#define GRECV_DATA msgjson[XorStrV2("Data")]
#define GRECV_CODE msgjson[XorStrV2("Code")]
#define GRECV_MSG msgjson[XorStrV2("Msg")]
#define GRECV_CLEAR msgjson.clear()

#define TAG_DevKey XorStrV1("DevKey")
#define TAG_GetParameter XorStrV1("GetParameter")
#define TAG_Register XorStrV1("Register")
#define TAG_GetExeInfo XorStrV1("GetExeInfo")
#define TAG_GetCode XorStrV1("GetCode")
#define TAG_Login XorStrV1("Login")
#define TAG_CarLogin XorStrV1("CarLogin")
#define TAG_UserPay XorStrV1("UserPay")
#define TAG_UpUserPwd XorStrV1("UpUserPwd")
#define TAG_BindDeviceID XorStrV1("BindDeviceID")
#define TAG_AddBlack XorStrV1("AddBlack")
#define TAG_GetUserInfo XorStrV1("GetUserInfo")
#define TAG_GetDataKey XorStrV1("GetDataKey")
#define TAG_GetExeData XorStrV1("GetExeData")
#define TAG_GetVariable XorStrV1("GetVariable")


//#define 变量表类名 "VAR_TABLE"     
//#define 变量数键名 "VAR_NUM"
//#define 变量表键名 "VAR_NAME"
//{
//	"TYPE":"VAR_TABLE",
//	"VAR_NUM":1,
//	"VAR_NAME":{"1":0x01, "2" : 0x02},
//}