# Blog Modelado

## Gráficas

### Gráfica1:
![Descripción de la imagen](https://github.com/LiamSaboridoSueiro/robot_description/blob/main/rosbags/grafica1.png)

La gráfica muestra la velocidad de las ruedas del robot en dos escenarios de simulación distintos (arena y piso). Al inicio, las velocidades de las ruedas aumentan hasta estabilizarse. Cerca del segundo 10, las velocidades disminuyen poco a poco, indicando un cambio en la velocidad deseada o una colisión con un objeto. Las diferencias en las velocidades entre los dos escenarios reflejan cómo las distintas superficies afectan el rendimiento del robot.

### Gráfica2:
![Descripción de la imagen](https://github.com/LiamSaboridoSueiro/robot_description/blob/main/rosbags/grafica2.png)

La gráfica muestra una comparación entre las velocidades de las ruedas del robot (publicadas en joint_states) y los desplazamientos estimados por el controlador (publicados en el topic de odometría). Al inicio, las velocidades de las ruedas aumentan y se estabilizan, mientras que la odometría refleja un desplazamiento lineal constante. Las diferencias entre las ruedas y la odometría muestran cómo las distintas superficies afectan la precisión del control del robot.

### Gráfica3:
![Descripción de la imagen](https://github.com/LiamSaboridoSueiro/robot_description/blob/main/rosbags/grafica3.png)

La gráfica muestra la aceleración lineal del robot en el eje X, registrada por el sensor IMU. Los picos y caídas abruptas en la aceleración indican momentos de impacto, especialmente notable alrededor del segundo 6 y el segundo 10, donde se observan cambios significativos en los valores de aceleración, señalando los choques con los cubos en los distintos mundos simulados.

Se puede acceder a los rosbags en la carpeta "[rosbags](https://github.com/LiamSaboridoSueiro/robot_description/tree/main/rosbags)" del repositorio.

## Vídeos

[floor.webm](https://github.com/LiamSaboridoSueiro/robot_description/assets/113594770/8d7c536c-1278-469b-96b0-9484ff342003)

[sand.webm](https://github.com/LiamSaboridoSueiro/robot_description/assets/113594770/b4ed3be6-b6cd-4b8f-8c49-7c665e88a38e)

## Video parte A



https://github.com/LiamSaboridoSueiro/robot_description/assets/113594770/9b1ffd2c-7218-4620-8dd5-b50df92540d6




