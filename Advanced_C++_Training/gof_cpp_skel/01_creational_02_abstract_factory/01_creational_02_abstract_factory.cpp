#include "stdafx.h"
#include <iostream>

class Product1 {};

class Product2 {};

class Product11 : public Product1 {};

class Product12 : public Product1 {};

class Product21 : public Product2 {};

class Product22 : public Product2 {};

class ProductsFactory
{
public:
	virtual Product1 createProduct1() const = 0;
	virtual Product2 createProduct2() const = 0;
};

class Factory1 : public ProductsFactory
{
public:
	Product1 createProduct1() const override
	{
		return Product11{};
	}
	Product2 createProduct2() const override
	{
		return Product21{};
	}
};

class Factory2 : public ProductsFactory
{
public:
	Product1 createProduct1() const override
	{
		return Product12{};
	}
	Product2 createProduct2() const override
	{
		return Product22{};
	}
};

int main()
{
	ProductsFactory& factory{ Factory2{} };
	Product1 p1{ factory.createProduct1() };
	Product2 p2{ factory.createProduct2() };

	// Obs: You cannot take the address of a constructor =>
	// best functional equivalent is to pass around the address
	// of the factory method

	getchar();
    return 0;
}
