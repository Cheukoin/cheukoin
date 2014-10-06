//
//  NetworkManager.cpp
//  Cheukoin
//
//  Created by Corentin on 10/6/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "NetworkManager.h"
#include "json/json.h"

void NetworkManager::createLobby() {
    sf::Http http;
    http.setHost("http://localhost/", 8000);
    sf::Http::Request request("/lobby/new/");
    sf::Http::Response response = http.sendRequest(request);

    sf::Http::Response::Status status = response.getStatus();
    if (status == sf::Http::Response::Ok)
    {
        Json::Value root;   // will contains the root value after parsing.
        Json::Reader reader;
        bool parsingSuccessful = reader.parse( response.getBody(), root );

        if (!parsingSuccessful)
        {
            // report to the user the failure and their locations in the document.
            cout  << "Failed to parse configuration\n" << reader.getFormattedErrorMessages();
            return;
        }
        else
        {
            cout << root["Hello"];
        }

    }
    else
    {
        cout << "Error " << status << std::endl;
    }
}