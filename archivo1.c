#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Orden {
	int folio;
	char cliente[50];
	char telefono[15];
	char marca[30];
	char modelo[30];
	int anio;
	char placas[15];
	int kilometraje;
	char servicio[30];
	char descripcion[200];
	float costo;
	char estado[20];
	char fechaIngreso[20];
};

struct Orden ordenes[100];
int totalOrdenes = 0;

// ------------------- Validaciones -------------------
int validarTelefono(char telefono[]) {
	int i;
	for(i=0;i<strlen(telefono);i++) {
		if(!isdigit(telefono[i])) return 0;
	}
	return 1;
}

int validarEstado(char estado[]) {
	if(strcmp(estado,"Pendiente")==0 || strcmp(estado,"En reparacion")==0 ||
	   strcmp(estado,"Finalizado")==0 || strcmp(estado,"Entregado")==0) return 1;
	return 0;
}

int verificarFolio(int folio) {
	int i;
	for(i=0;i<totalOrdenes;i++) {
		if(ordenes[i].folio==folio) return 1;
	}
	return 0;
}

float calcularCostoServicio(char servicio[]) {
	if(strcmp(servicio,"Cambio de aceite")==0) return 800;
	if(strcmp(servicio,"Afinacion")==0) return 1500;
	if(strcmp(servicio,"Frenos")==0) return 2800;
	if(strcmp(servicio,"Suspension")==0) return 4500;
	if(strcmp(servicio,"Direccion")==0) return 3800;
	if(strcmp(servicio,"Clutch")==0) return 6500;
	if(strcmp(servicio,"Transmision")==0) return 12000;
	if(strcmp(servicio,"Motor")==0) return 18000;
	return 0;
}

// ------------------- Funciones principales -------------------
void registrarOrden() {
	system("cls");
	printf("=== REGISTRAR ORDEN ===\n\n");
	
	if(totalOrdenes>=100) {
		printf("ERROR: Capacidad maxima alcanzada.\n");
		printf("Presione ENTER..."); getchar();
		return;
	}
	
	struct Orden nueva;
	printf("Ingrese folio (numero entero, no repetido): ");
	scanf("%d",&nueva.folio); getchar();
	if(verificarFolio(nueva.folio)) {
		printf("ERROR: Folio ya existe.\n");
		printf("Presione ENTER..."); getchar();
		return;
	}
	
	printf("Ingrese nombre completo del cliente: ");
	gets(nueva.cliente);
	if(strlen(nueva.cliente)==0) { printf("ERROR: Nombre vacio.\n"); return; }
	
	printf("Ingrese telefono (solo numeros): ");
	gets(nueva.telefono);
	if(!validarTelefono(nueva.telefono)) { printf("ERROR: Telefono invalido.\n"); return; }
	
	printf("Ingrese marca del vehiculo: ");
	gets(nueva.marca);
	if(strlen(nueva.marca)==0) { printf("ERROR: Marca vacia.\n"); return; }
	
	printf("Ingrese modelo del vehiculo: ");
	gets(nueva.modelo);
	if(strlen(nueva.modelo)==0) { printf("ERROR: Modelo vacio.\n"); return; }
	
	printf("Ingrese anio del vehiculo (1900-2050): ");
	scanf("%d",&nueva.anio); getchar();
	if(nueva.anio<1900 || nueva.anio>2050) { printf("ERROR: Anio invalido.\n"); return; }
	
	printf("Ingrese placas: ");
	gets(nueva.placas);
	if(strlen(nueva.placas)==0) { printf("ERROR: Placas vacias.\n"); return; }
	
	printf("Ingrese kilometraje (positivo): ");
	scanf("%d",&nueva.kilometraje); getchar();
	if(nueva.kilometraje<0) { printf("ERROR: Kilometraje invalido.\n"); return; }
	
	printf("Ingrese tipo de servicio (ej: Frenos, Motor, Cambio de aceite): ");
	gets(nueva.servicio);
	nueva.costo = calcularCostoServicio(nueva.servicio);
	if(nueva.costo<=0) { printf("ERROR: Servicio invalido.\n"); return; }
	
	printf("Ingrese descripcion del problema: ");
	gets(nueva.descripcion);
	if(strlen(nueva.descripcion)==0) { printf("ERROR: Descripcion vacia.\n"); return; }
	
	printf("Ingrese estado del vehiculo (Pendiente/En reparacion/Finalizado/Entregado): ");
	gets(nueva.estado);
	if(!validarEstado(nueva.estado)) { printf("ERROR: Estado invalido.\n"); return; }
	
	printf("Ingrese fecha de ingreso (ej: 29/06/2026): ");
	gets(nueva.fechaIngreso);
	
	ordenes[totalOrdenes]=nueva;
	totalOrdenes++;
	printf("Orden registrada correctamente.\n");
	printf("Presione ENTER..."); getchar();
}

