
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"

/** \brief Capturo del usuario un valor entero
 *
 * \param pResultado es la direccion de memoria donde almaceno el resultado
 * \param pMensaje es la consigna que recibe el usuario por pantalla
 * \param pMensajeError es el mensaje de error que recibe el usuario por pantalla
 * \param minimo es el valor minimo del rango aceptado
 * \param maximo es el valor maximo del rango aceptado
 * \param reintentos es la cantidad de veces que el usuario puede ingresar la informacion requerida
 * \return 0 si pudo conseguir el dato; -1 si hubo algun error
 *
 */
int getInt(	int *pResultado,
			char *pMensaje,
			char *pMensajeError,
			int minimo,
			int maximo,
			int reintentos)
{
        int retorno;
		int bBuffer;
		int i;
		int datoOk;
		char buffer[255];

	if(	pResultado != NULL &&
		pMensaje != NULL &&
		pMensajeError != NULL &&
		minimo < maximo &&
		reintentos > 0)
	{
		do
		{
			retorno = -1;
			datoOk = 1;
			i = 0;
			printf("%s",pMensaje);
			fflush(stdin);
			fgets(buffer,sizeof(buffer),stdin);
			buffer[strlen(buffer)-1]='\0';

			while(buffer[i] != '\0')
			{
				if(buffer[i] < '0' || buffer[i] > '9')
				{
					datoOk = 0;
				}
				i++;
			}
			if(datoOk)
			{
				bBuffer=atoi(buffer);
				if(bBuffer >= minimo && bBuffer <= maximo)
				{
					*pResultado = bBuffer;
					retorno = 0;
					break;
				}
			}
			printf("%s",pMensajeError);
			reintentos--;
		}while(reintentos >= 0);
	}
	return retorno;
}

/** \brief Capturo del usuario un valor de cadena de caracteres
 *
 * \param pResultado es la direccion de memoria donde almaceno el resultado
 * \param pMensaje es la consigna que recibe el usuario por pantalla
 * \param pMensajeError es el mensaje de error que recibe el usuario por pantalla
 * \param minimo es el valor minimo del rango aceptado
 * \param maximo es el valor maximo del rango aceptado
 * \param reintentos es la cantidad de veces que el usuario puede ingresar la informacion requerida
 * \return 0 si pudo conseguir el dato; -1 si hubo algun error
 *
 */
int getString(char *pResultado,
				char *pMensaje,
				char *pMensajeError,
				int minimo,
				int maximo,
				int reintentos)
{
	int retorno = -1;
	char buffer[255];

	if(		pResultado != NULL &&
			pMensaje != NULL &&
			pMensajeError != NULL &&
			minimo < maximo &&
			reintentos > 0)
	{
		do
		{
			printf("%s",pMensaje);
			fflush(stdin);
			fgets(buffer,sizeof(buffer),stdin);
			buffer[strlen(buffer)-1]='\0';
			if(strlen(buffer)<=maximo && strlen(buffer)>=minimo)
			{
				strncpy(pResultado,buffer,maximo+1);
				retorno = 0;
				break;
			}
			printf("%s",pMensajeError);
			reintentos--;
		}while(reintentos >= 0);
	}
	return retorno;
}

/** \brief Capturo del usuario un caracter
 *
 * \param resultado es la direccion de memoria donde almaceno el resultado
 * \param mensaje es la consigna que recibe el usuario por pantalla
 * \param mensajeError es el mensaje de error que recibe el usuario por pantalla
 * \param minimo es el valor minimo del rango aceptado
 * \param maximo es el valor maximo del rango aceptado
 * \param reintentos es la cantidad de veces que el usuario puede ingresar la informacion requerida
 * \return 0 si pudo conseguir el dato; -1 si hubo algun error
 *
 */
char getChar(char *resultado,
			char *mensaje,
			char *mensajeError,
			char minimo,
			char maximo,
			int reintentos)
{
	int retorno = -1;
	char buffer;
	if(	resultado != NULL &&
		mensaje	!= NULL &&
		mensajeError != NULL &&
		minimo < maximo &&
		reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			if(scanf("%c",&buffer)==1)
			{
				if(buffer == minimo || buffer == maximo)
				{
					retorno = 0;
					*resultado = buffer;
					break;
				}
			}
			printf("%s",mensajeError);
			reintentos--;
		}while(reintentos >= 0);
	}
	return retorno;
}

/** \brief Imprimie el menu en pantalla
 *
 * \param void
 * \return o si fue exitosa, -1 si hubo algun error
 *
 */
