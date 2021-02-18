#pragma once
#include "RBTree.hpp"

/*                                                      Funcoes Print                                                      */
template <typename T>
void RBTree<T>::inOrder(NODE<T>* n){
    if (n == Tnil) return;
    inOrder(n->left);
    std::cout<<n->data<<" ";
    inOrder(n->right);
    
}
template <typename T>

void RBTree<T>::preOrder(NODE<T>* n){
    if (n == Tnil) return;
    std::cout<<n->data<<" ";
    preOrder(n->left);
    preOrder(n->right);
}

template <typename T>
void RBTree<T>::posOrder(NODE<T>* n){
    if (n == Tnil) return;
    posOrder(n->left);
    posOrder(n->right);
    std::cout<<n->data<<" ";
}
template <typename T>
void RBTree<T>::PlotRecurse(NODE<T>* node,std::string separator,bool last)  {
    if(node != Tnil){
        std::cout<< separator;
        if(last){
            std::cout<<"R----";
            separator+="     ";
        }else{
            std::cout<<"L----";
            separator+="|    ";
        }
        std::cout
            <<node->data
            <<"("<<(node->color ? "RED" : "BLACK") <<")"<<std::endl;

        PlotRecurse(node->left,separator,false);
        PlotRecurse(node->right,separator,true);
    }
}
template <typename T>
void RBTree<T>::plot() noexcept{
    PlotRecurse(root,"",false);
}

template <typename T>
NODE<T>* RBTree<T>::search(T data)const noexcept{
    NODE<T> *pNode = root;
    while (pNode != Tnil && pNode->data != data)
        if(data > pNode->data) pNode = pNode->right;
        else pNode = pNode->left;
    return pNode;
    
}
template <typename T>
void RBTree<T>::show(const show_t show)  noexcept{
    switch (show)
    {
    case INORDER:
        inOrder(root);
        break;
    case POSORDER:
        posOrder(root);
        break;
    case PREORDER:
        preOrder(root);
        break;
    case PLOT:
    default:
        plot();
        break;
    }
}
/*                                                      Funcoes Print                                                      */
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*                                                      Funcoes Auxiliares                                                  */
template <typename T>
void RBTree<T>::NDReplace(NODE<T>* x,NODE<T>* y){
    if (x->parent == Tnil )
        this->root = y;
    else if(x==x->parent->left)  
        x->parent->left = y;
    else
        x->parent->right = y;
    y->parent = x->parent;
}


template <typename T>
NODE<T>* RBTree<T>::TreeMinimum(NODE<T>* node){
    while (node->left != Tnil)
        node = node->left;
    return node;
    
}
template <typename T>
NODE<T>* RBTree<T>::TreeMaximum(NODE<T>* node){
    while (node->right != Tnil)
        node = node->right;
    return node;
}
template <typename T>
void RBTree<T>::RotateLeft(NODE<T>* x){ 
    NODE<T>* y = x->right;
    x->right = y->left;
    if (y->left != Tnil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == Tnil) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    
    
}
template <typename T>
void RBTree<T>::RotateRight(NODE<T>* x){
    NODE<T>* y = x->left;
    x->left = y->right;
    if (y->right != Tnil) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == Tnil) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}
/*                                                      Funcoes Auxiliares                                                  */
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*                                                      Funcoes Insersao                                                  */
template <typename T>
void RBTree<T>::InsertRepairTree(NODE<T>* pNode){
    NODE<T>* pAux;
    while (pNode->parent->color == RED)
    {
        if(pNode->parent == pNode->parent->parent->right){//right
            pAux = pNode->parent->parent->left; // uncle
            if(pAux->color == RED){//case 1
                pAux->color = BLACK;
                pNode->parent->color = BLACK;
                pNode->parent->parent->color=RED;
                pNode = pNode->parent->parent;
            }else{
                if(pNode==pNode->parent->left){//case 2
                    pNode = pNode->parent;
                    RotateRight(pNode);
                }
                //case 3
                pNode->parent->color = BLACK;
                pNode->parent->parent->color = RED;
                RotateLeft(pNode->parent->parent);
            }
        }else{//left
            pAux = pNode->parent->parent->right;
            if(pAux->color == RED){
                pAux->color = BLACK;
                pNode->parent->color = BLACK;
                pNode->parent->parent->color = RED;
                pNode = pNode->parent->parent;
            }else{
                if(pNode ==  pNode->parent->right){
                    pNode = pNode->parent;
                    RotateLeft(pNode);
                }
                pNode->parent->color = BLACK;
                pNode->parent->parent->color = RED;
                RotateRight(pNode->parent->parent);

            }

        }
        
    }
    root->color = BLACK; 
}

