//////////////////////////////////////////////////
// Universidade Federal de Pernambuco - UFPE		  
// Residência Tecnológica em Software Automotivo      			  
// Módulo: SWT1 - RTOS e Sistemas Distribuídos
// Aluno: Bruno Carvalho do Nascimento Rosa 
//////////////////////////////////////////////////

#include "tpl_os.h"
#include "Arduino.h"
#include "board.h"

//Macro para definicoes
#define ETC2_ID			0x18F00503
#define ETC2_DLC			8
#define ETC2_EXT_FRAME		1

int valor;
int resolucao = 1;
float valorConvertido = 0;
int offset = -125;
int ultimoValor;

//Variavel que armazena o FRAME_DATA
unsigned char ETC2_data[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

//Constroi um objeto MCP_CAN e configura o chip selector para o pino 10.
MCP_CAN CAN1(ECU4_CAN1_CS);  

void setup()
{
	//Inicializa a interface serial: baudrate = 115200
	Serial.begin(115200);
	
	//Inicializa o controlador can : baudrate = 250K, clock=8MHz
	while(CAN1.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) != CAN_OK) 
    {         
        delay(200);        
    }
	Serial.println("MCP2515 can_send inicializado com sucesso!");
	//Modifica para o modo normal de operação
	CAN1.setMode(MCP_NORMAL);
}
//////////////////////////////////////////////////////////////////////////////////
//	Task M1   			    									   
//  Utilizada enviar as mensagens na rede CAN sobre a marcha atual					 					   
//  Taxa de transmissao e repeticao: 200 ms									   
//////////////////////////////////////////////////////////////////////////////////
TASK(M1)
{
	static byte ret = 0;
	
	//Envia mensagem para o barramento
	ret=CAN1.sendMsgBuf(ETC2_ID,ETC2_EXT_FRAME,ETC2_DLC,ETC2_data);
	if (ret==CAN_OK){
		Serial.println(valor);
	}
	else if (ret == CAN_SENDMSGTIMEOUT){
		
	}
	else {
	
	}
	
	TerminateTask();
}
//////////////////////////////////////////////////////////////////////////////////
//	Task M2    									   
//  Utilizada para enviar a marcha do motor para a ECU do motor e para o ICM através da rede CAN				 					   
//  Taxa de transmissao e repeticao: 100 ms									   
//////////////////////////////////////////////////////////////////////////////////
TASK(M2) {
	//Lê as mensagens no barramento

	if (Serial.available() > 0) {  // Verifica se há dados disponíveis na porta serial 
		valor = Serial.parseInt();  // Lê o valor recebido da porta serial
		valorConvertido = (valor * (1/resolucao)) - offset;
			if (valor != 0){
				ultimoValor = valorConvertido;				
				ETC2_data[3] = static_cast<unsigned char>(valorConvertido);
			} else {
				ETC2_data[3] = static_cast<unsigned char>(ultimoValor);
			}
			Serial.read();
		} else {
			ETC2_data[3] = static_cast<unsigned char>(ultimoValor);
		}
	Serial.read();
}