#include <ntifs.h>

// 进程消息回调
VOID OnProcessNotify(
	_Inout_ PEPROCESS Process,
	_In_ HANDLE ProcessId,
	_Inout_opt_ PPS_CREATE_NOTIFY_INFO CreateInfo
)
{
	UNREFERENCED_PARAMETER(Process);
	UNREFERENCED_PARAMETER(ProcessId);

	if (CreateInfo)
	{
		// 进程创建
		CreateInfo->CreationStatus = STATUS_ACCESS_DENIED;
	}
	else
	{
		// 进程结束
	}
}

VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	UNREFERENCED_PARAMETER(DriverObject);
	PsSetCreateProcessNotifyRoutineEx(OnProcessNotify, TRUE);
}

EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegisterPath)
{
	UNREFERENCED_PARAMETER(RegisterPath);
	DriverObject->DriverUnload = DriverUnload;
	
	// linker parameter /integritycheck 
	return PsSetCreateProcessNotifyRoutineEx(OnProcessNotify, FALSE);
}
