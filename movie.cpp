#include "movie.h"
#include <sstream>


Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string Genre, const std::string Rating):
	Product(category,name,price,qty),Genre_(Genre),Rating_(Rating)
{

}
Movie::~Movie()
{

}
std::set<std::string> Movie::keywords() const
{
	std::set<std::string> kw;
	kw.insert(Genre_);
	kw.insert(name_);
	return kw;
}

std::string Movie::displayString() const
{
	std::stringstream ss;
	ss << name_ << "\nGenre: " << Genre_ << " Rating: " << Rating_ << "\n" << price_ << " " << qty_ << " left." ;
	return ss.str();
}

void Movie::dump(std::ostream& os) const
{
	os << category_ << std::endl;
	os << name_ << std::endl;
	os << price_ << std::endl;
	os << qty_ << std::endl;  
	os << Genre_ << std::endl;
	os << Rating_ << std::endl;
}