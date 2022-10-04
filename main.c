/*
 * main.c
 * Created: 4/8/2022 12:09:55 PM
 */ 

#include <xc.h>
#include <stdio.h>
#include <math.h>
#include "lcd.h"
#include "avr.h"

int year = 0;
unsigned char month = 00;
unsigned char day = 00;
unsigned char hour = 00;
unsigned char minute = 00;
unsigned char second = 00;
int apm = 2;
int switch1 = 0;
int click = 0;


typedef struct {
	int year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
	int apm;
} DateTime;

void init_dt(DateTime *dt) {
	dt->year = 2022;
	dt->month = 01;
	dt->day = 01;
	dt->hour = 00;
	dt->minute = 00;
	dt->second = 00;
	dt->apm= 2;
}



int advance_dt(DateTime *dt, int s) {
	++dt->second;
	
	if(dt->second>60||dt->minute>=60||dt->hour>=24||(dt->hour>=12 && dt->apm ==0)||(dt->hour>=13 && dt->apm == 1)||dt->month>12){
		return 1;
	}
	
	switch(dt->month)
	{
		
		case 1:
			if(dt->day>=32){
				return 1;
			}
		case 2:
		//for leap year
			if(dt->year % 4 == 0){
				if(dt->day >= 30){
					return 1;
				}
				
			}
			else{
				if(dt->day>=29){
					return 1;
				}
				
			}
		case 3:
			if(dt->day>=32){
				return 1;
			}
		case 4:
			if(dt->day >= 31){
				return 1;
			}
		case 5:
			if(dt->day>=32){
				return 1;
			}
		case 6:
			if(dt->day >= 31){
				return 1;
			}
		case 7:
			if(dt->day>=32){
				return 1;
			}
		case 8:
			if(dt->day>=32){
				return 1;
			}
		case 9:
			if(dt->day >= 31){
				return 1;
			}
		case 10:
			if(dt->day>=32){
				return 1;
			}
		case 11:
			if(dt->day >= 31){
				return 1;
			}
		case 12:
			if(dt->day>=32){
				return 1;
			}
	}
	if (dt->second >= 60) {
		// Increase minute and check.
		// Repeat process as needed.
		dt->second = 0;
		dt->minute++;
		if(dt->minute>=60){
			dt->minute = 0;
			dt->hour++;
			if(dt->hour >= 12 && dt->apm == 0){
				dt->apm = 1;
			}
			else if(dt->hour >= 13 && dt->apm == 1){
				dt->hour = 1;
			}
			else if(dt->hour >= 24 || (dt->hour >= 12 && dt->apm == 1)){
				if(dt->apm == 1){
					dt->apm = 0;
				}
				dt->day++;
				dt->hour = 0;
				switch(dt->month)
				{
					case 1:
						if(dt->day > 31){
							dt->day = 1;
							dt->month++;
							if(dt->month>12){
								dt->month =1;
								dt->year++;
							}
						}
					case 2:
						//for leap year
						if(dt->year % 4 == 0){
							if(dt->day >= 30){
								dt->month++;
								dt->day = 1;
							}
						}
						else{
							if(dt->day > 28){
								dt->month++;
								dt->day = 1;
							}
						}
					case 3:
						if(dt->day > 31){
							dt->day = 1;
							dt->month++;
							if(dt->month>12){
								dt->month =1;
								dt->year++;
							}
						}
					case 4:
						if(dt->day >= 31){
							dt->month++;
							dt->day = 1;
						}
					case 5:
						if(dt->day > 31){
							dt->day = 1;
							dt->month++;
							if(dt->month>12){
								dt->month =1;
								dt->year++;
							}
						}
					case 6:
						if(dt->day >= 31){
							dt->month++;
							dt->day = 1;
						}
					case 7:
						if(dt->day > 31){
							dt->day = 1;
							dt->month++;
							if(dt->month>12){
								dt->month =1;
								dt->year++;
							}
						}
					case 8:
						if(dt->day > 31){
							dt->day = 1;
							dt->month++;
							if(dt->month>12){
								dt->month =1;
								dt->year++;
							}
						}
					case 9:
						if(dt->day >= 31){
							dt->month++;
							dt->day = 1;
						}
					case 10:
						if(dt->day > 31){
							dt->day = 1;
							dt->month++;
							if(dt->month>12){
								dt->month =1;
								dt->year++;
							}
						}
					case 11:
						if(dt->day >= 31){
							dt->month++;
							dt->day = 1;
						}
					case 12:
						if(dt->day > 31){
							dt->day = 1;
							dt->month++;
							if(dt->month>12){
								dt->month =1;
								dt->year++;
							}
						}
					
				}
			}
		}
	}
	return 0;
}

