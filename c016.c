/* c016.c: **********************************************************}
{* Téma:  Tabulka s Rozptýlenými Položkami
**                      První implementace: Petr Přikryl, prosinec 1994
**                      Do jazyka C prepsal a upravil: Vaclav Topinka, 2005
**                      Úpravy: Karel Masařík, říjen 2014
**                              Radek Hranický, 2014-2018
**
** Vytvořete abstraktní datový typ
** TRP (Tabulka s Rozptýlenými Položkami = Hash table)
** s explicitně řetězenými synonymy. Tabulka je implementována polem
** lineárních seznamů synonym.
**
** Implementujte následující procedury a funkce.
**
**  HTInit ....... inicializuje tabulku před prvním použitím
**  HTInsert ..... vložení prvku
**  HTSearch ..... zjištění přítomnosti prvku v tabulce
**  HTDelete ..... zrušení prvku
**  HTRead ....... přečtení hodnoty prvku
**  HTClearAll ... zrušení obsahu celé tabulky (inicializace tabulky
**                 poté, co již byla použita)
**
** Definici typů naleznete v souboru c016.h.
**
** Tabulka je reprezentována datovou strukturou typu tHTable,
** která se skládá z ukazatelů na položky, jež obsahují složky
** klíče 'key', obsahu 'data' (pro jednoduchost typu float), a
** ukazatele na další synonymum 'ptrnext'. Při implementaci funkcí
** uvažujte maximální rozměr pole HTSIZE.
**
** U všech procedur využívejte rozptylovou funkci hashCode.  Povšimněte si
** způsobu předávání parametrů a zamyslete se nad tím, zda je možné parametry
** předávat jiným způsobem (hodnotou/odkazem) a v případě, že jsou obě
** možnosti funkčně přípustné, jaké jsou výhody či nevýhody toho či onoho
** způsobu.
**
** V příkladech jsou použity položky, kde klíčem je řetězec, ke kterému
** je přidán obsah - reálné číslo.
*/

#include "c016.h"

int HTSIZE = MAX_HTSIZE;
int solved;

/*          -------
** Rozptylovací funkce - jejím úkolem je zpracovat zadaný klíč a přidělit
** mu index v rozmezí 0..HTSize-1.  V ideálním případě by mělo dojít
** k rovnoměrnému rozptýlení těchto klíčů po celé tabulce.  V rámci
** pokusů se můžete zamyslet nad kvalitou této funkce.  (Funkce nebyla
** volena s ohledem na maximální kvalitu výsledku). }
*/

int hashCode ( tKey key ) {
	int retval = 1;
	int keylen = strlen(key);
	for ( int i=0; i<keylen; i++ )
		retval += key[i];
	return ( retval % HTSIZE );
}

/*
** Inicializace tabulky s explicitně zřetězenými synonymy.  Tato procedura
** se volá pouze před prvním použitím tabulky.
*/

void htInit ( tHTable* ptrht ) {
	if (*ptrht != NULL){ //jestli tabulka neni prazdna
		for (size_t i = 0; i < HTSIZE; i++) { //nastavim vsem prvkum ukazatel na NULL
			(*ptrht)[i] = NULL;
		}
	}
	else{ //jestli je prazdna
		return; //nase prace zde konci :-)
	}
}

/* TRP s explicitně zřetězenými synonymy.
** Vyhledání prvku v TRP ptrht podle zadaného klíče key.  Pokud je
** daný prvek nalezen, vrací se ukazatel na daný prvek. Pokud prvek nalezen není,
** vrací se hodnota NULL.
**
*/

