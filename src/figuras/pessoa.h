#ifndef PESSOA
#define PESSOA
#define MAX 50

typedef void *Pessoa;

Pessoa addPessoa(char comandos[500]);

char *getPessoaCpf(Pessoa recebePessoa);
char *getPessoaNome(Pessoa recebePessoa);
char *getPessoaSobrenome(Pessoa recebePessoa);
char getPessoaSexo(Pessoa recebePessoa);
char *getPessoaNascimento(Pessoa recebePessoa);

void setPessoaX(Pessoa recebePessoa,double nX);
void setPessoaY(Pessoa recebePessoa,double nY);

void removePessoa(Pessoa recebePessoa);
int comparaPessoa(Pessoa recebePessoa1,Pessoa recebePessoa2);
int comparaKeyPessoa(Pessoa recebePessoa, char* key);



#endif
