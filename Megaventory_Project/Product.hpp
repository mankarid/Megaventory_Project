#include <string>

class ProductUnitCostObj {
    std::string CompanyName;
    std::string CompanyCurrencyCode;
    unsigned ProductUnitCost;
public:
    ProductUnitCostObj(std::string cname, std::string ccode, unsigned pcost) :
        CompanyName(cname), CompanyCurrencyCode(ccode), ProductUnitCost(pcost) {}
    ~ProductUnitCostObj() {}
};

class Product {
    unsigned ProductID;
    std::string ProductType;
    std::string ProductSKU;
    std::string ProductEAN;
    std::string ProductDescription;
    std::string ProductVersion;
    std::string ProductLongDescription;
    unsigned ProductCategoryID;
    std::string ProductUnitOfMeasurement;
    unsigned ProductSellingPrice;
    unsigned ProductPurchasePrice;
    ProductUnitCostObj ProductUnitCost;
    unsigned ProductWeight;
    unsigned ProductWeightUnitID;
    unsigned ProductLength;
    unsigned ProductBreadth;
    unsigned ProductHeight;
    std::string ProductImageURL;
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
    unsigned ProductMainSupplierID;
    unsigned ProductMainSupplierPrice;
    std::string ProductMainSupplierSKU = "";
    std::string ProductMainSupplierDescription = "";
    std::string ProductCreationDate;
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
    Product(unsigned pid, std::string ptype, std::string psku, std::string pean, std::string pdesc, std::string pver,
        std::string plongdesc, unsigned pcatid, std::string punmes, unsigned pselpr, unsigned ppurpr, std::string cname,
        std::string ccode, unsigned puncost, unsigned pweight, unsigned pweightid, unsigned plength, unsigned pbr,
        unsigned pheight, std::string pURL, std::string pcomments, unsigned pmainsupid, unsigned pmainsuppr, std::string pmainsupsku,
        std::string pmainsupdesc, std::string pcreatdate)
        :
        ProductID(pid), ProductType(ptype), ProductSKU(psku), ProductEAN(pean), ProductDescription(pdesc),
        ProductVersion(pver), ProductLongDescription(plongdesc), ProductCategoryID(pcatid),
        ProductUnitOfMeasurement(punmes), ProductSellingPrice(pselpr), ProductPurchasePrice(ppurpr),
        ProductUnitCost(ProductUnitCostObj(cname, ccode, puncost)), ProductWeight(pweight),
        ProductWeightUnitID(pweightid), ProductLength(plength), ProductBreadth(pbr),
        ProductHeight(pheight), ProductImageURL(pURL), ProductComments(pcomments),
        ProductMainSupplierID(pmainsupid), ProductMainSupplierPrice(pmainsuppr),
        ProductMainSupplierSKU(pmainsupsku), ProductMainSupplierDescription(pmainsupdesc),
        ProductCreationDate(pcreatdate) {}
};