void print_error(const DateTime *dt, int s){
	char buf1[20];
	// Print date on top row.
	lcd_pos(0, 0);
	sprintf(buf1, "Error            ");
	lcd_puts2(buf1);
	char buf4[25];
	lcd_pos(1, 0);
	sprintf(buf4, "                    ");
	lcd_puts2(buf4);
	avr_wait(5000);
	print_dt(dt, s);
}
void print_dt(const DateTime *dt, int s) {
	if(s == 0){
		char buf1[25];
		// Print date on top row.
		lcd_pos(0, 0);
		sprintf(buf1, "%04d-%02d-%02d",
		dt->year,
		dt->month,
		dt->day);
		lcd_puts2(buf1);
	
		// Do similar thing to print time on bottom row.
		char buf2[25];
		lcd_pos(1, 0);
		sprintf(buf2, "%02d:%02d:%02d   ",
		dt->hour,
		dt->minute,
		dt->second);
		lcd_puts2(buf2);
	}
	else{
		char buf3[17];
		// Print date on top row.
		lcd_pos(0, 0);
		sprintf(buf3, "%04d-%02d-%02d   ",
		dt->year,
		dt->month,
		dt->day);
		lcd_puts2(buf3);
				
		// Do similar thing to print time on bottom row.
		char buf4[20];
		lcd_pos(1, 0);
		if(dt->apm == 0){
			sprintf(buf4, "%02d:%02d:%02d AM",
			dt->hour,
			dt->minute,
			dt->second);
		}
		else if(dt->apm == 1){
			sprintf(buf4, "%02d:%02d:%02d PM",
			dt->hour,
			dt->minute,
			dt->second);
		}

		lcd_puts2(buf4);
	}
}
int is_pressed(int r, int c) {
	// Set all 8 GPIOs to N/C
	DDRC = 0;
	PORTC = 0;
	// Set r to "0"
	SET_BIT(DDRC, r);
	CLR_BIT(PORTC, r);
	SET_BIT(PORTC, c+4);
	avr_wait(1);
	// Set c to "w1"
	if (GET_BIT(PINC, c+4) == 0) {
		return 1;
	}
	return 0;
}

int get_key() {
	int i, j;
	for (i=0; i < 4; i++) {
		for (j=0; j < 4; j++) {
			if (is_pressed(i, j)) {
				return 4 * i + j + 1;
			}
		}
	}
	return 0;
}
typedef enum {
	A, As, B, C, Cs, D, Ds, Ee, F, Fs, G, Gs
} Note;

typedef enum {
	W, H, Q, Ei
} Duration;

typedef struct {
	Note note;
	Duration duration;
} PlayingNote;

int play_song(const PlayingNote song[], int length) {
	int i;
	for (i = 0; i < length; i++) {
		play_note(&song[i]);
		int k2;
		k2 = get_key();
		int row2 = (k2-1)/4;
		int col2 = (k2-1)%4;
		if(row2 == 1 && col2 == 3){
			return 1;
		}
		if(row2 == 0 && col2 == 1){
			return 2;
		}
		else if(row2 == 0 && col2 == 0){
			return 3;
		}
	}
	return 0;
}


void wait(unsigned short msec)
{
	TCCR0 = 2;
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.0001);
		SET_BIT(TIFR, TOV0);
		WDR();
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}

void play_note(const PlayingNote* note) {
	int i, k;
	unsigned short TH, TL;
	if(note->duration == W){
		k = 4;
	}
	else if(note->duration == H){
		k = 2;
	}
	else if(note->duration == Q){
		k = 1;
	}
	else if(note->duration == Ei){
		k = 0;
	}
	float P;
	if(note->note == A){
		P = 1/(pow(2, (float)0/12)*220);
	}
	else if(note->note == As){
		P = 1/(pow(2, (float)1/12)*220);
	}
	else if(note->note == B){
		P = 1/(pow(2, (float)2/12)*220);
	}
	else if(note->note == C){
		P = 1/(pow(2, (float)3/12)*220);
	}
	else if(note->note == Cs){
		P = 1/(pow(2, (float)4/12)*220);
	}
	else if(note->note == D){
		P = 1/(pow(2, (float)5/12)*220);
	}
	else if(note->note == Ds){
		P = 1/(pow(2, (float)6/12)*220);
	}
	else if(note->note == Ee){
		P = 1/(pow(2, (float)7/12)*220);
	}
	else if(note->note == F){
		P = 1/(pow(2, (float)8/12)*220);
	}
	else if(note->note == Fs){
		P = 1/(pow(2, (float)9/12)*220);
	}
	else if(note->note == G){
		P = 1/(pow(2, (float)10/12)*220);
	}
	else if(note->note == Gs){
		P = 1/(pow(2, (float)11/12)*220);
	}
	TH = round(P/2*10000);
	TL = round(P/2*10000);
	k = k/P;
	for (i = 0; i < k; i++) {
		SET_BIT(PORTB, 3);
		wait(TH);
		CLR_BIT(PORTB, 3);
		wait(TL);
	}
}

