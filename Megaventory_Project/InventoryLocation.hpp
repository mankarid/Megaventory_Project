#include <string>
#include <json/json.h>

class InventoryLocation {
    unsigned InventoryLocationID;
    std::string InventoryLocationName;
    std::string InventoryLocationAbbreviation;
    std::string InventoryLocationAddress;
    std::string InventoryLocationCurrencyCode;
public:
	Json::Value SupplierClientforInsert(std::string key) {
		Json::Value newProduct;
		newProduct["APIKEY"] = key;
		newProduct["mvInventoryLocation"]["InventoryLocationName"] = InventoryLocationName;
		newProduct["mvInventoryLocation"]["InventoryLocationAbbreviation"] = InventoryLocationAbbreviation;
		newProduct["mvRecordAction"] = "Insert";
		newProduct["mvInsertUpdateDeleteSourceApplication"] = "Megaventory_project";
		return newProduct;
	}

	Json::Value SupplierClientforUpdate(std::string key) {
		Json::Value newProduct;
		newProduct["APIKEY"] = key;
		newProduct["mvInventoryLocation"]["InventoryLocationID"] = InventoryLocationID;
		newProduct["mvInventoryLocation"]["InventoryLocationName"] = InventoryLocationName;
		newProduct["mvInventoryLocation"]["InventoryLocationAbbreviation"] = InventoryLocationAbbreviation;
		newProduct["mvInventoryLocation"]["SupplierClientBillingAddress"] = InventoryLocationAddress;
		newProduct["mvInventoryLocation"]["SupplierClientShippingAddress1"] = InventoryLocationCurrencyCode;

		newProduct["mvRecordAction"] = "Insert";
		newProduct["mvInsertUpdateDeleteSourceApplication"] = "Megaventory_project";
		return newProduct;
	}

    InventoryLocation(unsigned id, std::string name, std::string abbr, std::string addr, std::string code)
        : InventoryLocationID(id), InventoryLocationName(name), InventoryLocationAbbreviation(abbr),
        InventoryLocationAddress(addr), InventoryLocationCurrencyCode(code) {}
    ~InventoryLocation() {}
};