#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class Document
{
public:
	Document(const string& name) : m_name(name)
	{
		cout << "Created new document with name " << m_name << endl;
	}
protected:
	string m_name;
};

class TextDocument : public Document
{
public:
	TextDocument(const string& name) : Document(name) {}
};

class WordDocument : public Document
{
public:
	WordDocument(const string& name) : Document(name) {}
};

class PdfDocument : public Document
{
public:
	PdfDocument(const string& name) : Document(name) {}
};

class DocumentCreator
{
public:
	virtual Document createDocument(const string& name) const = 0;
};

class TextDocumentCreator : public DocumentCreator
{
public:
	Document createDocument(const string& name) const override
	{
		return TextDocument{ name + ".txt" };
	}
};

class WordDocumentCreator : public DocumentCreator
{
public:
	Document createDocument(const string& name) const override
	{
		return WordDocument{ name + ".docx" };
	}
};

class PdfDocumentCreator : public DocumentCreator
{
public:
	Document createDocument(const string& name) const override
	{
		return PdfDocument{ name + ".pdf" };
	}
};


int main()
{
	DocumentCreator& factory{ PdfDocumentCreator{} };
	Document doc1{ factory.createDocument("GOF1") };
	Document doc2{ factory.createDocument("GOF2") };

	getchar();
    return 0;
}
