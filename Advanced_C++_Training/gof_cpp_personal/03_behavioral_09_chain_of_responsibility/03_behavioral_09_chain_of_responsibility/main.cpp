//
//  main.cpp
//  03_behavioral_09_chain_of_responsibility
//
//  Created by Gabriel Oarga on 17/10/2017.
//  Copyright © 2017 Gabriel Oarga. All rights reserved.
//

#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

class Email
{
public:
    Email(string from, string to, string cc, string subject, string message) :
    from(from), to(to), cc(cc), subject(subject), message(message)
    {}
    
    friend ostream& operator<<(ostream& out, const Email& e);
    
    string getFrom() const { return from; }
    string getTo() const { return to; }
    string getCc() const { return cc; }
    string getSubject() const { return subject; }
    string getMessage() const { return message; }
    
private:
    string from, to, cc;
    string subject;
    string message;
};

ostream& operator<<(ostream& out, const Email& e)
{
    out << "from: " << e.from << ", to: " << e.to;
    return out;
}

class Outlook;

class Filter
{
public:
    Filter(Outlook& o) : m_outlook(o) {}
    
    virtual bool filter(Email& e) { return false; }
    
    virtual void handle(Email& e);
    
    //    void add(Filter* f) { m_filters.push_back(f); }
    
protected:
    Outlook& m_outlook;
    vector<Filter*> m_filters;
};

class DefaultFilter : public Filter
{
public:
    DefaultFilter(Outlook& o) : Filter(o) {}
    
    bool filter(Email& e) override;
};

//add FromFilter... other filters

class Outlook
{
public:
    Outlook() :
    rootFilter(Filter{ *this })
    {
        folders["organizational"] = vector<Email>{};
        folders["spam"] = vector<Email>{};
        folders["inbox"] = vector<Email>{};
    }
    
    vector<Email>& getFolder(string folderName)
    {
        return folders[folderName];  // always returns something
    }
    
    void emailReceived(Email& e)
    {
        // implement
    }
    
    void createNewFilter(Filter* f)
    {
        // implement
    }
    
    void showFolders()
    {
        for (auto folder : folders) {
            for (auto email : folder.second) {
                cout << email << endl;
            }
        }
    }
    
private:
    map<string, vector<Email>> folders{};
    Filter& rootFilter;
};


void Filter::handle(Email& e)
{
    bool processed = false;
    for (auto f : m_filters) {
        processed = f->filter(e);
        if (processed) {
            break;  // filter processed email and decided that chain should stop
        }
    }
    if (!processed)
        m_outlook.getFolder("inbox").push_back(e);
}

bool DefaultFilter::filter(Email& e)
{
    m_outlook.getFolder("inbox").push_back(e);
    return true;
}


int main()
{
    Outlook outlook{};
    // create filters...
    //    FromFilter* alina = new FromFilter{ "alina.banici@acc.com", "organizational", false, outlook };
    //    outlook.createNewFilter(alina);
    //    outlook.createNewFilter(FromFilter("gigi@gmail.com", "spam", false, outlook));
    //    outlook.createNewFilter(FromFilter("spam@spam.com", "spam", false, outlook));
    
    //    outlook.emailReceived(Email("alina.banici@acc.com", "cucu@microsoft.com", "", "", "Hello!"));
    //    outlook.emailReceived(Email("alina.banici@acc.com", "cucu@microsoft.com", "", "", "Hello!"));
    //    outlook.emailReceived(Email("spam@spam.com", "cucu@microsoft.com", "", "", "Hello!"));
    //    outlook.emailReceived(Email("gigi@gmail.com", "cucu@microsoft.com", "", "", "Hello!"));
    //    outlook.emailReceived(Email("bill.gates@microsoft.com", "cucu@microsoft.com", "", "", "Hello!"));
    
    outlook.showFolders();
    return 0;
}

