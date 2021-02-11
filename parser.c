#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int encabezado;
	char id[255];
	char nombre[255];
	char horasTrabajadas[255];
	char sueldo[255];
	Employee* aEmployee;

	encabezado = 0;
	while(!feof(pFile))
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horasTrabajadas,sueldo);
		if(encabezado != 0)
		{
			aEmployee = employee_newParametros(id, nombre, horasTrabajadas, sueldo);
			ll_add(pArrayListEmployee, aEmployee);
		}
		encabezado++;
	}
    return 1;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
    Employee* aEmployee;
    int retorno = -1;

    if(pFile != NULL)
    {
        while(!feof(pFile))
        {
            aEmployee = employee_new();
            fread(aEmployee,sizeof(Employee),1,pFile);
            ll_add(pArrayListEmployee,aEmployee);
        }
        retorno = 0;
    }
    return retorno;
}
