// Definições e diretivas
#include <built_in.h>
#define TRUE 1  // Exemplo: while(TRUE) = while(1)

// Configuração dos pinos usados para o LCD
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;

/* Programa principal */
void main() {
    unsigned int leituraADC;      // Variável para armazenar o valor lido do ADC
    float valorTemperatura;       // Variável para guardar a temperatura calculada
    char texto[5];               // String para exibir a temperatura no LCD

    // Configuração do módulo ADC
    ADCON1 = 0b00001110;          // Configura os pinos AN0 como entrada analógica
    ADC_Init();                   // Inicializa o ADC

    // Configuração do display LCD
    Lcd_Init();                   // Inicializa o LCD
    Lcd_Cmd(_LCD_CLEAR);          // Limpa o display
    Lcd_Cmd(_LCD_CURSOR_OFF);     // Desliga o cursor do display

    while (1) {
        leituraADC = ADC_Get_Sample(0);  // Realiza a leitura do canal AN0 (RA0)

        // Converte o valor do ADC para temperatura (LM35: 10mV por °C)
        valorTemperatura = (leituraADC * 5.0 / 1023.0) * 100.0;  // Calcula a temperatura em °C

        FloatToStr(valorTemperatura, texto);  // Converte o valor float para string
        texto[5] = '\0';  // Ajusta a string para exibir apenas duas casas decimais

        Lcd_Out(1, 1, "Temp:");             // Exibe "Temp:" na primeira linha
        Lcd_Out(1, 7, texto);               // Exibe o valor da temperatura
        Lcd_Out(1, 12, "C");                // Exibe o símbolo de graus Celsius

        Delay_ms(500);                      // Aguarda 500 ms antes da próxima leitura
    }
}
