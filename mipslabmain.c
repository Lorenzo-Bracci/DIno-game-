/* mipslabmain.c


#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)


/*int random(int r) {
    r = ((r+1)*7836) + 1234;
    return (unsigned int) (r % 5);
}*/

//up and down and it should start from page 1
int first_iteration = 1;
int up = 1;

int pixels = 0;
void zig(int x){
	int i, j;

		for(i = 0; i < 3; i++) {
				DISPLAY_CHANGE_TO_COMMAND_MODE;

				spi_send_recv(0x22);
				spi_send_recv(i);
        spi_send_recv(0x21);
				spi_send_recv(x & 0xF);
				spi_send_recv(0x10 | ((x >> 4) & 0xF));

				DISPLAY_CHANGE_TO_DATA_MODE;

				for(j = 0; j < 16; j++){

					if (i < 2){
						spi_send_recv((~ptero[j + (i * 16)] >> (pixels+1) & (0x7f >> pixels)) | ((~ptero[j + ((i+1) * 16)] << (7-pixels))));
					}
					else{
						spi_send_recv((~ptero[j + (i * 16)] >> (pixels+1)) | (0x01 << pixels) << (7-pixels));
					}
				}
			}
			pixels++;
			if (pixels == 8){
				pixels == 6;
				up = 0;
			}

			}
	}
	void zag(int x){
		int i, j;
	//	int k = 6;
	//	while(k!= -2){

			for(i = 0; i < 3; i++) {
					DISPLAY_CHANGE_TO_COMMAND_MODE;

					spi_send_recv(0x22);
					spi_send_recv(i);

          spi_send_recv(0x21);
					spi_send_recv(x & 0xF);
					spi_send_recv(0x10 | ((x >> 4) & 0xF));

					DISPLAY_CHANGE_TO_DATA_MODE;

					for(j = 0; j < 16; j++){
            if (pixels != -1){
						if (i < 2){
							spi_send_recv((~ptero[j + (i * 16)] >> (pixels+1) & (0x7f >> pixels)) | ((~ptero[j + ((i+1) * 16)] << (7-pixels))));
						}
						else{
							spi_send_recv((~ptero[j + (i * 16)] >> (pixels+1)) | (0x01 << pixels) << (7-pixels));
						}
					}
					else{
						spi_send_recv(~ptero[j + (i * 16) ]);
					}
					}
				}
				pixels--;
				if (pixels == -2){
					pixels = 0;
				up = 1;
				}
		//		}
		}

int iscactus = 1;

void init(void){
	T2CON = 0x50;
	PR2 = (80000000 / 64) / 10;
	TMR2 = 0x0;
	T2CONSET = 0x8000;

	T3CON = 0x50;
	PR3 = (80000000 / 64) / 10;
	TMR3 = 0x0;
	T3CONSET = 0x8000;

	T4CON = 0x50;
	PR4 = (80000000 / 64) / 10;
	TMR4 = 0x0;
	T4CONSET = 0x8000;
}

		int k = 128;
		int timerdone = 0;
		int done = 0;
		void dino_jump(int jump, int x){
			int i, j, w, h, g, l;
			int a [16];
				int b;
			uint8_t copy [64];

			for (w = 0; w < 64; w++) {
				copy[w] = dino2[w];
			}

			for(l = 0; l < jump; l++){

					timerdone = 0;

				while (!timerdone){
					if (IFS(0) & 0x100){
			if (!done){
			for ( h = 0; h < 4; h++){

			for ( g = 0; g < 16; g++ ){

				if (h < 3){
					copy[g + (h * 16)] = (~copy[g + (h * 16)] >> 1 & 0x7f) | ((~copy[g + ((h+1) * 16)] << 7) );
				}
				else{
				    copy[g + (h * 16)] = ((~copy[g + (h * 16)] >> 1 & 0x7f) | (0x01) << 7);
		    }
			}
		}
		for (w = 0; w < 64; w++) {
			copy[w] = ~copy[w];
		}
			for(i = 0; i < 4; i++) {
			//	quicksleep1(19);
					DISPLAY_CHANGE_TO_COMMAND_MODE;

					spi_send_recv(0x22);
					spi_send_recv(i);

					spi_send_recv(0x21);
					spi_send_recv(x & 0xF);
					spi_send_recv(0x10 | ((x >> 4) & 0xF));

					DISPLAY_CHANGE_TO_DATA_MODE;

					for(j = 0; j < 16; j++){
							spi_send_recv(~copy[j + (i*16)]);
						}
				}
			if (iscactus == 1){
				if(k > 0){
					display_bottom(k, 8, 4, 3, cactus);
					k--;
				}
				else{
					k = 128;
				}
	if( k > 16 && k < 22 && l < 7){
					display_string(1, "GAME OVER");
					display_update();
					done = 1;
				}
			}
else {
	if(k > 0){
		display_ptero(k, 3, ptero);
		k--;
	}
	else{
		k = 128;
	}
				if(k > 8 && k < 28 && l > 1){
					display_string(1, "GAME OVER");
					display_update();
					done = 1;
				}
			}
				IFSCLR(0) = 0x100;
			}
			timerdone = 1;
			}
     }
		}


		for(l = 0; l < jump; l++){

			timerdone = 1;

		while(timerdone){
			if (IFS(0) & 0x100){
		if (!done){
		for ( h = 0; h < 4; h++){

		for (g = 0; g < 16; g++){
			if (h > 0){
		b = ((~copy[g + (h * 16)]) >> 7) & 0x01;
		copy[g + (h * 16)] = ((~copy[g + (h * 16)] << 1 ) & 0xfe) | a[g]  ;
		a[g] = b;


			}
			else{
				a[g] = ((~copy[g + (h * 16)]) >> 7) & 0x01;
				copy[g + (h * 16)] = ((~copy[g + (h * 16)] << 1) | 0x01);

			}

		}
		}
		for (w = 0; w < 64; w++) {
		copy[w] = ~copy[w];
		}
		for(i = 0; i < 4; i++) {
			//	quicksleep1(19);
				DISPLAY_CHANGE_TO_COMMAND_MODE;

				spi_send_recv(0x22);
				spi_send_recv(i);

				spi_send_recv(0x21);
				spi_send_recv(x & 0xF);
				spi_send_recv(0x10 | ((x >> 4) & 0xF));

				DISPLAY_CHANGE_TO_DATA_MODE;

				for(j = 0; j < 16; j++){
						spi_send_recv(~copy[j + (i*16)]);
					}
			}
			if (iscactus == 1){
			if(k > 0){
				display_bottom(k, 8, 4, 3, cactus);
				k--;
			}
			else{
				k = 128;
			}

			if( k > 16 && k < 32 && l == 8){
				display_string(1, "GAME OVER");
				display_update();
				done = 1;
			}
		}
		else{
			if(k > 0){
				display_ptero(k, 3,  ptero);
				k--;
			}
			else{
				k = 128;
			}

			if(k > 8 && k < 25 && l < 14){
				display_string(1, "GAME OVER");
				display_update();
				done = 1;
			}
		}
			IFSCLR(0) = 0x100;
			}
			timerdone = 0;
		}
   }
	}
	}


