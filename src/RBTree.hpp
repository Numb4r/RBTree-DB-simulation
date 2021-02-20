#ifndef __RBTREE__
#define __RBTREE__
#include <iostream>
#include <functional>
/* 
Esse codigo foi baseado no livro do cormen 
Foram testados varios tipos de implemetacoes 
A menos complexa, e de melhor manutencao se baseia no fato que cada
folha e qualquer outro node que aponte para NULL(nullptr) na realidade
aponte para um ponto na memoria que seja do mesmo tipo do node,com cor preta
Alem disso, o unico algoritimo de remocao que funciona e baseado no livro do cormen,
que usa o Tnil

*/

enum color_t{BLACK,RED};
enum show_t{INORDER,PREORDER,POSORDER,PLOT};
template<typename T>
struct NODE
{
    T data;
    NODE<T>* parent = nullptr;
    NODE<T>* left = nullptr;
    NODE<T>* right = nullptr;
    color_t color = RED;
    NODE<T>()=default;
    NODE<T>(color_t color):color(color){}//Nodenil
    NODE<T>(color_t color,NODE<T>* parent):color(color),parent(parent){}
    NODE<T>(T data,NODE<T>* left=nullptr,NODE<T>* right=nullptr,NODE<T> *parent=nullptr):
    data(data),parent(parent),left(left),right(right){}
};



/* Class Definition */
template <typename T>
class RBTree
{   
    
    private:
        NODE<T> *root;

        NODE<T> *Tnil;

        NODE<T>* TreeMinimum(NODE<T>* node);
        NODE<T>* TreeMaximum(NODE<T>* node);
        void NDReplace(NODE<T>* x,NODE<T>* y);
        void PlotRecurse(NODE<T>* node,std::string separator,bool last);
        void RotateRight(NODE<T>* x);
        void RotateLeft(NODE<T>* x);
        void InsertRepairTree(NODE<T>* pNode);
        void DeleteRepairTree(NODE<T>* x);
        void fixDelete(NODE<T>* x);
        void preOrder(NODE<T>* n);
        void posOrder(NODE<T>* n);
        void inOrder(NODE<T>* n);
        void eraseTree(NODE<T>* n);
        void plot() noexcept;
        NODE<T>* searchNode(T data,std::function<bool(T v1,T v2)> foo) noexcept;
        void copyTreeHelper(RBTree<T> destTree,RBTree<T>  srcTree,NODE<T>* nodeCopying);
    public:
        // NODE* 
        void show(const show_t show = PLOT) noexcept;
        void insert(T data) noexcept;
        void erase(T data);
        
        T *search(const T &data,std::function<bool(T v1, T v2)> foo = nullptr);

        //Construtores
        RBTree<T>();
        RBTree<T>(std::initializer_list<T> list);
        RBTree<T>(RBTree<T> &obj) = delete;
        RBTree<T>(RBTree<T> &&obj);
        RBTree<T> operator=(RBTree<T> &obj) = delete;
        RBTree<T> &operator=(RBTree<T> &&obj);
        ~RBTree<T>();
};


#endif

