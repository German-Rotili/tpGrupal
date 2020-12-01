#tpGrupal


Dejo aca las formulas del Ray Casting

Teniendo para cada rayo:

theta : angulo de la dirección del rayo (Se mide con respecto al eje x de la grilla)

x, y : pos en grilla del actor

dX, dY : delta de pos con respecto a la grilla

Dependiendo de theta:

- pasoGrillaX, pasoGrillaY = +- 1
- pasoX, pasoY = tan(theta), 1/tan(theta)
- xIntercept = x + dX + -dY/tan(theta)
- yIntercept = y + dY + dX/tan(theta)

Llamamos [dist] a la distancia con la pared en la dirección del rayo
Siendo distX y distY sus respectivas componentes.

Además es necesaria realizar una proyección para evitar problemas de renderizado (ojo de pez)

Se de antemano el angulo de la direccion de visión del actor (alpha)

Y tengo que proyectar todas las direcciones hacia un plano imaginario que pasa perpendicular al vector de dirección del actor

Por trigonometria esa proyección seria:

Proy = dist * cos(theta - alpha)

Usando identidades trigonometricas nos queda:

Proy = dist cos(theta) cos(alpha) + dist sin(theta) sin(alpha)

Ademas sabemos que:

distX = d cos(theta)

distY = d sin(theta)

Entonces:

Proy = distX cos(alpha) + distY sin(alpha)

Y esta es la verdadera distancia con la que hay que dibujar

El tema de escalas despues se resuelve.

INFO extra:

Podemos cambiar el angulo de los rayos dependiendo el FOV que queremos usar, esto se puede determinar como variable de configuración.
Hay algunos pasos del algoritmo que dependen de la dirección del rayo y hay que tenerlo en cuenta.
