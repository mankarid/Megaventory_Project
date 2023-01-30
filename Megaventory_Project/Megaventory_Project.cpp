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

typedef std::string APIKEY;

static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
    std::string& text = *static_cast<std::string*>(param);
    size_t totalsize = size * nmemb;
    text.append(static_cast<char*>(buffer), totalsize);
    return totalsize;
}

Json::Value GetResultAsJSON(std::string result) {
    int start = result.find("model = ") + 8;
    int end = result.find("txt = $$('TEXTAREA')") - 7;
    int length = end - start;
    std::string json_string = result.substr(start, length);
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

std::string GetResultAsString(std::string URL,APIKEY apikey) {
    std::string CompleteURL = URL + "?APIKEY=" + apikey;
    std::string result;
    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, CompleteURL.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        res = curl_easy_perform(curl);
        if (CURLE_OK != res) {
            std::cerr << "CURL error: " << res << '\n';
        }
        curl_easy_cleanup(curl);
    }
    return result;
}

void PostResult(std::string URL, APIKEY apikey,std::string value) {
    std::string CompleteURL = URL + "?APIKEY=" + apikey;
    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, CompleteURL.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, value);
        res = curl_easy_perform(curl);
        if (CURLE_OK != res) {
            std::cerr << "CURL error: " << res << '\n';
        }
        curl_easy_cleanup(curl);
    }
}

void PostProduct(APIKEY key,unsigned pid, std::string sku, std::string type, double psel, double ppur) {
    Product* newproduct = new Product(pid,sku,type,psel,ppur);

    Json::Value json_product = newproduct->ProductforInsert(key);
    Json::FastWriter fastWriter;
    std::string output = fastWriter.write(json_product);
    PostResult("https://api.megaventory.com/v2017a/Product/ProductUpdate", key, output);

    json_product = newproduct->ProductforUpdate(key);
    Json::FastWriter fastWriter2;
    output = fastWriter2.write(json_product);
    PostResult("https://api.megaventory.com/v2017a/Product/ProductUpdate", key, output);
}

void PostSupplierClient(APIKEY key, unsigned scid, std::string type, std::string name, std::vector<MVContact> contacts,
    std::string baddr, std::string saddr1, std::string saddr2, std::string phone, std::string im) {
    SupplierClient* newsupclient = new SupplierClient(scid, type, name, contacts,
        baddr,saddr1,saddr2,phone,im);

    Json::Value json_supclient = newsupclient->SupplierClientforInsert(key);
    Json::FastWriter fastWriter;
    std::string output = fastWriter.write(json_supclient);
    PostResult("https://api.megaventory.com/v2017a/Product/ProductUpdate", key, output);

    json_supclient = newsupclient->SupplierClientforUpdate(key,"");
    Json::FastWriter fastWriter2;
    output = fastWriter2.write(json_supclient);
    PostResult("https://api.megaventory.com/v2017a/Product/ProductUpdate", key, output);


}

int main()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    APIKEY mykey = "961c2b8ebbc896e2@m139547";

    std::string result;
    result = GetResultAsString("https://api.megaventory.com/v2017a/Product/ProductGet",mykey);
    Json::Value completeJsonData;
    completeJsonData = GetResultAsJSON(result);


    PostProduct(mykey,26,"1112256", "Nike Shoes", 99.99, 49.99);
    PostProduct(mykey,26,"1112248 ", "Adidas shoes", 99.99, 49.99);

    std::vector<MVContact> contacts = { MVContact("babis","","babis@exampletest.com","true") };
    PostSupplierClient(mykey, 100, "Client", "babis", contacts, "", "Example 8, Athens", "", "1235698967", "");
    std::vector<MVContact> contacts2 = { MVContact("odysseus","","odysseus@exampletest.com","true") };;
    PostSupplierClient(mykey, 101, "Supplier", "odysseus", contacts2, "", "Example 10, Athens ", "", "1235698988", "");
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
