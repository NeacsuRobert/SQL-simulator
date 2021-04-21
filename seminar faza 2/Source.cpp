#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <filesystem>
using namespace std;
class ColoanaInt;
class ColoanaText;
class ColoanaFloat;
class InsertText;
class Coloana
{
	string numeColoana;
	string tipColoana;
	int dimensiuneColoana;

public:
	Coloana()
	{
	}
	Coloana(string numeColoana, string tipColoana, int dimensiuneColoana)
	{
		this->numeColoana = numeColoana;
		this->tipColoana = tipColoana;
		this->dimensiuneColoana = dimensiuneColoana;
	}
	friend ofstream& operator<<(ofstream& out, const ColoanaInt& col);
	friend ofstream& operator<<(ofstream& out, const ColoanaText& col1);
	friend ofstream& operator<<(ofstream& out, const ColoanaFloat& col);
};

class ColoanaText : public Coloana
{
	string valoareImplicita;

public:
	ColoanaText()
	{

	}
	ColoanaText(string numeColoana, string tipColoana, int dimensiuneColoana, string valoareImplicita) :Coloana(numeColoana, tipColoana, dimensiuneColoana)
	{
		this->valoareImplicita = valoareImplicita;
	}
	friend ofstream& operator<<(ofstream& out, const ColoanaText& col1)
	{
		out << col1.numeColoana << ": ";
		for (int i = 0; i < col1.dimensiuneColoana - 1; i++)
		{
			out << col1.valoareImplicita << ", ";
		}
		out << col1.valoareImplicita;
		return out;
	}
};

class ColoanaInt : public Coloana
{
	int valoareImplicita;

public:
	ColoanaInt()
	{

	}
	ColoanaInt(string numeColoana, string tipColoana, int dimensiuneColoana, int valoareImplicita) : Coloana(numeColoana, tipColoana, dimensiuneColoana)
	{
		this->valoareImplicita = valoareImplicita;
	}
	friend ofstream& operator<<(ofstream& out, const ColoanaInt& col)
	{
		out << col.numeColoana << ": ";
		for (int i = 0; i < col.dimensiuneColoana - 1; i++)
		{
			out << col.valoareImplicita << ", ";
		}
		out << col.valoareImplicita;
		return out;
	}
};

class ColoanaFloat : public Coloana
{
	float valoareImplicita;

public:
	ColoanaFloat()
	{

	}
	ColoanaFloat(string numeColoana, string tipColoana, int dimensiuneColoana, float valoareImplicita) : Coloana(numeColoana, tipColoana, dimensiuneColoana)
	{
		this->valoareImplicita = valoareImplicita;
	}
	friend ofstream& operator<<(ofstream& out, const ColoanaFloat& col)
	{
		out << col.numeColoana << ": ";
		for (int i = 0; i < col.dimensiuneColoana - 1; i++)
		{
			out << col.valoareImplicita << ", ";
		}
		out << col.valoareImplicita;
		return out;
	}

};

class Insert
{
	string numeColoana;
	int dimensiune;
	string* valori;
public:
	Insert()
	{

	}
	Insert(string numeColoana, int dimeniune, string* valori)
	{
		this->numeColoana = numeColoana;
		this->dimensiune = dimeniune;
		this->valori = new string[dimensiune];
		for (int i = 0; i < dimensiune; i++)
		{
			this->valori[i] = valori[i];
		}
	}
	friend ofstream& operator<<(ofstream& out, const Insert& ins)
	{
		out << ins.numeColoana << ": ";
		for (int i = 0; i < ins.dimensiune - 1; i++)
		{
			out << ins.valori[i] << ", ";
		}
		out << ins.valori[ins.dimensiune - 1];
		return out;
	}
};

