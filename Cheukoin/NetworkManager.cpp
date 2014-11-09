//
//  NetworkManager.cpp
//  Cheukoin
//
//  Created by Corentin on 10/6/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "NetworkManager.h"
#include <sstream>

#define LOGGING_ENABLED

using namespace std;
using namespace sf;

void NetworkManager::createLobby(const string& name)
{
    Json::Value response = post("/lobby/new/", "name=" + name);
    cout << response.toStyledString();
}

void NetworkManager::listLobbies()
{
    Json::Value response = get("/lobby/");
    cout << response.toStyledString();
}

void NetworkManager::sendTurn(Lobby const& lobby, Card const& card)
{
    stringstream params;
    params << "lobby="
           << lobby.getName()
           << "&player="
           << "player_id"
           << "&card_suit="
           << card.getSuit()
           << "&card_value="
           << card.getValue();

    Json::Value response = post("/turn/", params.str());
    cout << response.toStyledString();
}

Json::Value NetworkManager::request(const string& url, const string& body, Http::Request::Method method)
{
    Json::Value root;
    Http http(ROOT_URL);

    Http::Request httpRequest(url, method, body);
#ifdef LOGGING_ENABLED
    cout << "[Network] - Sending request to " << url << endl;
#endif
    Http::Response response = http.sendRequest(httpRequest);

    Http::Response::Status status = response.getStatus();

    if (status == Http::Response::Ok) {
        cout << "Ok: ";
    }
    else {
        cout << "Error: " << response.getBody();
    }

    Json::Reader reader;
    bool parsingSuccessful = reader.parse(response.getBody(), root);

    if (!parsingSuccessful) {
        cout << "Failed to parse configuration\n" << reader.getFormattedErrorMessages();
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