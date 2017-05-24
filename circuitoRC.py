import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
#Definimos el modelo que gobiena el sistema fisico
def model(x,R,C):
    time = -x/(R*C)
    return 10*C*(1-np.exp(time))
#Definimos la funcion de verosimilitud
def likelihood(y_obs, y_model):
    chi = (1.0/2.0)*sum(((y_obs-y_model)/np.std(y_obs))**2)
    return np.exp(-chi)
#Cargamos los datos en dos listas para ser analizados
data=np.loadtxt('CircuitoRC.txt')
t = np.array(data[:,0])
Q = np.array(data[:,1])
#Definimos ahora listas vacias para los parametros y la verosimilitud
R=[]
C=[]
L=[]
#Las inicializamos con una variable aleatoria
R.append(np.random.random()*10)
C.append(np.random.random()*10)
#Generamos los datos de prediccion del modelo
y_m = np.array(model(t,R[0],C[0]))
#Obtenemos el valor de verosimilitud y lo metemos en la lista
L.append(likelihood(Q,y_m))
#Comenzamos el proceso de iteracion:
for i in range(20000):
    r=np.random.normal(R[i],0.1)
    c=np.random.normal(C[i],0.1)
    y_i = np.array(model(t,R[i],C[i]))
    y_m = np.array(model(t,r,c))
    l_i = likelihood(Q,y_i)
    l = likelihood(Q,y_m)
    alpha = l/l_i
    if(alpha>=1.0):
        R.append(r)
        C.append(c)
        L.append(l)
    else:
        beta = np.random.random()
        if(beta<=alpha):
            R.append(r)
            C.append(c)
            L.append(l)
        else:
            R.append(R[i])
            C.append(C[i])
            L.append(L[i])
#Encontramos los parametros con el likelihood mas grande, y los graficamos para contrastarlos con los datos observados
max_likelihood_id = np.argmax(L)
best_r = R[max_likelihood_id]
best_c = C[max_likelihood_id]
best_y = model(t, best_r, best_c)
plt.scatter(t,Q)
plt.title("Mejores parametros")
plt.ylabel("Carga $(C)$")
plt.xlabel("Tiempo $(s)$")
plt.plot(t, best_y, label="R= %.3f, C= %.3f" %(R[max_likelihood_id], C[max_likelihood_id]), c="r")
plt.grid(True)
plt.legend(loc=0)
plt.savefig("fig_21.png")
plt.close()
#Generamos la grafica para el parametro R
plt.grid(True)
plt.title("Parametro R y log de verosimilitud")
plt.ylabel("log(verosimilitud)")
plt.xlabel("R $(\\Omega)$")
plt.scatter(R,-np.log(L))
plt.savefig("fig_22.png")
plt.close()
#Generamos la grafica para el parametro C
plt.grid(True)
plt.title("Parametro C y log de verosimilitud")
plt.ylabel("log(verosimilitud)")
plt.xlabel("C $(F)$")
plt.scatter(C,-np.log(L))
plt.savefig("fig_23.png")
