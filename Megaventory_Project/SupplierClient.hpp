#include <string>
#include <vector>

class MVContact {
	std::string ContactName;
	std::string ContactDepartment;
	std::string ContactEmail="";
	std::string ContantIsPrimary=false;
public:
	MVContact(std::string name, std::string dept, std::string email, std::string, std::string isprim)
		: ContactName(name), ContactDepartment(dept), ContactEmail(email), ContantIsPrimary(isprim) {}
};

class SupplierClient {

	unsigned SupplierClientID;
	std::string SupplierClientType;
	std::string SupplierClientName;
	std::vector<MVContact> mvContacts;
	std::string SupplierClientBillingAddress;
	std::string SupplierClientShippingAddress1;
	std::string SupplierClientShippingAddress2;
	std::string SupplierClientPhone1;
	std::string SupplierClientPhone2;
	std::string SupplierClientFax="";
	std::string SupplierClientIM = "";
	std::string SupplierClientEmail;
	std::string SupplierClientTaxID;
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


	SupplierClient(unsigned scid, std::string type, std::string name, std::vector<MVContact> contacts,
		std::string baddr, std::string saddr)
		: SupplierClientID(scid), SupplierClientType(type), SupplierClientName(name), mvContacts(contacts),
		SupplierClientBillingAddress(baddr), SupplierClientShippingAddress1(saddr) {}
};