#include <iostream>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>
#include <initguid.h>

using namespace std;

#pragma comment(lib, "setupapi.lib")

void ListUsbDevices()
{
	HDEVINFO deviceInfoSet;
	SP_DEVINFO_DATA deviceInfoData;
	DWORD i = 0;

	deviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_USB, NULL, NULL, DIGCF_PRESENT);
	if (deviceInfoSet == INVALID_HANDLE_VALUE)
	{
		cerr << "[#PROGRAM]: Eroare! Nu s-a putut obtine lista de dispozitive USB!" << endl;
		return;
	}

	deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	cout << "[#PROGRAM]: Dispozitivele USB conectate sunt: " << endl;
	while (SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData))
	{
		i++;

		char deviceInstanceId[256];
		if (SetupDiGetDeviceInstanceIdA(deviceInfoSet, &deviceInfoData, deviceInstanceId, sizeof(deviceInstanceId), NULL))
		{
			cout << " - " << deviceInstanceId << endl;
		}
	}

	SetupDiDestroyDeviceInfoList(deviceInfoSet);
}

int main(void)
{
	ListUsbDevices();
	return 0;
}