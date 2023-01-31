// Megaventory_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CURL_STATICLIB
//C++ Libraries
#include <iostream>
#include <string>
#include <fstream>

//JsonCpp Libraries
#include <json/json.h>

//Curl Libraries
#include "Curl/curl.h"

#ifdef DEBUG
#pragma comment (lib,"Curl/libcurl_a_debug.lib")
#else
#pragma comment (lib,"Curl/libcurl_a.lib")
#endif // DEBUG

#pragma comment (lib,"Normaliz.lib")
#pragma comment (lib,"Ws2_32.lib")
#pragma comment (lib,"Wldap32.lib")
#pragma comment (lib,"Crypt32.lib")
#pragma comment (lib,"advapi32.lib")

//Additional
#include "Product.hpp"
#include "SupplierClient.hpp"
#include "InventoryLocation.hpp"

typedef std::string APIKEY;

static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
    std::string& text = *static_cast<std::string*>(param);
    size_t totalsize = size * nmemb;
    text.append(static_cast<char*>(buffer), totalsize);
    return totalsize;
}

Json::Value GetResultAsJSON(std::string json_string) {
    std::ofstream write_file;
    write_file.open("temp.txt");
    if (!write_file) { // file couldn't be opened
        std::cerr << "Error: file could not be opened\n";
        exit(1);
    }
    write_file << json_string;
    write_file.close();
    std::ifstream read_file("temp.txt");
    if (!read_file) { // file couldn't be opened
        std::cerr << "Error: file could not be opened\n";
        exit(1);
    }
    // json reader
    Json::Reader reader;
    // this will contain complete JSON data
    Json::Value completeJsonData;
    // reader reads the data and stores it in completeJsonData
    reader.parse(read_file, completeJsonData);
    return completeJsonData;
}

std::string PostResult(std::string URL, APIKEY apikey,std::string value) {
    std::string CompleteURL = URL + "?APIKEY=" + apikey;
    CURL* curl;
    CURLcode res;
    struct curl_slist* slist;
    std::string result;
    slist = NULL;
    slist = curl_slist_append(slist, "Content-Type: application/json");
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, CompleteURL.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, value.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        res = curl_easy_perform(curl);
        if (CURLE_OK != res) {
            std::cerr << "CURL error: " << res << '\n';
        }
        return result;
        curl_easy_cleanup(curl);
    }
    return "";
}

Json::Value GetProductAsJSON(APIKEY key, std::string fname, std::string sop, std::string svalue, unsigned rec) {
    Json::Value json_product;
    Json::FastWriter fastWriter;
    json_product["Filters"]["FieldName"] = fname;
    json_product["Filters"]["SearchOperator"] = sop;
    json_product["Filters"]["SearchValue"] = svalue;
    json_product["ReturnTopNRecords"] = rec;
    std::string output = fastWriter.write(json_product);
    output = PostResult("https://api.megaventory.com/v2017a/Product/ProductGet", key, output);
    return GetResultAsJSON(output);
}

Json::Value GetSupplierClientAsJSON(APIKEY key, std::string fname, std::string sop, std::string svalue,
    std::string andor, std::string fname2, std::string sop2, std::string svalue2) {
    Json::Value json_supclient;
    Json::FastWriter fastWriter;
    json_supclient["Filters"][0]["FieldName"] = fname;
    json_supclient["Filters"][0]["SearchOperator"] = sop;
    json_supclient["Filters"][0]["SearchValue"] = svalue;
    json_supclient["Filters"][1]["AndOr"] = andor;
    json_supclient["Filters"][1]["FieldName"] = fname2;
    json_supclient["Filters"][1]["SearchOperator"] = sop2;
    json_supclient["Filters"][1]["SearchValue"] = svalue2;
    std::string output = fastWriter.write(json_supclient);
    output = PostResult("https://api.megaventory.com/v2017a/SupplierClient/SupplierClientGet", key, output);
    return GetResultAsJSON(output);
}

Json::Value GetInventoryLocationAsJSON(APIKEY key, std::string fname, std::string sop, std::string svalue, unsigned rec) {
    Json::Value json_invlocation;
    Json::FastWriter fastWriter;
    json_invlocation["Filters"]["FieldName"] = fname;
    json_invlocation["Filters"]["SearchOperator"] = sop;
    json_invlocation["Filters"]["SearchValue"] = svalue;
    json_invlocation["ReturnTopNRecords"] = rec;
    std::string output = fastWriter.write(json_invlocation);
    output = PostResult("https://api.megaventory.com/v2017a/InventoryLocation/InventoryLocationGet", key, output);
    return GetResultAsJSON(output);
}

