#ifndef RADIO
#define RADIO
#define MAX 50

typedef void *Radio;

Radio addRadio(char comandos[500],double cr,char cor1[MAX],char cor2[MAX]);

char *getRadioId(Radio recebeRadioRadio);
double getRadioX(Radio recebeRadio);
double getRadioY(Radio recebeRadio);
char *getRadioCfill(Radio recebeRadio);
char *getRadioCstrk(Radio recebeRadio);
double getRadioCr(Radio recebeRadio);

void setRadioX(Radio recebeRadio,double nX);
void setRadioY(Radio recebeRadio,double nY);

void removeRadio(Radio recebeRadio);
char* printValorRadio(Radio recebeRadio, char *dados);
int comparaRadio(Radio recebeRadio1,Radio recebeRadio2);
int comparaIdRadio(Radio recebeRadio1,Radio recebeRadio2);
int comparaKeyRadio(Radio recebeRadio, char* key);


#endif
