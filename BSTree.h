#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
    private:
        int nelem; //nº elem almacenados en los ABB
        BSNode<T> *root;//nodo raíz
    public:
        BSTree(){
             root = nullptr;
             nelem = 0;
        }
        int size() const{
            return nelem;
        }
        T search(T e) const{
            BSNode<T>* result = search(root, e);
            return result->elem;
        }

        T operator[](T e) const{
            return search(e);
        }

        void insert(T e){
            root = insert(root, e);
            nelem++;

        }

        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
            bst.print_inorder(out, bst.root);
            return out;

        }
        void remove(T e){
            remove(root, e);
            nelem--;

        }
        ~BSTree(){
            delete_cascade(root);
        }


private:
    BSNode<T>* search(BSNode<T>* n, T e) const{
        if(n == nullptr) throw std::runtime_error("vacío");
        if(n->elem == e) return n;
	       if(n->elem > e){ //si es más pequeño a la izquierda
	           return search(n->left, e);
	        }
           else{
	           return search(n->right, e);
	        }

    }


    BSNode<T>* insert(BSNode<T>* n, T e){
        if( n == nullptr)
            n = new BSNode<T>(e);
        else if(n->elem == e)
            throw std::runtime_error("ya existe");
        else if(n->elem < e)
            n->right = insert(n->right,e);
        else
            n->left = insert(n->left, e);
        return n;

    }

    	void print_inorder(std::ostream &out, BSNode<T>* n) const{
    if (n != nullptr) {
        print_inorder(out, n->left);
        out << n->elem << " ";
        print_inorder(out, n->right);
    }
}

    BSNode<T>* remove(BSNode<T>* n, T e){
        if(n == nullptr)
            throw std::runtime_error("no encontrado");
        else if(n->elem <e )
            n->right = remove(n->right, e);
        else if(n->elem > e)
            n->left = remove(n->left, e);
        else{
            if((n->left !=nullptr) && (n->right != nullptr)){
                n->elem = max(n->left);//busco el máximmo en el sub-árbol izquierdo
                n->left= remove_max(n->left);//eliminamos el máximo nodo del sub-árbol izquierdo y lo igualamos a sí mismo pero actualizado con el borrado
            }
            else
                n = (n->left != nullptr) ? n->left : n->right;
        }
        return n;
    }




    T max(BSNode<T>* n) const{//busca el elem max del sub-árbol que me pasan (en este caso el izquierdo)
        if(n == nullptr) throw std::runtime_error("no encontrado");
        else if(n->right != nullptr)
            return max(n->right);
        else
            return n->elem;
    }

    BSNode<T>* remove_max(BSNode<T>* n){//busca y elimina el nodo máximo
        if(n->right == nullptr)
            return n->left;
        else
            n->right = remove_max(n->right);
        return n;
    }
    void delete_cascade(BSNode<T>* n) {
    if (n != nullptr) {
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }
}

};
#endif
