#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

constexpr int MAX_STORE = 2;

class Cheese{
    private:
        string cheese;
    public:
        Cheese() = default;
        Cheese(const string &acheese) : cheese(acheese){};
        
        const string &getCheese() const { return cheese; }
};

class Pepperoni{
    private:
        string pepperoni;
    public:
        Pepperoni() = default;
        Pepperoni(const string &apepperoni) : pepperoni(apepperoni){};
        
        const string &getPepperoni() const { return pepperoni; }
};

class Vegetable{
    private:
        string vegies;
    public:
        Vegetable() = default;
        Vegetable(const string &vege) : vegies(vege){};
        
        const string &getVegies() const { return vegies; }
};

class Pizza{
    private:
        string type;
        Cheese cheese;
        Pepperoni pepperoni;
        Vegetable vegies;
        static int numOfPizzas;
    protected:
        void modifytype(const string &type){ this->type = type; };
    public:
        Pizza() = default;
        Pizza(const string &atype, const string &acheese, const string &apepperoni, const string &vege)
            : type(atype), cheese(acheese), pepperoni(apepperoni), vegies(vege){ numOfPizzas++; };
            
        const string &getType() const { return type; }
        const string &getCheese() const { return cheese.getCheese(); }
        const string &getPeppe() const { return pepperoni.getPepperoni(); }
        const string &getVegies() const { return vegies.getVegies(); }
        
        static Pizza *CreatePizza(const string &, const string &, const string &, const string &);
        
        virtual void prepare() const = 0;
};
int Pizza::numOfPizzas = 0;

class CheesePizza : public Pizza{
    private:
    public:
        CheesePizza() = default;
        CheesePizza(const string &atype, const string &acheese, const string &apepperoni, const string &vege)
            : Pizza(atype, acheese, apepperoni, vege){};
            
        virtual void prepare() const override { 
            cout << "Type:  " << getType();
            cout << "\nCheese: " << getCheese();
            if(getPeppe().compare("none")) cout << "\nPepperoni: " << getPeppe();
            if(getVegies().compare("none")) cout << "\nVege: " << getVegies();
        }
};

class PepperoniPizza : public Pizza{
    private:
    public:
        PepperoniPizza() = default;
        PepperoniPizza(const string &atype, const string &acheese, const string &apepperoni, const string &vege)
            : Pizza(atype, acheese, apepperoni, vege){};
            
        virtual void prepare() const override { 
            cout << "Type:  " << getType();
            if(getCheese().compare("none")) cout << "\nCheese: " << getCheese();
            cout << "\nPepperoni: " << getPeppe();
            if(getVegies().compare("none")) cout << "\nVege: " << getVegies();
        }
};
class VegePizza : public Pizza{
    private:
    public:
        VegePizza() = default;
        VegePizza(const string &atype, const string &acheese, const string &apepperoni, const string &vege)
            : Pizza(atype, acheese, apepperoni, vege){};
            
        virtual void prepare() const override { 
            cout << "Type:  " << getType();
            if(getCheese().compare("none")) cout << "\nCheese: " << getCheese();
            if(getPeppe().compare("none")) cout << "\nPepperoni: " << getPeppe();
            cout << "\nVege: " << getVegies();
        }
};

class PizzaStore{
    private:
        string location;
        static int numOfStores;
    protected:
        void modifyLocation(const string &);
    public:
        PizzaStore() = default;
        PizzaStore(const string &l) : location(l){ numOfStores++; };
        PizzaStore(const PizzaStore &) = default;
        virtual ~PizzaStore(){ numOfStores--; };
        
        // virtual void createPizza() const = 0;
        
        const string &getLocation() const { return location; }
        
        static PizzaStore *MatriculatePizzaStore(const string &, const string &, const string &, const string &, const string &);
        
        static int getNumOfStores() { return numOfStores; } 
        
        virtual void print() const = 0;
        
};
void PizzaStore::modifyLocation(const string &l){ location = l; }
int PizzaStore::numOfStores = 0;


class ChicagoPizzaStore : public PizzaStore{
    private:
        string pizzaType;
        Pizza *pizza;
    public:
        ChicagoPizzaStore() = default;
        ChicagoPizzaStore(const string &l, const string &type, const string &cheese, const string &pep, const string &vege) 
            : PizzaStore(l), pizzaType(type){
                pizza = Pizza::CreatePizza(type, cheese, pep, vege); 
            };
           
        
        virtual void print() const override{
            cout << "\nYou have ordered pizza at " << getLocation() << " store. ";
            cout << "The pizza type is " << pizzaType << ".\n";
            pizza->prepare();
        };
};

// class ChicagoStyleCheese : public ChicagoPizzaStore{};
// class ChicagoStylePepperoni : public ChicagoPizzaStore{};
// class ChicagoStyleVegies : public ChicagoPizzaStore{};

class NYPizzaStore : public PizzaStore{
    private:
        string pizzaType;
        Pizza *pizza;
    public:
        NYPizzaStore() = default;
        NYPizzaStore(const string &l, const string &type, const string &cheese, const string &pep, const string &vege) 
            : PizzaStore(l), pizzaType(type){
                pizza = Pizza::CreatePizza(type, cheese, pep, vege);        
            };
        
        virtual void print() const override{
            cout << "\nYou have ordered pizza at " << getLocation() << " store. ";
            cout << "The pizza type is " << pizzaType << ".\n";
            
            pizza->prepare();
        };
};

// class NYStyleCheese : public NYPizzaStore{};
// class NYStylePepperoni : public NYPizzaStore{};
// class NYStyleVegies : public NYPizzaStore{};

Pizza *Pizza::CreatePizza(const string &type, const string &acheese, const string &apepperoni, const string &vege){
    if(!type.compare("Cheese"))
        return new CheesePizza(type, acheese, apepperoni, vege);
    else if (!type.compare("Pepperoni"))
        return new PepperoniPizza(type, acheese, apepperoni, vege);
    else if (!type.compare("Vegetable"))
        return new VegePizza(type, acheese, apepperoni, vege);
        
    return nullptr;
};


PizzaStore *PizzaStore::MatriculatePizzaStore(const string &l, const string &type, const string &acheese, const string &apepperoni, const string &vege){
    if(!l.compare("Chicago"))
        return new ChicagoPizzaStore(l, type, acheese, apepperoni, vege);
    else if (!l.compare("New York"))
        return new NYPizzaStore(l, type, acheese, apepperoni, vege);
        
    return nullptr;
};

int main()
{
    PizzaStore *stores[MAX_STORE] = {};
    
    stores[0] = PizzaStore::MatriculatePizzaStore("Chicago", "Cheese", "Mozzarella", "slicedPeppe", "none");
    stores[1] = PizzaStore::MatriculatePizzaStore("New York", "Vegetable", "Italian", "none", "Pineapple");
    
    for(auto *store: stores){
        store->print();
        cout << "\n################\n";
    }
    
    for(auto *store: stores){
        delete store;
    }
    
    
    return 0;
}
