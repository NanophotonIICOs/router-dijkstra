def modificar_archivo(nombre_archivo):
    # Leer el contenido del archivo
    with open(nombre_archivo, 'r') as archivo:
        lineas = archivo.readlines()
    # Modificar la lista de acuerdo a las especificaciones
    lista_modificada = []
    for i, linea in enumerate(lineas):
        numero_elementos = i * 250000
        linea_modificada = f"{numero_elementos}, {linea}"
        lista_modificada.append(linea_modificada)

    # Guardar los cambios en el archivo original
    with open(nombre_archivo, 'w') as archivo:
        archivo.writelines(lista_modificada)

# Nombre del archivo a modificar
nombre_archivo = "D:/Desktop/tree3_3.txt"  # Reemplaza con la ruta y nombre correctos

# Llamar a la función para modificar el archivo
modificar_archivo(nombre_archivo)
