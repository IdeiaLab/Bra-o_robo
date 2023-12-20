/***************************
  IdeiaLab codigo para o braço robo, vesão Diamante (1.0)
  Data da ultima alteração 29.05.2023 ( versão 100% automatica com Rx - TX)
***************************/

// BIBLIOTECAS
#include <Servo.h> // inclui biblioteca do servomotor

// OBJETOS
Servo levante, base, avanco, garra; // "nomeia" os servos

//FUNÇÃO
void movimento (int qualServo, int pos_final); // função para movimentar o servo


//VARIAVEIS DE "MEMORIA" - ANGULOS POSIÇÃO NEUTRA
int memoria_angulo_levante = 85; // recomendação -> pos_inicial =  85 , pos_alta_max = 160 , pos_baixa_min = 63
int memoria_angulo_base = 94;    // recomendação -> pos_inicial =  94 , pos_livre = entre 2 a 188
int memoria_angulo_avanco = 90;  // recomendação -> pos_inicial =  90 , pos_avançada_max = 175 , pos_recuo_min = 33
int memoria_angulo_garra = 92;   // recomendação -> pos_inicial =  90(fechada),pos_fechada_max = 93, pos_aberta_max_recomendada = 120,pos_aberta_max =  137 ,

// CRONTROLE LOGICO
bool Ja_li = false; // Variável de controle logico

// CRONTROLE DE VELOCIDADE
// obs -- recomendação usar entre 5 (rapido) a 100(muito lento).
int velocidade_do_servo = 10; // referente a velociade que os apm são adicionados ou subtraidos na for,o limitante e o delay.
int atraso_final = 400; // delay no final de cada ativação da funçaõ movimento


void setup() {

  // SERIAL
  Serial.begin( 9600) ;

  // PINOS - SERVOS
  levante.attach(3); // servo da esquerda no pino 3 ( referencial: garra alinhada com o arduino)
  base.attach(6);    // servo de baixo no pino 5  ( referencial: o solo)
  avanco.attach(11);  // servo da direita no pino 6 ( referencial: garra alinhada com o arduino)
  garra.attach(9);   // servo de cima no pino 9  ( referencial: o solo)

  //POSIÇÃO INICIAL - SERVOS
  levante.write(memoria_angulo_levante); //defini a posição inicial do servo levante no angulo 85°
  base.write(memoria_angulo_base);    //defini a posição inicial do servo base no angulo 92°
  avanco.write(memoria_angulo_avanco);  //defini a posição inicial do servo avanco no angulo 90°
  garra.write(memoria_angulo_garra);   //defini a posição inicial do servo garra no angulo 92°

}

void loop() {

  if (Serial.available()) { // Verifica se há dados disponíveis para leitura
    char RD_carta = Serial.read(); // Lê o caractere recebido

    if (RD_carta == 'r' && !Ja_li) {
      //diretia
      movimento (4, 115); // garra
      movimento (1, 109); // levate
      movimento (3, 165); // avanco
      movimento (4, 100);  // garra  ***alterado de 90 pra 100***
      movimento (3, 100); // avanco
      movimento (1, 155); // levante ***alterado de 175 para 155***
      movimento (2, 18);  // base  *** direita  ***
      movimento (4, 115); // garra
      movimento (2, 94); // base
      movimento (1, 85); // levate
      movimento (3, 90); // avanco
      Serial.println("a"); // Envia uma mensagem

    }

    else if (RD_carta == 'g' && !Ja_li) {
      //esquerda
      movimento (4, 115); // garra
      movimento (1, 109); // levate
      movimento (3, 165); // avanco
      movimento (4, 100);  // garra  ***alterado de 90 pra 100***
      movimento (3, 100); // avanco
      movimento (1, 155); // levante ***alterado de 175 para 155***
      movimento (2, 155);  // base  ****Esquerda****
      movimento (4, 115); // garra
      movimento (2, 94); // base
      movimento (1, 85); // levate
      movimento (3, 90); // avanco

    }
    Ja_li = true; // Define a variável de controle como verdadeira
  }

  // Reinicia a variável de controle para permitir uma nova execução
  if (!Serial.available() && Ja_li) {
    Ja_li = false;
  }
}

