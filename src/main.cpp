#include "RBTree.hpp"
#include "RBTree.cpp"
#include "Database.hpp"
#include <ctime>
#define USERFILE "ml-1m/ratings.dat"
#define MOVIESFILE "ml-1m/movies.dat"



int main(int argc, char const *argv[])
{
    Database db;
    srand(time(nullptr));
    db.makeMovieTree(MOVIESFILE);
    // for (int i = 0; i < 100000; i++)
    // {
    //     auto p = 1+ rand()%3951;
    //     aux = db.movieTree.search(Movie(p,""),[](Movie v1,Movie v2){
    //         return v1 == v2;
    //     });
    // }
    
    db.makeUserTree(USERFILE);
    
    return 0;
}
