#include <iostream>
#include <map>
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

// Function to query WMI for cache memory level information
bool getCacheMemoryInformation() {
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
        bstr_t("SELECT * FROM Win32_CacheMemory"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres)) {
        std::cerr << "Query for cache memory information failed. Error code: " << hres << std::endl;
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

        // Get the value of the "Level" property
        hr = pclsObj->Get(L"Level", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Level: " << vtProp.uintVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "Location" property
        hr = pclsObj->Get(L"Location", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Location: Internal" << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "Caption" property
        hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Caption: " << vtProp.bstrVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "Purpose" property
        hr = pclsObj->Get(L"Purpose", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Purpose: " << vtProp.bstrVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "BlockSize" property
        hr = pclsObj->Get(L"BlockSize", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Block Size: " << vtProp.uintVal << " bytes" << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "InstalledSize" property
        hr = pclsObj->Get(L"InstalledSize", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Installed Size: " << vtProp.uintVal << " KB" << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "MaxCacheSize" property
        hr = pclsObj->Get(L"MaxCacheSize", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Max Cache Size: " << vtProp.uintVal << " KB" << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "CacheType" property
        hr = pclsObj->Get(L"CacheType", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Cache Type: " << vtProp.uintVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "WritePolicy" property
        hr = pclsObj->Get(L"WritePolicy", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Write Policy: " << vtProp.uintVal << std::endl;
            VariantClear(&vtProp);
        }

        // Get the value of the "Associativity" property
        hr = pclsObj->Get(L"Associativity", 0, &vtProp, 0, 0);
        if (!FAILED(hr)) {
            std::wcout << L"Associativity: " << vtProp.uintVal << std::endl << std::endl;
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
    if (getCacheMemoryInformation()) {
        //std::cout << "Cache memory information retrieved successfully." << std::endl;
    }
    else {
        std::cerr << "Failed to retrieve cache memory information." << std::endl;
    }

    return 0;
}