#include <iostream>
#include <map>
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

// Function to query WMI for physical memory information
bool getPhysicalMemoryInformation() {
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
        bstr_t("SELECT * FROM Win32_PhysicalMemory"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres)) {
        std::cerr << "Query for physical memory information failed. Error code: " << hres << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return false;
    }

    // Retrieve and print data from the query
    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;

    while (pEnumerator) {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

        if (uReturn == 0) {
            break;
        }

        VARIANT vtProp;

        // Print various properties of the Win32_PhysicalMemory class

        // Get the value of the "DeviceLocator" property
        hr = pclsObj->Get(L"DeviceLocator", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Device Locator: " << vtProp.bstrVal << std::endl;
            VariantClear(&vtProp);
        }

        //// Get the value of the "Capacity" property
        //hr = pclsObj->Get(L"Capacity", 0, &vtProp, 0, 0);
        //if (!FAILED(hr)) {
        //    std::wcout << L"Capacity: " << vtProp.ullVal << L" bytes" << std::endl;
        //    VariantClear(&vtProp);
        //}

        // Get the value of the "Speed" property
        hr = pclsObj->Get(L"Speed", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Speed: " << vtProp.uintVal << L" MHz" << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "Manufacturer" property
        hr = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Manufacturer: " << vtProp.bstrVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "PartNumber" property
        hr = pclsObj->Get(L"PartNumber", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Part Number: " << vtProp.bstrVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "SerialNumber" property
        hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Serial Number: " << vtProp.bstrVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "FormFactor" property
        hr = pclsObj->Get(L"FormFactor", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Form Factor: " << vtProp.uintVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "MemoryType" property
        hr = pclsObj->Get(L"MemoryType", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Memory Type: " << vtProp.uintVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "TotalWidth" property
        hr = pclsObj->Get(L"TotalWidth", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Total Width: " << vtProp.uintVal << " bits" << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "DataWidth" property
        hr = pclsObj->Get(L"DataWidth", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Data Width: " << vtProp.uintVal << " bits" << std::endl;
            VariantClear(&vtProp);
        }

        std::wcout << std::endl;
        // ... (similarly for other properties)

        pclsObj->Release();
    }

    // Cleanup
    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();

    return true;
}

int main() {
    if (getPhysicalMemoryInformation()) {
        //std::cout << "Physical memory information retrieved successfully." << std::endl;
    }
    else {
        std::cerr << "Failed to retrieve physical memory information." << std::endl;
    }

    return 0;
}
