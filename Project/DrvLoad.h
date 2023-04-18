#pragma once
#include<ntifs.h>

#define DrvObjNamePrefix L"\\Driver\\"
#define ServiceRegistryPath L"\\Registry\\Machine\\System\\CurrentControlSet\\Services\\"
#define WDF "WDFLDR.SYS"

typedef struct _ShellContext {
	PDRIVER_OBJECT DrvObj;
	PUNICODE_STRING PSTR;
}ShellContext, * PShellContext;

typedef struct _LDR_DATA_TABLE_ENTRY {
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG64 SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG32 Flags;
}LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

//WCHAR  DriverRegistryPrefix[0x100];

//关于无签名驱动加载
ULONG64 CIFun;
PULONG64 Pqword_14040EF40;
//获取Nt头
PIMAGE_NT_HEADERS(*RtlImageNtHeader)(PVOID DllBase);

//获取资源第一步
NTSTATUS(*MiGenerateSystemImageNames)(PUNICODE_STRING DriverPath, ULONG64 zero1, ULONG64 zero2, PUNICODE_STRING OutUnicode, PUNICODE_STRING OutUnicode14, PUNICODE_STRING String1);

//获取资源第二步 获取DriverSection _LDR_DATA_TABLE_ENTRY
NTSTATUS(*MiObtainSectionForDriver)(PUNICODE_STRING String1, PUNICODE_STRING DriverPath, ULONG64 zero1, ULONG64 zero2, PULONG64 PDriverSection);

//创建镜像虚拟地址
PUCHAR(*MiGetSystemAddressForImage)(PVOID PSECTION, int zero, int* un);

//映射镜像物理地址
NTSTATUS(*MiMapSystemImage)(PVOID PSECTION, PUCHAR BaseVa);

//get 数据目录地址
PUCHAR(*RtlImageDirectoryEntryToData)(PUCHAR DllBase, ULONG64 one, ULONG64 one1, PULONG32 PSize);

//填充IAT辅助函数
NTSTATUS(*MiSnapThunk)(PUCHAR importDllBase, PUCHAR DllBase, PULONG64 PITE, PULONG64 PIATE, ULONG64 zero);

//线程上锁
PKTHREAD(*MmAcquireLoadLock)();

//线程解锁
VOID(*MmReleaseLoadLock)(PKTHREAD thread);

//获取PPTE
ULONG64(*MiFillPteHierarchy)(ULONG64 va, PPTE_HIERARCHY Pout);

//需要调用这个函数，R3才能成功 CreateFile
VOID(*IopReadyDeviceObjects)(PDRIVER_OBJECT DrvObj);

//驱动入口
NTSTATUS(*ShellDriverEntry)(PVOID a, PVOID b);

//Other


ULONG64 SectionOffset;
PLIST_ENTRY64 PsLoadedModuleList;
ULONG64 BaseDllNameOffset;
ULONG64 DllBaseOffset;
ULONG64 SizeOfImageOffset;
ULONG64 FlagsOffset;


//----------------------

PULONG64 PIoDriverObjectType;

//资源锁参数
ULONG64 PIopDriverLoadResource;

//默认MajorFunction
ULONG64 PIopInvalidDeviceRequest;

//创建对象
NTSTATUS(*ObCreateObjectEx)(BOOLEAN AccMode, ULONG64 Type, POBJECT_ATTRIBUTES attributes, ULONG64 zero, PULONG64 Out, ULONG64 Size, ULONG64 zero1, ULONG64 zero2, PVOID PObject, ULONG64 zero3);

//加入对象表
NTSTATUS(*ObInsertObjectEx)(PVOID PObject, ULONG64 zero, ULONG64 one, ULONG64 zero1, ULONG64 zero2, ULONG64 zero3, PHANDLE PHandle);

//重新构造DriverSection并插入链表
NTSTATUS(*MiConstructLoaderEntry)(PLDR_DATA_TABLE_ENTRY DriverSection,
	PUNICODE_STRING DrvName,//"XXX.sys"
	PUNICODE_STRING DrvPath,//
	ULONG64 zero,
	ULONG64 one,
	PVOID PnewDriverSection);

ULONG64 PCmRegistryMachineHardwareDescriptionSystemName;

VOID LoadDrv(PWCHAR DrvPath);
BOOLEAN CamouflageDrvLoad(PWCHAR ADrvPath, PWCHAR ODrvPath, PWCHAR ServiceName);