Product* PostProductInsertUpdate(APIKEY key, std::string sku, std::string type, std::string desc ,double psel, double ppur) {
    Product* newproduct = new Product(sku,type,desc,psel,ppur);

    Json::Value json_product = newproduct->ProductforInsert(key);
    Json::FastWriter fastWriter;
    std::string output = fastWriter.write(json_product);
    PostResult("https://api.megaventory.com/v2017a/Product/ProductUpdate", key, output);

    json_product=GetProductAsJSON(key, "ProductDescription", "Equals", desc, 1);
    newproduct->SetID(json_product["mvProducts"][0]["ProductID"].asUInt());

    json_product = newproduct->ProductforUpdate(key);
    Json::FastWriter fastWriter2;
    output = fastWriter2.write(json_product);
    output=PostResult("https://api.megaventory.com/v2017a/Product/ProductUpdate", key, output);
    std::cout << "\n\n" << output << "\n\n";
    return newproduct;
}

SupplierClient* PostSupplierClientInsertUpdate(APIKEY key, unsigned scid, std::string type, std::string name, std::vector<MVContact> contacts,
    std::string baddr, std::string saddr1, std::string saddr2, std::string phone, std::string im) {
    SupplierClient* newsupclient = new SupplierClient(scid, type, name, contacts,
        baddr,saddr1,saddr2,phone,im);

    Json::Value json_supclient = newsupclient->SupplierClientforInsert(key);
    Json::FastWriter fastWriter;
    std::string output = fastWriter.write(json_supclient);
    PostResult("https://api.megaventory.com/v2017a/SupplierClient/SupplierClientUpdate", key, output);

    json_supclient = GetSupplierClientAsJSON(key, "SupplierClientType", "Equals", type, "And", "SupplierClientName", "Equals", name);
    newsupclient->SetID(json_supclient["mvSupplierClients"][0]["SupplierClientID"].asUInt());

    json_supclient = newsupclient->SupplierClientforUpdate(key,"");
    Json::FastWriter fastWriter2;
    output = fastWriter2.write(json_supclient);
    output=PostResult("https://api.megaventory.com/v2017a/SupplierClient/SupplierClientUpdate", key, output);
    std::cout << "\n\n" << output << "\n\n";
    return newsupclient;
}

InventoryLocation* PostInventoryLocationInsertUpdate(APIKEY key, unsigned id,std::string name, std::string abbr, std::string addr, std::string code) {
    InventoryLocation* newinvlocation = new InventoryLocation(id, name, abbr,
        addr, code);

    Json::Value json_invlocation = newinvlocation->InventoryLocationforInsert(key);
    Json::FastWriter fastWriter;
    std::string output = fastWriter.write(json_invlocation);
    PostResult("https://api.megaventory.com/v2017a/InventoryLocation/InventoryLocationUpdate", key, output);

    json_invlocation = GetInventoryLocationAsJSON(key, "InventoryLocationName", "Equals", name, 2);
    newinvlocation->SetID(json_invlocation["mvInventoryLocations"][0]["InventoryLocationID"].asUInt());

    json_invlocation = newinvlocation->InventoryLocationforUpdate(key);
    Json::FastWriter fastWriter2;
    output = fastWriter2.write(json_invlocation);
    output=PostResult("https://api.megaventory.com/v2017a/InventoryLocation/InventoryLocationUpdate", key, output);
    std::cout << "\n\n" << output << "\n\n";

    return newinvlocation;
}

Json::Value PostProductClientRelationship(APIKEY key, unsigned pid, unsigned cid,double cprice,
    std::string action) {
    Json::Value json_relationship;
    json_relationship["APIKEY"] = key;
    json_relationship["mvProductClientUpdate"]["ProductID"] = pid;
    json_relationship["mvProductClientUpdate"]["ProductClientID"] = cid;
    json_relationship["mvProductClientUpdate"]["ProductClientPrice"] = cprice;
    json_relationship["mvRecordAction"] = action;

    Json::FastWriter fastWriter;
    std::string output = fastWriter.write(json_relationship);
    output = PostResult("https://api.megaventory.com/v2017a/ProductClient/ProductClientUpdate", key, output);
    return GetResultAsJSON(output);
}


