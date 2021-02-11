#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;
    this = malloc(sizeof(LinkedList));
    this->size = 0;
    this->pFirstNode = NULL;
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* pNodo = NULL;
	int i;
	if(this != NULL && nodeIndex >=0 && nodeIndex < this->size)
	{
		pNodo = this->pFirstNode;
		for(i=0;i<nodeIndex;i++)
		{
			pNodo = pNodo->pNextNode;
		}
	}
    return pNodo;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* pNodo;
    Node* pNodoAnterior;
    if(this != NULL && nodeIndex >=0 && nodeIndex <= this->size)
    	{
    		pNodo = malloc(sizeof(pNodo));
    		this->size++;
    		pNodo->pElement = pElement;
    		returnAux = 0;
    		if(pNodo == NULL)
    		{
    			return returnAux;
    		}
    		if(nodeIndex == 0)
    		{
    			pNodo->pNextNode = this->pFirstNode;
    			this->pFirstNode = pNodo;

    		}
    		else
    		{
    			pNodoAnterior = getNode(this,nodeIndex-1);
    			pNodo->pNextNode = pNodoAnterior->pNextNode;
    			pNodoAnterior->pNextNode = pNodo;
    		}
    	}
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
	int returnAux = -1;
	int index;
	int newNode = -1;

	if(this != NULL)
    {
		index = this->size;
		newNode=addNode(this,index,pElement);
		if(newNode == 0 && this->size>index)
		{
			returnAux = 0;
		}

	}
	return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* thisNode;
    int size;
    size = ll_len(this);

    if(this != NULL && index >=0 && index < size)
    {
    	thisNode = getNode(this,index);
    	returnAux = thisNode->pElement;
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
	int returnAux = -1;
	Node* thisNode;
	int size;
	size = ll_len(this);

	if(this != NULL && index >=0 && index < size)
	{
		thisNode = getNode(this,index);
		thisNode->pElement=pElement;
		returnAux = 0;
	}
	return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
	int returnAux = -1;
	int size;
	Node* removeThis;
	Node* nextNode;
    Node* previousNode;

	if(this != NULL && index >= 0 && index < this->size)
    {
        size = ll_len(this);
        removeThis = getNode(this, index);
        if(size == 1)
        {
            free(removeThis->pElement);
            free(removeThis);
            this->pFirstNode = NULL;
        }
        else if(index == 0 && size >1)
        {
            nextNode = getNode(this,index+1);
            this->pFirstNode = nextNode;
            free(removeThis->pElement);
            free(removeThis);
        }
        else
        {
            if(removeThis != NULL)
            {
                previousNode = getNode(this, index-1);
                nextNode = getNode(this, index+1);
                previousNode->pNextNode = nextNode;
                free(removeThis->pElement);
                free(removeThis);
            }

        }
    this->size--;
    returnAux = 0;
    }

	return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int size;
    int i;
    Node* LastNode;

    if(this != NULL)
    {
    	size= this->size;
    	for(i=size;i>0;i--)
    	{
    		LastNode = getNode(this,i);
    		free(LastNode);
    	}
    	this->pFirstNode=NULL;
    	this->size = 0;
    	returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
   int returnAux = -1;

   if(this != NULL)
   {
        free(this);
        returnAux = 0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int size;
    int i;
    Node* pNode;

    if(this != NULL)
    {
    	size = this->size;
    	for(i=0;i<size;i++)
    	{
    		pNode = getNode(this,i);
    		if(pElement == pNode->pElement)
    		{
    			returnAux = i;
    			break;
    		}
    	}
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	if(this->size == 0)
    	{
    		returnAux = 1;
    	}
    	else
        {
            returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this != NULL && index >=0 && index <= this->size)
    {
        if(addNode(this,index,pElement)==0)
        {
            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;

    if(this != NULL && index >= 0 && index < this->size)
    {
    	returnAux = ll_get(this,index);
    	if(ll_remove(this,index)==-1)
        {
            returnAux = NULL;
        }
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    int size;
    Node* compareNode;

    if(this != NULL)
    {
    	size=this->size;
    	returnAux = 0;
    	for(i=0;i<size;i++)
    	{
    		compareNode = ll_get(this,i);
    		if(compareNode == pElement)
    		{
    			returnAux = 1;
    			break;
    		}
    	}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int size;
    void* aEmployee;

    if(this != NULL && this2 != NULL)
    {
    	returnAux = 1;
    	size = ll_len(this2);
    	for(int i = 0; i < size;i++)
        {
            aEmployee = ll_get(this2,i);
            if(!ll_contains(this,aEmployee))
            {
                returnAux = 0;
                break;
            }
        }
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    void* auxElement;

    if(!(this == NULL || from < 0 || from > ll_len(this) || to <= from || to > ll_len(this)))
    {
        cloneArray = ll_newLinkedList();
        if(cloneArray != NULL)
        {
            for(int i = from; i<to; i++)
            {
                auxElement = ll_get(this,i);
                ll_add(cloneArray,auxElement);
            }
        }
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    int i;
    int elementoClonado;
    LinkedList* cloneArray = NULL;
    Node* pClone;

    if(this != NULL)
    {
        cloneArray = ll_newLinkedList();
        for(i=0;i<this->size;i++)
        {
            pClone = getNode(this,i);

            addNode(cloneArray,i,pClone->pElement);
            elementoClonado++;
        }
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
	int i;
	int size;
	int sFlag;
	int returnAux= -1;
	void* pElementA;
	void* pElementB;
	void* pElementAux;

	if(this != NULL && pFunc != NULL)
	{
		if(order == 0 || order == 1)
		{
		 size = ll_len(this);
		 if(size > 0)
		 {
			 do
			 {
				 sFlag= 0;
				 for(i=0; i<size-1; i++)
				 {
					 pElementA = ll_get(this,i);
					 pElementB = ll_get(this,i+1);
					 if((pFunc(pElementA, pElementB) <0 && order==0) || (pFunc(pElementA, pElementB) >0 && order==1))
					 {
						 pElementAux= pElementA;
						 ll_set(this,i,pElementB);
						 ll_set(this,i+1,pElementAux);
						 sFlag= 1;
					 }
					 returnAux= 0;
				 }
			 }while(sFlag);
		 }
		}
	}
	return returnAux;
}


/** \brief Filtra la LinkedList y los elementos que estan incluidos en el filtro los copia en otra LinkedList
 *
 * \param this recibe la direccion de memoria de la LinkedList original
 * \param
 * \return Devuelve un nuevo LinkedList
 *
 */
 /*
LinkedList* ll_filter(LinkedList* this,int(*pFunc)(void))
{
    LinkedList* filteredList = NULL;
    void* auxElement = NULL;

    if(this != NULL && pFunc!=NULL)
    {
        filteredList = ll_newLinkedList();
        if(filteredList!=NULL)
        {
            for(int i =0; i < ll_len(this);i++)
            {
                auxElement = ll_get(this,i);
                if(pFunc(auxElement))
                {
                    ll_add(filteredList,auxElement);
                }
            }
        }
    }
    return filteredList;
}
*/
/** \brief Filtra los empleados con un sueldo entre 5000 y 20000
 *
 * \param aEmployee recibe la direccion de memoria de un empleado
 * \return devuelve 1 si fue exitoso 0 si hubo algun error.
 *
 */
 /*
int filterEmployeeBySalary(void* aEmployee)
{
    Employee* auxEmployee = NULL;
    int retorno = 0;
    if(aEmployee != NULL)
    {
        auxEmployee = aEmployee;
        if(aEmployee->sueldo >= 5000 && aEmployee->sueldo <= 20000)
        {
            retorno = 1;
        }
    }
    return retorno;
}
*/

//Desarrollar
//MAP
//FILTER me quedo con un set de datos de la primera lista
//REDUCE (achicar la lista segun una funcion criterio pero siempre quedando la lista original como resultado)
