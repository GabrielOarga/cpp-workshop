#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>
#include <functional>
#include <iostream>
#include <ostream>
#include <map>
#include <list>

using namespace std;
/*
class File;
class TextFile;
class Folder;

// composite in conjunctie cu visitor

class IVisitor
{
public:
    virtual void visit(File &) = 0;
    virtual void visit(TextFile &) = 0;
    virtual void visit(Folder &) = 0;
};

//clasa de baza
class File
{
public:
    File(string name, string ext) : m_name(name), m_ext(ext) {}
    
    virtual void open() { cout << "Opened " << m_name << "." << m_ext << endl; }
    virtual string cat() const { return ""; }
    
    string getExt() const { return m_ext; }
    string getName() const { return m_name; }
    
    virtual void operation(IVisitor &v)
    {
        v.visit(*this);
    }
    
protected:
    string m_name;
    string m_ext;
};

class TextFile : public File
{
public:
    TextFile(string name, string content) : File(name, "txt"),
    m_content(content) {}
    
    virtual string cat() const override { return m_content; }
    
    virtual void operation(IVisitor &v)
    {
        v.visit(*this);
    }
    
protected:
    string m_content;
    
};


class Folder : public File
{
public:
    Folder(string name) : File(name, "") {}
    
    string cat() const override
    {
        stringstream ss;
        ss << m_name << ": \n";
        
        for (auto f : m_children) {
            ss << f.get().getName()  << " : " << f.get().cat() << endl;
        }
        return ss.str();
    }
    
    Folder &add(File &f)
    {
        m_children.emplace_back(ref(f));
        return *this;
    }
    
    void rm(string name)
    {
        m_children.erase(remove_if(m_children.begin(), m_children.end(), [name] (auto f) {return f.get().getName() == name;}));
    }
    
    virtual void operation(IVisitor &v)
    {
        v.visit(*this);
    }
    
private:
    vector<reference_wrapper<File>> m_children;
    
};
*/
class Email;

class Folder
{
public:
    Folder(string name) : m_name(name) {};
    
    void addEmail(Email* email)
    {
        m_emails.push_back(email);
    }
    
private:
    string m_name;
    vector<Email*> m_emails;
};

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
    virtual bool filter(Email& e) = 0;
    
    void setName(string name) { m_name = name; }
    string getName() { return m_name; }
    
private:
    string m_name;
};

class DefaultFilter : public Filter
{
public:
    bool filter(Email& e) override;
};

class FromFilter : public Filter
{
public:
    bool filter(Email& e) override;
};
//add FromFilter... other filters

class Outlook
{
public:
    Outlook()
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
        for (auto filter : m_filters)
        {
            if (filter->filter(e))
            {
                folders.at(filter->getName()).push_back(e);
            }
        }
    }
    
    void createNewFilter(Filter* f)
    {
        m_filters.push_back(f);
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
    list<Filter*> m_filters{};
    
    
};

bool DefaultFilter::filter(Email& e)
{
    //
    return true;
}

bool FromFilter::filter(Email &e)
{
    if (e.getFrom() == "alina@email.com")
    {
        return true;
    }
    return false;
}


int main()
{
    Outlook outlook{};
    // create filters...
    
    FromFilter ffilter{};
    ffilter.setName("inbox");
    Email email{"alina@email.com", "mysadness@email.com", "", "subject", "spam"};
    
    outlook.createNewFilter(&ffilter);
    outlook.emailReceived(email);
    outlook.showFolders();
    
    
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

