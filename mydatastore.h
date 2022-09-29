#include "datastore.h"
#include "map"
#include "deque"


class MyDataStore: public DataStore
{
	public:
	~MyDataStore();
	void addProduct(Product* p);
	void addUser(User* u);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	void dump(std::ostream& ofile);
	void initialize_user();  // initialize the map by adding users with empty cart
	bool add_cart(std::string name, int n, const std::vector<Product*>& hits); 
	bool view_cart(std::string name);
  bool buy_cart(std::string name);
	private:
	std::vector<Product*> p_list;  //store pointers of all products
	std::vector<User*> u_list; // store pointers of all users
	std::map<User*, std::deque<Product*>> username; // map for the cart

};