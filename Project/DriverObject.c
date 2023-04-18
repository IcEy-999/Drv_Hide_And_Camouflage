#include"Head.h"

extern PDRIVER_OBJECT Driver;

//找一个没有设备的驱动，劫持它的IO
PDRIVER_OBJECT FindNotDeviceDriver() {
	PUCHAR DriverObjectByte = (PUCHAR)Driver;
	POBJECT_HEADER_NAME_INFO PObjHeaderNameInfo = DriverObjectByte - _OBJECT_HEADER_Body_Offset - sizeof(OBJECT_HEADER_NAME_INFO);
	POBJECT_DIRECTORY PDirectory = PObjHeaderNameInfo->Directory;//该驱动所在目录
	PDRIVER_OBJECT TargetDrvObj = NULL;
	POBJECT_DIRECTORY_ENTRY PSubDirectoryEntry = NULL;
	POBJECT_DIRECTORY_ENTRY PDirectoryEntry = NULL;
	//DbgBreakPoint();
	for (int i = 0; i < 37; i++) {
		PDirectoryEntry = PDirectory->HashBuckets[i];
		if (PDirectoryEntry == NULL) {
			continue;
		}
		PSubDirectoryEntry = PDirectoryEntry;
		while (PSubDirectoryEntry != NULL) {
			TargetDrvObj = PSubDirectoryEntry->Object;
			if (TargetDrvObj->DeviceObject == NULL) {
				return TargetDrvObj;
			}
			PSubDirectoryEntry = PSubDirectoryEntry->ChainLink;
		}
	}
	return NULL;
}