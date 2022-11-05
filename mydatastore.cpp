#include "mydatastore.h"
#include "util.h"


//initialize the map that stores cart information
void MyDataStore::initialize_user()
{
	int user_n = u_list.size();
	for(int i = 0; i < user_n; i++)
	{
		std::deque<Product*> temp;
		username[u_list[i]]=temp;
	}
}


//delete all allocated objects which are created by new expression
MyDataStore::~MyDataStore()
{
	for(int i = 0; i < int(u_list.size()); i++)
	{
		delete u_list[i];
	}
	for(int i = 0; i < int(p_list.size()); i++)
	{
		delete p_list[i];
	}


}

// return 1 when there is invalid input. Add products from hits to the cart map.
bool MyDataStore::add_cart(std::string name, int n, const std::vector<Product*>& hits)
{
	bool find = false;
	User* u = NULL;
	for(int i = 0; i < int(u_list.size()); i++)
	{
		if(name == u_list[i] -> getName())
		{
			find = true;
			u = u_list[i];
		}

	}
	if(!find || n<=0 || n>int(hits.size()))
	{
		return 1;
	}

	username[u].push_back(hits[n-1]);
	return 0;
}

// return 1 when there is invalid input. Call the displayString() function to view the cart.
bool MyDataStore::view_cart(std::string name)
{
	bool find = false;
	User* u = NULL;
	for(int i = 0; i < int(u_list.size()); i++)
	{
		if(name == u_list[i] -> getName())
		{
			find = true;
			u = u_list[i];
		}

	}
	if(!find)
	{
		return 1;
	}

	int n_cart = username[u].size();
	for(int i = 0; i < n_cart; i++)
	{
		std::cout<<"Item "<<i+1<<" :"<<std::endl;
		std::cout<<username[u][i]->displayString()<<std::endl;
		std::cout<<std::endl;
	}
	return 0;

}

// return 1 when there is invalid input. Buy items according to the sequence it is put into the cart
bool MyDataStore::buy_cart(std::string name)
{
	bool find = false;
	User* u = NULL;
	for(int i = 0; i < int(u_list.size()); i++)
	{
		if(name == u_list[i] -> getName())
		{
			find = true;
			u = u_list[i];
		}

	}
	if(!find)
	{
		return 1;
	}

	int cart_size = username[u].size();
	// create a vector to store index for removel later. Avoid mess up the index of cart.
	std::vector<int> remove_index;
	int index = 0;
	for(int i = 0; i < cart_size; i++)
	{
		if(username[u][i] -> getPrice()<=u -> getBalance() && username[u][i]->getQty()>0)
		{
			u -> deductAmount(username[u][i] -> getPrice());
			username[u][i]->subtractQty(1);
			remove_index.push_back(index);
		}
		index++;
	}
	for(int i=remove_index.size()-1; i>=0; i--)
	{
		username[u].erase(username[u].begin()+remove_index[i]);
	}
	return 0;
}



void MyDataStore::addProduct(Product* p)
{
	p_list.push_back(p);
}


void MyDataStore::addUser(User* u)
{
	u_list.push_back(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
	//vector for final result
	std::vector<Product*> result_v;
	//create a vector to store sets of items found for each keyword.
	std::vector<std::set<Product*>> all(terms.size(),std::set<Product*>{});
	for(int i = 0; i < int(p_list.size()); i++)
	{
		std::set<std::string> temp_set = p_list[i]->keywords();
		for(std::set<std::string>::iterator it = temp_set.begin(); it!=temp_set.end(); ++it)
		{
			std::string keyword = *it;
			keyword=convToLower(keyword);
			for(int j = 0; j < int(terms.size()); j++)
			{
				if(terms[j]==keyword)
				{
					
					all[j].insert(p_list[i]);
				}
			}
		}
	}



	// 	//vector for final result
	// std::vector<Product*> result_v;
	// //create a vector to store sets of items found for each keyword.
	// std::vector<std::set<Product*>> all(terms.size(),std::set<Product*>{});
	// for(int i = 0; i < int(p_list.size()); i++)
	// {
	// 	std::set<std::string> temp_set = p_list[i]->keywords();
	// 	for(std::set<std::string>::iterator it = temp_set.begin(); it!=temp_set.end(); ++it)
	// 	{
	// 		std::string word = *it;
	// 		std::set<std::string> word_parse = parseStringToWords(word);
	// 		for(std::set<std::string>::iterator it1 = word_parse.begin(); it1 != word_parse.end(); ++it1)
	// 		{
	// 			std::string keyword = *it1;
	// 			keyword=convToLower(keyword);
	// 			for(int j = 0; j < int(terms.size()); j++)
	// 			{
	// 				if(terms[j]==keyword)
	// 				{
						
	// 					all[j].insert(p_list[i]);
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	
	// OR
	if(type==1)
	{
		std::set<Product*> result_s = all[0];
		for(int i = 1; i < int(terms.size()); i++)
		{
			result_s = setUnion(result_s, all[i]);
		}
		for(std::set<Product*>::iterator it = result_s.begin(); it!=result_s.end(); ++it)
		{
			result_v.push_back(*it);
		}
	}

	// AND
	else if(type==0)
	{
		std::set<Product*> result_s = all[0];
		for(int i = 1; i < int(terms.size()); i++)
		{
			result_s = setIntersection(result_s, all[i]);
		}
		for(std::set<Product*>::iterator it = result_s.begin(); it!=result_s.end(); ++it)
		{
			result_v.push_back(*it);
		}
	}
	return result_v;

}


void MyDataStore::dump(std::ostream& ofile)
{
	ofile << "<products>" << std::endl;
	for(int i = 0; i<int(p_list.size()); i++)
	{
		p_list[i]->dump(ofile);
	}
	ofile << "</products>" << std::endl;
  ofile << "<users>" << std::endl;
	for(int i = 0; i<int(u_list.size()); i++)
	{
		u_list[i]->dump(ofile);
	}
	ofile << "</users>" << std::endl;

}