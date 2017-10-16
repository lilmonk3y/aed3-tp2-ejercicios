tests.txt es el archivo para que el algoritmo utilice como entrada

testsModerados.txt son los tests que se utilizaron para generar tiemposCostosModerados.csv

testsExtremos.txt son los tests que se utilizaron para generar tiemposCostosExtremos.csv

las columnas de los csv son
	n: cantidad de trabajos en la entrada
	tCompl: tiempo que tardo la funcion completarSubsoluciones
	tRecons: tiempo que tardo la funcion reconstruirSolucion
	tTotal: tiepo de ambas funciones
	costo: costo de la reparticion de trabajos de la subsolucion encontrada
	trabMaaOut: cantidad de trabajos que hace una de las maquinas	

tiemposCostosModerados.csv tiene los tiempos de correr el algoritmo con costos de trabajos moderados (distribucion normal (2,3))
tiemposCostosModerados2.csv tiene los tiempos de una segunda ejecucion con los mismos datos de entrada que tiempoCostosModerados

tiemposCostsoExtremos.csv tiene los tiempos de correr el algoritmo con costos de trabajos extremos (distribucion normal (3,10))






Observaciones:
	1) El crecimiento es bastante regular, no cambia mucho el tiempo de ejecucion los costos de una entrada en particular.
	Los outliers en costosModerados no son los mismos que costosModerados2 por lo que parece que se dan por motivos ajenos al algoritmo.
	
	2) No parece haber diferencia entre moderados y extremos