#include <iostream>
#include <map>
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

// Function to query WMI for processor information
bool getProcessorInformation() {
    HRESULT hres;

    // Step 1: Initialize COM
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        std::cerr << "Failed to initialize COM library. Error code: " << hres << std::endl;
        return false;
    }

    // Step 2: Set general COM security levels
    hres = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL);

    if (FAILED(hres)) {
        std::cerr << "Failed to initialize security. Error code: " << hres << std::endl;
        CoUninitialize();
        return false;
    }

    // Step 3: Obtain the initial locator to WMI
    IWbemLocator* pLoc = NULL;
    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator,
        (LPVOID*)&pLoc);

    if (FAILED(hres)) {
        std::cerr << "Failed to create IWbemLocator object. Error code: " << hres << std::endl;
        CoUninitialize();
        return false;
    }

    // Step 4: Connect to WMI through the IWbemLocator::ConnectServer method
    IWbemServices* pSvc = NULL;
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"),  // Object path of WMI namespace
        NULL,                    // User name
        NULL,                    // User password
        0,                       // Locale
        NULL,                    // Security flags
        0,                       // Authority
        0,                       // Context object
        &pSvc);

    if (FAILED(hres)) {
        std::cerr << "Could not connect to WMI. Error code: " << hres << std::endl;
        pLoc->Release();
        CoUninitialize();
        return false;
    }

    // Step 5: Set security levels on the proxy
    hres = CoSetProxyBlanket(
        pSvc,                        // Indicates the proxy to set
        RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
        RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
        NULL,                        // Server principal name
        RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx
        RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
        NULL,                        // client identity
        EOAC_NONE                    // proxy capabilities
    );

    if (FAILED(hres)) {
        std::cerr << "Could not set proxy blanket. Error code: " << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return false;
    }

    // Step 6: Use the IWbemServices pointer to make requests of WMI
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_Processor"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres)) {
        std::cerr << "Query for processor information failed. Error code: " << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return false;
    }

    // Step 7: Retrieve the data from the query in step 6
    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;

    while (pEnumerator) {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

        if (uReturn == 0) {
            break;
        }

        VARIANT vtProp;

        // Get the value of the "Name" property
        hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Name: " << vtProp.bstrVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "ProcessorType" property
        hr = pclsObj->Get(L"ProcessorType", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Type: " << vtProp.uintVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "Manufacturer" property
        hr = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Manufacturer: " << vtProp.bstrVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "Caption" property
        hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Caption: " << vtProp.bstrVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "Family" property
        hr = pclsObj->Get(L"Family", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Family: " << vtProp.uintVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "DeviceID" property
        hr = pclsObj->Get(L"DeviceID", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"DeviceID: " << vtProp.bstrVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "Architecture" property
        hr = pclsObj->Get(L"Architecture", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Architecture: " << vtProp.uintVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "AddressWidth" property
        hr = pclsObj->Get(L"AddressWidth", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Address Width: " << vtProp.uintVal << " bits" << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "DataWidth" property
        hr = pclsObj->Get(L"DataWidth", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Data Width: " << vtProp.uintVal << " bits" << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "MaxClockSpeed" property
        hr = pclsObj->Get(L"MaxClockSpeed", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Max Clock Speed: " << vtProp.uintVal << " MHz" << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "CurrentClockSpeed" property
        hr = pclsObj->Get(L"CurrentClockSpeed", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Current Clock Speed: " << vtProp.uintVal << " MHz" << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "ThreadCount" property
        hr = pclsObj->Get(L"ThreadCount", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Thread Count: " << vtProp.uintVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "CurrentVoltage" property
        hr = pclsObj->Get(L"CurrentVoltage", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Current Voltage: " << vtProp.uintVal << " millivolts" << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "NumberOfCores" property
        hr = pclsObj->Get(L"NumberOfCores", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Number of Cores: " << vtProp.uintVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "NumberOfLogicalProcessors" property
        hr = pclsObj->Get(L"NumberOfLogicalProcessors", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Number of Logical Processors: " << vtProp.uintVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "L2CacheSize" property
        hr = pclsObj->Get(L"L2CacheSize", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"L2 Cache Size: " << vtProp.uintVal << " KB" << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "L3CacheSize" property
        hr = pclsObj->Get(L"L3CacheSize", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"L3 Cache Size: " << vtProp.uintVal << " KB" << std::endl;
            VariantClear(&vtProp);
        }

        pclsObj->Release();
    }

    std::wcout << std::endl << std::endl;

    // Cleanup
    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();

    return true;
}

int main() {
    if (getProcessorInformation()) {
        //std::cout << "Processor information retrieved successfully." << std::endl;
    }
    else {
        std::cerr << "Failed to retrieve processor information." << std::endl;
    }

    return 0;
}