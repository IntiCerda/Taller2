# Taller2 Inti Cerda Ramirez
# Para jugar: 
    g++ main.cpp board.cpp ai.cpp
    .\a


#  Poda y su implementacion
    El algoritmo minimax con poda alfa-beta es una técnica eficiente para la toma de decisiones en juegos de adversario, ya que permite explorar las opciones de manera más efectiva, evitando explorar ramificaciones que no afectarán la decisión final.
    Además, el uso de la poda alfa-beta en el algoritmo minimax permite reducir el número de nodos que se exploran, lo que puede ser eficiente en juegos con un gran factor de ramificación, como es el caso del Connect 4. 
    Esto lleva a una mejora significativa en el rendimiento del algoritmo, permitiendo tomar decisiones más rápidamente a la IA.
    Sin la poda alfa-beta, el programa podría presentar un rendimiento decrepido en términos de velocidad y eficiencia, especialmente en situaciones donde la profundidad de búsqueda es alta. Además, la ausencia de poda alfa-beta podría hacer que el programa se bloquee o crashe cuando se realiza la búsqueda en profundidades mayores

#   Notas
    El guardado de la partida, junto con el cargado de la misma no estan funcionando. No logre implementarlos