Json::Value PostProductSupplierRelationship(APIKEY key, unsigned pid, unsigned cid, bool ismain,
    std::string leadtdesc,std::string qrangeid,std::string qrangedesc,std::string action) {
    Json::Value json_relationship;
    json_relationship["APIKEY"] = key;
    json_relationship["mvProductSupplierUpdate"]["ProductID"] = pid;
    json_relationship["mvProductSupplierUpdate"]["ProductSupplierID"] = cid;
    json_relationship["mvProductSupplierUpdate"]["IsMainSupplier"] = ismain;
    json_relationship["mvProductSupplierUpdate"]["ProductSupplierLeadTime"]["LeadTimeDescription"] = leadtdesc;
    json_relationship["mvProductSupplierUpdate"]["ProductSupplierQuantityRange"]["QuantityRangeID"] = qrangeid;
    json_relationship["mvProductSupplierUpdate"]["ProductSupplierQuantityRange"]["QuantityRangeDescription"] = qrangedesc;
    json_relationship["mvRecordAction"] = action;

    Json::FastWriter fastWriter;
    std::string output = fastWriter.write(json_relationship);
    output = PostResult("https://api.megaventory.com/v2017a/ProductSupplier/ProductSupplierUpdate", key, output);
    return GetResultAsJSON(output);
}

Json::Value UpdateAvailabilityInInventoryLocation(APIKEY key, std::string psku,
    unsigned invlocid) {
    Json::Value json_stock;
    json_stock["APIKEY"] = key;
    json_stock["mvProductStockUpdateList"][0]["ProductSKU"] = psku;
    json_stock["mvProductStockUpdateList"][0]["ProductQuantity"] = 5;
    json_stock["mvProductStockUpdateList"][0]["InventoryLocationID"] = invlocid;
    Json::FastWriter fastWriter;
    std::string output = fastWriter.write(json_stock);
    output = PostResult("https://api.megaventory.com/v2017a/InventoryLocationStock/ProductStockUpdate", key, output);
    return GetResultAsJSON(output);
}


int main()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    APIKEY mykey = "961c2b8ebbc896e2@m139547";
    std::string result;

    //Posting 2 Products
    Product* prod_1=PostProductInsertUpdate(mykey,"1112257","BuyFromSupplier", "Nike Shoes", 99.99, 49.99);
    Product* prod_2=PostProductInsertUpdate(mykey,"1112249  ","BuyFromSupplier", "Adidas shoes", 99.99, 49.99);


    //Posting a Client and a Supplier
    std::vector<MVContact> contacts = { MVContact("babis","","babis@exampletest.com","true") };
    SupplierClient* client1=PostSupplierClientInsertUpdate(mykey, 100, "Client", "babis", contacts, "", 
        "Example 8, Athens", "", "1235698967", "");

    std::vector<MVContact> contacts2 = { MVContact("odysseus","","odysseus@exampletest.com","true") };;
    SupplierClient* sup_1=PostSupplierClientInsertUpdate(mykey, 101, "Supplier", "odysseus", contacts2,
        "", "Example 10, Athens ", "", "1235698988", "");


    //Posting an Inventory Location
    InventoryLocation* invloc_1=PostInventoryLocationInsertUpdate(mykey, 100, "Test Project Location", 
        "Test", "Example 20, Athens", "");


    //GetClient
    Json::Value babis = GetSupplierClientAsJSON(mykey, "SupplierClientType", "Equals", "Client", "And",
        "SupplierClientName", "Equals", "babis")["mvSupplierClients"][0];

    //GetProduct
    Json::Value nikeshoes = GetProductAsJSON(mykey, "ProductDescription", "Equals", "Nike Shoes", 1)["mvProducts"][0];

    //Form Relationship
    Json::Value relationship1 = PostProductClientRelationship(mykey, nikeshoes["ProductID"].asUInt(), 
        babis["SupplierClientID"].asUInt(), 99.99, "Insert");
    std::cout << "\n\n" << relationship1 << "\n\n";


    //GetSupplier
    Json::Value odysseus = GetSupplierClientAsJSON(mykey, "SupplierClientType", "Equals", "Supplier", "And",
        "SupplierClientName", "Equals", "odysseus")["mvSupplierClients"][0];

    //GetProduct
    Json::Value adidasshoes = GetProductAsJSON(mykey, "ProductDescription", "Equals", "Adidas Shoes", 1)["mvProducts"][0];

    //Form Relationship
    Json::Value relationship2 = PostProductSupplierRelationship(mykey, nikeshoes["ProductID"].asUInt(),
        odysseus["SupplierClientID"].asUInt(), false, "Test Test", "0", "Test", "Insert");
    std::cout << "\n\n" << relationship2 << "\n\n";


    //GetLocation
    Json::Value invloc = GetInventoryLocationAsJSON(mykey, "InventoryLocationName", "Equals", "Test Project Location",
        2)["mvInventoryLocations"][0];

    //Update 
    Json::Value stockupdate = UpdateAvailabilityInInventoryLocation(mykey,
        nikeshoes["ProductSKU"].asString(),invloc["InventoryLocationID"].asUInt());
    std::cout << "\n\n" << stockupdate << "\n\n";

}