int getsw( void ){
  return (PORTD >> 8) & 0x0f;
}

int getbtns( void ){
  return (PORTD >> 5) & 0x7;
}

int main(void) {
        /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */

	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;

	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	/* Set up input pins */
	//TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);

	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
  SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;
	TRISDSET = ~ 0x0fe0;

	init();
  IEC(0) = IEC(0) | 0x0100;
	IPC(2) = 4;

	IPC(3) = IPC(3) >> 24;
	IPC(3) = 4;


	display_init();
	display_string(0, "   Dino Runner");
	display_update();
	display_image(0, 0, 16, dino1);
	//display_image(0, dino);
	//display_image2(0, dino1);
	//display_string(0, "Dino Runner");
	//display_update();
		int duck = 0;
		int jump = 0;
		int timeoutcount = 0;
		//int r = (TMR4 >> 8);;
		//srand(TMR4 >> 8);
		//int r = rand() % 5;

		while(1){
			int sw = getsw();
			int btns = getbtns();

			while(!done){
			int sw = getsw();
			int btns = getbtns();


			if(IFS(0) & 0x100){

			if(sw == 0x8){
				display_image(1, 16, 128, dino);
			}

			if(btns & 2){
				display_bottom(16, 16, 3, 2, eraser );
				display_bottom(16, 16, 4, 3, dino_duck);
				duck = 1;
				if(k == 28 && iscactus == 1){
					display_string(1, "GAME OVER");
					display_update();
					done = 1;
				}
			}

			if(sw == 0xc){
				if(iscactus == 1){
					if(k>= 0){
						display_bottom(k, 8, 4, 3, cactus);
						k--;
					}
					else{
						k = 112;
						display_bottom(0, 8, 4, 3, eraser);
						//if(r < 3){
							iscactus = 0;
						//}
					}
				}

				else{
				if(k>= 0){
				//	display_ptero(k, 3, ptero);
				if(up){
				zig(k);
}else{
	zag(k);
}
					k--;


				}
				else{
					k = 120;
					display_ptero(0, 3, eraser);
					iscactus = 1;
				}
			}
			}
			IFSCLR(0) = 0x100;

}
			if(btns & 0x1){
				dino_jump(14,16);
				jump = 1;
			}

			if(k == 24 && jump == 0 && iscactus == 1){
				display_string(1, "GAME OVER");
				display_update();
				done = 1;
			}

			if(duck && btns == 0){
				display_image(1, 16, 16, dino2);
				duck = 0;
			}

			jump = 0;
	}

	if(sw == 0x1){
		done = 0;
		k = 128;
	}


		}


	return 0;
}
