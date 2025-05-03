#ifndef ENGINEDETOURS_H
#define ENGINEDETOURS_H


#ifdef _WIN32
#pragma once
#endif

#undef NOINLINE
#undef FASTCALL
#define __thiscall
#include <valve_minmax_off.h>
#define ZYDIS_DEPRECATED
#include <polyhook2/IHook.hpp>

#ifdef _WIN64
#include <polyhook2/Detour/x64Detour.hpp>
#else
#include <polyhook2/Detour/x86Detour.hpp>
#endif

#include <valve_minmax_on.h>
#include <helpers/misc_helpers.h>
#include <memy/memytools.h>
#ifdef CLIENT_DLL
#ifdef BLACKLISTS
    #include <qol/blacklists.h>
#endif
#endif

#ifdef GAME_DLL


struct GIGAplayerStruct
{
    int                     entindex                    = -1;
    CBasePlayer*            basePlayerParent            = nullptr;
    int 					m_iLastProcessPacketTick    = 0;
    int 					m_iThisProcessPacketTick    = 0;
    double 					m_dflProcessPacketTime      = 0.0;
};


#endif


#ifdef SDKSENTRY
    #include <sdksentry/sdksentry.h>
#endif


class sdkdetour
{
public:
    void whackVars()
    {
        patternSize         = {};
        pattern             = {};
        patternAddr         = {};
        detourPtr           = {};
        // callbackAddr     = {};
        detourTrampoline    = {};
    };

    sdkdetour()
    {
        //Warning("test");
        whackVars();
    };
    ~sdkdetour()
    {
        //Warning("untest");
        //detourPtr->unHook(); // broken by dynamic code policy on windows...?
        //whackVars();
    };
    size_t patternSize          = {};
    const char* pattern         = {};
    uintptr_t patternAddr       = {};
#ifdef _WIN64
    PLH::x64Detour* detourPtr   = {};
#else
    PLH::x86Detour* detourPtr   = {};
#endif
    //uint64_t callbackAddr       = {};
    uint64_t detourTrampoline   = {};
};

static void populateAndInitDetour(sdkdetour* detour, void* callback)
{
    detour->patternAddr = memy::FindPattern
    (
        engine_bin,
        detour->pattern,
        detour->patternSize,
        0
    );
    if (!detour->patternAddr)
    {
        Error("Could not get address for detour!");
    }
#ifdef _WIN64
    detour->detourPtr = new PLH::x64Detour
#else
    detour->detourPtr = new PLH::x86Detour
#endif
    (
        (const uint64_t)detour->patternAddr,
        (const uint64_t)(callback),
        &detour->detourTrampoline
    );
    detour->detourPtr->hook();
}


class CEngineDetours : public CAutoGameSystem
{
public:
                        CEngineDetours();

    void                Shutdown() override;

};

extern CEngineDetours* gCEngineDetours;

#endif
