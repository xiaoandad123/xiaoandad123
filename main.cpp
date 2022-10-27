#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include "XorString.h"
#include "main.h"
#include "initUi.h"
#include "mspkeyapi.h"
#include <openssl/rc4.h>
#include "utils.h"
#include "log.h"
#include <exception>

using namespace hv;

int client(void* lpParam)
{
	GlobalParam* pGlobal = (GlobalParam*)lpParam;
	auto ws = new mspkeyapi(XorStrV1("62cd98135df9d43c97f8a575"), XorStrV1("62c5848304"));
	pGlobal->mspkeyapi_p = ws;

	ws->connect(XorStrV1("ws://120.25.148.102:8811/api/user/ws"));
	return 0;
}

int init(void*)
{
	GlobalParam *globalParam = new GlobalParam;
	globalParam->inputBuffer = new CilentInputBoxBuffer;
	//sprintf_s(globalParam->exe_id, XorStrV1("%s"), XorStrV1("62c5848e497e7f4a7fb67304"));
	//sprintf_s(globalParam->hwid_id, XorStrV1("%s"), XorStrV1("62c5848e49"));
	HANDLE T1 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)client, globalParam, 0, 0);
	CloseHandle(T1);
	HANDLE T2 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HAK_WND, globalParam, 0, 0);
	WaitForSingleObject(T2, -1);
	CloseHandle(T2);
	return 0;
}

int main()
{
	//HANDLE MT = ;
	return WaitForSingleObject(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, 0, 0, 0), -1);
}

