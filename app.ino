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

int botaoDesativarAlarme;
int botaoDefinirAlarme;
int botaoDefinirMusica;

int musicaAtual = 1;

const int notaA = 262;
const int notaB = 294;
const int notaBb = 143;
const int notaC = 330;
const int notaD = 394;
const int notaE = 198;
const int notaF = 440;
const int notaG = 495;

int melodia1[] = {
    notaE, notaD, notaE, notaD, notaE, notaB, notaD, notaC, notaA, 0, notaC, notaE, notaA, notaB, 0,
    notaE, notaD, notaE, notaD, notaE, notaB, notaD, notaC, notaA, 0, notaC, notaE, notaA, notaB, 0,
    notaE, notaC, notaD, notaE, notaG, notaF, notaE, notaD, notaC, 0, notaE, notaG, notaA, 0, notaF,
    notaE, notaD, notaE, notaD, notaE, notaB, notaD, notaC, notaA, 0, notaC, notaE, notaA, notaB, 0};

int tempoMelodia1[] = {
    8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4,
    8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 8, 4, 4,
    8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4};

int melodia2[] = {
    notaE, notaE, 0, notaE, 0, notaC, notaE, 0, notaG, 0, 0, 0, notaG, 0, 0, 0,
    notaC, 0, 0, notaG, 0, 0, notaE, 0, 0, notaA, 0, notaB, 0, notaBb, 0, notaA,
    notaG, 0, notaE, notaG, notaA, 0, notaF, notaG, 0, notaE, 0, notaC, notaD, notaB, 0, 0,
    notaC, 0, 0, notaG, 0, 0, notaE, 0, 0, notaA, 0, notaB, 0, notaBb, 0, notaA,
    notaG, 0, notaE, notaG, notaA, 0, notaF, notaG, 0, notaE, 0, notaC, notaD, notaB, 0, 0};

int tempoMelodia2[] = {
    8, 8, 4, 8, 4, 8, 8, 4, 8, 4, 4, 4, 8, 4, 4, 4,
    8, 4, 4, 8, 4, 4, 8, 4, 4, 8, 4, 8, 8, 8, 8, 8,
    4, 4, 8, 8, 8, 4, 8, 8, 4, 8, 4, 8, 8, 8, 8, 8,
    8, 4, 4, 8, 4, 4, 8, 4, 4, 8, 4, 8, 8, 8, 8, 8,
    4, 4, 8, 8, 8, 4, 8, 8, 4, 8, 4, 8, 8, 8, 8, 8};

int melodia3[] = {
    notaE, 0, notaD, 0, notaC, 0, notaB, 0,
    notaA, 0, notaB, 0, notaC, 0, notaD, 0,
    notaE, 0, notaD, 0, notaC, 0, notaB, 0,
    notaA, 0, notaB, 0, notaD, 0, notaD, 0, notaC, 0};

int tempoMelodia3[] = {
    4, 2, 4, 2, 4, 2, 4, 2,
    4, 2, 4, 2, 4, 2, 4, 2,
    4, 2, 4, 2, 4, 2, 4, 2,
    4, 2, 4, 2, 4, 2, 4, 2, 4, 2};

int qtdNotas1 = sizeof(melodia1) / sizeof(melodia1[0]);
int qtdNotas2 = sizeof(melodia2) / sizeof(melodia2[0]);
int qtdNotas3 = sizeof(melodia3) / sizeof(melodia3[0]);

int tempoDelay = 0;

int horaDespertador = 14;
int minutoDespertador = 14;

bool alarmeDefinido = false;

char result[5];

void setup()
{
  dis.begin(0x70);
  pinMode(pinoBuzzer, OUTPUT);
  pinMode(pinoDefinirAlarme, OUTPUT);
}

void loop()
{

  eventoClickBotao();

  monitorarAlarme();
  atualizarDisplay();

  delay(200);
  configurarTempoRelogio(200);
}

void definirHoraAlarme()
{
  horaDespertador = horas;
  minutoDespertador = minutos;

  alarmeDefinido = true;
}

void monitorarAlarme()
{
  if (alarmeDefinido && horas == horaDespertador && minutos == minutoDespertador)
  {

    if (musicaAtual == 1)
    {
      tocarMusica(melodia1, tempoMelodia1, qtdNotas1);
    }
    else if (musicaAtual == 2)
    {
      tocarMusica(melodia2, tempoMelodia2, qtdNotas2);
    }
    else
    {
      tocarMusica(melodia3, tempoMelodia3, qtdNotas3);
    }
  }
}

void alterarMusica()
{
  if (musicaAtual != 3)
  {
    musicaAtual++;
  }
  else
  {
    musicaAtual = 1;
  }
}

void tocarMusica(int *melodia, int *tempoMeloadia, int qtdNotasMelodia)
{
  unsigned long tempoInicial = 0;
  tempoInicial = millis();
  int indice = 0;

  while (true)
  {

    int duracao = 1000 / tempoMeloadia[indice];
    if (melodia[indice] == 0)
    {
      delay(duracao);
    }
    else
    {
      tone(pinoBuzzer, melodia[indice], duracao);
    }

    botaoAcHora = digitalRead(pinoAcHora);
    botaoDecHora = digitalRead(pinoDecHora);
    botaoAcMin = digitalRead(pinoAcMin);
    botaoDecMin = digitalRead(pinoDecMin);

    botaoDesativarAlarme = digitalRead(pinoPararAlarme);

    if (botaoDesativarAlarme == HIGH)
    {
      unsigned long tempoFinal = millis() - tempoInicial;
      segundos += (tempoFinal / 1000);
      alarmeDefinido = false;
      break;
    }

    if (botaoAcHora == HIGH || botaoAcMin == HIGH || botaoDecHora == HIGH || botaoDecMin == HIGH)
    {
      unsigned long tempoFinal = millis() - tempoInicial;
      segundos += (tempoFinal / 1000);

      break;
    }

    indice++;

    if (indice >= qtdNotasMelodia)
    {
      indice = 0;
    }

    unsigned long tempoFinal = millis() - tempoInicial;

    if (tempoFinal >= 60000)
    {
      incrementarMinuto();
      break;
    }
  }
}

void incrementarHora()
{
  horas++;

  if (horas >= 24)
  {
    horas = 0;
  }
}

void decrementarHora()
{
  horas--;
  if (horas < 0)
  {
    horas = 23;
  }
}

void incrementarMinuto()
{
  minutos++;

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

void configurarTempoRelogio(int tempo)
{
  tempoDelay += tempo;

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

void eventoClickBotao()
{

  botaoAcHora = digitalRead(pinoAcHora);
  botaoDecHora = digitalRead(pinoDecHora);
  botaoAcMin = digitalRead(pinoAcMin);
  botaoDecMin = digitalRead(pinoDecMin);

  botaoDefinirAlarme = digitalRead(pinoDefinirAlarme);
  botaoDefinirMusica = digitalRead(pinoDefinirMusica);

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
    definirHoraAlarme();
  }

  if (botaoDefinirMusica == HIGH)
  {
    alterarMusica();
  }
}
