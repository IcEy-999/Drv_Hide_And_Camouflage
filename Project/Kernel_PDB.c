#include"Head.h"


extern PDRIVER_OBJECT Driver;

//导出的函数或全局变量才能用这个
ULONG64 GetSymAddress(PWCHAR Name) {
	UNICODE_STRING UName = { 0 };
	RtlInitUnicodeString(&UName, Name);
	return MmGetSystemRoutineAddress(&UName);
}

//初始化需要用到的偏移  自己想办法拿咯
BOOLEAN InitAllOffSet() {
	PsLoadedModuleList = GetSymAddress(L"PsLoadedModuleList");
	BaseDllNameOffset = 0x58;//GetMembersOffset(L"_LDR_DATA_TABLE_ENTRY", L"BaseDllName");
	SectionOffset = 0x70;//GetMembersOffset(L"_LDR_DATA_TABLE_ENTRY",L"HashLinks");
	DllBaseOffset = 0x30;//GetMembersOffset(L"_LDR_DATA_TABLE_ENTRY", L"DllBase");
	SizeOfImageOffset = 0x40;//GetMembersOffset(L"_LDR_DATA_TABLE_ENTRY", L"SizeOfImage");
	FlagsOffset = 0x68;//GetMembersOffset(L"_LDR_DATA_TABLE_ENTRY", L"Flags");

	Pqword_14040EF40 = 0xfffff8042ba0ef20 + 0x20;//GetSymAddress(L"SeCiCallbacks") + 0x20;

	PULONG64 b = &RtlImageNtHeader;
	*b = GetSymAddress(L"RtlImageNtHeader");

	b = &MiGenerateSystemImageNames;
	*b = 0xfffff8042bc69728;//

	b = &MiObtainSectionForDriver;
	*b = 0xfffff8042bbdaaac;//

	b = &MiGetSystemAddressForImage;
	*b = 0xfffff8042bc37064;//

	b = &MiMapSystemImage;
	*b = 0xfffff8042bc69104;//

	b = &RtlImageDirectoryEntryToData;
	*b = GetSymAddress(L"RtlImageDirectoryEntryToData");

	b = &MiSnapThunk;
	*b = 0xfffff8042bbda7e4;//

	b = &MmAcquireLoadLock;
	*b = 0xfffff8042bc6c260;//

	b = &MmReleaseLoadLock;
	*b = 0xfffff8042bc6c220;//
	
	b = &MiFillPteHierarchy;
	*b = 0xfffff8042b6f53f0;//

	b = &IopReadyDeviceObjects;
	*b = 0xfffff8042bc63b3c;//

	//------驱动伪装特有-------------

	PCmRegistryMachineHardwareDescriptionSystemName = 0xfffff8042bf6e888;//GetSymAddress(L"CmRegistryMachineHardwareDescriptionSystemName");


	b = &MiConstructLoaderEntry;
	*b = 0xfffff8042bc69db0;// GetSymAddress(L"MiConstructLoaderEntry");


	b = &ObInsertObjectEx;
	*b = 0xfffff8042bc84f50;// GetSymAddress(L"ObInsertObjectEx");

	b = &ObCreateObjectEx;
	*b = 0xfffff8042bc96270;// GetSymAddress(L"ObCreateObjectEx");

	PIopInvalidDeviceRequest = 0xfffff8042b67bd70;//GetSymAddress(L"IopInvalidDeviceRequest");

	PIopDriverLoadResource = 0xfffff8042ba36ba0;// GetSymAddress(L"IopDriverLoadResource");

	PIoDriverObjectType = GetSymAddress(L"IoDriverObjectType");

	return TRUE;	
}

