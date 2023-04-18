#pragma once
#include<ntddk.h>

#pragma once
#include<ntddk.h>

//_OBJECT_HEADER 内两个成员的偏移
enum _OBJECT_HEADER_Offset {
    _OBJECT_HEADER_Body_Offset = 0x30,
    _OBJECT_HEADER_TypeIndex_Offset = 0x18
};

//0x18 bytes (sizeof)
typedef struct _OBJECT_DIRECTORY_ENTRY
{
    struct _OBJECT_DIRECTORY_ENTRY* ChainLink;                                      //0x0
    VOID* Object;                                                           //0x8
    ULONG HashValue;                                                        //0x10
}OBJECT_DIRECTORY_ENTRY, * POBJECT_DIRECTORY_ENTRY;

//0x158 bytes (sizeof)
typedef struct _OBJECT_DIRECTORY
{
    POBJECT_DIRECTORY_ENTRY HashBuckets[37];                                //0x0
    ULONG64 Lock;                                                           //0x128
    ULONG64 DeviceMap;                                                      //0x130
    struct _OBJECT_DIRECTORY* ShadowDirectory;                                      //0x138
    VOID* NamespaceEntry;                                                   //0x140
    VOID* SessionObject;                                                    //0x148
    ULONG Flags;                                                            //0x150
    ULONG SessionId;                                                        //0x154
}OBJECT_DIRECTORY, * POBJECT_DIRECTORY;

//0x20 bytes (sizeof)
typedef struct _OBJECT_HEADER_NAME_INFO
{
    POBJECT_DIRECTORY Directory;                                            //0x0
    UNICODE_STRING Name;                                                    //0x8
    LONG ReferenceCount;                                                    //0x18
    ULONG Reserved;                                                         //0x1c
}OBJECT_HEADER_NAME_INFO, * POBJECT_HEADER_NAME_INFO;

PDRIVER_OBJECT FindNotDeviceDriver();