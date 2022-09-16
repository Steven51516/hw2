#include "product.h"

class Movie : public Product
{
	public:
	Movie(const std::string category, const std::string name, double price, int qty, const std::string Genre, const std::string Rating);
	~Movie();
	std::set<std::string> keywords() const;
	std::string displayString() const;
	void dump(std::ostream& os) const;

	private:
	std::string Genre_;
	std::string Rating_;
};