/* lcd.c
 *
 *  Created on: 02/09/2015
 *      Author: Usuario
 */
#include "Aplicacion.h"
uint8_t flag[N_AXIS] = {1,1,1};
extern volatile st_block_t st_auto_block;

void Display_lcd( char *msg , char renglon , char posicion )
{
	unsigned char i ;

#ifdef LCD_16x2
	if( renglon )
		posicion = posicion + 0xc0 ;
	else
		posicion = posicion + 0x80 ;
#endif

#ifdef LCD_20x4
	switch( renglon )
	{
	case RENGLON0:
		posicion = posicion + 0x80 ;
		break;
	case RENGLON1:
		posicion = posicion + 0xc0 ;
		break;
	case RENGLON2:
		posicion = posicion + 0x94 ;
		break;
	case RENGLON3:
		posicion = posicion + 0xd4 ;
		break;
	}
#endif

	Dato_LCD( posicion , LCD_CONTROL );
	for( i = 0 ; msg[ i ] != '\0' ; i++ )
		Dato_LCD( msg[ i ] , LCD_DATA );

}

void Deb_Disp (char* s){

	static uint8_t i=0;
	if(i == 4)
		Dato_LCD(LCD_CLEARDISPLAY ,LCD_CONTROL);
	i%=4;
	Display_lcd(s,i,0);
	i++;
}

void Dis_Pos (void )
{
	char posx[30],posy[30],posz[30];
	uint8_t i;
//	static uint8_t flag[N_AXIS] = {1,1,1};

	float pos_mm[N_AXIS];

	for ( i=0; i< N_AXIS; i++)
	{
		pos_mm[i] = sys.position[i] / (float) settings.steps_per_mm[i];
	}

	Display_lcd (" Posiciones: ", RENGLON0, 1);

	if (st_auto_block.steps[X_AXIS])
	{
		sprintf(posx, "X: %3.2f", (float) pos_mm[X_AXIS] );
		sendSerialString(posx);
		sendSerialString("%");
		Display_lcd(posx,RENGLON1,10);
		flag[X_AXIS] = 1;
	}
	else if (flag[X_AXIS])
	{
		sprintf(posx, "X: %3.2f", (float) pos_mm[X_AXIS] );
		sendSerialString(posx);
		sendSerialString("%");
		Display_lcd(posx,RENGLON1,10);
		flag[X_AXIS] = 0;
	}

	if (st_auto_block.steps[Y_AXIS])
	{
		sprintf(posy, "Y: %3.2f", (float) pos_mm[Y_AXIS] );
		sendSerialString(posy);
		sendSerialString("%");
		Display_lcd(posy,RENGLON2,10);
		flag[Y_AXIS] = 1;
	}
	else if (flag[Y_AXIS])
	{
		sprintf(posy, "Y: %3.2f", (float) pos_mm[Y_AXIS] );
		sendSerialString(posy);
		sendSerialString("%");
		Display_lcd(posy,RENGLON2,10);
		flag[Y_AXIS] = 0;
	}

	if (st_auto_block.steps[Z_AXIS])
	{
		sprintf(posz, "Z: %3.2f", (float) pos_mm[Z_AXIS] );
		sendSerialString(posz);
		sendSerialString("%");
		Display_lcd(posz,RENGLON3,10);
		flag[Z_AXIS] = 1;
	}
	else if (flag[Z_AXIS])
	{
		sprintf(posz, "Z: %3.2f", (float) pos_mm[Z_AXIS] );
		sendSerialString(posz);
		sendSerialString("%");
		Display_lcd(posz,RENGLON3,10);
		flag[Z_AXIS] = 0;
	}
}


void Display_bienvenida(void )
{
	Dato_LCD(LCD_CLEARDISPLAY ,LCD_CONTROL);
	Display_lcd (" Bienvenido.", RENGLON0, 1);
	Display_lcd (" Inicializando...", RENGLON1, 1);
	TimerStart ( DISP_WELCOME, 1200);

}






























