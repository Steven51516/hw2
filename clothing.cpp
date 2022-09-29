#include "clothing.h"
#include <sstream>


Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string Size, const std::string Brand):
	Product(category,name,price,qty),Size_(Size),Brand_(Brand)
{

}
Clothing::~Clothing()
{

}
std::set<std::string> Clothing::keywords() const
{
	std::set<std::string> kw;
	kw.insert(Brand_);
	kw.insert(name_);
	return kw;
}

std::string Clothing::displayString() const
{
	std::stringstream ss;
	ss << name_ << "\nSize: " << Size_ << " Brand: " << Brand_ << "\n" << price_ << " " << qty_ << " left." ;
	return ss.str();
}

void Clothing::dump(std::ostream& os) const
{
	os << category_ << std::endl;
	os << name_ << std::endl;
	os << price_ << std::endl;
	os << qty_ << std::endl;  
	os << Size_ << std::endl;
	os << Brand_ << std::endl;
}