import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
#Definimos la funcion que grafica un circulo dadas las coordenadas del centro y el radio
def drawCircle(c_x,c_y,r):
    t=np.linspace(0,2*np.pi,1000)
    plt.plot(r*np.cos(t)+c_x,r*np.sin(t)+c_y,c="r")
    return 0
#Cargamos los datos producidos.
canal1=np.loadtxt("Canal_ionico.txt")
canal2=np.loadtxt("Canal_ionico1.txt")
resul1=np.loadtxt("Resultados1.txt")
resul2=np.loadtxt("Resultados2.txt")
x1=np.array(canal1[:,0])
y1=np.array(canal1[:,1])
x2=np.array(canal2[:,0])
y2=np.array(canal2[:,1])
c_x1=np.array(resul1[:,0])
c_y1=np.array(resul1[:,1])
r1=np.array(resul1[:,2])
c_x2=np.array(resul2[:,0])
c_y2=np.array(resul2[:,1])
r2=np.array(resul2[:,2])
#Graficamos el circulo de mayor radio obtenido.
plt.grid(True)
plt.axis('equal')
plt.ylabel("$y(\\AA)$")
plt.xlabel("$x(\\AA)$")
plt.title("Canal Ionico uno: $c_x=$"+str(c_x1[len(c_x1)-1])+", $c_y=$"+str(c_y1[len(c_y1)-1])+" y $r=$"+str(r1[len(r1)-1])+"$( \\AA )$")
plt.scatter(x1,y1,c="b")
drawCircle(c_x1[len(c_x1)-1],c_y1[len(c_x1)-1],r1[len(r1)-1])
plt.savefig("canal1.png")
plt.close()
plt.grid(True)
plt.axis('equal')
plt.ylabel("$y(\\AA)$")
plt.xlabel("$x(\\AA)$")
plt.title("Canal Ionico dos: $c_x=$"+str(c_x2[len(c_x2)-1])+", $c_y=$"+str(c_y2[len(c_y2)-1])+" y $r=$"+str(r2[len(r2)-1])+"$( \\AA )$")
plt.scatter(x2,y2,c="b")
drawCircle(c_x2[len(c_x2)-1],c_y2[len(c_x2)-1],r2[len(r2)-1])
plt.savefig("canal2.png")
plt.close()
# Pasamos ahora a los histogramas.
n, bins, patches = plt.hist(c_x1, 50, facecolor='green', alpha=0.75)
plt.xlabel('Valores $(\\AA)$')
plt.ylabel('Frecuencia')
plt.title("Coordenada $x$ en el canal uno.")
plt.grid(True)
plt.savefig("centrox_1.png")
plt.close()
n, bins, patches = plt.hist(c_y1, 50, facecolor='green', alpha=0.75)
plt.xlabel('Valores $(\\AA)$')
plt.ylabel('Frecuencia')
plt.title("Coordenada $y$ en el canal uno.")
plt.grid(True)
plt.savefig("centroy_1.png")
plt.close()
n, bins, patches = plt.hist(c_x2, 50, facecolor='green', alpha=0.75)
plt.xlabel('Valores $(\\AA)$')
plt.ylabel('Frecuencia')
plt.title("Coordenada $x$ en el canal dos.")
plt.grid(True)
plt.savefig("centrox_2.png")
plt.close()
n, bins, patches = plt.hist(c_y2, 50, facecolor='green', alpha=0.75)
plt.xlabel('Valores $(\\AA)$')
plt.ylabel('Frecuencia')
plt.title("Coordenada $y$ en el canal dos.")
plt.grid(True)
plt.savefig("centroy_2.png")
plt.close()
