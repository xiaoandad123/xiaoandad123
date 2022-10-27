#pragma once

struct GameInfo
{
    unsigned __int32                hWnd = 0;
    void* hProcess = 0;
    unsigned long       dwProcessId = 0;
    unsigned __int64      dwModuleBase = 0;
    unsigned __int64      objXYZbaseAddr = 0;
    unsigned __int64      dwModuleSize = 0;
};

struct GuiWndParam
{
    int         Width = 170;
    int         Height = 195;
    bool        showlogin = true;
    bool        showmenu = true;
};

struct UiStatus
{
    bool show = true;
    bool islogin = false;
    //bool wait_login_repo = false;
    //bool wait_reg_repo = false;
    //bool wait_vfcode_repo = false;
    //bool wait_pay_repo = false;
};

struct CilentInputBoxBuffer
{
    char exe_id[260] = "";
    char hwid_id[260] = "";
    char vif_code_inpu[8] = "";
    char reg_username[260] = "";
    char reg_password[260] = "";
    char logoin_username[260] = "";
    char logoin_password[260] = "";
    char pay_newcar_user[260] = "";
    char new_card_serial[260] = "";
    char rebind_hwid_user[260] = "";
    char rebind_hwid_pswd[260] = "";
    char reset_pswd_user[260] = "";
    char reset_pswd_newpswd[260] = "";
    char reset_pswd_oldpswd[260] = "";
};

struct Offsets
{
    unsigned __int64 mapObjBase = 0;
    unsigned __int64 mmissPosBase = 0;
    unsigned __int64 mapObjO2 = 0;
    unsigned __int64 mapObjO5 = 0;
    unsigned __int64 mmissPosO6 = 0;
};

struct GlobalParam
{
    char exe_id[260] = "";
    char hwid_id[260] = "";
    char servet_url[260] = "";
    void* mspkeyapi_p = nullptr;
    GameInfo                gameInfo;
    Offsets			        offsets;
    GuiWndParam             guiParam;
    UiStatus                uiStatus;
    CilentInputBoxBuffer* inputBuffer = nullptr;
};