int funcionMenu(void)
{
        int retorno;
	    int opcion;
        int listaEmpleadosVacia;
        int ll_creada;
        int cargaBin;
        int sortedList;
        char eliminarLista;
        char salir;
        int from = -1;
        int to = -1 ;
        int auxIndexSubLista = -1;
        char rtaDeleteSubLista = 'n';

        Employee* auxEmployeeSubList = NULL;
	    retorno = -1;
		ll_creada = 0;
        cargaBin = 0;
   		LinkedList* listaEmpleados = ll_newLinkedList();
   		LinkedList* listaEmpleadosBackup = NULL;
   		ll_creada = 1;
   		sortedList = 0;
   		listaEmpleadosVacia = ll_isEmpty(listaEmpleados);
   		eliminarLista = 'n';
   		salir = 'n';

	    do{
			if(getInt(&opcion,"\n\nSeleccione la opcion deseada:\n\t  1- Cargar los datos de los empleados(modo txt)\n\t  2- Cargar los datos de los empleados(modo binario)\n\t  3- Alta Empleado\n\t  4- Modificar Empleado\n\t  5- Baja Empleado\n\t  6- Listar Empleados\n\t  7- Ordenar Empleados\n\t  8- Guardar los datos (modo txt)\n\t  9- Guardar los datos (modo binario) \n\t 10 - Eliminar lista de empleados\n\t 11 - Buscar e Insertar un nuevo Empleado \n\t 12 - Buscar por nombre y borrar empleado \n\t 13 - Backup Lista Empleados \n\t 14 - Validar integridad del backup \n\t 15 - Extraer una lista de Empleados(Borrado o Copia) \n\t 16 - Salir\n","Ha ingresado una opcion invalida, reintente.",1,16,2)==0)
	        {
				switch(opcion)
	            {
	                case 1:
	                	if(controller_loadFromText("data.csv",listaEmpleados))
	                	{
	                		listaEmpleadosVacia = ll_isEmpty(listaEmpleados);
	                		printf("\n\t\tDatos Cargados correctamente.\n\n");
	                	}
                        break;
	                case 2:
	                    if(cargaBin == 1)
                        {
                            if(controller_loadFromBinary("data.bin",listaEmpleados))
                            {
                                listaEmpleadosVacia = ll_isEmpty(listaEmpleados);
                                printf("\n\t\tDatos Cargados correctamente.\n\n");
                                break;
                            }
                        }
                        printf("No hay datos de tipo binario para cargar.\n");
	                    break;
	                case 3:
	                	controller_addEmployee(listaEmpleados);
	                	if(listaEmpleadosVacia)
	                	{
	                	    listaEmpleadosVacia = ll_isEmpty(listaEmpleados);
	                	}
	                	break;
	                case 4:
	                	if(ll_isEmpty(listaEmpleados))
                        {
                            printf("No hay Empleados para ser modificados.\n");
                            break;
                        }
	                	controller_editEmployee(listaEmpleados);
	                    break;
	                case 5:
	                    if(ll_isEmpty(listaEmpleados))
                        {
                            printf("No hay Empleados para dar de baja.\n");
                            break;
                        }
	                    controller_removeEmployee(listaEmpleados);
	                	break;
	                case 6:
	                	if(ll_isEmpty(listaEmpleados))
	                	{
	                		printf("\t\tNo se pueden listar empleados porque no hay datos que mostrar.\n\n");
	                		break;
	                	}
	                	controller_ListEmployee(listaEmpleados);
	                    break;
	                case 7:
	                	if(ll_isEmpty(listaEmpleados))
	                	{
	                		printf("\t\tNo se pueden listar empleados porque no hay datos que mostrar.\n\n");
	                		break;
	                	}
	                	controller_sortEmployee(listaEmpleados);
	                	sortedList = 1;
	                    break;
	                case 8:
	                	if(listaEmpleadosVacia && !ll_creada)
                        {
                            printf("No hay informacion para exportar a un archivo.\n\n");
                            break;
                        }
                        controller_saveAsText("data.csv", listaEmpleados);
	                	printf("\t\tDatos almacenados en modo Texto correctamente.\n");
	                    break;
	                case 9:
	                	if(controller_saveAsBinary("data.bin",listaEmpleados))
                        {
                            printf("\t\tDatos almacenados en modo Binario correctamente.\n");
                            cargaBin = 1;
                        }
	                	break;
                    case 10:
                        if(ll_isEmpty(listaEmpleados))
                        {
                            printf("\t\tNo hay una lista de Empleados para borrar; no hay datos ingresados.\n");
                            break;
                        }
                        getChar(&eliminarLista,"\nDesea eliminar por completo la lista de empleados cargada?(s/n)\n","Ha ingresado una opcion invalida, reintente.\n",'n','s',3);
                        if(eliminarLista == 's' && ll_clear(listaEmpleados)==0)
                        {
                            listaEmpleadosVacia = 0;
                            sortedList = 0;
                            printf("\n\t\tSe ha eliminado la lista de empleados.\n");
                        }
                        break;
                    case 11:
                        if(ll_isEmpty(listaEmpleados))
                        {
                            printf("\t\tNo hay una lista de Empleados cargada; no se puede procesar.\n");
                            break;
                        }
                        else if(sortedList != 1)
                        {
                            printf("\t\tLa lista no se encuentra ordenada; no se puede procesar.\n");
                            break;
                        }
                        findPushEmployeeByName(listaEmpleados);
                        break;
                    case 12:
                        if(listaEmpleadosVacia == 0 && sortedList == 1)
                        {
                            findDeleteEmployeeByName(listaEmpleados);
                            break;
                        }
                        else
                        {
                            printf("\n\t\tNo se puede buscar por nombre ya que la lista esta vacia o no se encuentra ordenada.\n");
                            break;
                        }
                    case 13:
                        if(!ll_isEmpty(listaEmpleados))
                        {
                            listaEmpleadosBackup = ll_clone(listaEmpleados);
                            if(listaEmpleadosBackup != NULL)
                            {
                                controller_saveAsText("backup.csv", listaEmpleadosBackup);
                                controller_saveAsBinary("backup.bin",listaEmpleadosBackup);
                                printf("\t\tCopia de seguridad generada exitosamente.\n");
                                break;
                            }
                        }
                        else
                        {
                            printf("\t\tNo se puede generar una copia ya que la lista de empleados se encuentra vacia o se produjo un error.\n");
                            break;
                        }
                    case 14:
                        if(ll_isEmpty(listaEmpleadosBackup))
                        {
                            printf("\t\t\nNo hay un backup creado, por favor resguarde la información\n");
                            break;
                        }
                        else
                        {
                            if(ll_containsAll(listaEmpleados, listaEmpleadosBackup))
                            {
                                printf("\t\tLa copia de seguridad es integra.\n");
                            }
                            else
                            {
                                ll_clear(listaEmpleadosBackup);
                                printf("La copia de seguridad no contiene todos los elementos; por favor genere una nueva.\n");
                            }
                            break;
                        }
                    case 15:
                        if(!ll_isEmpty(listaEmpleados) && sortedList == 0)
                        {
                            getInt(&from,"Ingrese desde que Nro de ID desea seleccionar empleados\n","Ha ingresado un valor invalido. Reintente\n",0,ll_len(listaEmpleados),3);
                            getInt(&to,"Ingrese hasta que Nro de ID desea seleccionar empleados\n","Ha ingresado un valor invalido. Reintente\n",from,ll_len(listaEmpleados),3);
                            if(from != -1 && to != -1)
                            {
                                for(int i = 0;i<ll_len(listaEmpleados);i++)
                                {
                                    auxEmployeeSubList=ll_get(listaEmpleados,i);
                                    if(from == auxEmployeeSubList->id)
                                    {
                                        from = i;
                                    }
                                    if(to == auxEmployeeSubList->id)
                                    {
                                        to = i;
                                        break;
                                    }
                                }
                                LinkedList* subLista = ll_subList(listaEmpleados,from,to);
                                if(subLista != NULL)
                                {
                                    printf("Se ha generado la nueva lista solicitada.\n\n Los empleados seleccionados fueron: \n");
                                    controller_ListEmployee(subLista);
                                    getChar(&rtaDeleteSubLista,"\nDesea eliminar todos los empleados seleccionados del listado original?(S/N)\n","Ha ingresado una rta invalida. Reintente\n",'N','S',3);
                                    if(rtaDeleteSubLista != 'N')
                                    {
                                        for(int i = 0;i<ll_len(subLista);i++)
                                        {
                                            auxEmployeeSubList = ll_get(subLista,i);
                                            auxIndexSubLista = ll_indexOf(listaEmpleados,auxEmployeeSubList);
                                            ll_pop(listaEmpleados,auxIndexSubLista);
                                        }
                                        printf("\nSe eliminaron exitosamente los empleados seleccionados.\n");
                                        break;
                                    }
                                    else
                                    {
                                        getChar(&rtaDeleteSubLista,"Desea exportar los empleados seleccionados a un nuevo archivo de texto?(S/N)\n","Ha ingresado una rta invalida. Reintente.\n",'N','S',3);
                                        if(rtaDeleteSubLista != 'N')
                                        {
                                            if(controller_saveAsText("subLista.csv", subLista)==0)
                                            {
                                                printf("\nSe almaceno una copia de los empleados seleccionados\n");
                                                break;
                                            }
                                            else
                                            {
                                                printf("No se pudo guardar la copia solicitada. Reintente nuevamente\n");
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            break;
                                        }
                                    }
                                }
                                else
                                {
                                    printf("\nNo se puede generar una sublista. Reintente.\n");
                                    break;
                                }
                            }
                            else
                            {
                                printf("\nNo se puede generar una seleccion. Reintente.\n");
                                break;
                            }
                        }
                        else
                        {
                            printf("\nNo se puede generar una seleccion ya que no hay empleados cargados o la lista se encuentra ordenada por algun criterio.\n");
                            break;
                        }
                    case 16:
                        getChar(&salir,"\nDesea salir? (s/n)\n", "\nHa seleccionado una opcion invalida. Reintente.\n",'n','s',3);
                        if(salir == 's')
                        {
                            ll_deleteLinkedList(listaEmpleados);
                            retorno = 0;
                            break;
                        }
	                }
	        }
	    }while(salir != 's');
	    return retorno;
}

/** \brief Valida si lo ingresa es un caracter valido
 *
 * \param buffer es la direccion de memoria donde se almaceno el caracter ingresado a validar
 * \return 0 si la validacion fue exitosa; -1 si hubo algun error
 *
 */
int esSoloChar(char *buffer){
    int i;
    int retorno;
    int datoOk;
    retorno = -1;

    if(buffer != NULL)
    {
        i = 0;
        datoOk = 1;
        while(buffer[i] != '\0')
        {
            if((buffer[i] != ' ') && (buffer[i] < 'a' || buffer[i] > 'z') && (buffer[i] < 'A' || buffer[i] > 'Z'))
            {
                datoOk = 0;
            }
            i++;
        }
        if(datoOk)
        {
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Valida si lo ingresa es una cadena alfanumerica
 *
 * \param buffer es la direccion de memoria donde se almaceno el valor ingresado a validar
 * \return 0 si la validacion fue exitosa; -1 si hubo algun error
 *
 */
int esAlfaNumerico (char *buffer){
    int i;
    int retorno;
    int datoOk;

    if(buffer != NULL)
    {
        i = 0;
        retorno = -1;
        datoOk = 1;
        while(buffer[i] != '\0')
        {
            if((buffer[i] != ' ') && (buffer[i] != '-') && (buffer[i] < 'a' || buffer[i] > 'z') && (buffer[i] < 'A' || buffer[i] > 'Z') && (buffer[i] < '0' || buffer[i] > '9'))
            {
                datoOk = 0;
            }
            i++;
        }
        if(datoOk)
        {
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Valida si lo ingresado es un numero valido
 *
 * \param buffer es la direccion de memoria donde se almaceno el valor ingresado a validar
 * \return 0 si la validacion fue exitosa; -1 si hubo algun error
 *
 */
int esNumerico(char *buffer)
{
    int i;
    int retorno;
    int datoOk;

    if(buffer != NULL)
    {
        i = 0;
        retorno = -1;
        datoOk = 1;
        while(buffer[i] != '\0')
        {
            if(buffer[i] < '0' || buffer[i] > '9')
            {
                datoOk = 0;
            }
            i++;
        }
        if(datoOk)
        {
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Valida si lo ingresa es un caracter o un espacio
 *
 * \param buffer es la direccion de memoria donde se almaceno el valor ingresado a validar
 * \return 0 si la validacion fue exitosa; -1 si hubo algun error
 *
 */
int isCharOrSpace(char buffer[])
{
    int retorno = -1;
    int errorCarga;

    for(int i=0;i<strlen(buffer);i++)
    {
        if((buffer[i]>='A' && buffer[i]<='Z') || (buffer[i]>='a' && buffer[i]<='z') || buffer[i]==' ' || buffer[i]=='\0')
        {
            errorCarga = 0;
        }
        else
        {
            errorCarga = -1;
            break;
        }
    }
    if(errorCarga == 0)
    {
        retorno = 0;
    }
    return retorno;
}

/** \brief Capturo del usuario un caracter dentro de un rango de caracteres
 *
 * \param resultado es la direccion de memoria donde almaceno el resultado
 * \param mensaje es la consigna que recibe el usuario por pantalla
 * \param mensajeError es el mensaje de error que recibe el usuario por pantalla
 * \param minimo es el valor minimo del rango aceptado
 * \param maximo es el valor maximo del rango aceptado
 * \param reintentos es la cantidad de veces que el usuario puede ingresar la informacion requerida
 * \return 0 si pudo conseguir el dato; -1 si hubo algun error
 *
 */
char getCharVarios(char *resultado,
			char *mensaje,
			char *mensajeError,
			char minimo,
			char maximo,
			int reintentos)
{
	int retorno = -1;
	char buffer;
	if(	resultado != NULL &&
		mensaje	!= NULL &&
		mensajeError != NULL &&
		minimo < maximo &&
		reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			if(scanf("%c",&buffer)==1)
			{
				if(buffer >= minimo && buffer <= maximo)
				{
					retorno = 0;
					*resultado = buffer;
					break;
				}
			}
			printf("%s",mensajeError);
			reintentos--;
		}while(reintentos >= 0);
	}
	return retorno;
}