void mostrarOrdenes() {
	system("cls");
	printf("=== MOSTRAR ORDENES ===\n\n");
	if(totalOrdenes==0) {
		printf("No hay ordenes registradas.\n");
	} else {
		int i;
		for(i=0;i<totalOrdenes;i++) {
			printf("Folio:%d\nCliente:%s\nTelefono:%s\nServicio:%s\nCosto:%.2f\nEstado:%s\nFecha:%s\n",
				   ordenes[i].folio, ordenes[i].cliente, ordenes[i].telefono,
				   ordenes[i].servicio, ordenes[i].costo, ordenes[i].estado,
				   ordenes[i].fechaIngreso);
		}
	}
	printf("\nPresione ENTER..."); getchar();
}

void buscarOrden() {
	system("cls");
	printf("=== BUSCAR ORDEN POR FOLIO ===\n\n");
	int folio,i,encontrado=0;
	printf("Ingrese folio: ");
	scanf("%d",&folio); getchar();
	for(i=0;i<totalOrdenes;i++) {
		if(ordenes[i].folio==folio) {
			printf("Cliente:%s Telefono:%s Servicio:%s Estado:%s\n",
				   ordenes[i].cliente, ordenes[i].telefono,
				   ordenes[i].servicio, ordenes[i].estado);
			encontrado=1;
		}
	}
	if(!encontrado) printf("Orden no encontrada.\n");
	printf("Presione ENTER..."); getchar();
}

void buscarPorCliente() {
	system("cls");
	printf("=== BUSCAR ORDEN POR CLIENTE ===\n\n");
	char nombre[50]; int i,encontrado=0;
	printf("Ingrese nombre del cliente: ");
	gets(nombre);
	for(i=0;i<totalOrdenes;i++) {
		if(strcmp(ordenes[i].cliente,nombre)==0) {
			printf("Folio:%d Servicio:%s Estado:%s\n",
				   ordenes[i].folio, ordenes[i].servicio, ordenes[i].estado);
			encontrado=1;
		}
	}
	if(!encontrado) printf("Cliente no encontrado.\n");
	printf("Presione ENTER..."); getchar();
}

void actualizarOrden() {
	system("cls");
	printf("=== ACTUALIZAR ORDEN ===\n\n");
	int folio,i;
	printf("Ingrese folio a actualizar: ");
	scanf("%d",&folio); getchar();
	for(i=0;i<totalOrdenes;i++) {
		if(ordenes[i].folio==folio) {
			printf("Orden encontrada.\n");
			printf("Ingrese nuevo estado (Pendiente/En reparacion/Finalizado/Entregado): ");
			gets(ordenes[i].estado);
			if(!validarEstado(ordenes[i].estado)) { printf("ERROR: Estado invalido.\n"); return; }
			printf("Orden actualizada.\n");
			printf("Presione ENTER..."); getchar();
			return;
		}
	}
	printf("Orden no encontrada.\n");
	printf("Presione ENTER..."); getchar();
}

void eliminarOrden() {
	system("cls");
	printf("=== ELIMINAR ORDEN ===\n\n");
	int folio,i,j;
	printf("Ingrese folio a eliminar: ");
	scanf("%d",&folio); getchar();
	for(i=0;i<totalOrdenes;i++) {
		if(ordenes[i].folio==folio) {
			printf("Orden encontrada. Eliminando...\n");
			for(j=i;j<totalOrdenes-1;j++) {
				ordenes[j]=ordenes[j+1];
			}
			totalOrdenes--;
			printf("Orden eliminada.\n");
			printf("Presione ENTER..."); getchar();
			return;
		}
	}
	printf("Orden no encontrada.\n");
	printf("Presione ENTER..."); getchar();
}
void ordenarPorPrioridad() {
	int i,j;
	struct Orden temp;
	for(i=0;i<totalOrdenes-1;i++) {
		for(j=0;j<totalOrdenes-1-i;j++) {
			if(ordenes[j].costo < ordenes[j+1].costo) {
				temp = ordenes[j];
				ordenes[j] = ordenes[j+1];
				ordenes[j+1] = temp;
			}
		}
	}
}

