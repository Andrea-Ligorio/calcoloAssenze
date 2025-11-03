/*
@author AndreaLigorio
@file CalcoloAssenze
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string week(int i);

void menu();

void weekSetting(int difH[], int& Q, int& wlyH);
void schoolSetting(float& H);
void setAbsence(float& H);

bool import(string filePath, float& totH, int& weeklyH, int& weekQ, int dayH[], float absH);
int save(string filePath, float totH, int weeklyH, int weekQ, int dayH[], float absH);

int main(){
	const float absPerc=25;//percentuale di assenze sulle ore totali che si possono fare

	float totH = 0;//ore totali da fare in un anno
	float absH = 0;//ore di assenza fatte fino ad ora
	
	int weekQ = 0;//quantita di ore giornaliere diverse
	int dayH[7];//array che salva ogni quantita giornaliera di ore diversa
	int weeklyH = 0;//ore settimanali
	
	float posAbsH;//ore di assenza che si possono ancora fare
	
	const string percorsoFile = "C:\\Users\\Andrea\\programmazione\\progetti\\calcoloAssenze\\assenze.txt";//percorso del file su cui eseguire i salvataggi

	if(!import(percorsoFile, totH, weeklyH,	weekQ, dayH, absH)){
		schoolSetting(totH);
		weekSetting(dayH, weekQ, weeklyH);
		setAbsence(absH);
	}
	
	int i;
	char command;
	
	do{
		if(save(percorsoFile, totH, weeklyH, weekQ, dayH, absH) == 127){
			cout << "Errore durante il salvataggio" << endl;
			return 127;
		}
		
		posAbsH = (totH * (absPerc / 100)) - absH;

		cout << "Puoi ancora assentarti:" << endl;

		cout << posAbsH <<" ore" << endl;
		for(i = 0 ; i < weekQ ; i++){
			cout << posAbsH / dayH[i] << " giorni da " << dayH[i] << " ore" << endl;
		}
		cout << posAbsH / weeklyH << " settimane" << "\n\n";
		
		cin >> command;
		
		switch (command){
			case 'h'://help
				menu();
				break;
			case 'w'://week
				weekSetting(dayH,weekQ,weeklyH);
				break;
			case 's'://school
				schoolSetting(totH);
				break;
			case 'a'://absence
				setAbsence(absH);
				break;
			case 'e'://exit
				cout << "Arrivederci" << endl;
				break;
			case 'r'://reset
				system(("rm " + percorsoFile).c_str());
				cout << "Reset effettuato" << endl;
				break;
			default:
				cout<<"Comando non riconosciuto"<<endl;
				command='z';
				break;
		}

		

	}while(command!='e'&&command!='r');

return 0;
}

bool import(string filePath, float& totH, int& weeklyH, int& weekQ, int dayH[], float absH){
	bool used;
	int i;
	
	fstream file;

	file.open(filePath, ios :: in);

	if(!file.is_open()){
		file.open(filePath, ios :: out);
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

int save(string filePath, float totH, int weeklyH, int weekQ, int dayH[], float absH){
	int i;
	
	fstream file;
	file.open(filePath, ios :: out);

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

void menu(){
	system("cls");
				
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
	
	cout << "Inserisci quanti giorni a settimana vai a scuola:" << "\n\n";
	do{
		cin >> dayWeek;	
	}while(dayWeek < 1 || dayWeek > 7);
	
	
	for(i = 0 ; i < dayWeek ; i++){
		cout << "Inserisci quante ore fai di " << week(i) << ": " << "\n\n";
		do{
			cin >> H;	
		}while(H < 1 || H > 24);
		
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
	
	cout<<"Inserisci la scuola che frequenti:"<<endl;
	
	for(i=0;i<n;i++){
		cout << i + 1 << " - " << schName[i] << " (" << schH[i] << ")" << endl;
	}
	cout << "\n\n";
	do{
		cin >> opt;
	}while(opt < 1 || opt > n);
	
	
	
	opt--;
	
	if(opt == n - 1){
		cout << "Inserisci le ore annuali totali:" << endl;
		
		do{
			cin >> schH[opt];
		}while(schH[opt] < 2);
	}
	
	H = schH[opt];
	
	system("cls");
	
return;
}

void setAbsence(float& H){
	system("cls");
	
	cout << "Inserisci le ore di assenza fatte fino ad ora:" << endl;
	cin >> H;
	
return;
}

string week(int i){
	string days[]{"lunedi", "minerdi", "mercoledi", "giovedi", "venerdi", "sabato", "domenica"};
	
return days[i];
}