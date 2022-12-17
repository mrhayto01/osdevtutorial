#pragma once

#include <Windows.h>
#include <ntstatus.h>
#include <stdio.h>

#pragma comment(lib, "ntdll.lib")

#define TOKEN_QUERY             (0x0008)

#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)

NTSTATUS NTAPI NtOpenProcessToken(
    _In_ HANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PHANDLE TokenHandle);

NTSTATUS NTAPI NtQueryInformationToken(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _Out_writes_bytes_to_opt_(TokenInformationLength, *ReturnLength) PVOID TokenInformation,
    _In_ ULONG TokenInformationLength,
    _Out_ PULONG ReturnLength);

NTSTATUS NTAPI NtClose(HANDLE Handle);

NTSTATUS NTAPI RtlAllocateAndInitializeSid(
    _In_ PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
    _In_ UCHAR SubAuthorityCount,
    _In_ ULONG SubAuthority0,
    _In_ ULONG SubAuthority1,
    _In_ ULONG SubAuthority2,
    _In_ ULONG SubAuthority3,
    _In_ ULONG SubAuthority4,
    _In_ ULONG SubAuthority5,
    _In_ ULONG SubAuthority6,
    _In_ ULONG SubAuthority7,
    _Out_ PSID* Sid);

BOOLEAN NTAPI RtlEqualSid(
    _In_ PSID Sid1,
    _In_ PSID Sid2);

PVOID NTAPI RtlFreeSid(
    _In_ PSID Sid);
