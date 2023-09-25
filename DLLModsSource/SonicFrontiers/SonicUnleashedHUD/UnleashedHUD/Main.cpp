#include "Main.h"
float Main::intensity = 90.0f;


void __declspec(naked) GetScoreEnabled()
{
	static uint32_t returnAddress = 0x1401CFFA0;
	__asm
	{
        lea r8, returnAddress
		movups xmm9, [r8]
		jmp [returnAddress]
	}
}

void __declspec(naked) HudSonicStage_CRivalMetalSonicLastHit()
{
    static uint32_t returnAddress = 0xCC8B73;
    __asm
    {
        add     eax, 0FFFFFFFFh
        mov     [edi + 200h], eax
        fldz
        sub     esp, 8
        jmp     [returnAddress]
    }
}

HOOK(void, __fastcall, HudSonicStage_CBossPerfectChaosCStateDefeated, 0x5D1C70, void* This)
{
    originalHudSonicStage_CBossPerfectChaosCStateDefeated(This);
}

void Main::Install()
{
	// WRITE_JUMP(ADDR, METHOD)
	// See: GetScoreEnabled
	WRITE_JUMP(0x1401CFF9D, GetScoreEnabled);
}