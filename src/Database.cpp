#include "Database.hpp"

void Database::makeMovieTree(const char* fileName){
    const char* token="::";
    RBTree<Movie> rb;
    std::ifstream file{fileName};
    if(!file){
        std::cerr<<"[ERRO] Erro ao abrir o arquivo"<<std::endl;
        exit(-1);
    }
    std::string s;
    int id;
    char* name;
    while (std::getline(file,s))
    {
        
        char str[strlen(s.c_str()+1)];
        strcpy(str,s.c_str());
        char *pch = strtok(str,token);
        id = atoi(pch);
        pch = strtok(NULL,token);
        name = new char[strlen(pch)+1];
        strcpy(name,pch);
        this->movieTree.insert(Movie(id,name));
    }
    file.close();
}

void Database::makeUserTree(const char* fileName){
    
    std::list<Movie> listMovies;
    
    const char* token = "::";
    std::ifstream file{fileName};
    int userId{};
    int movieId{};
    bool userNotFound{false};
    std::string s;
    while (std::getline(file,s))
    {
        
        char str[strlen(s.c_str()+1)];
        strcpy(str,s.c_str());
        char *pch = strtok(str,token);
        userId = atoi(pch);
        pch = strtok(NULL,token);
        movieId = atoi(pch);
        User* us = userTree.search(userId);
        if(!us){
            userNotFound = true;
            us = new User(userId);
        } 

        Movie* m = movieTree.search(movieId);

        if (m) us->moviesWatched.push_back(*m); // Copy

        if (userNotFound){
            userTree.insert(*us);
            delete us;
            userNotFound = false;
        }
        
        
    }
    file.close();
}
std::ostream& operator<<(std::ostream& os,const Movie &m){
    os << m.ID<<" / "<<m.name;
    return os;
}

std::ostream& operator<<(std::ostream& os,const User &u){
    os<<u.ID;
    return os;
}