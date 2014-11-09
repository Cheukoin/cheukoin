//
//  NetworkManager.h
//  Cheukoin
//
//  Created by Corentin on 10/6/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#pragma once

#include <iostream>
#include "SFML/Network.hpp"
#include "json/json.h"
#include "Lobby.h"

//#define ROOT_URL "http://cheukoin.herokuapp.com/"
#define ROOT_URL "http://127.0.0.1/", 8000

class NetworkManager {

public:
    static void createLobby(const std::string& name);
    static void listLobbies();
    static void sendTurn(Lobby const& lobby, Card const& card);

private:
    static Json::Value request(const std::string& url, const std::string& body, sf::Http::Request::Method method);
    static Json::Value get(const std::string& url);
    static Json::Value post(const std::string& url, const std::string& body);
};
