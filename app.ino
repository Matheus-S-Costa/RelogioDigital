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
const int pinoContBuzzer = 7;
const int pinoDefinirAlarme = 8;

int tempoDelay = 0;

int horaDespertador = 14;
int minutoDespertador = 14;

bool alarmeAtivo;
bool definirProximoAlarme;
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
    int contBuzzer = digitalRead(pinoContBuzzer);
    int botaoDefinirAlarme = digitalRead(pinoDefinirAlarme);

    eventoClickBotao(botaoAcHora, botaoDecHora, botaoAcMin, botaoDecMin, botaoDefinirAlarme);
    atualizarStatusAlarme(contBuzzer);

    atualizarDisplay();
    delay(196);
    atualizarTempoDelay();
}

void atualizarHoraDespertador()
{
    if (horas == horaDespertador && minutos == minutoDespertador || !alarmeDefinido)
    {
        horaDespertador = horas;
        minutoDespertador = minutos;
        alarmeDefinido = true;
        definirProximoAlarme = false;
    }
}

void eventoClickBotao(int botaoAcHora, int botaoDecHora, int botaoAcMin, int botaoDecMin, int botaoDefinirAlarme)
{
    botaoAcHora == HIGH ? incrementarHora() : 0;
    botaoDecHora == HIGH ? decrementarHora() : 0;
    botaoAcMin == HIGH ? incrementarMinuto() : 0;
    botaoDecMin == HIGH ? decrementarMinuto() : 0;
    botaoDefinirAlarme ? atualizarHoraDespertador() : 0;
}

void atualizarStatusAlarme(int contBuzzer)
{
    alarmeAtivo = (horas == horaDespertador && minutos == minutoDespertador);

    if ((horas == horaDespertador && minutos != minutoDespertador) || contBuzzer == HIGH)
    {
        alarmeAtivo = false;
    }

    digitalWrite(pinoBuzzer, alarmeAtivo ? HIGH : LOW);
}

void incrementarHora()
{
    horas++;
    alarmeAtivo = false;

    if (horas >= 24)
    {
        horas = 0;
    }

    delay(100);
}

void decrementarHora()
{
    horas--;
    alarmeAtivo = false;

    if (horas < 0)
    {
        horas = 23;
    }

    delay(100);
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

    delay(100);
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

    delay(100);
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
    tempoDelay += 240;

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