int CREATE(string comanda)
{
	int counter = 0;
	string dimensiuneColoana;
	string valImp;
	string task, numeTabela, numeColoana, tipColoana;
	task = "CREATE TABLE";
	int pozitie = string::npos;
	pozitie = comanda.find("CREATE TABLE");
	if (pozitie == string::npos)
	{
		cout << "Eroare de sintaxa!";
		return 0;
	}
	else
	{
		bool conditieLoop = false;
		string copieComanda;
		copieComanda = comanda;
		string selectie, selectie2;
		copieComanda.erase(0, task.length());
		if (copieComanda[0] != ' ')
		{
			cout << "Eroare de sintaxa!";
			return 0;
		}
		copieComanda.erase(0, 1);
		pozitie = copieComanda.find(" ");
		if (pozitie == string::npos)
		{
			cout << "Eroare de sintaxa!";
			return 0;
		}
		numeTabela = copieComanda.substr(0, pozitie);
		ifstream check;
		check.open(numeTabela + ".txt");
		if (check)
		{
			cout << "Tabela deja exista!";
			return 0;
		}
		string numeFisierinf;
		numeFisierinf = numeTabela + "INFO.txt";
		ofstream fileOutput2(numeFisierinf, ios::out);
		fileOutput2 << copieComanda << endl;
		copieComanda.erase(0, pozitie + 1);
		if (copieComanda[copieComanda.length() - 1] != ')' || copieComanda[0] != '(')
		{
			cout << "Missing ( / )";
			return 0;
		}
		copieComanda.erase(0, 1);
		copieComanda.erase(copieComanda.length() - 1, copieComanda.length());
		if (copieComanda[0] != '(')
		{
			cout << "Missing (";
			return 0;
		}
		pozitie = copieComanda.find("), ");
		if (pozitie == string::npos)
		{
			pozitie = copieComanda.find(")");
		}
		else
		{
			conditieLoop = true;
		}
		if (pozitie == string::npos)
		{
			cout << "Missing )";
			return 0;
		}
		selectie = copieComanda.substr(0, pozitie + 1);
		if (selectie[0] != '(' || selectie[selectie.length() - 1] != ')')
		{
			cout << "Missing ( / )";
			return 0;
		}
		selectie.erase(0, 1);
		selectie.erase(selectie.length() - 1, selectie.length());
		while (selectie != "")
		{
			if (counter < 3)
			{
				pozitie = selectie.find(", ");
			}
			if (pozitie == string::npos)
			{
				cout << "Missing ,";
				return 0;
			}
			if (counter < 3)
			{
				selectie2 = selectie.substr(0, pozitie);
			}
			else
			{
				selectie2 = selectie;
			}
			if (counter == 0)
			{
				numeColoana = selectie2;
			}
			else
				if (counter == 1)
				{
					if (selectie2 != "text" && selectie2 != "float" && selectie2 != "integer")
					{
						cout << "Invalid datatype!";
						return 0;
					}
					tipColoana = selectie2;
				}
				else
					if (counter == 2)
					{
						dimensiuneColoana = selectie2;
					}
					else
						if (counter == 3)
						{
							valImp = selectie;
						}
			selectie.erase(0, pozitie + 2);
			if (counter == 3)
			{
				selectie.erase();
			}
			counter++;
		}
		/*	int valoare;
			cout << valImp << endl;
			valoare = std::stoi(valImp);
			cout << valoare;*/
		if (counter != 4)
		{
			cout << "Numar insuficient de coloane!";
			return 0;
		}
		if (tipColoana == "integer")
		{
			int valInt, dimensiune;
			valInt = std::stoi(valImp);
			dimensiune = std::stoi(dimensiuneColoana);
			ColoanaInt col(numeColoana, tipColoana, dimensiune, valInt);
			string numeFisier;
			numeFisier = numeTabela + ".txt";
			ofstream fileOutput(numeFisier, ios::out);
			fileOutput << col << endl;
		}
		else
			if (tipColoana == "text")
			{
				int dimensiune;
				dimensiune = std::stoi(dimensiuneColoana);
				ColoanaText col(numeColoana, tipColoana, dimensiune, valImp);
				string numeFisier;
				numeFisier = numeTabela + ".txt";
				ofstream fileOutput(numeFisier, ios::out);
				fileOutput << col << endl;
			}
			else
				if (tipColoana == "float")
				{
					int valFloat, dimensiune;
					valFloat = std::stof(valImp);
					dimensiune = std::stoi(dimensiuneColoana);
					ColoanaInt col(numeColoana, tipColoana, dimensiune, valFloat);
					string numeFisier;
					numeFisier = numeTabela + ".txt";
					ofstream fileOutput(numeFisier, ios::out);
					fileOutput << col << endl;
				}
		while (conditieLoop == true)
		{
			pozitie = copieComanda.find("), ");
			if (pozitie == string::npos)
			{
				conditieLoop = false;
			}
			copieComanda.erase(0, pozitie + 3);
			pozitie = copieComanda.find(")");
			selectie = copieComanda.substr(0, pozitie + 1);
			if (selectie[0] != '(' || selectie[selectie.length() - 1] != ')')
			{
				cout << "Missing ( / )";
				return 0;
			}
			counter = 0;
			selectie.erase(0, 1);
			selectie.erase(selectie.length() - 1, selectie.length());
			while (selectie != "")
			{
				if (counter < 3)
				{
					pozitie = selectie.find(", ");
				}
				if (pozitie == string::npos)
				{
					cout << "Missing ,";
					return 0;
				}
				if (counter < 3)
				{
					selectie2 = selectie.substr(0, pozitie);
				}
				else
				{
					selectie2 = selectie;
				}
				if (counter == 0)
				{
					numeColoana = selectie2;
				}
				else
					if (counter == 1)
					{
						if (selectie2 != "text" && selectie2 != "float" && selectie2 != "integer")
						{
							cout << "Invalid datatype!";
							return 0;
						}
						tipColoana = selectie2;
					}
					else
						if (counter == 2)
						{
							dimensiuneColoana = selectie2;
						}
						else
							if (counter == 3)
							{
								valImp = selectie;
							}
				selectie.erase(0, pozitie + 2);
				if (counter == 3)
				{
					selectie.erase();
				}
				counter++;
			}
			pozitie = copieComanda.find("), ");
			if (pozitie == string::npos)
			{
				conditieLoop = false;
			}
			if (tipColoana == "integer")
			{
				int valInt, dimensiune;
				valInt = std::stoi(valImp);
				dimensiune = std::stoi(dimensiuneColoana);
				ColoanaInt col(numeColoana, tipColoana, dimensiune, valInt);
				string numeFisier;
				numeFisier = numeTabela + ".txt";
				ofstream fileOutput(numeFisier, fstream::app);
				fileOutput << col << endl;
			}
			else
				if (tipColoana == "text")
				{
					int dimensiune;
					dimensiune = std::stoi(dimensiuneColoana);
					ColoanaText col(numeColoana, tipColoana, dimensiune, valImp);
					string numeFisier;
					numeFisier = numeTabela + ".txt";
					ofstream fileOutput(numeFisier, fstream::app);
					fileOutput << col << endl;
				}
				else
					if (tipColoana == "float")
					{
						int valFloat, dimensiune;
						valFloat = std::stof(valImp);
						dimensiune = std::stoi(dimensiuneColoana);
						ColoanaInt col(numeColoana, tipColoana, dimensiune, valFloat);
						string numeFisier;
						numeFisier = numeTabela + ".txt";
						ofstream fileOutput(numeFisier, fstream::app);
						fileOutput << col << endl;
					}
		}

		//cout << copieComanda;
	}
	string numeFisierBinar;
	numeFisierBinar = numeTabela + ".bin";
	ofstream outputBin(numeFisierBinar);
	ifstream citireFisier(numeTabela + ".txt");
	string rand;
	getline(citireFisier, rand);
	while (rand != "")
	{
		int lungime = rand.length();
		outputBin.write((char*)&lungime, sizeof(lungime));
		outputBin.write((rand + "\n").c_str(), lungime);
		rand.erase();
		getline(citireFisier, rand);
	}
	return 1;
}

