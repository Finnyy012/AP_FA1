#include <ctime>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <list>
#include <utility>

using namespace std;

struct Game
{
    string title;
    int releaseDate;
    float originalPrice;

    public:
        Game(string t, int r, float o){
            title = move(t);
            releaseDate = r;
            originalPrice = o;
        }
        string getTitle(){
            return title;
        }
        void setTitle(string t){
            title = move(t);
        }
        int getReleaseDate(){
            return releaseDate;
        }
        void setReleaseDate(int r){
            releaseDate = r;
        }
        float getOriginalPrice(){
            return originalPrice;
        }
        void setOriginalPrice(float o){
            originalPrice = o;
        }

        float calculateCurrentPrice(){
            time_t curr_time = time(NULL);
            tm *tm_local = localtime(&curr_time);
            int diff = tm_local->tm_year + 1900 - releaseDate;
            return (originalPrice*pow(0.7, diff));
        }

        bool operator==(const Game &rhs) const {
            return title == rhs.title &&
                   releaseDate == rhs.releaseDate &&
                   originalPrice == rhs.originalPrice;
        }

        bool operator!=(const Game &rhs) const {
            return !(rhs == *this);
        }

        friend ostream &operator<<(ostream &os, const Game &game) {
            os << "title: " << game.title << " releaseDate: " << game.releaseDate << " originalPrice: "
               << game.originalPrice;
            return os;
        }
};

struct Person
{
    float budget;
    string name;
    list<Game> games;

    public:
        Person(string n, float b){
            name = move(n);
            budget = b;
        }

        bool buy(Game& game){
            float price = game.calculateCurrentPrice();
            if(!count(games.begin(), games.end(), game) && price<=budget){
                budget=budget-price;
                games.push_back(game);
                return true;
            }
            return false;
        }

        bool sell(Game& game, Person& buyer){
            if(count(games.begin(), games.end(), game)) {
                if(buyer.buy(game)){
                    games.remove(game);
                    budget = budget+game.calculateCurrentPrice();
                    return true;
                }
            }
            return false;
        }

        void addGame(Game game) {
            games.push_back(game);
        }

        void removeGame(Game game) {
            games.remove(game);
        }

        float getBudget(){
            return budget;
        }
        void setBudget(float budget){
            Person::budget = budget;
        }
        string getName(){
            return name;
        }
        void setName(string name) {
            Person::name = move(name);
        }

        list<Game> getGames(){
            return games;
        }

        void setGames(list<Game> games) {
            Person::games = move(games);
        }

        friend ostream &operator<<(ostream &os, const Person &person) {
            string gameStr;
            for(const auto& i : person.games){
                gameStr += (i.title + "; ");
            }
            os << "name: " << person.name << " budget: " << person.budget << " games: " << gameStr;
            return os;
        }
};


int main()
{
    time_t result = std::time(NULL);
    cout << std::asctime(std::localtime(&result));
    time_t curr_time = time(NULL);
    tm *tm_local = localtime(&curr_time);
    int releaseDate1 = tm_local->tm_year + 1899; // 1 jaar geleden
    int releaseDate2 = tm_local->tm_year + 1898; // 2 jaar geleden

    Game g1("Just Cause 3", releaseDate1 , 49.98);
    Game g2("Need for Speed: Rivals", releaseDate2 , 45.99);
    Game g3("Need for Speed: Rivals", releaseDate2 , 45.99);

    Person p1("Eric", 200);
    Person p2("Hans", 55);
    Person p3("Arno", 185);

    // Druk de volgende transacties af (pas de code aan)
    cout << p1.buy(g1) << endl;
    cout << p1.buy(g2) << endl;
    cout << p1.buy(g3) << endl;
    cout << p2.buy(g2) << endl;
    cout << p2.buy(g1) << endl;
    cout << p3.buy(g3) << endl;

    // Druk personen p1, p2 en p3 nu af naar de console
    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;


    // Druk de volgende transacties af (pas de code aan)
    cout << p1.sell(g1, p3) << endl;
    cout << p2.sell(g2, p3) << endl;
    cout << p2.sell(g1, p1) << endl;

    // Druk personen p1, p2 en p3 nu af naar de console
    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;
}
