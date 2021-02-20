#ifndef __MOVIEMANAGER__
#define __MOVIEMANAGER__
#include "RBTree.hpp"
#include "RBTree.cpp"
#include <cstring>
#include <list>
#include <fstream>
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*                                                      Movie                                                              */
struct Movie{
    int ID;
    char* name;
    bool operator>(Movie obj){
        return this->ID > obj.ID;
    }
    bool operator<(Movie obj){
        return this->ID < obj.ID;
    }
    bool operator==(Movie obj){
        return (this->ID == obj.ID);
    }
    
    bool operator!=(Movie obj){
        return(this->ID != obj.ID );
    }
    Movie()=default;
    Movie(int ID,char* name):ID(ID),name(name){
    }
    Movie(int ID):ID(ID),name(""){
        
    }
    friend std::ostream& operator<<(std::ostream& os,const Movie &m);
};


/*                                                      Movie                                                              */
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*                                                      User                                                               */

struct User{
    int ID;
    
    std::list<Movie> moviesWatched;
    bool operator>(User obj){
        return this->ID > obj.ID;
    }
    bool operator<(User obj){
        return this->ID < obj.ID;
    }
    bool operator==(User obj){
        return this->ID == obj.ID;
    }
    
    bool operator!=(User obj){
        return this->ID != obj.ID;
    }
    User(int ID):ID(ID){}
    User(int ID,std::list<Movie> moviesWatched):ID(ID),moviesWatched(moviesWatched){}
    User()=default;

};




/*                                                      User                                                               */
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/




class Database
{
private:
    
    
public:
    RBTree<User> userTree;
    RBTree<Movie> movieTree;
    void makeUserTree(const char* fileName);
    void makeMovieTree(const char* fileName);
};

#endif