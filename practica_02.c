#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
//nota importante 


int main(int argc, char const *argv[])
{
    int comprob=0;
    char replace[50],testo[20];
    DIR *diretzion; 

    /*==Comprobacion de arguentos==*/
    
    //comprobacion de catidad de argumentos
    if(argc < 2)
    {
        printf("Necesito dos argumentos para funcionar:\n1.el nombre del directorio\n2.El nombre del archivo\nIntentelo de nuevo\n");
        return 1;
    }

    //Comprobacion de directorio si ya existe te pide otro hasta que de nombre a uno no creado
    while (comprob == 0)
    {
        if((diretzion = opendir(argv[1])) ==NULL){
            printf("Archivo no repetido adelante\n");
            comprob =1;
        }
        else
        {
            printf("Error! directorio ya existe aca que onda jajaja dame otro nombre porfapls\n");
            fflush(stdin);
            scanf("%s",testo);
            argv[1]= testo;
            printf("%s es e; nuevo nombre\n",argv[1]);

        }
        
    }
    //Creacion del directorio bien bonis aca 
    printf("Creando el directorio %s\n",argv[1]);
    mkdir(argv[1],0755);

    char path[255];
    FILE *archPtr;
    FILE *testeo_file;

    //Comprobando y creando el .txt

    comprob =0;
    while (comprob == 0)
    {
        sprintf(path,"./%s/%s.txt",argv[1],argv[2]);
        testeo_file = fopen(path,"r");
        if(!testeo_file){
            printf("Creando el directorio %s\n",path);
            creat(path,0777);
            comprob =1;
        }
        else{
            printf("Ese documento ya existe dame otro nombre para el documento alv\n");
            fflush(stdin);
            scanf("%s",testo);
            argv[1]= testo;
            printf("%s es e; nuevo nombre\n",argv[2]);
        }
    }
    
    // printf("Creando el directorio %s",path);
    // creat(path,0777);

    //La escribicion en el documento usando el write
    int descriptorFile;
    char mensaje[250];
    char *mensaje_Ptr = &(mensaje[0]);
    int sizeMensaje;
    int nbytes;

    descriptorFile = open(path,O_RDWR);
    if(descriptorFile == -1){
        printf("Error al abrir el archivo\n");
        return -1;
    }
    else{
        printf("Exito al abrir el archivo\n");
    }

    sprintf(mensaje_Ptr,"%s","Equipo: Chiripiorkas\nIntegrantes:\nBenjamin Hoyos Herrera\nAngel Yedid Nacif Mena\nCarlos Abraham Martinez Zamora\nGenaro Gonzalez Lozada");
    sizeMensaje = strlen(mensaje_Ptr);
    nbytes = write(descriptorFile,mensaje_Ptr,sizeMensaje);

    if(nbytes == -1){
        printf("Error no se puedo escribir en el archivo\n");
        return -1;
    }

    //Creando las ligaciones
    int ligas;
    char path_linkshard[255];
    char path_linksoft[255];


    sprintf(path_linkshard,"./%sHard.txt",argv[2]);
    printf("%s\n",path_linkshard);

    ligas = link(path,path_linkshard);

    //enlace fisico o duro
    if(ligas == -1){
        printf("Error creando la liga\n");
        return -1;
    }
    else{
        printf("Liga creada con exito\n");
    }

    //Enlace simbolico o suave
    sprintf(path_linksoft,"./%sSoft.txt",argv[2]);
    printf("%s\n",path_linksoft);
    ligas = symlink(path,path_linksoft);
    if(ligas == -1){
        printf("Error creando la liga\n");
        return -1;
    }
    else{
        printf("Liga creada con exito\n");
    }

    //Enlistar lo que ocupo del punto 4 : 
    struct stat archInfo;
    stat(path,&archInfo);
    //inodo
    printf("El inodo de %s es: %ld\n",path,archInfo.st_ino);
    //tamaño en bytes
    printf("El tamaño de %s es de: %ld bytes\n",path,archInfo.st_size);
    //numero de enlaces que tiene el archivo
    printf("El numero de enlaces que tiene %s es: %ld\n",path,archInfo.st_nlink);

    //punto 5:

    DIR *dir;
    struct dirent *entry;

    if((dir = opendir("./"))==NULL){
        printf("Error al abrir el archivo que onda jajaja\n");
    }
    else{
        printf("Contenido de la carpeta de trabajo\n");
        while ((entry=readdir(dir))!=NULL)
        {
            printf("Nombre: %s\ninodo: %ld\n\n",entry->d_name,entry->d_ino);
        }
        closedir(dir);
        
    }

        


    return 0;
}
