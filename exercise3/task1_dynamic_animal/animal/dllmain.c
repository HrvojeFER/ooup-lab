#include "pch.h"


// ReSharper disable once CppInconsistentNaming
BOOL APIENTRY DllMain(HMODULE h_module, const DWORD ul_reason_for_call, LPVOID lp_reserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: // NOLINT(bugprone-branch-clone)
        printf("Initializing animals...\n");
        break;
    case DLL_THREAD_ATTACH: // NOLINT(bugprone-branch-clone)
        printf("Initializing animals on thread...\n");
        break;
    case DLL_THREAD_DETACH: // NOLINT(bugprone-branch-clone)
        printf("Terminating animals on thread...\n");
        break;
    case DLL_PROCESS_DETACH: // NOLINT(bugprone-branch-clone)
        printf("Terminating animals...\n");
        break;
    default:
        break;
    }
    return TRUE;
}