//OBESERVAÇÕES
/* Para facilitar vou referenciar os servos na função abaixo
   por numeros sendo:
   levante = 1
   base = 2
   avanco = 3
   garra = 4
*/

void movimento ( int qualServo, int pos_final) {

  // Bloco de verificação do servo e angulo da memoria
  int memoria_angulo_temporaria;

  if ( qualServo == 1) {
    // atribuir a temporaria o valor da fixa levante - angulo
    memoria_angulo_temporaria = memoria_angulo_levante;
  }
  else if ( qualServo == 2) {
    // atribuir a temporaria o valor da fixa base - angulo
    memoria_angulo_temporaria = memoria_angulo_base;
  }
  else if ( qualServo == 3) {
    // atribuir a temporaria o valor da fixa avanco - angulo
    memoria_angulo_temporaria = memoria_angulo_avanco;
  }
  else if ( qualServo == 4) {
    // atribuir a temporaria o valor da fixa garra - angulo
    memoria_angulo_temporaria = memoria_angulo_garra;
  }

  // Bloco de verificação angulo inicial e angulo final
  int sentido_angulo;

  if ( memoria_angulo_temporaria < pos_final ) {
    // movimento de avanço, angulo final maior que angulo inicial
    sentido_angulo = 1;
  }
  else if ( memoria_angulo_temporaria > pos_final ) {
    // movimento de retorno, angulo final menor que angulo inicial
    sentido_angulo = -1;
  }
  else {
    sentido_angulo = 0;
  }

  // Bloco de ação
  int caixa_de_apm;
  // obs -> apm = angulo de posição mutavel
  // AVANÇO
  if ( sentido_angulo == 1) {
    if ( qualServo == 1) {
      for ( int apm = memoria_angulo_temporaria; apm < pos_final; apm++) {
        levante.write(apm);
        delay(velocidade_do_servo);
        caixa_de_apm = apm ;
      }
      memoria_angulo_levante = caixa_de_apm ;
    }
    else if ( qualServo == 2) {
      for ( int apm = memoria_angulo_temporaria; apm < pos_final; apm++) {
        base.write(apm);
        delay(velocidade_do_servo);
        caixa_de_apm = apm ;
      }
      memoria_angulo_base = caixa_de_apm;
    }
    else if ( qualServo == 3) {
      for ( int apm = memoria_angulo_temporaria; apm < pos_final; apm++) {
        avanco.write(apm);
        delay(velocidade_do_servo);
        caixa_de_apm = apm ;
      }
      memoria_angulo_avanco = caixa_de_apm;
    }
    else if ( qualServo == 4) {
      for ( int apm = memoria_angulo_temporaria; apm < pos_final; apm++) {
        garra.write(apm);
        delay(velocidade_do_servo);
        caixa_de_apm = apm;
      }
      memoria_angulo_garra = caixa_de_apm;
    }
    delay(atraso_final);
  }
  //RETORNO
  if ( sentido_angulo == -1) {
    if ( qualServo == 1) {
      for ( int apm = memoria_angulo_temporaria; apm > pos_final; apm--) {
        levante.write(apm);
        delay(velocidade_do_servo);
        caixa_de_apm = apm ;
      }
      memoria_angulo_levante = caixa_de_apm;
    }
    else if ( qualServo == 2) {
      for ( int apm = memoria_angulo_temporaria; apm > pos_final; apm--) {
        base.write(apm);
        delay(velocidade_do_servo);
        caixa_de_apm = apm ;
      }
      memoria_angulo_base = caixa_de_apm;
    }
    else if ( qualServo == 3) {
      for ( int apm = memoria_angulo_temporaria; apm > pos_final; apm--) {
        avanco.write(apm);
        delay(velocidade_do_servo);
        caixa_de_apm = apm ;
      }
      memoria_angulo_avanco = caixa_de_apm;
    }
    else if ( qualServo == 4) {
      for ( int apm = memoria_angulo_temporaria; apm > pos_final; apm--) {
        garra.write(apm);
        delay(velocidade_do_servo);
        caixa_de_apm = apm ;
      }
      memoria_angulo_garra = caixa_de_apm;
    }
    delay(atraso_final);
  }
}
