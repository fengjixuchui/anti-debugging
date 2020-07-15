#pragma once

#include <windows.h>
#include <iostream>
#include <Winternl.h>

bool hasADbgAttached = true;

LONG WINAPI GetExecutedOnUnhandledException(EXCEPTION_POINTERS * pExceptionInfo) {
    hasADbgAttached = false;

    // thx @mambda for this tip!
    pExceptionInfo->ContextRecord->Eip += 1;
    
    return EXCEPTION_CONTINUE_EXECUTION;
}

bool MethodUnhandledException() {
    hasADbgAttached = true;

    SetUnhandledExceptionFilter(
      (LPTOP_LEVEL_EXCEPTION_FILTER) GetExecutedOnUnhandledException
    );

    __debugbreak( );

    return hasADbgAttached;
}