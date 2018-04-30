//
//  01.13.02.14-STL_Study.cpp
//  Xcode9.3(9E145)-STL
//
//  Created by das on 01/05/2018.
//  Copyright © 2018 das. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Medal {
public:
    enum MedalType {
        GOLD,
        SILVER,
        BRONZE
    };
    enum GameType {
        SWIMMING,
        RUNNING
    };
    
    Medal() {}
    
    Medal(MedalType medal_type, GameType game_type, string winner_name)
    : medal_type_(medal_type),
    game_type_(game_type),
    winner_name_(winner_name) {}
    
    MedalType GetMedalType() const {
        return medal_type_;
    }
    
private:
    MedalType medal_type_;
    GameType game_type_;
    string winner_name_;
};

const char* CountryNames[] = {"Korea", "USA", "Japan"};

bool GreaterMedal(const Medal& m1, const Medal& m2) {
    return m1.GetMedalType() > m2.GetMedalType();
}

bool LessMedal(const Medal& m1, const Medal& m2) {
    return m1.GetMedalType() < m2.GetMedalType();
}

class Country {
public:
    enum CountryType {
        KOREA,
        USA,
        JAPAN
    };
    
    Country() {}
    Country(CountryType country_type)
    : country_type_(country_type) {}
    
    void AddMedal(const Medal& medal) {
        medals_.push_back(medal);
    }
    
    void AddMedal(const Medal::MedalType medal_type,
                  const Medal::GameType game_type,
                  const string& winner_name) {
        AddMedal(Medal(medal_type, game_type, winner_name));
    }
    
    int GetMedalSize() const {
        return medals_.size();
    }
    
    string GetName() const {
        return CountryNames[country_type_];
    }
    
    void SortMedal() {
        sort(medals_.begin(), medals_.end(), GreaterMedal);
    }
    
    vector<Medal>& GetMedal() { return medals_; }
    
private:
    CountryType country_type_;
    vector<Medal> medals_;
};

bool CountryCompare(Country* c1, Country* c2) {
    return lexicographical_compare(c1->GetMedal().begin(), c1->GetMedal().end(),
                                   c2->GetMedal().begin(), c2->GetMedal().end(),
                                   LessMedal);
}

class OlympicCommittee {
public:
    ~OlympicCommittee() {
        for (vector<Country*>::iterator iter = countries.begin();
             iter != countries.end(); ++iter) {
            delete *iter;
        }
        countries.clear();
    }
    
    // 절대로 지우지 말것.
    Country* AddCountry(const Country::CountryType country_type) {
        Country* country = new Country(country_type);
        countries.push_back(country);
        return country;
    }
    
    void Sort() {
        for(vector<Country*>::const_iterator iter = countries.begin();
            iter != countries.end();
            ++iter) {
            (*iter)->SortMedal();
        }
        sort(countries.begin(), countries.end(), CountryCompare);
    }
    
    void Print() {
        for(vector<Country*>::const_iterator iter = countries.begin();
            iter != countries.end();
            ++iter) {
            cout << (*iter)->GetName() << endl;
        }
    }
    
private:
    vector<Country*> countries;
};

int main() {
    OlympicCommittee committee;
    Country* country = committee.AddCountry(Country::KOREA);
    country->AddMedal(Medal::GOLD, Medal::SWIMMING, "형욱");
    country->AddMedal(Medal::SILVER, Medal::RUNNING, "성조");
    country = committee.AddCountry(Country::USA);
    country->AddMedal(Medal::BRONZE, Medal::SWIMMING, "태협");
    country = committee.AddCountry(Country::JAPAN);
    country->AddMedal(Medal::GOLD, Medal::RUNNING, "도연");
    committee.Sort();
    committee.Print();
    return 0;
}