int DROP(string comanda)
{
	string nume;
	int pozitie = string::npos;
	pozitie = comanda.find("DROP TABLE");
	if (pozitie == string::npos)
	{
		cout << "Eroare de sintaxa!";
		return 0;
	}
	else
	{
		nume = comanda.substr(pozitie + strlen("DROP TABLE "), comanda.length());
	}
	if (remove((nume + ".txt").c_str()) == 0 && remove((nume + "INFO.txt").c_str()) == 0 && remove((nume + ".bin").c_str()) == 0)
	{
		cout << "stergere efectuata";
	}
	else
	{
		cout << "fisierul nu exista";
	}
	return 1;
}

int INSERT(string comanda)
{
	string numeTabela, selectie;
	int dimensiune = 0;
	string dim;
	string valoareImplicita;
	int pozitie;
	pozitie = comanda.find("INSERT INTO ");
	if (pozitie != 0)
	{
		cout << "Eroare de sintaxa!";
		return 0;
	}
	comanda.erase(0, 12);
	pozitie = comanda.find(" ");
	if (pozitie == string::npos)
	{
		cout << "Eroare de sintaxa!";
		return 0;
	}
	selectie = comanda.substr(0, pozitie);
	numeTabela = selectie;
	comanda.erase(0, pozitie + 1);
	pozitie = comanda.find("VALUES");
	if (pozitie == string::npos)
	{
		cout << "Eroare de sintaxa!";
		return 0;
	}
	comanda.erase(0, pozitie + 6);
	string numeFisier;
	numeFisier = numeTabela + "INFO.txt";
	ifstream input;
	input.open(numeFisier);
	if (!input)
	{
		cout << "Tabela nu exista";
		return 0;
	}
	int nrColoane = 0;
	string info;
	string add;
	getline(input, info);
	pozitie = info.find("((");
	info.erase(0, pozitie + 1);
	info.erase(info.length() - 1, info.length());
	string* valori;
	valori = new string[dimensiune];
	int counter;
	string val;
	string valoare;
	ifstream input2;
	string numeFisierDate;
	numeFisierDate = numeTabela + ".txt";
	input2.open(numeFisierDate);
	comanda.erase(0, 1);
	comanda.erase(comanda.length() - 1, comanda.length());
	ofstream afisare(numeTabela + "2.txt", ios::app);
	string numeColoana;
	while (info != "")
	{
		counter = 0;
		pozitie = info.find(",");
		numeColoana = info.substr(1, pozitie - 1);
		info.erase(0, pozitie + 1);
		pozitie = info.find(",");
		info.erase(0, pozitie + 2);
		pozitie = info.find(",");
		dim = info.substr(0, pozitie);
		dimensiune = std::stoi(dim);
		info.erase(0, pozitie + 2);
		pozitie = info.find(")");
		valoareImplicita = info.substr(0, pozitie);
		nrColoane++;
		pozitie = info.find("), ");
		if (pozitie != string::npos)
		{
			info.erase(0, pozitie + 3);
		}
		else
		{
			info = "";
		}
		getline(input2, val);
		if (valori != NULL)
		{
			delete[] valori;
		}
		valori = new string[dimensiune];
		pozitie = val.find(": ");
		val.erase(0, pozitie + 2);
		while (val != "")
		{
			pozitie = val.find(",");
			if (pozitie != string::npos)
			{
				valoare = val.substr(0, pozitie);
			}
			else
			{
				valoare = val;
			}
			valori[counter] = valoare;
			if (pozitie != string::npos)
			{
				val.erase(0, pozitie + 2);
			}
			else
			{
				val = "";
			}
			counter++;
		}
		pozitie = comanda.find(",");
		add = comanda.substr(0, pozitie);
		comanda.erase(0, pozitie + 2);
		if (valori[dimensiune - 1] != valoareImplicita)
		{
			cout << "Tabela este plina!";
			return 0;
		}
		for (int j = 0; j < dimensiune; j++)
		{
			if (valori[j] == valoareImplicita)
			{
				valori[j] = add;
				j = dimensiune + 1;
			}
		}
		Insert coloana(numeColoana, dimensiune, valori);
		afisare << coloana << endl;
	}
	input.close();
	input2.close();
	afisare.close();
	int ok = 0;
	if (remove(numeFisierDate.c_str()) == 0)
	{
		ok = 1;
	}
	else
	{
		ok = 0;
	}
	if (rename((numeTabela + "2.txt").c_str(), (numeTabela + ".txt").c_str()) == 0)
	{
		ok = 1;
	}
	else
	{
		ok = 0;
	}
	if (remove((numeTabela + "2.txt").c_str()) == 0)
	{
		ok = 1;
	}
	else
	{

	}

	if (ok == 1)
	{
		string numeFisierBinar;
		numeFisierBinar = numeTabela + ".bin";
		ofstream outputBin(numeFisierBinar);
		ifstream citireFisier(numeTabela + ".txt");
		string rand;
		getline(citireFisier, rand);
		while (rand != "")
		{
			int lungime = rand.length();
			outputBin.write((char*)&lungime, sizeof(lungime));
			outputBin.write((rand + "\n").c_str(), lungime);
			rand.erase();
			getline(citireFisier, rand);
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

int SELECT(string comanda)
{
	int pozitie;
	string selectie;
	pozitie = comanda.find("SELECT ");
	if (pozitie == string::npos)
	{
		cout << "Eroare de sintaxa!";
		return 0;
	}
	comanda.erase(0, strlen("SELECT "));
	pozitie = comanda.find(")");
	selectie = comanda.substr(0, pozitie + 1);
	comanda.erase(0, pozitie + 1);
	if (selectie[0] != '(' || selectie[selectie.length() - 1] != ')')
	{
		cout << "Missing ( / )";
		return 0;
	}
	selectie.erase(0, 1);
	selectie.erase(selectie.length() - 1, selectie.length());
	int pozitie2;
	pozitie2 = comanda.find(" FROM ");
	if (pozitie2 == string::npos)
	{
		cout << "Eroare de sintaxa (Missing FROM)";
		return 0;
	}
	string selectie2;
	selectie2 = comanda.substr(pozitie2, comanda.length());
	selectie2.erase(0, strlen(" FROM "));
	comanda.erase(pozitie2, comanda.length());
	if (comanda != "")
	{
		cout << "Eroare de sintaxa";
		return 0;
	}
	ifstream input;
	input.open(selectie2 + ".txt");
	if (!input)
	{
		cout << "Tabelul nu exista!";
		return 0;
	}
	ifstream check;
	ofstream output;
	string numeSelect;
	string is;
	string col, numecol;
	for (int i = 0;; i++)
	{
		numeSelect = "SELECT";
		is = std::to_string(i);
		numeSelect = numeSelect + is;
		numeSelect = numeSelect + ".txt";
		check.open(numeSelect);
		if (!check)
		{
			break;
		}
		check.close();
	}
	output.open(numeSelect, ios::app);
	getline(input, col);
	int ok = 0;
	while (selectie != "")
	{
		pozitie = selectie.find(", ");
		if (pozitie != string::npos)
		{
			selectie2 = selectie.substr(0, pozitie);
		}
		else
		{
			selectie2 = selectie;
		}
		pozitie2 = col.find(":");
		numecol = col.substr(0, pozitie2);
		if (selectie2 == numecol)
		{
			output << col << endl;
			ok = 1;
		}
		if (pozitie != string::npos)
		{
			selectie.erase(0, pozitie + 2);
		}
		else
		{
			if (ok == 1)
			{
				selectie.erase();
			}
		}
		getline(input, col);
		if (col == "" && ok == 0)
		{
			cout << "Nu exista coloane cu acest nume!";
			return 0;
		}
	}
}
void executare_instructiune_delete(string numeTabela, ifstream& fisier, int nrColoane, int nrInregistrari, string numeColoana, string valoareCautata) {
	string cuvant, coloanaCurenta, linie;
	int a, i = 0;
	float b;
	int v[10], k = 0;
	ofstream rezultat;
	rezultat.open("rezultat.txt");
	while (i < nrColoane)
	{
		getline(fisier, linie);
		if (linie.find(",") == string::npos) {
			cout << "Tabelul nu are valori care pot fi cautate.";
			return;
		}
		coloanaCurenta = linie.substr(0, linie.find(":"));
		linie.erase(0, linie.find(" ") + 1);
		if (coloanaCurenta == numeColoana)
		{
			for (int j = 0; j < nrInregistrari; j++)
			{
				string valoare;
				if (j == (nrInregistrari - 1))
				{
					valoare = linie.substr(0, linie.length());
				}
				else
				{
					valoare = linie.substr(0, linie.find(","));
				}
				if (valoare == valoareCautata)
				{
					v[k] = j + 1;
					k++;
				}
				if (j != (nrInregistrari - 1))
				{
					linie.erase(0, linie.find(" ") + 1);
				}
			}
			fisier.seekg(ios::beg);
			for (int z = 0; z < nrColoane; z++)
			{
				getline(fisier, linie);
				int counter = 0;
				for (int m = 0; m < k; m++)
				{
					int pozitie = linie.find(" ") + 1;
					for (int l = 0; l < v[m] - counter - 1; l++)
					{
						pozitie = linie.find(" ", pozitie) + 1;
					}
					if (v[m] == nrInregistrari)
					{
						linie.erase(pozitie, linie.length() - pozitie + 1);
						linie.erase(pozitie - 2, linie.length() - pozitie - 1);
					}
					else
					{
						linie.erase(pozitie, linie.find(" ", pozitie) + 1 - pozitie);
					}

					counter++;
				}




				rezultat << linie << endl;

			}

			break;
		}

		i++;
	}
	fisier.close();
	rezultat.close();
	remove((numeTabela + ".txt").c_str());
	rename("rezultat.txt", (numeTabela + ".txt").c_str());
	if (remove((numeTabela + ".csv").c_str()) != 0)
	{
		cout << "Fisierul CSV nu a existat inainte ";
	}
	else
	{
		cout << "Fisierul CSV va fi rescris ";
	}
	string numeCSV = numeTabela + ".csv";
	ofstream csvFileOutput(numeCSV, ios::out);
	ifstream rezultat2;
	rezultat2.open((numeTabela + ".txt").c_str());
	string linie2;
	while (getline(rezultat2, linie2))
	{
		csvFileOutput << linie2.substr(0, linie2.find(" ") - 1) << ": ,";
		linie2.erase(0, linie2.find(" ") + 1);
		while (linie2.find(" ") != string::npos)
		{
			csvFileOutput << linie2.substr(0, linie2.find(" ") - 1) << ", ";
			linie2.erase(0, linie2.find(" ") + 1);
		}
		csvFileOutput << linie2.substr(0, linie2.length());
		csvFileOutput << endl;
	}
	csvFileOutput.close();
	rezultat2.close();
	string numeBIN = numeTabela + ".bin";
	ofstream binFileOutput(numeBIN, ios::out | ios::binary);
	ifstream rezultat3;
	rezultat3.open((numeTabela + ".txt").c_str());
	string linie3;

	while (getline(rezultat3, linie3))
	{
		int lungime = linie3.length() + 1;
		binFileOutput.write((char*)&lungime, sizeof(lungime));
		binFileOutput.write((linie3 + "\n").c_str(), lungime);

	}
	binFileOutput.close();
	rezultat3.close();
}
int DELETE(string comanda)
{
	string task, numeTabela, numeColoana;
	task = "DELETE FROM";
	int pozitie = string::npos;
	pozitie = comanda.find("DELETE FROM");
	if (pozitie == string::npos)
	{
		cout << "Comanda nu exista. Va rugam introduceti sintaxa corecta.";
		return 0;
	}
	else
	{
		string copieComanda;
		copieComanda = comanda;
		string selectie, selectie2;
		copieComanda.erase(0, task.length());
		if (copieComanda[0] != ' ')
		{
			return 0;
		}
		copieComanda.erase(0, 1);
		pozitie = copieComanda.find(" ");
		if (pozitie == string::npos)
		{
			return 0;
		}
		numeTabela = copieComanda.substr(0, pozitie);
		ifstream fileInputTabel(numeTabela + "INFO.txt", ios::in);
		if (!fileInputTabel.is_open())
		{
			cout << "Eroare deschidere fisier";
			return 0;
		}

		copieComanda.erase(0, pozitie + 1);
		int pozitie2;
		pozitie2 = comanda.find("WHERE");
		if (pozitie2 == string::npos)
		{
			cout << "Comanda nu exista. Va rugam introduceti sintaxa corecta.";
			return 0;
		}



		copieComanda.erase(0, copieComanda.find(" ") + 1);
		numeColoana = copieComanda.substr(0, copieComanda.find(" "));
		string coloana, coloanaCurenta, linie;
		bool gasitColoana = false;
		getline(fileInputTabel, linie);
		linie.erase(0, linie.find(" ") + 1);
		linie.erase(0, 1);
		while (linie.find("(", 1) != string::npos)
		{

			coloanaCurenta = linie.substr(1, linie.find("(", 1));
			int er = linie.find(',');
			coloana = coloanaCurenta.substr(0, er - 1);

			if (coloana == numeColoana)
			{
				gasitColoana = true;
			}

			linie.erase(0, linie.find("(", 1));
		}

		coloana = linie.substr(1, linie.find(",") - 1);

		if (coloana == numeColoana) {
			gasitColoana = true;
		}
		if (gasitColoana == false)
		{
			cout << "Coloana introdusa este gresita";
			return 0;
		}

		copieComanda.erase(0, copieComanda.find(" ") + 3);
		int a;
		float b;
		string c;
		c = copieComanda.substr(0, copieComanda.length());
		ifstream fileInput(numeTabela + ".txt", ios::in);
		int nrColoane = 0, nrInregistrari = 0;
		string line;
		while (getline(fileInput, line))
		{
			nrColoane++;
		}
		cout << endl;
		fileInput.clear();
		fileInput.seekg(ios::beg);
		getline(fileInput, line);
		for (int x = 0; x < line.length(); x++)
		{
			if (line[x] == ' ')
			{
				nrInregistrari++;
			}
		}
		fileInput.clear();
		fileInput.seekg(ios::beg);
		executare_instructiune_delete(numeTabela, fileInput, nrColoane, nrInregistrari, numeColoana, c);

	}

}
void executare_instructiune_display_table(string numeTabela, ifstream& fisier, int nrColoane, int nrInregistrari) {
	string coloanaCurenta, linie;
	int j = 0, i = 0, ia = 0, ib = 0;
	string a1[10][10];
	ofstream rezultat;
	rezultat.open("DISPLAY TABLE " + numeTabela + ".txt");
	while (i < nrColoane)
	{
		getline(fisier, linie);


		for (j = 0; j < nrInregistrari; j++)
		{
			a1[i][j] = linie.substr(0, linie.find(" ") - 1);
			linie.erase(0, linie.find(" ") + 1);
		}
		a1[i][j] = linie.substr(0, linie.length());

		i++;
	}
	for (int k = 0; k <= j +1 ; k++)
	{
		for (int l = 0; l < nrColoane-1; l++)
		{
			cout << a1[l][k] << " - ";
			rezultat << a1[l][k] << " ";

		}

		cout << endl;
		rezultat << endl;
	}




	fisier.close();
	rezultat.close();
	if (remove(("DISPLAY TABLE " + numeTabela + ".csv").c_str()) != 0)
	{
		cout << "Fisierul CSV nu a existat inainte ";
	}
	else
	{
		cout << "Fisierul CSV va fi rescris ";
	}
	string numeCSV = "DISPLAY TABLE " + numeTabela + ".csv";
	ofstream csvFileOutput(numeCSV, ios::out);
	ifstream rezultat2;
	rezultat2.open(("DISPLAY TABLE " + numeTabela + ".txt").c_str());
	string linie2;
	while (getline(rezultat2, linie2))
	{
		csvFileOutput << linie2.substr(0, linie2.find(" ")) << ",";
		linie2.erase(0, linie2.find(" ") + 1);
		while (linie2.find(" ") != string::npos)
		{
			csvFileOutput << linie2.substr(0, linie2.find(" ")) << ",";
			linie2.erase(0, linie2.find(" ") + 1);
		}
		csvFileOutput << linie2.substr(0, linie2.length());
		csvFileOutput << endl;
	}
	csvFileOutput.close();
	rezultat2.close();
	string numeBIN = "DISPLAY TABLE " + numeTabela + ".bin";
	ofstream binFileOutput(numeBIN, ios::out | ios::binary);
	ifstream rezultat3;
	rezultat3.open(("DISPLAY TABLE " + numeTabela + ".txt").c_str());
	string linie3;

	while (getline(rezultat3, linie3))
	{
		int lungime = linie3.length() + 1;
		binFileOutput.write((char*)&lungime, sizeof(lungime));
		binFileOutput.write((linie3 + "\n").c_str(), lungime);

	}
	binFileOutput.close();
	rezultat3.close();

}
int DISPLAY_TABLE(string comanda)
{
	string task, numeTabela, numeColoana;
	task = "DISPLAY TABLE";
	int pozitie = string::npos;
	pozitie = comanda.find("DISPLAY TABLE");
	if (pozitie == string::npos)
	{
		cout << "Comanda nu exista. Va rugam introduceti sintaxa corecta.";
		return 0;
	}
	else
	{
		string copieComanda;
		copieComanda = comanda;
		string selectie, selectie2;
		copieComanda.erase(0, task.length());
		if (copieComanda[0] != ' ')
		{
			cout << "Comanda nu exista. Va rugam introduceti sintaxa corecta.";
			return 0;
		}
		copieComanda.erase(0, 1);
		numeTabela = copieComanda.substr(0, copieComanda.length());



		ifstream fileInputTabel(numeTabela + ".txt", ios::in);
		if (!fileInputTabel.is_open())
		{
			cout << "Eroare deschidere fisier sau fisierul nu exista.";
			return 0;
		}
		int nrColoane = 0, nrInregistrari = 0;
		string line;
		while (getline(fileInputTabel, line))
		{
			nrColoane++;
		}
		cout << endl;
		fileInputTabel.clear();
		fileInputTabel.seekg(ios::beg);
		getline(fileInputTabel, line);
		for (int x = 0; x < line.length(); x++)
		{
			if (line[x] == ' ')
			{
				nrInregistrari++;
			}
		}
		fileInputTabel.clear();
		fileInputTabel.seekg(ios::beg);
		executare_instructiune_display_table(numeTabela, fileInputTabel, nrColoane, nrInregistrari);

	}

}
//bool exista(string numetabel)
//{
//	ifstream fis;
//	fis.open(numetabel.c_str());
//	return bool(fis);
//}
//int UPDATE(string comanda_update)
//{
//	string rezerva;
//	string rezerva2;
//	int n = string::npos;
//
//
//	string update = "UPDATE"; string set; string where;
//	string numetabel; string numecoloana; string conditie;
//
//	n = comanda_update.find("UPDATE");
//	if (n == string::npos)
//		cout << "Eroare de sintaxa ! ";
//	else
//	{
//		string linie;
//		linie = comanda_update;
//		n = linie.find(" ");
//		if (n == string::npos)
//			cout << "Eroare de sintaxa ! ";
//		else
//		{
//			linie.erase(0, n + 1);
//			n = linie.find(" ");
//			numetabel = linie.substr(0, n);
//			numetabel = numetabel + ".txt";
//			if (numetabel == numetabel.c_str())
//			{
//
//				if (exista(numetabel.c_str()))
//				{
//
//
//					linie.erase(0, n);
//					string linie2;
//					linie2 = linie;
//					n = linie2.find(" ");
//					linie2.erase(0, n);
//					set = linie2;
//					n = set.find("SET");
//
//					if (n == string::npos)
//						cout << "Eroare de sintaxa!";
//					else
//					{
//						string liniefis;
//						size_t pozitiefis;
//						string numecoloana2;
//						string valoare;
//						linie2.erase(0, n + 4);
//						n = linie2.find(" ");
//						numecoloana = linie2.substr(0, n);
//						linie2.erase(0, n);
//						fstream fis(numetabel.c_str());
//						while (fis.good())
//						{
//							getline(fis, liniefis);
//							pozitiefis = liniefis.find(numecoloana);
//							if (pozitiefis != string::npos)
//							{
//								n = linie2.find(" = ");
//								if (n != string::npos)
//								{
//									linie2.erase(0, n + 3);
//									n = linie2.find(" ");
//									valoare = linie2.substr(0, n); // valoare e citita bine
//									linie2.erase(0, n);
//									n = linie2.find(" ");
//									where = linie2.find("WHERE");
//									if (n == string::npos)
//										cout << "Eroare de sintaxa!";
//									else
//									{
//
//										linie2.erase(0, n + 7);
//										n = linie2.find(" ");
//										numecoloana2 = linie2.substr(0, n); // coloana din conditie
//
//										linie2.erase(0, n);
//										n = linie2.find(" = ");
//										linie2.erase(0, n + 3);
//										n = linie2.find(" ");
//										conditie = linie2.substr(0, n); // conditie citta bine 
//
//
//
//
//
//
//
//
//
//
//									}
//
//								}
//
//								else
//									cout << "Eroare de sintaxa ! ";
//
//
//
//
//
//
//
//
//
//								break;
//
//
//
//
//
//							}
//
//
//
//
//						}
//
//						int virgule, counter = 0;
//
//						while (fis.good())
//						{
//
//							int poz = string::npos;
//							string linie;
//							getline(fis, linie);
//
//							poz = linie.find(numecoloana2);
//							if (poz != string::npos)
//							{
//								while (linie != "")
//
//								{
//
//
//									poz = linie.find(", ");
//									if (poz != string::npos)
//									{
//										counter++;
//
//									}
//
//									linie.erase(0, poz + 2);
//
//								}
//
//
//							}
//						}
//
//						fis.close();
//						fis.open(numetabel.c_str());
//						while (fis.good())
//						{
//							int poz2;
//							string val;
//							int poz = string::npos;
//							getline(fis, rezerva);
//							string linie2;
//							linie2 = rezerva;
//							poz = rezerva.find(numecoloana);
//							if (poz != string::npos)
//							{
//								for (int i = 0; i <= counter; i++)
//								{
//									poz = linie2.find(", ");
//									linie2.erase(0, poz + 2);
//
//								}
//								poz2 = linie2.find(",");
//								if (poz2 != string::npos)
//								{
//									val = linie2.substr(0, poz2);
//								}
//
//								else
//									val = linie2;
//								poz2 = rezerva.find(val);
//								rezerva.replace(poz2 - 1, val.length(), valoare);
//								rezerva2 = rezerva;
//							}
//
//						}
//
//
//
//						fis.close();
//						fis.open(numetabel.c_str());
//						ofstream fis2("rezerva.txt", ios::app);
//						int poz;
//						while (fis.good())
//						{
//							getline(fis, linie2);
//							poz = linie2.find(numecoloana);
//							if (poz == string::npos)
//							{
//								fis2 << linie2 << endl;
//							}
//							else
//
//								fis2 << rezerva2 << endl;
//
//						}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//					}
//
//
//
//
//				}
//
//			}
//			else
//				cout << "Tabelul nu exista!";
//
//
//
//
//
//		}
//
//
//
//
//
//
//
//	}
//
//
//	remove(numetabel.c_str());
//	rename("rezerva.txt", numetabel.c_str());
//
//
//	return 0;
//
//}
void main()
{
	int i;
	string comanda;
	int pozitie;
	getline(std::cin, comanda);
	/*ifstream inputFisier("comanda.txt");
	getline(inputFisier, comanda);*/
	pozitie = comanda.find("CREATE");
	if (pozitie != string::npos)
	{
		i = CREATE(comanda);

		if (i == 1)
		{
			cout << "Create realizat cu succes!";
		}
		else
		{
			cout << endl << "Eroare la realizarea Create!";
		}
	}
	else
	{
		pozitie = comanda.find("DROP");
		if (pozitie != string::npos)
		{
			DROP(comanda);
		}
		else
		{
			pozitie = comanda.find("INSERT");
			if (pozitie != string::npos)
			{
				i = INSERT(comanda);
				if (i == 1)
				{
					cout << "Insert realizat cu succes!";
				}
				else
					cout << endl << "Eroare la realizarea insert!";
			}
			else
			{
				pozitie = comanda.find("SELECT");
				if (pozitie != string::npos)
				{
					SELECT(comanda);
				}
				else
				{
					pozitie = comanda.find("DISPLAY");
					if (pozitie != string::npos)
					{
						DISPLAY_TABLE(comanda);
					}
					else
					{
						pozitie = comanda.find("DELETE");
						if (pozitie != string::npos)
						{
							DELETE(comanda);
						}
						else
						{
							cout << "Comanda nu exista!";
						}
						/*else
						{
							pozitie = comanda.find("UPDATE");
							if (pozitie != string::npos)
							{
								UPDATE(comanda);
							}
							else
							{
								cout << "Comanda nu exista!";
							}
						}*/
					}
				}
			}
		}
	}
}