/*
@author AndreaLigorio
@file CalcoloAssenze
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Assenza{
	float totalH;
	int weeklyH;
	int weekQ;
	float absenceH;
	int dayH[7];
};

//restituisce il nome del giorno della settimana corrispondente all'indice inserito
string week(int i);

void home(Assenza user);
//stampa i comandi disponibili
void menu();

//prende l'input dall'utente controllando che sia compreso nei valori dei parametri
void check(int& inserimento, int min, int max);
void check(float& inserimento, float min, float max);

//imposta 
void weekSetting(int difH[], int& Q, int& weeklyH);
void schoolSetting(float& H);
void setAbsence(float& H, float totalH);

bool import(string fileName, Assenza& user);
int save(string fileName, Assenza& user);

int main(){

	Assenza user;

	const int width = 27;
	
	const string nomeFile = "assenze.bin";//percorso del file su cui eseguire i salvataggi

	if(!import(nomeFile, user)){
		schoolSetting(user.totalH);
		weekSetting(user.dayH, user.weekQ, user.weeklyH);
		setAbsence(user.absenceH, user.totalH);
	}
	
	int i;
	char command = 'z';
	
	do{
		system("cls");

		home(user);

		if(save(nomeFile, user) == 127){
			cout << "Errore durante il salvataggio" << endl;
			return 127;
		}
		
		

		if(command != 'h'){
			cout << "Per visualizzare i comandi [h]" << "\n\n";
		}else{
			menu();
		}
		
		cin >> command;
		
		switch (command){
			case 'h'://help
				break;
			case 'w'://week
				weekSetting(user.dayH, user.weekQ, user.weeklyH);
				break;
			case 's'://school
				schoolSetting(user.totalH);
				break;
			case 'a'://absence
				setAbsence(user.absenceH, user.totalH);
				break;
			case 'e'://exit
				cout << "Arrivederci" << endl;
				break;
			case 'r'://reset
				system(("rm " + nomeFile).c_str());
				cout << "Reset effettuato" << endl;
				break;
			case 'm'://mine mode
				for(i = 0 ; i < 10 ; i++){
					system("start https://youtu.be/e5sgt5kdg0s?t=3");
				}
				break;
			default:
				cout << "Comando non riconosciuto" << endl;
				command = 'z';
				break;
		}
	}while(command != 'e' && command != 'r');

return 0;
}

void home(Assenza user){
	const float absPerc = 25;
	
	float posAbsH;
	int i;

	posAbsH = (user.totalH * (absPerc / 100.0)) - user.absenceH;

	cout << "___________________________\n|" << endl;
	cout << "| " << "Ti sei assentato:" << endl;
	cout << "| " << user.absenceH <<" ore" << endl;

	cout << "|__________________________\n|" << endl;
	cout << "| " << "Puoi ancora assentarti:" << endl;

	cout << "| " << posAbsH <<" ore" << endl;
	for(i = 0 ; i < user.weekQ ; i++){
		cout << "| " << fixed << setprecision(1) << posAbsH / user.dayH[i] << " giorni da " << user.dayH[i] << " ore" << endl;
	}
	cout << "| " << posAbsH / user.weeklyH << " settimane" << "\n|__________________________"<< "\n\n";

return;
}

//prende l'input dall'utente controllando che sia compreso nei valori dei parametri
void check(int& inserimento, int min, int max){
	
	if(min < max){
		cout << "\n";
		do{
			cout << "\033[F\033[K";
			cin >> inserimento;
		}while(inserimento < min || inserimento > max);
	}
return;
}

void check(float& inserimento, float min, float max){
	
	if(min < max){
		cout << "\n";
		do{
			cout << "\033[F\033[K";
			cin >> inserimento;
		}while(inserimento < min || inserimento > max);
	}
return;
}

bool import(string fileName, Assenza& user){
	bool used;
	
	fstream file;

	file.open(fileName, ios :: in | ios :: binary);

	if(!file.is_open()){
		file.open(fileName, ios :: out | ios :: binary);
		used = false;
	} else if(file.peek() == EOF){
		used = false;
	} else{
		file.read((char*)&user, sizeof(user));
		used = true;
	}

	file.close();

return used;
}

int save(string fileName, Assenza& user){
	int i;
	
	fstream file;
	file.open(fileName, ios :: out | ios :: binary);

	if(!file.is_open()){
		cout << "Errore apertura file in output"<<"\n\n";
		return 127;
	}

	file.write((char*)&user,sizeof(user));

	file.close();

return 0;
}

//stampa i comandi disponibili
void menu(){	
	cout << "- w -> setta le ore di ogni giorno della settimana" << endl;
	cout << "- s -> setta le ore totali dell'anno scolastico" << endl;
	cout << "- a -> setta le ore di assenza effettuate fino ad ora" << endl;
	cout << "- e -> chiude il programma salvando i dati inseriti" << endl;
	cout << "- r -> resetta i dati e chiude il programma" << "\n\n";

return;
}

void weekSetting(int difH[], int& Q, int& weeklyH){
	int i, j, H;
	int dayWeek;
	bool flag;
	
	system("cls");
	
	cout << "Inserisci quanti giorni a settimana vai a scuola:" << endl;
	check(dayWeek, 1, 7);
	
	Q = 0;
	weeklyH = 0;

	for(i = 0 ; i < dayWeek ; i++){
		cout << "Inserisci quante ore fai di " << week(i) << endl;
		check(H, 1, 24);
		weeklyH += H;
		
		for(j = 0, flag = false ; j < Q ; j++){
			if(difH[j] == H){
				flag = true;		
			}
		}
		
		if(!flag || i == 0){
			difH[i] = H;
			Q++;	
		}
	}
return;
}

void schoolSetting(float& H){
	
	const int n = 4;
	string schName[n]{"Tecnico", "Scientifico", "Professionale", "Personalizzato"};
	int schH[n]{1056, 990, 1122, 0};
	int i, opt;
	
	system("cls");
	
	cout << "Inserisci la scuola che frequenti:" << endl;
	for(i = 0 ; i < n ; i++){
		cout << i + 1 << " - " << schName[i] << " (" << schH[i] << ")" << endl;
	}
	check(opt, 1, n);
	
	opt--;
	
	if(opt == n - 1){
		cout << "Inserisci le ore annuali totali:" << endl;
		check(schH[opt], 2, 8766);
	}
	
	H = schH[opt];
return;
}

void setAbsence(float& H, float totalH){
	system("cls");
	
	cout << "Inserisci le ore di assenza fatte fino ad ora:" << endl;
	check(H, 0.0, totalH);
	
return;
}

//restituisce il nome del giorno della settimana corrispondente all'indice inserito
string week(int i){
	string days[]{"lunedi", "martedi", "mercoledi", "giovedi", "venerdi", "sabato", "domenica"};
return days[i];
}