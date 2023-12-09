#include "Adafruit_LEDBackpack.h"

Adafruit_7segment dis = Adafruit_7segment();

int horas = 0;
int minutos = 0;
int segundos = 0;

const int pinoAcHora = 2;
const int pinoDecHora = 3;
const int pinoAcMin = 4;
const int pinoDecMin = 5;

const int pinoBuzzer = 6;
const int pinoPararAlarme = 7;
const int pinoDefinirAlarme = 8;
const int pinoDefinirMusica = 9;

int botaoAcHora;
int botaoDecHora;
int botaoAcMin;
int botaoDecMin;

int botaoPararAlarme;
int botaoDefinirAlarme;
int botaoDefinirMusica;


const int notaA = 262;
const int notaB = 294;
const int notaBb = 142.56; 
const int notaC = 330;
const int notaD = 394;
const int notaE = 198;
const int notaF = 440;
const int notaG = 495;

  int melody[] = {
    notaE, notaD, notaE, notaD, notaE, notaB, notaD, notaC, notaA, 0, notaC, notaE, notaA, notaB, 0, 
    notaE, notaD, notaE, notaD, notaE, notaB, notaD, notaC, notaA, 0, notaC, notaE, notaA, notaB, 0, 
    notaE, notaC, notaD, notaE, notaG, notaF, notaE, notaD, notaC, 0, notaE, notaG, notaA, 0, notaF,
    notaE, notaD, notaE, notaD, notaE, notaB, notaD, notaC, notaA, 0, notaC, notaE, notaA, notaB, 0
  };

  int tempo[] = {
    8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4, 
    8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4, 
    8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 8, 4, 4,
    8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4
  };

  int melodyMario[] = {
    notaE, notaE, 0, notaE, 0, notaC, notaE, 0, notaG, 0, 0, 0, notaG, 0, 0, 0,
    notaC, 0, 0, notaG, 0, 0, notaE, 0, 0, notaA, 0, notaB, 0, notaBb, 0, notaA,
    notaG, 0, notaE, notaG, notaA, 0, notaF, notaG, 0, notaE, 0, notaC, notaD, notaB, 0, 0,
    notaC, 0, 0, notaG, 0, 0, notaE, 0, 0, notaA, 0, notaB, 0, notaBb, 0, notaA,
    notaG, 0, notaE, notaG, notaA, 0, notaF, notaG, 0, notaE, 0, notaC, notaD, notaB, 0, 0
  };

  int tempoMario[] = {
    8, 8, 4, 8, 4, 8, 8, 4, 8, 4, 4, 4, 8, 4, 4, 4,
    8, 4, 4, 8, 4, 4, 8, 4, 4, 8, 4, 8, 8, 8, 8, 8,
    4, 4, 8, 8, 8, 4, 8, 8, 4, 8, 4, 8, 8, 8, 8, 8,
    8, 4, 4, 8, 4, 4, 8, 4, 4, 8, 4, 8, 8, 8, 8, 8,
    4, 4, 8, 8, 8, 4, 8, 8, 4, 8, 4, 8, 8, 8, 8, 8
  };

int notas = sizeof(melody) / sizeof(melody[0]);
int notasMario = sizeof(melodyMario) / sizeof(melodyMario[0]);

int tempoDelay = 0;

int comando = 1;

int horaDespertador = 14;
int minutoDespertador = 14;

bool alarmeAtivo;
bool alarmeDefinido;

char result[5];

void setup()
{
  dis.begin(0x70);
  pinMode(pinoBuzzer, OUTPUT);
  pinMode(pinoDefinirAlarme, OUTPUT);
}

void loop()
{

  int botaoAcHora = digitalRead(pinoAcHora);
  int botaoDecHora = digitalRead(pinoDecHora);
  int botaoAcMin = digitalRead(pinoAcMin);
  int botaoDecMin = digitalRead(pinoDecMin);

  int botaoPararAlarme = digitalRead(pinoPararAlarme);
  int botaoDefinirAlarme = digitalRead(pinoDefinirAlarme);
  int botaoDefinirMusica = digitalRead(pinoDefinirMusica);

  eventoClickBotao(botaoAcHora, botaoDecHora, botaoAcMin, botaoDecMin, botaoDefinirAlarme, botaoPararAlarme, botaoDefinirMusica);
  

  atualizarDisplay();
  delay(250);
  atualizarTempoDelay();
}

void atualizarHoraDespertador()
{
  if (horas == horaDespertador && minutos == minutoDespertador || !alarmeDefinido)
  {
    horaDespertador = horas;     // PARA SIMULAR O FUNCIONAMENTO
    minutoDespertador = minutos; // PARA SIMULAR O FUNCIOCNAMENTO

    alarmeDefinido = true;
  }
}

void eventoClickBotao(int botaoAcHora, int botaoDecHora, int botaoAcMin, int botaoDecMin, int botaoDefinirAlarme, int botaoPararAlarme, int botaoDefinirMusica)
{
  if (botaoAcHora == HIGH)
  {
    incrementarHora();
  }

  if (botaoDecHora == HIGH)
  {
    decrementarHora();
  }

  if (botaoAcMin == HIGH)
  {
    incrementarMinuto();
  }

  if (botaoDecMin == HIGH)
  {
    decrementarMinuto();
  }

  if (botaoDefinirAlarme == HIGH)
  {
    atualizarHoraDespertador();
  }

 
  if (botaoDefinirMusica == HIGH || botaoDefinirAlarme){
    tocarMusica();
  }
}
void alterarMusica(){
  
}

void tocarMusica() {
for (int i = 0; i < notas; i++) {
  
  botaoPararAlarme = digitalRead(pinoPararAlarme);
  if (botaoPararAlarme == HIGH){
    break;
  }
  
    int duration = 1000 / tempoMario[i];
    if (melodyMario[i] == 0) {
      delay(duration);
    } else {
      tone(pinoBuzzer, melodyMario[i], duration);
      delay(duration); // Adiciona um pequeno delay entre as notas
    }
    noTone(pinoBuzzer);
    delay(50); // Pequeno delay entre as notas para separá-las
  }
}


void incrementarHora()
{
  horas++;
  alarmeAtivo = false;

  if (horas >= 24)
  {
    horas = 0;
  }
}

void decrementarHora()
{
  horas--;
  alarmeAtivo = false;

  if (horas < 0)
  {
    horas = 23;
  }
}

void incrementarMinuto()
{
  minutos++;
  alarmeAtivo = false;

  if (minutos >= 60)
  {
    minutos = 0;
    horas++;
  }

  if (horas >= 24)
  {
    horas = 0;
  }
}

void decrementarMinuto()
{
  minutos--;
  alarmeAtivo = false;

  if (minutos < 0 && horas != 0)
  {
    minutos = 59;
    horas--;
  }

  if (minutos < 0 && horas == 0)
  {
    minutos = 59;
    horas = 23;
  }

  if (horas >= 24)
  {
    horas = 0;
  }
}

void atualizarDisplay()
{
  int tempo = horas * 100 + minutos;
  sprintf(result, "%04d", tempo);
  dis.println(result);
  dis.writeDisplay();
}

void atualizarTempoDelay()
{
  tempoDelay += 250;

  if (tempoDelay >= 1000)
  {
    tempoDelay = 0;
    segundos++;

    if (segundos > 59)
    {
      segundos = 0;
      minutos++;

      if (minutos > 59)
      {
        horas++;

        if (horas == 24)
        {
          horas = 0;
          minutos = 0;
        }
      }
    }
  }
}
