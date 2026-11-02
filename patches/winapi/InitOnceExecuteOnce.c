#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <search.h>

#include "winnt_types.h"
#include "pe_linker.h"
#include "ntoskernel.h"
#include "log.h"
#include "winexports.h"
#include "util.h"

typedef BOOL (WINAPI *PINIT_ONCE_FN_COMPAT)(
    PVOID InitOnce,
    PVOID Parameter,
    PVOID *Context
);

STATIC BOOL WINAPI InitOnceExecuteOnce(
    PVOID InitOnce,
    PINIT_ONCE_FN_COMPAT InitFn,
    PVOID Parameter,
    PVOID *Context)
{
    PVOID *state;
    PVOID ctx = NULL;

    DebugLog(
        "InitOnce=%p InitFn=%p Parameter=%p Context=%p",
        InitOnce,
        InitFn,
        Parameter,
        Context
    );

    if (!InitOnce || !InitFn)
        return FALSE;

    state = (PVOID *)InitOnce;

    /*
     * Already initialized.
     *
     * 1 is our synthetic "completed without context" marker.
     */
    if (*state != NULL) {
        if (Context)
            *Context = (*state == (PVOID)1) ? NULL : *state;

        return TRUE;
    }

    /*
     * Execute the actual initialization callback.
     */
    if (!InitFn(InitOnce, Parameter, &ctx))
        return FALSE;

    /*
     * Remember initialization succeeded.
     */
    *state = ctx ? ctx : (PVOID)1;

    if (Context)
        *Context = ctx;

    return TRUE;
}

DECLARE_CRT_EXPORT(
    "InitOnceExecuteOnce",
    InitOnceExecuteOnce
);
