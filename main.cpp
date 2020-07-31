#include <iostream>
#include <string>

// szablon klasy o zmiennej liczbie parametrow moze byc wykorzystany
// do generycznego definiowania wielodziedziczenia, czyli wiemy ze klasa
// moze dziedziczyc po wielu klasach ale nie wiemy po ilu wiec to bedzie
// zawarte w pakiecie parametrow

class MusicEnthusiast {
private:
    int number_of_favourite_songs;
public:

    explicit MusicEnthusiast(const int numbers_of_favourite_songs) :
            number_of_favourite_songs{numbers_of_favourite_songs} {
        std::cout << "INSIDE MUSIC ENTHUSIAST CONSTRUCTOR" << std::endl;
    }

    void music_info() const {
        std::cout << "MUSIC ENTHUSIAST. NUMBER OF FAVOURITE SONGS: " << number_of_favourite_songs << std::endl;
    }
};

class SportEnthusiast {
private:
    std::string sport_discipline;
public:

    explicit SportEnthusiast(const std::string &sport_discipline) :
            sport_discipline{sport_discipline} {
        std::cout << "INSIDE SPORT ENTHUSIAST CONSTRUCTOR" << std::endl;
    }

    void sport_info() const {
        std::cout << "SPORT ENTHUSIAST. SPORT DISCIPLINE: " << sport_discipline << std::endl;
    }
};

class BooksEnthusiast {
private:
    std::string last_book_title;
public:
    explicit BooksEnthusiast(const std::string &last_book_title) :
            last_book_title{last_book_title} {
        std::cout << "INSIDE BOOKS ENTHUSIAST CONSTRUCTOR" << std::endl;
    }

    void books_info() const {
        std::cout << "BOOKS ENTHUSIAST. LAST BOOK TITLE: " << last_book_title << std::endl;
    }
};

template<typename ... BASE_CLASSES>
class Person : public BASE_CLASSES ... { // tutaj mamy liste pochodzenia klasy
private:
    std::string name;
public:
    // najpierw podajesz w liscie inicjalizacyjnej argumenty dla klas bazowych a potem dopiero
    // dla pol klasy pochodnej
    explicit Person(const std::string &name, BASE_CLASSES... args) : BASE_CLASSES(args)..., name{name} {
        std::cout << "INSIDE PERSON CONSTRUCTOR" << std::endl;
    }
};

void music(const MusicEnthusiast &music_enthusiast) {
    music_enthusiast.music_info();
}

void sport(const SportEnthusiast &sport_enthusiast) {
    sport_enthusiast.sport_info();
}

void book(const BooksEnthusiast &books_enthusiast) {
    books_enthusiast.books_info();
}

// ----------------------------------------------------------------------------
// specjalizacja klasy szablonowej
// ----------------------------------------------------------------------------
class GamesEnthusiast {
private:
    std::string game_category;
public:

    explicit GamesEnthusiast(const std::string &game_category) :
            game_category{game_category} {
        std::cout << "INSIDE GAME ENTHUSIAST CONSTRUCTOR" << std::endl;
    }

    void game_info() const {
        std::cout << "GAME ENTHUSIAST. FAVOURITE GAME CATEGORY: " << game_category << std::endl;
    }
};


// specjalizacja numer 1
template<>
class Person<> {
private:
    std::string name;
public:
    explicit Person(const std::string &name) : name{name} {}

    void info() const {
        std::cout << "PERSON: " << name << std::endl;
    }
};

// specjalizacja numer 2
template<>
class Person<GamesEnthusiast> : public GamesEnthusiast {
private:
    std::string name;
public:
    explicit Person(const std::string &name, const std::string &game_category) : GamesEnthusiast(game_category),
                                                                                 name{name} {}

    void only_game_info() const {
        std::cout << "PERSON: " << name << std::endl;
    }
};


int main() {

    Person/*<MusicEnthusiast, BooksEnthusiast>*/ music_and_book_enthusiast(
            std::string("ANDY"),
            static_cast<MusicEnthusiast>(10), // mamy explicit wiec jawne rzutowanie
            static_cast<BooksEnthusiast>(std::string("HARRY POTTER"))); // ----- || -----

    music(music_and_book_enthusiast);
    book(music_and_book_enthusiast);
    // sport(music_and_book_enthusiast); // blad

    // przyklady dla utworzonych specjalizacji
    Person person("EVA");
    person.info();

    Person<GamesEnthusiast> game_enthusiast("MICHAEL", "RPG");
    game_enthusiast.game_info();

    return 0;
}
