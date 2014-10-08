//
//  NetworkManager.cpp
//  Cheukoin
//
//  Created by Corentin on 10/6/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "NetworkManager.h"

#define LOGGING_ENABLED

using namespace std;
using namespace sf;

void NetworkManager::createLobby()
{
    auto response = get("/lobby/new/");
    cout << response.toStyledString();
}

Json::Value NetworkManager::request(const string& url, const string& body, Http::Request::Method method)
{
    Json::Value root;
    Http http(ROOT_URL);

    Http::Request httpRequest("/lobby/new/");
#ifdef LOGGING_ENABLED
//    cout << "[Network] - Sending request to " << httpRequest.url;
#endif
    Http::Response response = http.sendRequest(httpRequest);

    Http::Response::Status status = response.getStatus();

    if (status == Http::Response::Ok) {
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(response.getBody(), root);

        if (!parsingSuccessful) {
            cout << "Failed to parse configuration\n" << reader.getFormattedErrorMessages();
        }
    }
    else {
        cout << "Error " << status << std::endl;
    }

    return root;
}

Json::Value NetworkManager::get(const string& url)
{
    return request(url, "", Http::Request::Get);
}

Json::Value NetworkManager::post(const string& url, const string& body)
{
    return request(url, body, Http::Request::Post);
}