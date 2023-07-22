//////////////////////////////////////////////////
// Universidade Federal de Pernambuco - UFPE		  
// Residência Tecnológica em Software Automotivo      			  
// Módulo: SWT1 - RTOS e Sistemas Distribuídos
// Aluno: Bruno Carvalho do Nascimento Rosa 
//////////////////////////////////////////////////

#include "tpl_os.h"
#include "Arduino.h"
#include "board.h"

int velocidade;
int rotacao;
int marchaAtual;
int resolucaoM1 = 1;
static byte offsetM1 = -125;
float resolucaoM2 = 0.125;
static byte offsetM2 = 0;
float resolucaoM3 = 1/256;
static byte offsetM3 = 0;

// --------------------

unsigned int intTEST= 0xABCD;
unsigned int byteCOMPLETO =0x00;
unsigned int byteCOMPLETO2 =0x00;
byte bH = intTEST>>8;
byte bL = intTEST;

//Variavel para armazenar informacoes do frame recebido
unsigned char 		m1DLC = 0;
unsigned char 		m1DATA[8];
long unsigned int 	m1ID;

//Constroi um objeto MCP_CAN.
MCP_CAN CAN1(ECU2_CAN1_CS); 

void setup()
{	
	//Inicializa a interface serial: baudrate = 115200
	Serial.begin(115200);
	
	//Inicializa o controlador can : baudrate = 500K, clock=08MHz
	while(CAN1.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) != CAN_OK)
    {         
        delay(200);        
    }	
	Serial.println("Modulo CAN inicializado!");
	//Configura o controlador MCP2515 no modo normal.
	CAN1.setMode(MCP_NORMAL);  

}
//////////////////////////////////////////////////////////////////////////////////
//	Task M1    									   
//  Utilizada para receber todas as mensagens através da rede CAN			 					   
//  Taxa de transmissao e repeticao: 200 ms									   
//////////////////////////////////////////////////////////////////////////////////
TASK(M1) {
	// Criar 2 task´s uma só pra recebimento e outra para a impressão(simplifica)

		
		if(!digitalRead(ECU2_CAN1_INT)){
		//Lê os dados: mID = identificador, mDLC = comprimento, mDATA = dados do freame
		CAN1.readMsgBuf(&m1ID, &m1DLC, m1DATA);
		
			
			if((m1ID & 0x18F00503) == 0x18F00503){
			
				marchaAtual = (static_cast<int>(m1DATA[3])*resolucaoM1)+offsetM1; // Reconvertendo 
			}
			
			if((m1ID & 0x0CF00400) == 0x0CF00400){
			
				byteCOMPLETO =((m1DATA[3]<<8) | m1DATA[4]);
			
				rotacao = (static_cast<int>(byteCOMPLETO)*resolucaoM2)+offsetM2; // Reconvertendo

			}
			
			if((m1ID & 0x18FEF100) == 0x18FEF100){
				
				byteCOMPLETO2 =((m1DATA[1]<<8) | m1DATA[2]);
				
				velocidade = (static_cast<int>(byteCOMPLETO2)*resolucaoM3)+offsetM3; // Reconvertendo

			}
			
		}
	
}
//////////////////////////////////////////////////////////////////////////////////
//	Task M2    									   
//  Utilizada para enviar as informações obtidas nas leituras				 					   
//  Taxa de transmissao e repeticao: 100 ms									   
//////////////////////////////////////////////////////////////////////////////////
TASK(M2) {
				

		Serial.print("m1DATA: ");
		for (int i = 0; i < m1DLC; i++) {
			Serial.print(m1DATA[i], HEX);
			Serial.print(" ");
		}
			Serial.println();
	
}