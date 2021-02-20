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

        User* us = userTree.search(User(userId),[](User v1,User v2){
            return v1.ID == v2.ID;
        });

        if (!us)
        {
            userNotFound = true;
            us = new User(userId);
        }
        
       /*
       TODO:
       Fazer teste de tempo para:
       leitura apenas dos filmes (escrita sequencial)
       leitura apenas dos usuarios(escrita sequencial)
       leitura apenas dos usuarios(escrita randomica com busca)
       leitura apenas dos usuarios com criacao de lista dos filmes(escrita randomica com busca)
       */

        Movie *movie = movieTree.search(Movie(movieId,""),[](Movie v1,Movie v2){
                return v1.ID == v2.ID;
        });
        if(movie){
            us->moviesWatched.push_back(*movie); //Copy
        }
        if(userNotFound){
            userTree.insert(*us); //Copy
            userNotFound = false;
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