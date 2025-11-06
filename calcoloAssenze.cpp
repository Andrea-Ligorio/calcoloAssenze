/*
@author AndreaLigorio
@file CalcoloAssenze
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

//restituisce il nome del giorno della settimana corrispondente all'indice inserito
string week(int i);

void home();
//stampa i comandi disponibili
void menu();

//prende l'input dall'utente controllando che sia compreso nei valori dei parametri
void check(int& inserimento, int min, int max);

//imposta 
void weekSetting(int difH[], int& Q, int& wlyH);
void schoolSetting(float& H);
void setAbsence(float& H, float totH);

bool import(string fileName, float& totH, int& weeklyH, int& weekQ, int dayH[], float& absH);
int save(string fileName, float totH, int weeklyH, int weekQ, int dayH[], float absH);

int main(){
	const int width = 27;

	const float absPerc = 25;//percentuale di assenze sulle ore totali che si possono fare

	float totH = 0;//ore totali da fare in un anno
	float absH = 0;//ore di assenza fatte fino ad ora
	
	int weekQ = 0;//quantita di ore giornaliere diverse
	int dayH[7];//array che salva ogni quantita giornaliera di ore diversa
	int weeklyH = 0;//ore settimanali
	
	float posAbsH;//ore di assenza che si possono ancora fare
	
	const string nomeFile = "assenze.txt";//percorso del file su cui eseguire i salvataggi

	if(!import(nomeFile, totH, weeklyH,	weekQ, dayH, absH)){
		schoolSetting(totH);
		weekSetting(dayH, weekQ, weeklyH);
		setAbsence(absH, totH);
	}
	
	int i;
	char command;
	
	do{
		system("cls");

		if(save(nomeFile, totH, weeklyH, weekQ, dayH, absH) == 127){
			cout << "Errore durante il salvataggio" << endl;
			return 127;
		}
		
		posAbsH = (totH * (absPerc / 100)) - absH;


		cout << "___________________________\n|" << endl;
		cout << "| " << "Ti sei assentato:" << endl;
		cout << "| " << absH <<" ore" << endl;

		cout << "|__________________________\n|" << endl;
		cout << "| " << "Puoi ancora assentarti:" << endl;

		cout << "| " << posAbsH <<" ore" << endl;
		for(i = 0 ; i < weekQ ; i++){
			cout << "| " << fixed << setprecision(1) << posAbsH / dayH[i] << " giorni da " << dayH[i] << " ore" << endl;
		}
		cout << "| " << posAbsH / weeklyH << " settimane" << "\n|__________________________"<< "\n\n";

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
				weekSetting(dayH,weekQ,weeklyH);
				break;
			case 's'://school
				schoolSetting(totH);
				break;
			case 'a'://absence
				setAbsence(absH, totH);
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
				cout<<"Comando non riconosciuto"<<endl;
				command='z';
				break;
		}
	}while(command!='e'&&command!='r');

return 0;
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

bool import(string fileName, float& totH, int& weeklyH, int& weekQ, int dayH[], float& absH){
	bool used;
	int i;
	
	fstream file;

	file.open(fileName, ios :: in);

	if(!file.is_open()){
		file.open(fileName, ios :: out);
		used = false;
	} else if(file.peek() == EOF){
		used = false;
	} else{
		file >> totH;
		file >> weeklyH;
		file >> weekQ;
		for(i = 0 ; i < weekQ ; i++){
			file >> dayH[i];
		}
		file >> absH;

		used = true;
	}

	file.close();

return used;
}

int save(string fileName, float totH, int weeklyH, int weekQ, int dayH[], float absH){
	int i;
	
	fstream file;
	file.open(fileName, ios :: out);

	if(!file.is_open()){
		cout << "Errore apertura file in output"<<"\n\n";
		return 127;
	}

	file << totH << endl;
	file << weeklyH << endl;
	file << weekQ << endl;
	for(i = 0 ; i < weekQ ; i++){
		file << dayH[i] << endl;
	}
	file << absH;

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

void weekSetting(int difH[], int& Q, int& wlyH){
	int i, j, H;
	int dayWeek;
	bool flag;
	
	system("cls");
	
	cout << "Inserisci quanti giorni a settimana vai a scuola:" << endl;
	check(dayWeek, 1, 7);
	
	for(i = 0 ; i < dayWeek ; i++){
		cout << "Inserisci quante ore fai di " << week(i) << endl;
		check(H, 1, 24);
		
		wlyH+=H;
		
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

void setAbsence(float& H, float totH){
	system("cls");
	
	cout << "Inserisci le ore di assenza fatte fino ad ora:" << endl;
	check(H, 0.0, totH);
	
return;
}

//restituisce il nome del giorno della settimana corrispondente all'indice inserito
string week(int i){
	string days[]{"lunedi", "martedi", "mercoledi", "giovedi", "venerdi", "sabato", "domenica"};
return days[i];
}