#include <string>
#include <vector>

class MVContact {
public:
	std::string ContactName;
	std::string ContactDepartment;
	std::string ContactEmail = "";
	std::string ContantIsPrimary = "false";
	MVContact(std::string name, std::string dept, std::string email,std::string isprim)
		: ContactName(name), ContactDepartment(dept), ContactEmail(email), ContantIsPrimary(isprim) {}
};

class SupplierClient {

	unsigned SupplierClientID;
	std::string SupplierClientType;
	std::string SupplierClientName;
	std::vector<MVContact> mvContacts;
	std::string SupplierClientBillingAddress;
	std::string SupplierClientShippingAddress1;
	std::string SupplierClientShippingAddress2="";
	std::string SupplierClientPhone1;
	std::string SupplierClientPhone2="";
	std::string SupplierClientFax="";
	std::string SupplierClientIM = "";
	std::string SupplierClientEmail="";
	std::string SupplierClientTaxID="";
	std::string SupplierClientComments="";
	std::string SupplierClientCustomField1="";
	std::string SupplierClientCustomField2="";
	std::string SupplierClientCustomField3="";
	std::string SupplierClientCustomField4="";
	std::string SupplierClientCustomField5="";
	std::string SupplierClientOption1="";
	std::string SupplierClientOption2="";
	std::string SupplierClientOption3="";
	std::string SupplierClientOption4="";
	std::string SupplierClientOption5="";
	std::string SupplierClientCreationDate="/Date(1499856477997-0000)/";

public:
	Json::Value SupplierClientforInsert(std::string key) {
		Json::Value newProduct;
		newProduct["APIKEY"] = key;
		newProduct["mvSupplierClient"]["SupplierClientID"] = SupplierClientID;
		newProduct["mvSupplierClient"]["SupplierClientType"] = SupplierClientType;
		newProduct["mvSupplierClient"]["SupplierClientName"] = SupplierClientName;
		for (int i = 0; i < mvContacts.size(); i++) {
			newProduct["mvSupplierClient"]["mvContacts"][i]["ContactName"] = mvContacts[i].ContactName;
			newProduct["mvSupplierClient"]["mvContacts"][i]["ContactDepartment"] = mvContacts[i].ContactDepartment;
			if(mvContacts[i].ContactEmail!="")
				newProduct["mvSupplierClient"]["mvContacts"][i]["ContactEmail"] = mvContacts[i].ContactEmail;
			if(mvContacts[i].ContantIsPrimary=="false")
			newProduct["mvSupplierClient"]["mvContacts"][i]["ContantIsPrimary"] = mvContacts[i].ContantIsPrimary;
		}
		newProduct["mvSupplierClient"]["SupplierClientBillingAddress"] = SupplierClientBillingAddress;
		newProduct["mvSupplierClient"]["SupplierClientShippingAddress1"] = SupplierClientShippingAddress1;

		newProduct["mvGrantPermissionsToAllUser"] = "true";
		newProduct["mvRecordAction"] = "Insert";
		newProduct["mvInsertUpdateDeleteSourceApplication"] = "Megaventory_project";
		return newProduct;
	};

	Json::Value SupplierClientforUpdate(std::string key,std::string baddr) {
		SupplierClientBillingAddress = baddr;
		Json::Value newProduct;
		newProduct["APIKEY"] = key;
		newProduct["mvSupplierClient"]["SupplierClientID"] = SupplierClientID;
		newProduct["mvSupplierClient"]["SupplierClientName"] = SupplierClientName;
		newProduct["mvSupplierClient"]["SupplierClientBillingAddress"] = SupplierClientBillingAddress;
		newProduct["mvSupplierClient"]["SupplierClientShippingAddress2"] = SupplierClientShippingAddress2;
		newProduct["mvSupplierClient"]["SupplierClientPhone1"] = SupplierClientPhone1;
		newProduct["mvSupplierClient"]["SupplierClientIM"] = SupplierClientIM;

		newProduct["mvRecordAction"] = "Update";
		return newProduct;
	};

	SupplierClient(unsigned scid, std::string type, std::string name, std::vector<MVContact> contacts,
		std::string baddr, std::string saddr1, std::string saddr2, std::string phone, std::string im)
		: SupplierClientID(scid), SupplierClientType(type), SupplierClientName(name), mvContacts(contacts),
		SupplierClientBillingAddress(baddr), SupplierClientShippingAddress1(saddr1),
		SupplierClientShippingAddress2(saddr2), SupplierClientPhone1(phone), SupplierClientIM(im){}
	~SupplierClient() {
		mvContacts.clear();
	}
};