tHTItem* htSearch ( tHTable* ptrht, tKey key ) { //fix
	if ((*ptrht) == NULL){//kdyz tabulka neexistuje, nemame co hledat....
		return NULL;
	}
	else{
		if((*ptrht)[hashCode(key)]==NULL){//kdyz polozka neni,...
			return NULL;
		}
		else{
			tHTItem* polozka = (*ptrht)[hashCode(key)];
			while (polozka != NULL){ //pprocahzej dokud neni prazdne
				if (polozka->key == key){ //kdyz najdeme
					return polozka; //vracime hodnotu
				}
				else{
					polozka = polozka->ptrnext; //jinak zvedame pointer
				}
			}
			return NULL;
		}
	}
	return 0;
}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato procedura vkládá do tabulky ptrht položku s klíčem key a s daty
** data.  Protože jde o vyhledávací tabulku, nemůže být prvek se stejným
** klíčem uložen v tabulce více než jedenkrát.  Pokud se vkládá prvek,
** jehož klíč se již v tabulce nachází, aktualizujte jeho datovou část.
**
** Využijte dříve vytvořenou funkci htSearch.  Při vkládání nového
** prvku do seznamu synonym použijte co nejefektivnější způsob,
** tedy proveďte.vložení prvku na začátek seznamu.
**/

void htInsert ( tHTable* ptrht, tKey key, tData data ) {
	if (ptrht == NULL){//ma to smysl?
		return;
	}
	else{
		tHTItem* hledej = htSearch(ptrht, key);//vyhledavam a ukladam do heldej
		if (hledej != NULL){
			hledej->data = data;
		}
		else{
			tHTItem* novaData = malloc(sizeof(tHTItem));
			if (novaData == NULL){
				return;//vracel bych nulu, ale mame void
			}
			novaData->key = key;
			novaData->data = data;
			novaData->ptrnext = (*ptrht)[hashCode(key)];
			(*ptrht)[hashCode(key)] = novaData;
		}
	}


}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato funkce zjišťuje hodnotu datové části položky zadané klíčem.
** Pokud je položka nalezena, vrací funkce ukazatel na položku
** Pokud položka nalezena nebyla, vrací se funkční hodnota NULL
**
** Využijte dříve vytvořenou funkci HTSearch.
*/

tData* htRead ( tHTable* ptrht, tKey key ) {
	if(ptrht == NULL){
		return NULL;
	}
	else{
		tHTItem *polozka = htSearch(ptrht, key);
		if (polozka == NULL){
			return NULL;
		}
		else{
			return &(polozka->data);
		}
	}
}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato procedura vyjme položku s klíčem key z tabulky
** ptrht.  Uvolněnou položku korektně zrušte.  Pokud položka s uvedeným
** klíčem neexistuje, dělejte, jako kdyby se nic nestalo (tj. nedělejte
** nic).
**
** V tomto případě NEVYUŽÍVEJTE dříve vytvořenou funkci HTSearch.
*/

void htDelete ( tHTable* ptrht, tKey key ) {
//pomocna promenna
	if (ptrht == NULL){
		return;
	}
	else{
		tHTItem *last = NULL;
		// tHTItem *polozka = NULL;
		if((*ptrht)[hashCode(key)]!=NULL){
			tHTItem* polozka = (*ptrht)[hashCode(key)];
			while (polozka != NULL){
				if (polozka->key == key){
					if (last != NULL){
						last->ptrnext = polozka->ptrnext;
					}
					if (polozka == (*ptrht)[hashCode(key)]){
						(*ptrht)[hashCode(key)] = polozka->ptrnext;
						//bafiky
					}

					free(polozka);
					polozka = NULL;
					return;
				}
				else{
					last = polozka;
					polozka = polozka->ptrnext;
				}
			}
		}
	}

}

/* TRP s explicitně zřetězenými synonymy.
** Tato procedura zruší všechny položky tabulky, korektně uvolní prostor,
** který tyto položky zabíraly, a uvede tabulku do počátečního stavu.
*/

void htClearAll ( tHTable* ptrht ) {
	tHTItem *polozka;
	tHTItem *nasledujici = NULL;
	for (size_t i = 0; i < HTSIZE; i++) { //pro každý řádek v teabulce
		polozka = (*ptrht)[i];
		while(polozka != NULL){
			nasledujici = polozka;
			polozka = polozka->ptrnext;
			free (nasledujici);
		}
		(*ptrht)[i] = NULL;
	}
}
