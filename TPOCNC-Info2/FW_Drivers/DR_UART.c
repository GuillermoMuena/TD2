/*
 * ISR.c
 *
 *  Created on: 06/07/2013
 *      Author: Usuario
 */

#include "Aplicacion.h"

#define I_RX         2
#define I_TX         1
#define CTI          6

extern unsigned char TxStart;

void UART1_IRQHandler (void)
{
	unsigned char iir,dato;

    int aux;
	do
	{
		//IIR es reset por HW, una vez que lo lei se resetea.
		iir = U1IIR; // Pagina 323
	   /* bit 0= IntStatus  Si es 0--> Hay una interrup de UART1 pendiente
						// Si es 1--> No hay una interrup de UART1 pendiente

		  bit 3:1 IntId  Si vale 010--> Interr por RX
								 001--> Interr por TX
								 011--> Interr por LINE STATUS
								 110--> Interr por Character time_out Indicator
								 000--> Interr por MODEM

		 */

		switch((iir & 0x0E)>>1)
		{
			 case (I_RX):
						  dato=U1RBR;
						  push_RX(dato);
						  break;


			 case (I_TX):
						  aux=pop_TX();
						   if(aux>0)
						   {
							 U1THR = aux;
						   }
						   else
							  TxStart=0; //par asegurar que se fue
						   break;

			 case (CTI):   // Este INT ocurre cuando se usa la FIFO de RX y hay mensajes que no fueron leidos
						   // de la FIFO dentro de un tiempo equivalente a 5 ó 6 caracteres. ESto puede ocurrir durante
						   // un breakpoint ( en un debugging)De esta forma nos aseguramos que se vacie la FIFO
						  dato=U1RBR;
						  push_RX(dato);
						  break;

			 default:
						   break;

		}


	}
	while( ! ( iir & 0x01 ) ); /* me fijo si cuando entr‚ a la ISR habia otra
						     	int. pendiente de atenci¢n: b0=1 (ocurre £nicamente si dentro del mismo
								espacio temporal lleguan dos interrupciones a la vez) */
}

void UART0_IRQHandler (void)
{
	unsigned char iir,dato;
    int aux;


	do
	{
		//IIR es reset por HW, una vez que lo lei se resetea.
		iir = U0IIR; // Pagina 323
		                           /* bit 0= IntStatus  Si es 0--> Hay una interrup de UART1 pendiente
		                                            // Si es 1--> No hay una interrup de UART1 pendiente

		                              bit 3:1 IntId  Si vale 010--> Interr por RX
		                                                     001--> Interr por TX
		                                                     011--> Interr por LINE STATUS
		                                                     110--> Interr por Character time_out Indicator
		                                                     000--> Interr por MODEM*/

		switch((iir & 0x0E)>>1)
	                    {
		            		 case (I_RX):
		                                  dato=U0RBR;
		                                  push_RX(dato);
		            		              break;


		            		 case (I_TX):
                                          aux=pop_TX();
		            		               if(aux>0)
		            		               {
		            		            	 U0THR = aux;
		            		               }
                                           else
		            		                  TxStart=0; //par asegurar que se fue
		            		               break;

		            		 case (CTI):   // Este INT ocurre cuando se usa la FIFO de RX y hay mensajes que no fueron leidos
		            				       // de la FIFO dentro de un tiempo equivalente a 5 ó 6 caracteres. ESto puede ocurrir durante
		            				       // un breakpoint ( en un debugging)De esta forma nos aseguramos que se vacie la FIFO
		            			          dato=U0RBR;
		            			 		  push_RX(dato);
		            			          break;

		            		 default:
		            			           break;

	                    }


	}
	while( ! ( iir & 0x01 ) ); /* me fijo si cuando entr‚ a la ISR habia otra
						     	int. pendiente de atenci¢n: b0=1 (ocurre £nicamente si dentro del mismo
								espacio temporal lleguan dos interrupciones a la vez)*/
}



