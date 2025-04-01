#include <cbase.h>


#include <engine_memutils.h>
#include <memytools.h>
#include <atomic>
#include <csignal>

volatile uintptr_t GetSpewPtr = NULL;
bool initEngineSpew()
{
	    /*                     v-- unique string -------------v
        FUN_180282d10(param_1,"\nConsole History (reversed)\n\n",95000,-1);
		do {
			lVar9 = lVar9 + 1;
		} while (param_1[lVar9] != '\0');
		iVar8 = (int)lVar9;
		if ((ulonglong)(longlong)iVar8 < 95000) {
			FUN_1802077c0((undefined8 *)(param_1 + iVar8),94999 - iVar8);
			param_1[94999] = '\0';
		}
		return;



			   18020ac30 48  8b  c4       MOV        RAX ,RSP
	   18020ac33 48  89  58       MOV        qword ptr [RAX  + local_res10 ],RBX
				 10
	   18020ac37 48  89  70       MOV        qword ptr [RAX  + local_res18 ],RSI
				 18
	   18020ac3b 48  89  48       MOV        qword ptr [RAX  + local_res8 ],param_1
				 08
	   18020ac3f 57              PUSH       RDI
	   18020ac40 41  56           PUSH       R14
	   18020ac42 41  57           PUSH       R15
	   18020ac44 48  81  ec       SUB        RSP ,0x270
				 70  02  00
				 00
	   18020ac4b 0f  29  70       MOVAPS     xmmword ptr [RAX  + local_28[0] ],XMM6
				 d8
	   18020ac4f 0f  29  78       MOVAPS     xmmword ptr [RAX  + local_38[0] ],XMM7
				 c8
	   18020ac53 4c  8b  f9       MOV        R15 ,param_1
	   18020ac56 49  c7  c6       MOV        R14 ,-0x1
				 ff  ff  ff
				 ff
    */
#ifdef _WINDOWS
#ifdef _WIN64
	//Signature for FUN_18020ac30:
	// 48 8b c4 48 89 58 10 48 89 70 18 48 89 48 08 57 41 56 41 57 48 81 ec 70 02 00 00 0f 29 70 d8 0f 29 78 c8 4c 8b f9 49 c7 c6 ff ff ff ff
	static constexpr const char* pattern = "\x48\x8B\xC4\x48\x89\x58\x10\x48\x89\x70\x18\x48\x89\x48\x08\x57\x41\x56\x41\x57\x48\x81\xEC\x70\x02\x00\x00\x0F\x29\x70\xD8\x0F\x29\x78\xC8\x4C\x8B\xF9\x49\xC7\xC6\xFF\xFF\xFF\xFF";
	static constexpr size_t patternSize = 45;
#else
	    /*                              v-- unique string -------------v
        sub_10246FC0(Destination, "\nConsole History (reversed)\n\n", 95000, -1);
        v16 = strlen(Destination);
        if (v16 < 0x17318)
        {
            result = GetSpew_sub_101FC3A0(&Destination[v16], 94999 - v16);
            Destination[94999] = 0;
        }
        return result;
		*/
	//Signature for  GetSpew_sub_101FC3A0:
	//55 8B EC 53 FF 15 ?  ?  ?  ?  8B D0 BB  ?  ?  ?  ? 3B 15 ? ? ? ?     74 ? 8B CA 33 C0 F0 0F B1 0B 85 C0 74 ? F3 90 6A 00 52 8B CB FF 15 ? ? ? ? EB ? FF 05 ? ? ? ? 0F B7 05 ? ? ? ?
	static constexpr const char* pattern = "\x55\x8B\xEC\x53\xFF\x15\x2A\x2A\x2A\x2A\x8B\xD0\xBB\x2A\x2A\x2A\x2A\x3B\x15\x2A\x2A\x2A\x2A\x74\x2A\x8B\xCA\x33\xC0\xF0\x0F\xB1\x0B\x85\xC0\x74\x2A\xF3\x90\x6A\x00\x52\x8B\xCB\xFF\x15\x2A\x2A\x2A\x2A\xEB\x2A\xFF\x05\x2A\x2A\x2A\x2A\x0F\xB7\x05\x2A\x2A\x2A\x2A";
	static constexpr size_t         patternSize = 65;
#endif
#else // LINUX

    // for now these sigs are the same
    // -sappho
//#ifdef GAME_DLL
//  // Signature for _Z7GetSpewPcj:
//  // 55 89 E5 57 56 53 83 EC 2C 8B 7D 08 8B 75 0C E8 ? ? ? ?
//  static constexpr const char*    pattern     = "\x55\x89\xE5\x57\x56\x53\x83\xEC\x2C\x8B\x7D\x08\x8B\x75\x0C\xE8\x2A\x2A\x2A\x2A";
//  static constexpr size_t         patternSize = 20;
//#else
#ifdef _WIN64
	// Signature for FUN_0069b3e0:
	// 55 48 8d 0d ?? ?? ?? ?? 48 89 e5 41 57 41 56 49 89 fe 41 55 49 89 f5 41 54 4c 8d 25 ?? ?? ?? ??
	static constexpr const char* pattern = "\x55\x48\x8D\x0D\x2A\x2A\x2A\x2A\x48\x89\xE5\x41\x57\x41\x56\x49\x89\xFE\x41\x55\x49\x89\xF5\x41\x54\x4C\x8D\x25\x2A\x2A\x2A\x2A";
	static constexpr size_t         patternSize = 32;
#else
    // Signature for sub_5742E0:
    // 55 89 E5 57 56 53 83 EC 2C 8B 7D 08 8B 75 0C E8 ? ? ? ?
    static constexpr const char*    pattern     = "\x55\x89\xE5\x57\x56\x53\x83\xEC\x2C\x8B\x7D\x08\x8B\x75\x0C\xE8\x2A\x2A\x2A\x2A";
    static constexpr size_t         patternSize = 20;       
#endif
#endif

    GetSpewPtr = memy::FindPattern(engine_bin, pattern, patternSize, 0);
    ConVarRef sys_minidumpspewlines("sys_minidumpspewlines", false);
    if (sys_minidumpspewlines.IsValid())
    {
        // will never be null if valid
        ConVar* spewCvar = static_cast<ConVar*>(sys_minidumpspewlines.GetLinkedConVar());
        // up defaults from 512 to 2048
        spewCvar->SetDefault("2048");
        spewCvar->SetValue(2048);
        return true;
    }
    return false;
}

