/*
 * The_Safe.c
 *  Author: Mahmoud Ayman
 */ 


#include "Data_type.h"
#include "LCD_ECU.h"
#include "Keypad_ECU.h"
#include "EEPROM_MCAL.h"
#define  EEPROM_STATUS_LOCATION 0x03
#define  EEPROM_PASSWORD_LOCATION1 0x04
#define  EEPROM_PASSWORD_LOCATION2 0x05
#define  EEPROM_PASSWORD_LOCATION3 0x06
#define  EEPROM_PASSWORD_LOCATION4 0x07
#define  MAX_TRIES 3

u8 arr[4];

int main(void){
	u8 val=NOTPRESSED;
	u8 flag =0;
	u8 Tries = MAX_TRIES;
	keypad_vInit('D');
	LCD_vInit(Four_bit,High_Nibble,'A','B',2,'B',3,'B',4);
	if (EEPROM_Read(EEPROM_STATUS_LOCATION)==NOTPRESSED){
		LCD_vsend_string(Four_bit,High_Nibble,'A','B',2,'B',4,"Set Pass:");
		do {
			val = keypad_u8check_press('D');
		} while (val ==NOTPRESSED);
		LCD_vsend_char(Four_bit,High_Nibble,'A','B',2,'B',4,val);
		_delay_ms(500);
		LCD_Move_Cursor(Four_bit,High_Nibble,'A','B',2,'B',4,1,10);
		LCD_vsend_char(Four_bit,High_Nibble,'A','B',2,'B',4,0x2A);
		_delay_ms(500);
		EEPROM_Write(EEPROM_PASSWORD_LOCATION1,val);
		val=NOTPRESSED;
		do {
			val = keypad_u8check_press('D');
		} while (val ==NOTPRESSED);
		LCD_vsend_char(Four_bit,High_Nibble,'A','B',2,'B',4,val);
		_delay_ms(500);
		LCD_Move_Cursor(Four_bit,High_Nibble,'A','B',2,'B',4,1,11);
		LCD_vsend_char(Four_bit,High_Nibble,'A','B',2,'B',4,0x2A);
		_delay_ms(500);
		EEPROM_Write(EEPROM_PASSWORD_LOCATION2,val);
		val=NOTPRESSED;
		do {
			val = keypad_u8check_press('D');
		} while (val ==NOTPRESSED);
		LCD_vsend_char(Four_bit,High_Nibble,'A','B',2,'B',4,val);
		_delay_ms(500);
		LCD_Move_Cursor(Four_bit,High_Nibble,'A','B',2,'B',4,1,12);
		LCD_vsend_char(Four_bit,High_Nibble,'A','B',2,'B',4,0x2A);
		_delay_ms(500);
		EEPROM_Write(EEPROM_PASSWORD_LOCATION3,val);
		val=NOTPRESSED;
		do {
			val = keypad_u8check_press('D');
		} while (val ==NOTPRESSED);
		LCD_vsend_char(Four_bit,High_Nibble,'A','B',2,'B',4,val);
		_delay_ms(500);
		LCD_Move_Cursor(Four_bit,High_Nibble,'A','B',2,'B',4,1,13);
		LCD_vsend_char(Four_bit,High_Nibble,'A','B',2,'B',4,0x2A);
		_delay_ms(500);
		EEPROM_Write(EEPROM_PASSWORD_LOCATION4,val);
		val=NOTPRESSED;
		EEPROM_Write(EEPROM_STATUS_LOCATION,0x00);
		
	}
	while(0==flag){
		arr[0]=arr[1]=arr[2]=arr[3]=NOTPRESSED;
		LCD_clear_screen(Four_bit,High_Nibble,'A','B',2,'B',4);
		LCD_vsend_string(Four_bit,High_Nibble,'A','B',2,'B',4,"Enter pass:");
		
		do{
			arr[0]=keypad_u8check_press('D');
		}while(arr[0]==NOTPRESSED);
		LCD_vsend_char(Four_bit,High_Nibble,'A','B',2,'B',4,arr[0]);
		_delay_ms(500);
		LCD_Move_Cursor(Four_bit,High_Nibble,'A','B',2,'B',4,1,12);
		LCD_vsend_char(Four_bit,High_Nibble,'A','B',2,'B',4,0x2A);
		_delay_ms(500);
		
		do{
			arr[1]=keypad_u8check_press('D');
		}while(arr[1]==NOTPRESSED);
		LCD_vsend_char(Four_bit,High_Nibble,'A','B',2,'B',4,arr[1]);
		_delay_ms(500);
		LCD_Move_Cursor(Four_bit,High_Nibble,'A','B',2,'B',4,1,13);
		LCD_vsend_char(Four_bit,High_Nibble,'A','B',2,'B',4,0x2A);
		_delay_ms(500);
		
		do{
			arr[2]=keypad_u8check_press('D');
		}while(arr[2]==NOTPRESSED);
		LCD_vsend_char(Four_bit,High_Nibble,'A','B',2,'B',4,arr[2]);
		_delay_ms(500);
		LCD_Move_Cursor(Four_bit,High_Nibble,'A','B',2,'B',4,1,14);
		LCD_vsend_char(Four_bit,High_Nibble,'A','B',2,'B',4,0x2A);
		_delay_ms(500);
		
		do{
			arr[3]=keypad_u8check_press('D');
		}while(arr[3]==NOTPRESSED);
		LCD_vsend_char(Four_bit,High_Nibble,'A','B',2,'B',4,arr[3]);
		_delay_ms(500);
		LCD_Move_Cursor(Four_bit,High_Nibble,'A','B',2,'B',4,1,15);
		LCD_vsend_char(Four_bit,High_Nibble,'A','B',2,'B',4,0x2A);
		_delay_ms(500);
		
		if (EEPROM_Read(EEPROM_PASSWORD_LOCATION1)==arr[0]  && EEPROM_Read(EEPROM_PASSWORD_LOCATION2)==arr[1]  && EEPROM_Read(EEPROM_PASSWORD_LOCATION3)==arr[2]  && EEPROM_Read(EEPROM_PASSWORD_LOCATION4)==arr[3]){
			LCD_clear_screen(Four_bit,High_Nibble,'A','B',2,'B',4);
			LCD_vsend_string(Four_bit,High_Nibble,'A','B',2,'B',4,"Right Password");
			LCD_Move_Cursor(Four_bit,High_Nibble,'A','B',2,'B',4,2,1);
			LCD_vsend_string(Four_bit,High_Nibble,'A','B',2,'B',4,"The safe is open");
			flag=1;
		}else{
			Tries-=1;
			if (Tries > 0){
				LCD_clear_screen(Four_bit,High_Nibble,'A','B',2,'B',4);
				LCD_vsend_string(Four_bit,High_Nibble,'A','B',2,'B',4,"Wrong Password");
				_delay_ms(1000);
				LCD_clear_screen(Four_bit,High_Nibble,'A','B',2,'B',4);
				LCD_vsend_string(Four_bit,High_Nibble,'A','B',2,'B',4,"Tries left:");
				LCD_display_number(Four_bit,High_Nibble,'A','B',2,'B',4,Tries);
				_delay_ms(1000);
			}else{
				LCD_clear_screen(Four_bit,High_Nibble,'A','B',2,'B',4);
				LCD_vsend_string(Four_bit,High_Nibble,'A','B',2,'B',4,"Wrong Password");
				LCD_Move_Cursor(Four_bit,High_Nibble,'A','B',2,'B',4,2,1);
				LCD_vsend_string(Four_bit,High_Nibble,'A','B',2,'B',4,"The safe closed");
				_delay_ms(1000);
				LCD_clear_screen(Four_bit,High_Nibble,'A','B',2,'B',4);
				LCD_vsend_string(Four_bit,High_Nibble,'A','B',2,'B',4,"Access denied");
				LCD_Move_Cursor(Four_bit,High_Nibble,'A','B',2,'B',4,2,1);
				LCD_vsend_string(Four_bit,High_Nibble,'A','B',2,'B',4,"HHH 7ramy");
				_delay_ms(1000);
				LCD_clear_screen(Four_bit,High_Nibble,'A','B',2,'B',4);
				LCD_vsend_string(Four_bit,High_Nibble,'A','B',2,'B',4,"ya 7ramy ya wis5");
				LCD_Move_Cursor(Four_bit,High_Nibble,'A','B',2,'B',4,2,1);
				LCD_vsend_string(Four_bit,High_Nibble,'A','B',2,'B',4,"Help ya gd3aan");
				break;
			}
		}
	}
    while(1)
    {
        //TODO:: Please write your application code 
    }
}