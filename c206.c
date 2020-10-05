
/* c206.c **********************************************************}
{* Téma: Dvousměrně vázaný lineární seznam
**
**                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
**                            Přepracované do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Kamil Jeřábek, září 2019
**
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou
** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
** jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního
** seznamu). Definici konstant a typů naleznete v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu
** s výše uvedenou datovou částí abstrakce tvoří abstraktní datový typ
** obousměrně vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu před prvním použitím,
**      DLDisposeList ... zrušení všech prvků seznamu,
**      DLInsertFirst ... vložení prvku na začátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu,
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek před aktivním prvkem,
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLPred .......... posune aktivitu na předchozí prvek seznamu,
**      DLActive ........ zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce
** explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
	L->First = NULL; //nastavim vsechny promenne na NULL
	L->Last = NULL;
	L->Act = NULL;

}

void DLDisposeList (tDLList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
** uvolněny voláním operace free.
**/
	//TODO posefit
	tDLElemPtr name; //netusim jak pojmenovat
	while(L->First != NULL){ //projdeme cely seznam
		name = L->First->rptr; //ulozim si do docastne promenne prvni
		free(L->First);
		L->First = name;
	}
	L->Act = NULL;
	L->Last = NULL;

}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vloží nový prvek na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	tDLElemPtr name; //netusim jak pojmenovat
	name = malloc(sizeof(struct tDLElem));
	if (name == NULL){
		DLError();
	}
	else{
		name->lptr = NULL;//ukazatel vlevo bude null
		name->rptr = NULL;//ukazatel vtavo bude null
		name->data = val; // nahravam data
		if(L->Last != NULL){ //jestlize nevkladam poprve
			name->rptr = L->First; //napravo budeme ukatovat na pervni prvek
			L->First->lptr = name; //nalevo ukazujeme na nas pomocny prvek

		}
		else{
			name->rptr = L->First;
			L->Last = name; //posledni je nas vlozeny prvek
		}
		L->First = name;//prvni bude nas vlozeny prvek
	}

}

void DLInsertLast(tDLList *L, int val) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
	tDLElemPtr name; //funkce temer identicka s predchozi, jen upravene first/last a lptr/rptr
	name = malloc(sizeof(struct tDLElem));
	if (name == NULL){
		DLError();
	}
	else{
		name->lptr = NULL;
		name->rptr = NULL;
		name->data = val;
		if(L->Last != NULL){
			name->lptr = L->Last;
			L->Last->rptr = name;

		}
		else{
			name->lptr = L->Last;
			L->First = name;
		}
		L->Last = name;
	}

}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	L->Act = L->First;
}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	L->Act = L->Last;
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
	if(L->First == NULL){//jestli je seznam prazdyn
		DLError();//error
	}
	else{
		*val = L->First->data;
	}
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
	if(L->First == NULL){
		DLError();
	}
	else{
		*val = L->Last->data;
	}
}

void DLDeleteFirst (tDLList *L) {
/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita
** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/
	if(L->First == NULL){ //seznam je prazdy, nedelej nic
		return;
	}
	else{//v seznamu neco je
		tDLElemPtr name = L->First;
		if(L->Last == L->First){	//posledni prvek je schodny se prvnim
			L->Last = NULL; //nastavim na null
		}
		else{
			if(L->Act == L->First){ //jestli je prvni aktivni
				L->Act = NULL; //zrusim aktivitu
			}
			L->First = name->rptr;//prvek napravo od prvniho je novy prvni
			L->First->lptr = NULL;	//prvek novy ukazuje na levo
		}
		free(name);
	}
}

void DLDeleteLast (tDLList *L) {
/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/
	if(L->First == NULL){ //viz fce vys
		//return;
	}
	else{
		tDLElemPtr name = L->Last;
		if(L->Last == L->First){
			L->Last = NULL;
      L->First = NULL;
      L->Act = NULL;
		}
		else{
			if(L->Act == L->Last){
				L->Act = NULL;
			}
			L->Last = name->lptr;
			L->Last->rptr = NULL;
		}
		free(name);
	}
}//maybe fix


void DLPostDelete (tDLList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/
	if(L->Act != NULL && L->Act != L->Last){
		tDLElemPtr name = L->Act->rptr; //ulozim prvek ktery je k smazani
		if(L->Last == name){
			L->Last=L->Act;
		}
		else{
			name->lptr->rptr = L->Act;
		}
		free(name);
	}
}

void DLPreDelete (tDLList *L) {
/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/
	if(L->Act != NULL && L->Act != L->First){
		tDLElemPtr name = L->Act->lptr; //ulozim prvek ktery je k smazani
    L->Act->lptr = name->lptr;
		if(name->lptr == NULL){
			L->First=L->Act;
		}
		else{
			name->lptr->rptr = L->Act;
		}
		free(name);
	}
}//fix?

void DLPostInsert (tDLList *L, int val) {
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
  if(L->Act != NULL){
    tDLElemPtr name = malloc(sizeof(struct tDLElem));
    name->data=val;
    if (name == NULL){
      DLError();
    }
    else{
      if (L->Act == L->Last){
        name->lptr = L->Last;
        name->rptr = NULL;
        L->Act->rptr=name;
        L->Last=name;
      }
      else{
        name->lptr=L->Act;
        name->rptr=L->Act->rptr;
        L->Act->rptr->lptr=name;
        L->Act->rptr=name;
      }
    }
  }
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vloží prvek před aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/
  if(L->Act != NULL){
    tDLElemPtr name = malloc(sizeof(struct tDLElem));
    name->data=val;
    if (name == NULL){
      DLError();
    }
    else{
      if (L->Act == L->First){
        name->rptr = L->First;
        name->lptr = NULL;
        L->Act->lptr=name;
        L->First=name;
      }
      else{
        name->rptr=L->Act;
        name->lptr=L->Act->lptr;
        L->Act->lptr->rptr=name;
        L->Act->lptr=name;
      }
    }
  }
}

void DLCopy (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/
  if(L->Act != NULL){
    *val = L->Act->data;
  }else{
    DLError();
  }
}

void DLActualize (tDLList *L, int val) {
/*
** Přepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedělá nic.
**/
  if(L->Act != NULL){
      L->Act->data = val;
  }
}

void DLSucc (tDLList *L) { //zkusit fix
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
**/
  if(L->Act != NULL){
    if(L->Act != L->Last){
      L->Act = L->Act->rptr;
    }
    else{
      L->Act = NULL;
    }
  }
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na předchozí prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
**/
  if(L->Act != NULL){
    L->Act = L->Act->lptr;
  }
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním příkazem return.
**/

	if(L->Act == NULL){
		return FALSE;
	}
	else{
		return TRUE;
	}
}

/* Konec c206.c*/
