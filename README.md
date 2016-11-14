# [P001] Seguidor de Lineas - PisteroMSP430

## Descripción:



## Integrantes:
- Santiago Rodríguez


## Estado del proyecto:
- [x] La versión de código actual de "azulPicasso" compila. Queda probar el programa en el hardware para ver si funciona como debe o si hay algún
 error.

## Notas

 - Para poder programar correctamente el micro utilizando Energia, copiar la carpeta "launchpad_28pin" en "Energia\hardware\msp430\variants".
 Además, agregar en el archivo "boards" (en hardware/msp430) lo siguiente:
 
##############################################################
lpmsp430g2553.name=LaunchPad w/ msp430g2553_28pin (16MHz)
lpmsp430g2553.upload.protocol=rf2500
lpmsp430g2553.upload.maximum_size=16384
lpmsp430g2553.build.mcu=msp430g2553
lpmsp430g2553.build.f_cpu=16000000L
lpmsp430g2553.build.core=msp430
lpmsp430g2553.build.variant=launchpad_28pin
lpmsp430g2553.upload.maximum_ram_size=512
 
 Ahora podrá seleccionarse la "board" launchpad_28pin que permite programar los puertos P3_x del MSP430G2553 de 28 pines. Probado en "energia-0101E0015".
	
## Link al proyecto:
[Link al proyecto en el sitio del Club](http://cdrunlp.com.ar/proyecto1/)

