#include "Header.h"

int main()
{
    NTSTATUS status;
    int flag = 0;
    HANDLE hToken = NULL;
    PTOKEN_GROUPS pTkGroups = NULL;
    ULONG attributes, i, retLen = 0;
    PSID adminGroup = NULL;
    SID_IDENTIFIER_AUTHORITY ntAuth = SECURITY_NT_AUTHORITY;

    if (NtOpenProcessToken(NtCurrentProcess(), TOKEN_QUERY, &hToken) < 0) return 1;
    do
    {
        status = NtQueryInformationToken(hToken, TokenGroups, NULL, 0, &retLen);
        if (status != STATUS_BUFFER_OVERFLOW && status != STATUS_BUFFER_TOO_SMALL && status != STATUS_INFO_LENGTH_MISMATCH) break;

        pTkGroups = malloc(retLen);
        if (pTkGroups == NULL) break;

        if (NtQueryInformationToken(hToken, TokenGroups, pTkGroups, retLen, &retLen) < 0) break;
        if (RtlAllocateAndInitializeSid(&ntAuth, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminGroup) < 0) break;

        for (i = 0; i < pTkGroups->GroupCount; i++)
        {
            attributes = pTkGroups->Groups[i].Attributes;
            if (RtlEqualSid(adminGroup, pTkGroups->Groups[i].Sid))
            {
                if ((attributes & SE_GROUP_ENABLED) && (!(attributes & SE_GROUP_USE_FOR_DENY_ONLY)))
                {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag != 1) flag = -1;
    } while (FALSE);

    if (hToken) NtClose(hToken);
    if (pTkGroups) free(pTkGroups);
    if (adminGroup) RtlFreeSid(adminGroup);

    if (flag == 1) printf("Process Has Admin Access\r\n");
    else if (flag == -1) printf("Process does not Have Admin Access\r\n");
    else printf("Can not Determine Admin Access\r\n");

    return 0;
}
