#include <cstdio>
#include <curl/curl.h>

#include <vector>
#include <algorithm>

size_t callback(void* buffer, size_t size, size_t nmemb, void* userp)
{
    char* cbuff = (char*)buffer;
    std::vector<char>* store = (std::vector<char>*)userp;
    int prevs = store->size();
    store->resize(store->size() + size*nmemb);
    std::copy(cbuff, cbuff+size*nmemb, store->begin() + prevs);
    return size*nmemb;
}

size_t pullfile(std::vector<char>& out, char* uri, char* user = NULL, char* pass = NULL)
{
    char* errorbuff = new char[CURL_ERROR_SIZE];
    CURL* handle = curl_easy_init();
    
    curl_easy_setopt(handle, CURLOPT_URL, uri);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, &callback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&out);
    curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, errorbuff);

    if(user) {
        curl_easy_setopt(handle, CURLOPT_USERNAME, user);
        if(pass) {
            curl_easy_setopt(handle, CURLOPT_PASSWORD, pass);
        }
    } 
    
    CURLcode ret = curl_easy_perform(handle);

    fprintf(stderr, "%u:%s\n", ret, errorbuff);
    fwrite((void*)&out[0], 1, out.size(), stdout);
    
    curl_easy_cleanup(handle);
    delete[] errorbuff;
}

int main(int argc, char** argv)
{
#if WIN32
    curl_global_init(CURL_GLOBAL_SSL | CURL_GLOBAL_WIN32);
#else 
    curl_global_init(CURL_GLOBAL_SSL);
#endif
    if(argc < 2) {
        printf("%s <uri> [user [pass]]\n", argv[0]);
        return 0;
    }
    
    std::vector<char> buffer;
    if(argc == 2)
        pullfile(buffer, argv[1]);
    else if(argc == 3)
        pullfile(buffer, argv[1], argv[2]);
    else if(argc == 4)
        pullfile(buffer, argv[1], argv[2], argv[3]);
    else  {
        printf("%s <string>\n", argv[0]);
        return 0;
    }

    curl_global_cleanup();
}
