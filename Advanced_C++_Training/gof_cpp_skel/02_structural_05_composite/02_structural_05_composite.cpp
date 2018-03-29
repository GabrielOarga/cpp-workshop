#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>
#include <functional>

using namespace std;

class File
{
public:
	File(string name, string ext) : m_name(name), m_ext(ext) {}
	
	virtual void open() { cout << "Opened " << m_name << "." << m_ext << endl; }
	virtual string cat() const { return ""; };

	string getExt() const { return m_ext; }
	string getName() const { return m_name; }

protected:
	string m_name;
	string m_ext;
};

class TextFile : public File
{
public:
	TextFile(string name, string content) : File(name, "txt"), m_content(content) {}
	virtual string cat() const override { return m_content; }

protected:
	string m_content;
};

class Folder : public File
{
public:
	Folder(string name) : File(name, "") {}
	virtual string cat() const override
	{
		stringstream ss;
		ss << m_name << ":\n";
		for (auto f : m_children) {
			ss << f.get().getName() << ":" << f.get().cat() << endl;
		}
		return ss.str();
	}

	Folder& add(File& f)
	{
		m_children.emplace_back(ref(f));
		return *this;
	}

	void rm(string fileName)
	{
		m_children.erase(remove_if(m_children.begin(), m_children.end(),
				[&fileName] (auto f) { return f.get().getName() == fileName; }));
	}
private:
	vector<reference_wrapper<File>> m_children{};
};

int main()
{
	TextFile a11{ "a11", "content11" };
	TextFile a12{ "a12", "content12" };
	TextFile a13{ "a13", "content13" };
	TextFile a14{ "a14", "content14" };

	TextFile a21{ "a21", "content21" };
	TextFile a22{ "a22", "content22" };
	TextFile a23{ "a23", "content23" };
	Folder subfolder{ "subfolder" };
	subfolder.add(ref(a21)).add(ref(a22)).add(ref(a23));

	Folder root{ "root" };
	root.add(ref(a11)).add(ref(a12)).add(ref(a13)).add(ref(a14));
	root.add(ref(subfolder));
	cout << root.cat() << endl;

	subfolder.rm("a22");
	cout << root.cat() << endl;

	getchar();
	return 0;
}