char SpewOut[256000] = {};
// Do not free the return value of this function ever - it is a global char[256000]
char* Engine_GetSpew()
{
	typedef void GetSpew(char* buffer, unsigned int length);
	GetSpew* SpewFunc = (GetSpew*)GetSpewPtr;
    SpewFunc( (char*)SpewOut, 256000 );
	return SpewOut;
}

#ifdef GAME_DLL
#include <iclient.h>
#include <inetchannel.h>
#include <inetchannelinfo.h>

// uniquish string demorestart in ExecStringCmd, that function + 3, see here
// https://github.com/sapphonie/StAC-tf2/blob/a834bb1c2b4a0431de9b89998504684e3fc7af5f/gamedata/stac.txt#L86-L130
/*
 dd offset _ZN11CBaseClient20ExecuteStringCommandEPKc ; CBaseClient::ExecuteStringCommand(char const*)
 dd offset _ZN11CBaseClient10SendNetMsgER11INetMessageb ; CBaseClient::SendNetMsg(INetMessage &,bool)
 dd offset _ZN11CBaseClient12ClientPrintfEPKcz ; CBaseClient::ClientPrintf(char const*,...)
 dd offset _ZNK11CBaseClient11IsConnectedEv ; CBaseClient::IsConnected(void)
 dd offset _ZNK11CBaseClient9IsSpawnedEv ; CBaseClient::IsSpawned(void)
 dd offset _ZNK11CBaseClient8IsActiveEv ; CBaseClient::IsActive(void)
*/

/*
	sub_1009B4E0
	sub_1009B4E0
	sub_1009B4E0
	sub_1009B4E0          ; BOOL __thiscall sub_1009B4E0(_DWORD *this)
	sub_1009B4E0          sub_1009B4E0 proc near
	sub_1009B4E0      000 xor     eax, eax        ; Logical Exclusive OR
	sub_1009B4E0+2    000 cmp     dword ptr [ecx+0C4h], 6 ; Compare Two Operands (you want the 0xC4 here)
	sub_1009B4E0+9    000 setz    al              ; Set Byte if Zero (ZF=1)
	sub_1009B4E0+C    000 retn                    ; Return Near from Procedure
	sub_1009B4E0+C        sub_1009B4E0 endp
	sub_1009B4E0+C
*/

int GetSignOnStateFromNetChanInfo(INetChannelInfo* info)
{
	if (!info)
	{
		return -1;
	}
	INetChannel* netchan = static_cast<INetChannel*>(info);
	IClient* iclient = static_cast<IClient*>(netchan->GetMsgHandler());
	if (!iclient)
	{
		return -1;
	}
	uintptr_t iclient_addr = (uintptr_t)iclient;

#ifdef _WIN32
	uintptr_t offs = 0xC4;
#else
	uintptr_t offs = 0xC8;
#endif

#ifdef _WIN32
	uint8 signonstate_byte = *(reinterpret_cast<uint8*>( iclient_addr + offs));
#else
	uint8 signonstate_byte = *(reinterpret_cast<uint8*>( (iclient_addr - 0x4) + offs));
#endif
	int signonstate = signonstate_byte;

	return signonstate;
}


int UTIL_GetSignonState(CBasePlayer* basePlayer)
{
	if (!basePlayer)
	{
		Warning("Null baseplayer in GetClientSignonstate\n");
		return -1;
	}
	INetChannelInfo* info = engine->GetPlayerNetInfo(basePlayer->entindex());
	return GetSignOnStateFromNetChanInfo(info);
}


int UTIL_GetSignonState(INetChannelInfo* info)
{
	return GetSignOnStateFromNetChanInfo(info);
}


bool UTIL_IsFullySignedOn(CBasePlayer* basePlayer)
{
	int signonstate = UTIL_GetSignonState(basePlayer);
	if (signonstate != 6 && signonstate != 7)
	{
		return false;
	}
	return true;
}

#endif

/*
	if ( !UTIL_IsFullySignedOn(pPlayer) )
	{
		return TICK_INTERVAL;
	}
*/