int get_sample() {
	ADMUX = 0b01000000;
	ADCSRA = 0b11000000;
	while (GET_BIT(ADCSRA, 6));
	return ADC;
}

int get_sample1() {
	ADMUX = 0b01000001;
	ADCSRA = 0b11000111;
	while (GET_BIT(ADCSRA, 6));
	return ADC;
}

int getPassword(){
	int final_result = 0;
	int count = 0;
	int display_col = 0;
	while(count < 4){
		avr_wait(500);
		int k;
		k = get_key();
		int row = (k-1)/4;
		int col = (k-1)%4;
		if(row == 0 && col == 0){
			lcd_pos(1,display_col);
			lcd_put('1');
			final_result= final_result*10+1;
			display_col++;
			count++;
		}
		else if(row == 0 && col == 1){
			lcd_pos(1,display_col);
			lcd_put('2');
			final_result= final_result*10+2;
			display_col++;
			count++;
		}
		else if(row == 0 && col == 2){
			lcd_pos(1,display_col);
			lcd_put('3');
			final_result= final_result*10+3;
			display_col++;
			count++;
		}
		else if(row == 1 && col == 0){
			lcd_pos(1,display_col);
			lcd_put('4');
			final_result= final_result*10+4;
			display_col++;
			count++;
		}
		else if(row == 1 && col == 1){
			lcd_pos(1,display_col);
			lcd_put('5');
			final_result= final_result*10+5;
			display_col++;
			count++;
		}
		else if(row == 1 && col == 2){
			lcd_pos(1,display_col);
			lcd_put('6');
			final_result= final_result*10+6;
			display_col++;
			count++;
		}
		else if(row == 2 && col == 0){
			lcd_pos(1,display_col);
			lcd_put('7');
			final_result= final_result*10+7;
			display_col++;
			count++;
		}
		else if(row == 2 && col == 1){
			lcd_pos(1,display_col);
			lcd_put('8');
			final_result= final_result*10+8;
			display_col++;
			count++;
		}
		else if(row == 2 && col == 2){
			lcd_pos(1,display_col);
			lcd_put('9');
			final_result= final_result*10+9;
			display_col++;
			count++;
		}
		else if(row == 3 && col == 1){
			lcd_pos(1,display_col);
			lcd_put('0');
			final_result= final_result*10;
			display_col++;
			count++;
		}
	}
	return final_result;
}

