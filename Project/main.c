#include"head.h"
#define HideDrvPath L"\\??\\C:\\Users\\nihao\\Desktop\\test\\Test_Drv.sys"

#define ADrvPath L"\\??\\C:\\Users\\nihao\\Desktop\\test\\Test_Drv.sys"
#define ODrvPath L"\\??\\C:\\Users\\nihao\\Desktop\\test\\360AntiHacker64.sys"
#define ServiceName  L"AntiHacker"

PDRIVER_OBJECT Driver = NULL;

NTSTATUS Exit(DRIVER_OBJECT* DriverObject) {
	DbgPrint("DriverUnload\n");
	return STATUS_SUCCESS;
}


NTSTATUS DriverEntry(DRIVER_OBJECT* DriverObject, UNICODE_STRING* STR) {
	//DbgBreakPoint();
	NTSTATUS status = STATUS_SUCCESS;
	Driver = DriverObject;
	if (InitAllOffSet()) {
		//LoadDrv(HideDrvPath);// Çý¶¯Òþ²Ø¼ÓÔØ²âÊÔ
		CamouflageDrvLoad(ADrvPath, ODrvPath, ServiceName);//Çý¶¯Î±×°¼ÓÔØ²âÊÔ
	}

	return status;

}