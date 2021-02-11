#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED

/*typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;*/

typedef struct
{
    int id;
    int anioNacimiento;
    char nombre[50];
    char dni[8];
    //eFecha fechaPresentacion;
    char fechaPresentacion[10];
    char temaPresentacion[30];
    int puntajePrimeraRonda;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldo);
void employee_delete();

int employee_setId(Employee* this,char* id);
int employee_getId(Employee* this,int *id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,char* horasTrabajadasStr);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,char* sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int isValidNombre(Employee* this, char* nombreStr);
int isValidId(Employee* this, char* id);
int isValidHsTrabajadas(Employee* this, char* horasTrabajadasStr);
int isValidSueldo(Employee* this, char* sueldo);

int getIdStr(char *pResultado,char *pMensaje,char *pMensajeError,int minimo,int maximo,int reintentos);
int getNombreStr(char *pResultado,char *pMensaje,char *pMensajeError,int minimo,int maximo,int reintentos);
int getHsTrabajadasStr(char *pResultado,char *pMensaje,char *pMensajeError,int minimo,int maximo,int reintentos);
int getSueldoStr(char *pResultado,char *pMensaje,char *pMensajeError,int minimo,int maximo,int reintentos);

int employee_sortByName(void* dato1,void* dato2);
int findPushEmployeeByName(LinkedList* this);
int controller_pushEmployee(LinkedList* pArrayListEmployee,int auxId, Employee* replaceEmployee);
int findDeleteEmployeeByName(LinkedList* this);
int employee_setDni(Employee* this,char* dni);

int employee_setAnio(Employee* this,char* anio);

int employee_setFechaPresentacion(Employee* this,char* fechaPresentacion);

int employee_setTemaPresentacion(Employee* this,char* temaPresentacion);

int employee_setPuntaje(Employee* this,char* puntajePrimeraRonda);

int employee_getInt(Employee* this,int *number);
int employee_setInt(Employee* this,char* number);

int employee_getStr(Employee* this,char* cadena);
int employee_setStr(Employee* this,char* cadena);

int employee_getDni(Employee* this,char* dni);
int employee_getAnio(Employee* this,int *anio);
int employee_getFechaPresentacion(Employee* this,char* fecha);
int employee_getTemaPresentacion(Employee* this,char* tema);
int employee_getPuntajePrimeraRonda(Employee* this,int *number);


#endif // EMPLOYEE_H_INCLUDED