int main () {
	avr_init();
	lcd_init();
	DDRB = 0x0F;
	char buf[20];
	int p1 = 0;
	int p2 = 0;
	int p3 = 0;
	int count = 0;
	lcd_pos(0, 0);
	sprintf(buf, "enter commend    ");
	lcd_puts2(buf);
	lcd_pos(1,0);
	int mpw = 1000;
	PlayingNote incorrect_sound[] ={
		{A, W},
		{A, W}
	};
	PlayingNote correct_sound[] = {
		{C, W},
		{C, W}
	};
	
	PlayingNote locked_sound[] = {
		{B, W},
		{A, W}
	};
	
	while (1) {
		int valid_pass = 1;
		int number = -1;
		int password = -1;
		avr_wait(500);
		int k1;
		k1 = get_key();
		int row1 = (k1-1)/4;
		int col1 = (k1-1)%4;
		if(row1 == 1 && col1 == 3){
			lcd_pos(0, 0);
			sprintf(buf, "Set password      ");
			lcd_puts2(buf);
			password = getPassword();
			
			if(p1 == password || p2 == password || p3 == password){
				valid_pass = 0;
				lcd_pos(0, 0);
				sprintf(buf, "Old password        ");
				lcd_puts2(buf);
				lcd_pos(1,0);
				sprintf(buf, "                   "      );
				lcd_puts2(buf);
				avr_wait(5000);
				lcd_pos(0, 0);
				sprintf(buf, "Enter commend      ");
				lcd_puts2(buf);
			}
			
			if(valid_pass == 1){
				p1 = p2;
				p2 = p3;
				p3 = password;
				lcd_pos(0, 0);
				sprintf(buf, "Password set       ");
				lcd_puts2(buf);
				lcd_pos(1,0);
				sprintf(buf, "                   "      );
				lcd_puts2(buf);
				avr_wait(5000);
				lcd_pos(0, 0);
				sprintf(buf, "Enter commend      ");
				lcd_puts2(buf);
				//lcd_pos(1,0);
				//sprintf(buf, "       %d, %d            ", target[0], index);
				//lcd_puts2(buf);
		
			}
		}
		
		//lcd_pos(1,0);
		//sprintf(buf, "       %d, %d            ", target[0], index);
		//lcd_puts2(buf);
		
		//lock the system
		else if(row1 == 0 && col1 == 3){
			int N = sizeof(locked_sound)/sizeof(locked_sound[0]);
			play_song(locked_sound, N);
			lcd_pos(0, 0);
			sprintf(buf, "System locked      ");
			lcd_puts2(buf);
			avr_wait(3000);
			lcd_pos(0, 0);
			sprintf(buf, "Enter password      ");
			lcd_puts2(buf);
			int false_count = 0;
			while(1){
				number = getPassword();
				//lcd_pos(0, 0);
				//sprintf(buf, "%d, %d                    ", target[currindex], currindex);
				//lcd_puts2(buf);
				if(number != p3){
					false_count++;
					if(false_count == 3){
						int N = sizeof(locked_sound)/sizeof(locked_sound[0]);
						play_song(locked_sound, N);
						int second = 60;
						lcd_pos(0, 0);
						sprintf(buf, "locked %d secs         ", second);
						lcd_puts2(buf);
						lcd_pos(1, 0);
						sprintf(buf, "                        ");
						while(second >0){
							avr_wait(1000);
							lcd_pos(0, 0);
							sprintf(buf, "locked %d secs         ", second--);
							lcd_puts2(buf);
							lcd_pos(1, 0);
							sprintf(buf, "                        ");
							lcd_puts2(buf);
							//manager mode
							int k2;
							k2 = get_key();
							int row2 = (k2-1)/4;
							int col2 = (k2-1)%4;
							if(row2 == 2 && col2 ==3){
								lcd_pos(0, 0);
								sprintf(buf, "Enter password          ");
								lcd_puts2(buf);
								lcd_pos(1, 0);
								sprintf(buf, "                        ");
								lcd_puts2(buf);
								int manager_pw = getPassword();
								if(manager_pw == mpw){
									int N = sizeof(correct_sound)/sizeof(correct_sound[0]);
									play_song(correct_sound, N);
									lcd_pos(0, 0);
									sprintf(buf, "correct                 ");
									lcd_puts2(buf);
									lcd_pos(1, 0);
									sprintf(buf, "                        ");
									lcd_puts2(buf);
									avr_wait(3000);
									break;
								}
								else{
									int N = sizeof(incorrect_sound)/sizeof(incorrect_sound[0]);
									play_song(incorrect_sound, N);
									lcd_pos(0, 0);
									sprintf(buf, "incorrect               ");
									lcd_puts2(buf);
									lcd_pos(1, 0);
									sprintf(buf, "                        ");
									lcd_puts2(buf);
									avr_wait(3000);
								}
							}
						}
						lcd_pos(0, 0);
						sprintf(buf, "Enter command           ");
						lcd_puts2(buf);
						lcd_pos(1, 0);
						sprintf(buf, "                        ");
						lcd_puts2(buf);
						break;
					}
					else{
						int N = sizeof(incorrect_sound)/sizeof(incorrect_sound[0]);
						play_song(incorrect_sound, N);
						lcd_pos(0, 0);
						sprintf(buf, "incorrect           ");
						lcd_puts2(buf);
						lcd_pos(1, 0);
						sprintf(buf, "                        ");
						lcd_puts2(buf);
						avr_wait(3000);
						lcd_pos(0, 0);
						sprintf(buf, "Enter password      ");
						lcd_puts2(buf);
						lcd_pos(1, 0);
						sprintf(buf, "                        ");
						lcd_puts2(buf);
					}

					

				}
				else{

					int N = sizeof(correct_sound)/sizeof(correct_sound[0]);
					play_song(correct_sound, N);
					lcd_pos(0, 0);
					sprintf(buf, "correct password      ");
					lcd_puts2(buf);
					lcd_puts2(buf);
					lcd_pos(1,0);
					sprintf(buf, "                         ");
					
					


					

					avr_wait(5000);
					lcd_pos(0, 0);
					sprintf(buf, "Enter commend      ");
					lcd_puts2(buf);
					lcd_pos(1, 0);
					sprintf(buf, "                        ");
					lcd_puts2(buf);
					break;
				}
			}

		}


		
	}
	return 0;
}