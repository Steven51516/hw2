#include "book.h"
#include <sstream>


Book::Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string Author):
	Product(category,name,price,qty),ISBN_(ISBN),Author_(Author)
{

}
Book::~Book()
{

}
std::set<std::string> Book::keywords() const
{
	std::set<std::string> kw;
	kw.insert(ISBN_);
	kw.insert(Author_);
	return kw;
}

std::string Book::displayString() const
{
	std::stringstream ss;
	ss << category_ << " " << name_ << " " << price_ << " " << qty_ << " " << ISBN_ << " " << Author_;
	return ss.str();
}

void Book::dump(std::ostream& os) const
{
	os << category_ << std::endl;
	os << name_ << std::endl;
	os << price_ << std::endl;
	os << qty_ << std::endl;  
	os << ISBN_ << std::endl;
	os << Author_ << std::endl;
}