void mostrarPrioridad() {
	system("cls");
	printf("=== ORDENES POR PRIORIDAD (COSTO) ===\n\n");
	if(totalOrdenes==0) {
		printf("No hay ordenes registradas.\n");
	} else {
		ordenarPorPrioridad();
		int i;
		for(i=0;i<totalOrdenes;i++) {
			printf("Folio:%d Cliente:%s Servicio:%s Costo:%.2f Estado:%s\n",
				   ordenes[i].folio, ordenes[i].cliente,
				   ordenes[i].servicio, ordenes[i].costo,
				   ordenes[i].estado);
		}
	}
	printf("\nPresione ENTER..."); getchar();
}

void mostrarEstadisticas() {
	system("cls");
	printf("=== ESTADISTICAS ===\n\n");
	if(totalOrdenes==0) {
		printf("No hay ordenes registradas.\n");
	} else {
		int i;
		float totalDinero=0, promedio=0;
		char servicioMasSolicitado[30];
		char servicioMasCostoso[30];
		int contadorServicios[8]={0}; // 8 tipos definidos
		char servicios[8][30]={"Cambio de aceite","Afinacion","Frenos","Suspension","Direccion","Clutch","Transmision","Motor"};
		
		float maxCosto=0;
		for(i=0;i<totalOrdenes;i++) {
			totalDinero += ordenes[i].costo;
			if(ordenes[i].costo > maxCosto) {
				maxCosto = ordenes[i].costo;
				strcpy(servicioMasCostoso, ordenes[i].servicio);
			}
			int j;
			for(j=0;j<8;j++) {
				if(strcmp(ordenes[i].servicio,servicios[j])==0) {
					contadorServicios[j]++;
				}
			}
		}
		promedio = totalDinero/totalOrdenes;
		
		int maxSolicitado=0, idx=0;
		for(i=0;i<8;i++) {
			if(contadorServicios[i]>maxSolicitado) {
				maxSolicitado=contadorServicios[i];
				idx=i;
			}
		}
		strcpy(servicioMasSolicitado, servicios[idx]);
		
		printf("Total de ordenes: %d\n", totalOrdenes);
		printf("Total de dinero estimado: %.2f\n", totalDinero);
		printf("Servicio mas solicitado: %s\n", servicioMasSolicitado);
		printf("Servicio mas costoso: %s\n", servicioMasCostoso);
		printf("Promedio del costo de los servicios: %.2f\n", promedio);
	}
	printf("\nPresione ENTER..."); getchar();
}

// ------------------- Menu principal -------------------
int main() {
	int opcion;
	do {
		system("cls");
		printf("=== MENU PRINCIPAL ===\n");
		printf("1. Registrar orden\n");
		printf("2. Mostrar todas las ordenes\n");
		printf("3. Buscar orden por folio\n");
		printf("4. Buscar por nombre del cliente\n");
		printf("5. Actualizar una orden\n");
		printf("6. Eliminar una orden\n");
		printf("7. Mostrar vehiculos por prioridad\n");
		printf("8. Estadisticas\n");
		printf("9. Salir\n");
		printf("Seleccione una opcion: ");
		scanf("%d",&opcion); getchar();
		
		switch(opcion) {
		case 1: registrarOrden(); break;
		case 2: mostrarOrdenes(); break;
		case 3: buscarOrden(); break;
		case 4: buscarPorCliente(); break;
		case 5: actualizarOrden(); break;
		case 6: eliminarOrden(); break;
		case 7: mostrarPrioridad(); break;
		case 8: mostrarEstadisticas(); break;
		case 9: printf("Saliendo del sistema...\n"); break;
		default: printf("Opcion invalida.\nPresione ENTER..."); getchar();
		}
	} while(opcion!=9);
	
	return 0;
}