template <typename T>
void RBTree<T>::insert(T data) noexcept{
    NODE<T>* pNode = new NODE<T>(data,Tnil,Tnil);// left = right = Null 
    NODE<T>* pParent = Tnil;
    NODE<T>* pSentinel = root;
    
    while (pSentinel != Tnil)
    {
        pParent = pSentinel; // Ao final do loop pParent sera o parente de pNode
        if(pNode->data  > pSentinel->data)
            pSentinel = pSentinel->right;
        else 
            pSentinel = pSentinel->left;
    }
    pNode->parent= pParent;
    if (pParent == Tnil )
    {
        /*Caso seja o primeiro item,sera preto e nao precisara fazer nada*/
        root = pNode;
    }else{
        if(pNode->data > pParent->data)
            pParent->right = pNode;
        else 
            pParent->left = pNode;
    }
    
    InsertRepairTree(pNode);
}
/*                                                      Funcoes Insersao                                                  */
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*                                                      Funcoes Remocao                                                   */
template <typename T>
void RBTree<T>::DeleteRepairTree(NODE<T>* x){
    NODE<T>* w;
    while (x != root && x->color == BLACK) 
    {
        if(x == x->parent->left){ // left
            w = x->parent->right;
            if (w->color==RED)//Case 1
            {
                w->color = BLACK;
                x->parent->color = RED;
                RotateLeft(x->parent);
                w = x->parent->right;
            }
            if(w->left->color == BLACK && w->right->color == BLACK){//case 2
                w->color = RED;
                x = x->parent;
            }else{
                if (w->right->color == BLACK)//case 3
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    RotateRight(w);
                    w = x->parent->right;
                }
                //case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK; 
                RotateLeft(x->parent);
                x = root;
            }
            
        }else{//right
            w = x->parent->left;
            if(w->color == RED){ // case 1
                w->color = BLACK;
                x->parent->color = RED;
                RotateRight(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)//case 2
            {
                w->color = RED;
                x = x->parent;
            }else{
                if(w->left->color == BLACK){//case 3
                    w->right->color = BLACK;
                    w->color = RED;
                    RotateLeft(w);
                    w = x->parent->left;
                }
                //case 4
                x->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RotateRight(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK; 
    
}
template <typename T>
void RBTree<T>::eraseTree(NODE<T>* n){
    if (n == Tnil) return;
    eraseTree(n->left);
    eraseTree(n->right);
    delete n;
    n = nullptr;

}
template <typename T>
void RBTree<T>::erase(T data) {
    NODE<T>* z = this->search(data);
    if(z == Tnil || z->data != data) {
        throw "Couldn`t find data in the tree";
        return;
    }
    NODE<T>* y = z;
    NODE<T>* x;
    color_t y_original_color = y->color;
    //Confere se possui algum filho null
    if(z->left == Tnil){
        x = z->right;
        NDReplace(z,z->right);
        if(z == root) root = x;
    }else if(z->right == Tnil){
        x=z->left;
        NDReplace(z,z->left);
        if(z == root) root = x;
    }else{//Possui 2 filhos
        y = TreeMinimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if(y->parent == z){
            x->parent = y;
        }else{
            NDReplace(y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        NDReplace(z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
        if(z == root) root = y;
    }
    delete z;
    z = nullptr;
    
    if(y_original_color == BLACK)
        DeleteRepairTree(x);
}

/*                                                      Funcoes Remocao                                                   */
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
template <typename T>
void RBTree<T>::copyTreeHelper(RBTree<T> srcTree,NODE<T>* nodeCopying){

}
template <typename T>
RBTree<T>::RBTree(){
    Tnil  = new NODE<T>(BLACK);
    root = Tnil;
}
template <typename T>
RBTree<T>::RBTree(RBTree<T> &&obj){
    root = obj.root;
    Tnil = obj.Tnil;
    obj.Tnil = new NODE<T>(BLACK);
}
template <typename T>
RBTree<T> RBTree<T>::operator=(RBTree<T> &&obj){
    RBTree<T> tree;
    tree.root = obj.root;
    tree.Tnil = obj.Tnil;
    obj.Tnil = new NODE<T>(BLACK);
    return tree;
}
template <typename T>
RBTree<T>::~RBTree(){
    eraseTree(root);
    delete Tnil;
    Tnil = nullptr;
}
template <typename T>
RBTree<T>::RBTree(std::initializer_list<T> list):RBTree<T>(){
    for (auto &&i : list)
        this->insert(i);
}