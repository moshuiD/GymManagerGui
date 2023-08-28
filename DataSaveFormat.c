#include "DataSaveFormat.h"
static char* szThisBuffer;
static void MembersInfoCallBack(void* info) {
    char buff[512]={0};
    MemberBodyInfo* const tempInfo = info;
    sprintf(buff,
        "{"
        "\"m_szDate\": \"%s,\", "
        "\"m_uHeight\": \"%u\", "
        "\"m_uWeight\": \"%u\", "
        "\"m_fBodyFat\": %f "
        "},",
        tempInfo->m_szDate,
        tempInfo->m_uHeight,
        tempInfo->m_uWeight,
        tempInfo->m_fBodyFat);
    strcat(szThisBuffer, buff);
}
int Menbers2Json(Member* const member,char* buffer) {
    szThisBuffer = buffer;
    int returnCode = sprintf(buffer,
        "{"
        "\"m_uID\": %u, "
        "\"m_szName\": \"%s\", "
        "\"m_szDateOfBirth\": \"%s\", "
        "\"m_uAge\": %u, "
        "\"m_Gander\": %d, "
        "\"m_szAddress\": \"%s\", "
        "\"m_szPhone\": \"%s\", "
        "\"m_fmoney\": %f,"
        "\"MemberBodyInfo\":[",
        member->m_uID,
        member->m_szName,
        member->m_szDateOfBirth,
        member->m_uAge,
        member->m_Gander,
        member->m_szAddress,
        member->m_szPhone,
        member->m_fmoney);
    if (-1 == returnCode) {
        buffer = '\0';
        return -1;
    }
    for_each((iterator)member->m_BodyInfoList.m_Begin, MembersInfoCallBack);
    buffer[strlen(buffer) - 1] = '\0';
    strcat(buffer, "]}\r\n");
}