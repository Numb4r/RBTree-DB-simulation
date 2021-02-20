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
    
    FILE * file;
    if(!(file = fopen(fileName,"r"))){
        std::cerr<<"[ERRO] Erro ao abrir o arquivo"<<std::endl;
        exit(-1);
        
    }
    int userId{};
    int movieId{};
    
    int dumb,dumb2;
    char line[20];
    userTree.insert(User(1));
    bool userNotFound{false};
    while (!feof(file))
    {
        fscanf(file,"%d::%d::%d::%d",&userId,&movieId,&dumb,&dumb2);

        User* us = userTree.search(User(userId));

        if (!us)
        {
            userNotFound = true;
            us = new User(userId);
        }
        
    
        Movie *movie = movieTree.search(Movie(movieId));
        if(movie){
            us->moviesWatched.push_back(*movie); //Copy
        }
        if(userNotFound){
            userTree.insert(*us); //Copy
            userNotFound = false;
            delete us;
        }
        
    }
    fclose(file);
}
std::ostream& operator<<(std::ostream& os,const Movie &m){
    os << m.ID<<" / "<<m.name;
    return os;
}

std::ostream& operator<<(std::ostream& os,const User &u){
    os<<u.ID;
    return os;
}