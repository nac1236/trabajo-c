#include "sub.h"


//quiero crear la estructura para manejar los datos del archivo
struct arreglo_sub * init_arreglo(struct arreglo_sub *a, int initial_size) {
  a->a = (struct sub *)malloc(initial_size * sizeof(struct sub));
  a->tamanio = initial_size;
  a->ocupado = 0;
	return a;
}


struct arreglo_sub *insert_sub(struct arreglo_sub *a, struct sub * dato){
  if (a->ocupado == a->tamanio) {
    a->tamanio *= 2;
    a->a = (struct sub *)realloc(a->a, a->tamanio * sizeof(struct sub));
  }
  a->a[a->ocupado++] = *dato;
  return a;
}

struct arreglo_sub * inicializar(FILE * entrada){
	struct arreglo_sub * arreglo = calloc(1,sizeof(struct arreglo_sub));
	arreglo = init_arreglo(arreglo,1);
	struct sub *dato;
	char dato1[100];
	int indice;

	//empiezo a leer

	while(fscanf(entrada,"%d\n",&indice) != EOF){
		dato = malloc(sizeof(struct sub));
		dato->indice = indice;
		fscanf(entrada,"%d",&dato->inicio.tm_hour);
		fgetc(entrada);
		fscanf(entrada,"%d",&dato->inicio.tm_min);
		fgetc(entrada);
		fscanf(entrada,"%d",&dato->inicio.tm_sec);
		fgetc(entrada);
		fscanf(entrada,"%d",&dato->inicio.tm_ml);
		fgetc(entrada);
		fgetc(entrada);
		fgetc(entrada);
		fgetc(entrada);
		fgetc(entrada);
		fscanf(entrada,"%d",&dato->fin.tm_hour);
		fgetc(entrada);
		fscanf(entrada,"%d",&dato->fin.tm_min);
		fgetc(entrada);
		fscanf(entrada,"%d",&dato->fin.tm_sec);
		fgetc(entrada);
		fscanf(entrada,"%d",&dato->fin.tm_ml);
		fgetc(entrada);
		fgetc(entrada);
		fgetc(entrada);
		dato->texto = malloc(sizeof(char) * 100);
		while(3 != strcasecmp((fgets(dato1, 100 ,entrada)),"\n")){
			//aca podria poner una sentencia de control para que haga realloc de ser necesario	!!!!			
						
			strcat(dato->texto,dato1);	
			
			
		}	
		printf("%s",dato->texto);
		arreglo = insert_sub(arreglo,dato);

		
		//free(dato->texto);
		//free(dato);		Si hago el free de estos datos ahora no me deja usarlos en ningun lado posteriormente. averiguar por que? ***
		
	}
	printf("Salio");
	getchar();
	

	//quiero imprimir el indice de cada struct que guardo en la estrcutura   !!!!
	//for(int i = 0; i < dim_l; i++){
	//	printf("Indice:%d  \n Texto: %s \n",(arreglo + i * 8)->indice,(arreglo + i * 8)->texto);
		//printf("Dimension logica:%d.\n", dim_l);
	//}

	//dim = dim_l;

	return arreglo;
}


// CREO QUE NO ESTOY PUDIENDO METER LA INFORMACION EN EL ARCHIVO DE SALIDA PORQUE HAY INCOMPATIBILIDAD EN LA FORMA EN QUE LO GUARDE Y EN LA FORMA EN QUE ESTOY TRATANDO DE RECUPERAR LA INFORMACION(EN EL ARCHIVO DE SALIDA ME QUEDAN DIRECCIONES A LA INFORMACION NADA MAS)
void crear_salida(struct arreglo_sub * sub,FILE ** salida){
	printf("Entro a guardar la estructura.");
	getchar();	
	for(int i = 0; i < sub->ocupado - 1; i++){
		fprintf(*salida,"%d",sub->a[i].indice);
		fputc('\n',*salida);
		fprintf(*salida,"%d",sub->a[i].inicio.tm_hour);
		fputc(':',*salida);
		fprintf(*salida,"%d",sub->a[i].inicio.tm_min);
		fputc(':',*salida);
		fprintf(*salida,"%d",sub->a[i].inicio.tm_sec);
		fputc(',',*salida);
		fprintf(*salida,"%d",sub->a[i].inicio.tm_ml);
		fputc(' ',*salida);
		fputc('-',*salida);
		fputc('-',*salida);
		fputc('>',*salida);
		fputc(' ',*salida);
		fprintf(*salida,"%d",sub->a[i].fin.tm_hour);
		fputc(':',*salida);
		fprintf(*salida,"%d",sub->a[i].fin.tm_min);
		fputc(':',*salida);
		fprintf(*salida,"%d",sub->a[i].fin.tm_sec);
		fputc(',',*salida);
		fprintf(*salida,"%d",sub->a[i].fin.tm_ml);
		//fputc('\t',*salida);		
		fputc('\n',*salida);
		
		fprintf(*salida,"%s",sub->a[i].texto);
		fputc('\n',*salida);			// EDITAR FORMA DE ACCESO AL CAMPO PARA QUE FUNCIONE
	}
	
	//en la salida quedan algunos errores

}

