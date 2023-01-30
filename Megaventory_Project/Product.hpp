#include <string>

class Product {
    unsigned ProductID;
    std::string ProductType;
    std::string ProductSKU;
    std::string ProductEAN="";
    std::string ProductDescription="newproductdescription";
    std::string ProductVersion="";
    std::string ProductLongDescription="";
    unsigned ProductCategoryID=0;
    std::string ProductUnitOfMeasurement="" ;
    double ProductSellingPrice;
    double ProductPurchasePrice;
    double ProductUnitCost=0;
    unsigned ProductWeight=0;
    unsigned ProductWeightUnitID=0;
    unsigned ProductLength=0;
    unsigned ProductBreadth=0;
    unsigned ProductHeight=0;
    std::string ProductImageURL="";
    std::string ProductComments="";
    std::string ProductCustomField1 = "";
    std::string ProductCustomField2 = "";
    std::string ProductCustomField3 = "";
    std::string ProductCustomField4 = "";
    std::string ProductCustomField5 = "";
    std::string ProductCustomField6 = "";
    std::string ProductCustomField7 = "";
    std::string ProductCustomField8 = "";
    std::string ProductCustomField9 = "";
    std::string ProductCustomField10 = "";
    unsigned ProductMainSupplierID=0;
    double ProductMainSupplierPrice=0;
    std::string ProductMainSupplierSKU = "";
    std::string ProductMainSupplierDescription = "";
    std::string ProductCreationDate="/Date(1507650714280 - 0000)/";
    bool ProductOption1=false;
    bool ProductOption2=false;
    bool ProductOption3=false;
    bool ProductOption4=false;
    bool ProductOption5=false;
    bool IsInventorySerialised=false;
    bool IsBatchNumbersEnabled=false;
    bool IsPurchasable=true;
    bool IsSellable=true;
public:
    Json::Value ProductforInsert(std::string key) {
        Json::Value newProduct;
        newProduct["APIKEY"] = key;
        newProduct["mvProduct"]["ProductID"] = ProductID;
        newProduct["mvProduct"]["ProductType"] = ProductType;
        newProduct["mvProduct"]["ProductDescription"] = ProductDescription;
        newProduct["mvProduct"]["ProductSellingPrice"] = ProductSellingPrice;
        newProduct["mvProduct"]["ProductPurchasePrice"] = ProductPurchasePrice;
        newProduct["mvProduct"]["mvProductMainSupplier"]["SupplierClientName"] = "A4 Paper Supplier";

        newProduct["mvRecordAction"] = "Insert";
        return newProduct;
    };
    Json::Value ProductforUpdate(std::string key) {
        Json::Value newProduct;
        newProduct["APIKEY"] = key;
        newProduct["mvProduct"]["ProductSKU"] = ProductSKU;
        newProduct["mvProduct"]["ProductSKU"] = ProductSKU;
        newProduct["mvProduct"]["ProductType"] = ProductType;
        newProduct["mvProduct"]["ProductDescription"] = ProductDescription;

        newProduct["mvRecordAction"] = "Update";
        return newProduct;
    };
    Product(unsigned pid,std::string psku,std::string ptype, double pselpr, double ppurpr)
    :ProductID(pid), ProductSKU(psku), ProductType(ptype), ProductSellingPrice(pselpr), ProductPurchasePrice(ppurpr) {
    }
    ~Product() {}

};

