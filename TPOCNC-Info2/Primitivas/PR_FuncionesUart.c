#include "Aplicacion.h"

unsigned char buf_rx[TAM_BUF_RX],buf_tx[TAM_BUF_TX];
int out_tx = 0, in_tx = 0, out_rx = 0, in_rx = 0;

int serialRead(void)
{
	int aux=-1;
	if(out_rx != in_rx)
	{
		aux = buf_rx[out_rx];
		out_rx++;
		out_rx %= TAM_BUF_RX;
	}
	return aux;
}

void sendSerialString ( char *msg )
{
	int i;

	for ( i = 0 ; msg[i] ; i ++ )
	{
		push_TX( msg[i]);
	}
}

void push_TX(unsigned char dato)
{
	buf_tx [in_tx] = dato;
	in_tx++;
	in_tx %= TAM_BUF_TX;
	if (U0_FLAG_TX )
	{
		dato=pop_TX();
		U0_REG_SAL_TX = dato;
	}
}

void push_RX(unsigned char dato)
{
	buf_rx[in_rx]=dato;
	in_rx++;
	in_rx %= TAM_BUF_RX;
}

int pop_TX(void)
{
   int aux=-1;
   if(in_tx != out_tx)
   {
		aux=buf_tx[out_tx];
		out_tx++;
		out_tx %=TAM_BUF_TX;
   }
   return aux;
}

void Serial_reset_buff_rx ( void )
{
	memset( &buf_rx, 0, sizeof(buf_rx));
	out_rx = 0;
	in_rx = 0;
}



























