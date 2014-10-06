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

using namespace std;

class NetworkManager {

public:
    static void createLobby();

private:
    static Json::Value request(const string& url, const string& body, sf::Http::Request::Method method);
    static Json::Value get(const string& url);
    static Json::Value post(const string& url, const string& body);
};
