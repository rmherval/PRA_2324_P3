#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../../pract1/PRA_2324_P1/ListLinked.h"  // ¡¡¡¡MODIFICAR!!!!
#include <ostream>
#include <iostream>
template <typename V>
class HashTable: public Dict<V> {

    private:
        int n; //nº elementos almacenados en la tabla hash
	int max; //tamaño de la tabla hash(nº tot de cubetas)
	ListLinked<TableEntry<V>>* table;

    
    int h(std::string key){
		int suma = 0;
		for(int i = 0; i< key.size(); i++){
			suma += key[i];
		}
		return suma%max;
	}

    public:
	HashTable(int size){
		 table = new ListLinked<TableEntry<V>>[size];
		 n = 0;
		 max = size;
	}

	~HashTable(){
		delete[] table;
	}

	int capacity(){
	return max;
	}
friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
	out<<"HashTable [entries: "<<th.n<<", capacity: "<<th.max<<"]"<<std::endl;
    for(int varmax = 0; varmax != th.max; varmax++) {
        out << "Cubeta " << varmax << std::endl;
        out << "List => [";

        // Itero sobre la lista enlazada en la posición varmax
        for (int i = 0; i < th.table[varmax].size(); ++i) {
            // Utilizo el método get de ListLinked para obtener el TableEntry
            TableEntry<V> entry = th.table[varmax].get(i);


            out << "('" << entry.key << "=>" << entry.value << "') ";

            // Agrego una coma y espacio si no es el último elemento
            if (i < th.table[varmax].size() - 1) {
                out << ", ";
            }
        }

        out << "]" << std::endl;
    }

    return out;
}
	V operator[](std::string key){
		int valor = search(key);
		return valor;
	}

	void insert(std::string key, V value) override {
		int pos = h(key);

			 if(table[pos].search(key) != -1) //ya está en el diccionario
				 throw std::runtime_error("la clave ya existe");



		TableEntry<V> new_entry(key, value);
		table[pos].prepend(new_entry);
		n++;
        }


		V search(std::string key) override{
			int buscado = h(key);
			TableEntry<V> new_entry(key);

			if(table[buscado].search(new_entry) != -1)
				return table[buscado].get(table[buscado].search(new_entry)).value;

        throw std::runtime_error("la clave no existe"); // Si no se encuentra

    }




V remove(std::string key) override {
    int buscado = h(key);
    TableEntry<V> new_entry(key);  // Creo un nuevo objeto TableEntry con la clave dada.

    // Verifico si la tabla en esa pos contiene la clave
    if (table[buscado].search(new_entry) != -1) {
        // Obtengo el índice de la clave en la lista enlazada
        int index = table[buscado].search(new_entry);

        // Obtengo el valor asociado a la clave en la posición 'index' de la lista
        V valueToRemove = table[buscado].get(index).value;

        // Elimino el elemento de la lista enlazada en la posición 'index'
        table[buscado].remove(index);


        n--;

        // Devuelvo el valor eliminado.
        return valueToRemove;
    }

    // Si la clave no se encuentra, lanzo una excepción
    throw std::runtime_error("la clave no existe");
}

		int entries() override{
			return n;
		}

        
};

#endif
